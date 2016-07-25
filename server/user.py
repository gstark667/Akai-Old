import database


users = []
message_queue = []


class UserException(Exception):
    pass


def get_user(name):
    for user in users:
        if user.name == name:
            return user
    raise UserException('User "%s" is not online' % (name))


def split_message(message):
    trailer = None
    if ':' in message:
        message, trailer = message.split(':')
    args = message.split()
    if trailer:
        args.append(trailer)
    return args


class User:
    def __init__(self, sock):
        self.sock = sock
        self.sock.setblocking(False)
        self.name = None
        self.buff = ''

    def fileno(self):
        return self.sock.fileno()

    def send(self, *args, **kwargs): 
        return self.sock.send(*args, **kwargs)
    
    #TODO make the socket non-blocking and recv the entire buffer
    def recv(self):
        recvd = self.sock.recv(256).decode('utf-8')
        if len(recvd) == 0:
            return False
        self.buff += recvd
        return True
    
    def close(self):
        return self.sock.close()
    
    def register(self, name, password):
        database.create_user(name, password)
        self.name = name

    def authenticate(self, name, password):
        database.authenticate(name, password)
        self.name = name
        for message in database.get_messages(self.name):
            sender = database.get_user_by_id(message['sender'])
            self.send_message('USERMSG %s :%s' % (sender['name'], message['message']))

    def friend(self, friend_name, message=None):
        database.add_friend(self.name, friend_name)
        try:
            user = get_user(friend_name)
            user.friend_req(self.name, message)
        except UserException:
            if message:
                database.leave_message(self.name, friend_name, 'FRIEND %s :%s' % (self.name, message))
            else:
                database.leave_message(self.name, friend_name, 'FRIEND %s' % (self.name))

    def friend_req(self, friend_name, message=None):
        if message:
            self.send_message('FRIEND %s :%s' % (friend_name, message))
        else:
            self.send_message('FRIEND %s' % (friend_name))

    def unfriend(self, friend_name):
        database.remove_friend(self.name, friend_name)

    def send_message(self, message):
        message += '\r\n'
        message_queue.append((self.sock, message.encode('utf-8')))

    def usermsg(self, name, message):
        if not database.is_friend(self.name, name):
            raise UserException('User "%s" is not your friend' % (self.name))
        self.send_message('USERMSG %s :%s' % (name, message))

    def send_usermsg(self, name, message):
        try:
            user = get_user(name)
            user.usermsg(self.name, message)
        except UserException:
            pass
        database.save_message(self.name, name, message)

    def friends(self):
        friends = database.list_friends(self.name)
        message = "FRIENDS :"
        for friend in friends:
            message += friend['name'] + ' '
        message = message.strip()
        self.send_message(message)

    def quit(self):
        self.close()
        users.remove(self)

    def process_message(self, message):
        args = split_message(message)
        argc = len(args)

        actions = {
            'REGISTER': self.register,
            'USER'    : self.authenticate,
            'USERMSG' : self.send_usermsg,
            'FRIEND'  : self.friend,
            'UNFRIEND': self.unfriend,
            'FRIENDS' : self.friends,
            'QUIT'    : self.quit
        }

        try:
            if args[0] in actions:
                actions[args[0]](*(args[1:]))
            else:
                self.send_message('ERROR: Invalid command')
        except TypeError as e:
            self.send_message('ERROR: Wrong number of arguments')
        except Exception as e:
            self.send_message('ERROR: ' + str(e))

    def process_messages(self):
        while '\r\n' in self.buff:
            message, self.buff = self.buff.split('\r\n', 1)
            self.process_message(message)

