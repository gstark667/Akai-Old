from threading import Thread
from select import select
from socket import *

from user import User, users, message_queue


if __name__ == '__main__':
    server = socket(AF_INET, SOCK_STREAM)
    server.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    server.bind(('0.0.0.0', 6667))
    server.listen(5)

    while True:
        read, write, error = select(users + [server], [], users)
        for item in read:
            if item == server:
                newsock, addr = item.accept()
                users.append(User(newsock))
                print('User connected')
            else:
                if not item.recv():
                    users.remove(item)
                item.process_messages()
        #TODO make this multithreaded
        for message in message_queue:
            message[0].send(message[1])
        del message_queue[:]

    u.close()
    server.close()
