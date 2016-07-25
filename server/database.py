from pymongo import MongoClient
import binascii, hashlib, os


client = MongoClient('localhost', 27017)
db = client.akai


class DBException(Exception):
    pass


def create_salt():
    return binascii.hexlify(os.urandom(64)).decode('utf-8')


def hash_password(password, salt, iterations=10000):
    password = password.encode('utf-8')
    salt = salt.encode('utf-8')
    for i in range(iterations):
        password = hashlib.sha512(password + salt).hexdigest().encode('utf-8')
    return password.decode('utf-8')


def get_user(name):
    for user in db.users.find({'name': name}):
        return user
    raise DBException('User "%s" not found' % (name))

def get_user_by_id(id):
    for user in db.users.find({'_id': id}):
        return user
    raise DBException('User "%s" not found' % (str(id)))


def create_user(name, password):
    user = None
    try:
        user = get_user(name)
    except DBException:
        salt = create_salt()
        hash = hash_password(password, salt)
        return db.users.insert({'name': name, 'hash': hash, 'salt': salt})
    raise DBException('User "%s" exists' % (name))


def authenticate(name, password):
    user = get_user(name)
    hash = hash_password(password, user['salt'])
    if hash != user['hash']:
        raise DBException('Credentials are incorrect for user "%s"' % (name))


def add_friend(name, friend_name):
    #TODO make sure we don't get dups
    user = get_user(name)
    friend = get_user(friend_name)
    db.users.update({'name': name}, {'$push': {'friends': friend['_id']}})


def remove_friend(name, friend_name):
    #TODO make sure they're actually a friend
    user = get_user(name)
    friend = get_user(friend_name)
    db.users.update({'name': name}, {'$pop': {'friends': friend['_id']}})


def is_friend(name, friend_name):
    user = get_user(name)
    friend = get_user(friend_name)
    if friend['_id'] in user['friends']:
        return True
    return False


def list_friends(name):
    user = get_user(name)
    if not 'friends' in user:
        return []
    #TODO handle users that leave
    return [get_user_by_id(friend) for friend in user['friends']]


def save_message(name, receiver_name, message):
    if not is_friend(receiver_name, name):
        raise DBException('User "%s" is not your friend' % (receiver_name))
    user = get_user(name)
    receiver = get_user(receiver_name)
    db.messages.insert({'sender': user['_id'], 'receiver': receiver['_id'], 'message': message})


def get_messages(name):
    user = get_user(name)
    return [message for message in db.messages.find({'receiver': user['_id']})]
