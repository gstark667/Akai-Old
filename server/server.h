#include <semaphore.h>

typedef enum
{
    NICK,
    USER,
    QUIT,
    SHUTDOWN,
    NONE
} CommandType;

sem_t shutdown_sem;


int create_server(int port);
void close_server(int sockfd);
