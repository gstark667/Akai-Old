#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#include <pthread.h>
#include <semaphore.h>

#include "client.h"


typedef enum
{
    NICK,
    USER,
    QUIT,
    SHUTDOWN,
    NONE
} CommandType;


struct channel
{
    struct client **clients;
};


sem_t shutdown_sem;


int split_args(char *buffer, char ***args)
{
    char **output = malloc(sizeof(char*));
    int cnt = 1;
    buffer = strsep(&buffer, "\n");
    output[0] = buffer;

    size_t buffer_len = strlen(buffer);


    for (size_t i = 0; i < buffer_len; ++i)
    {
        if (buffer[i] == ' ')
        {
            ++cnt;
            output = realloc(output, sizeof(char*) * cnt);
            output[cnt - 1] = &buffer[i + 1];
            buffer[i] = '\0';
            if (buffer[i + 1] == ':')
                ++buffer[i];
                break;
        }
    }

    *args = output;
    return cnt;
}


int handle_message(char *message, int message_len, struct client *client)
{
    printf("MESSAGE: %s", message);
    char **argv = NULL;
    int argc = split_args(message, &argv);
    printf("CMD: %s\n", argv[0]);

    CommandType command = NONE;
    if (strcmp(argv[0], "NICK") == 0)
        command = NICK;
    else if (strcmp(argv[0], "USER") == 0)
        command = USER;
    else if (strcmp(argv[0], "QUIT") == 0)
        command = QUIT;
    else if (strcmp(argv[0], "SHUTDOWN") == 0)
        command = SHUTDOWN;

    switch (command)
    {
    case NICK:
        printf("NICK: %s\n", argv[1]);
        client->nick = strdup(argv[1]);
        break;
    case QUIT:
        printf("Client Quit\n");
        close(client->sockfd);
        break;
    case SHUTDOWN:
        sem_post(&shutdown_sem);
        break;
    }

    if (argv)
    {
	free(argv);
    }
}


void *handle_client(void *args)
{
    struct client *client = (struct client*)args;
    ssize_t n = 0;

    while (1 == 1)
    {
        char buffer[256] = "";
        n = recv(client->sockfd, buffer, 256, 0);
        if (n <= 0)
            return NULL;
        if (handle_message(buffer, n, client) == -1)
            break;
    }
    remove_client(client->sockfd);
}


int create_server(int port)
{
    int sockfd, newsockfd;
    struct sockaddr_in serv_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
    {
        fprintf(stderr, "Unable to create socket\n");
        return -1;
    }

    int reuse = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
    {
        fprintf(stderr, "Unable to set socket option\n");
        return -1;
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        fprintf(stderr, "Unable to bind socket\n");
        return -1;
    }

    listen(sockfd, 5);

    return sockfd;
}


void *listen_for_clients(void *args)
{
    int sockfd = *((int *)args);
    int newsockfd, clilen;
    struct sockaddr cli_addr;
    clilen = sizeof(cli_addr);

    clients = malloc(0);

    while (1 == 1)
    {
        newsockfd = accept(sockfd, &cli_addr, (socklen_t*)&clilen);
	if (newsockfd < 0)
	{
	    fprintf(stderr, "Error while accepting client\n");
            sem_post(&shutdown_sem);
	    return;
	}

        struct client *new_client = add_client(newsockfd);

        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, new_client);

    }
}


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        return -1;
    }

    int portno = atoi(argv[1]);
    int sockfd = create_server(portno);


    pthread_t client_listener;
    pthread_create(&client_listener, NULL, listen_for_clients, &sockfd);

    sem_wait(&shutdown_sem);

    for (int i = 0; i < client_cnt; ++i)
    {
        close(clients[i].sockfd);
        void *out;
    }

    printf("Shutting down server\n");

    close(sockfd);
}
