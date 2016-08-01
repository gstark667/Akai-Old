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
    def __init__(self, sock, addr):
        self.sock = sock
        self.sock.setblocking(False)
        self.addr = addr
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

    def authenticated(self, name):
        self.name = name
        self.send_message('ISAUTH ' + name)
    
    def register(self, name, password):
        database.create_user(name, password)
        self.authenticated(name)

    def authenticate(self, name, password):
        user = None
        try:
            user = get_user(name)
        except UserException:
            pass
        if user:
            raise UserException('User "%s" is already logged in' % (name))
        database.authenticate(name, password)
        self.authenticated(name)

    def message_history(self):
        for message in database.get_messages(self.name):
            sender = database.get_user_by_id(message['sender'])
            receiver = database.get_user_by_id(message['receiver'])
            if sender['name'] == self.name:
                self.send_message('USERMSGSNT %s :%s' % (receiver['name'], message['message']))
            else:
                self.send_message('USERMSG %s :%s' % (sender['name'], message['message']))

    def friend(self, friend_name, message=None):
        database.add_friend(self.name, friend_name)
        try:
            user = get_user(friend_name)
            user.friend_req(self.name, message)
        except UserException:
            pass

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
        database.save_message(self.name, name, message)
        self.send_message('USERMSGSNT %s :%s' % (name, message))
        try:
            user = get_user(name)
            user.usermsg(self.name, message)
        except UserException:
            pass

    def friends(self):
        friends = database.list_friends(self.name)
        message = "FRIENDS :"
        for friend in friends:
            message += friend + ' '
        self.send_message(message.strip())

    def call(self, name, addr, port):
        if not database.is_friend(self.name, name):
            raise UserException('User "%s" is not your friend' % (self.name))
        self.send_message('CALL %s %s %s' % (name, addr, port))

    def send_call(self, name, port):
        user = get_user(name)
        user.call(self.name, self.addr[0], port)

    def users(self):
        users = database.list_users()
        message = 'USERS :'
        for user in users:
            if self.name != user:
                message += user + ' '
        self.send_message(message.strip())

    def quit(self):
        self.close()
        users.remove(self)

    def process_message(self, message):
        print('Processing: ' + message)
        args = split_message(message)
        argc = len(args)

        actions = {
            'REGISTER': self.register,
            'USER'    : self.authenticate,
            'USERS'   : self.users,
            'USERMSG' : self.send_usermsg,
            'MSGHIST' : self.message_history,
            'FRIEND'  : self.friend,
            'UNFRIEND': self.unfriend,
            'FRIENDS' : self.friends,
            'CALL'    : self.send_call,
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

