#ifndef H_SERVER
#define H_SERVER

#include <semaphore.h>

typedef enum
{
    AWAY,
    DIE,
    HELP,
    INVITE,
    ISON,
    JOIN,
    KICK,
    KILL,
    LIST,
    MODE,
    NAMES,
    NICK,
    NOTICE,
    PART,
    PASS,
    PING,
    PRIVMSG,
    QUIT,
    SETNAME,
    USER,
    USERS,
    NONE
} CommandType;

sem_t shutdown_sem;


int create_server(int port);
void close_server(int sockfd);

#endif
