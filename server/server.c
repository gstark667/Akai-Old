#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#include <pthread.h>

#include "server.h"
#include "client.h"
#include "channel.h"


int split_args(char *buffer, char ***args);

int handle_message(char *message, int message_len, struct client *client);

void *handle_client(void *args);

void *listen_for_clients(void *args);

void close_server(int sockfd);


int split_args(char *buffer, char ***args)
{
    char **output = malloc(sizeof(char*));
    int cnt = 1;
    buffer = strsep(&buffer, "\n");
    buffer = strsep(&buffer, "\r");
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
            {
                ++output[cnt - 1];
                break;
            }
        }
    }

    *args = output;
    return cnt;
}


int handle_message(char *message, int message_len, struct client *client)
{
    char **argv = NULL;
    char *error = NULL;
    int argc = split_args(message, &argv);

    // kill the server
    if (strcmp(argv[0], "DIE") == 0)
    {
        sem_post(&shutdown_sem);
    }
    // invite a user to a channel
    else if (strcmp(argv[0], "INVITE") == 0 && argc == 3)
    {
        error = channel_invite(argv[1], argv[2], client);
    }
    // check if a user is on
    else if (strcmp(argv[0], "ISON") == 0)
    {
    }
    else if (strcmp(argv[0], "CREATE") == 0 && argc == 2)
    {
        channel_create(argv[1], client);
    }
    // join a channel
    else if (strcmp(argv[0], "JOIN") == 0 && argc == 2)
    {
        error = channel_join(argv[1], client);
    }
    // kick user from a channel
    else if (strcmp(argv[0], "KICK") == 0 && argc == 3)
    {
        error = channel_kick(argv[1], argv[2], client);
    }
    // list registered users
    else if (strcmp(argv[0], "USERLIST") == 0 && argc == 1)
    {
        client_list(client);
    }
    // list users in channel
    else if (strcmp(argv[0], "CHANLIST") == 0 && argc == 2)
    {
        channel_list(argv[1], client);
    }
    // leave a channel
    else if (strcmp(argv[0], "PART") == 0 && argc == 2)
    {
        error = channel_part(argv[1], client);
    }
    // ping the server
    else if (strcmp(argv[0], "PING") == 0 && argc == 1)
    {
        send(client->sockfd, "PONG\n", 5, 0);
    }
    // send a message to a user
    else if (strcmp(argv[0], "USERMSG") == 0 && argc == 3)
    {
        client_usermsg(argv[1], argv[2], client);
    }
    // send a message to a channel
    else if (strcmp(argv[0], "CHANMSG") == 0 && argc == 3)
    {
        error = channel_chanmsg(argv[1], argv[2], client);
    }
    // log off of the server
    else if (strcmp(argv[0], "QUIT") == 0 && argc == 1)
    {
        client_quit(client);
    }
    // authenticate to the server
    else if (strcmp(argv[0], "USER") == 0 && argc == 3)
    {
        client_user(argv[1], argv[2], client);
    }
    else
    {
        error = "ERROR: Invalid command\n";
    }

    if (error)
        send(client->sockfd, error, strlen(error), 0);

    if (argv)
    {
        free(argv);
    }
}


void *handle_client(void *args)
{
    int sockfd = *((int *)args);
    struct client client;
    client.sockfd = sockfd;
    ssize_t n = 0;

    while (1 == 1)
    {
        char buffer[256] = "";
        n = recv(client.sockfd, buffer, 256, 0);
        if (n <= 0)
            return NULL;
        if (handle_message(buffer, n, &client) == -1)
            break;
    }
    remove_client(client.sockfd);
}


void *listen_for_clients(void *args)
{
    int sockfd = *((int *)args);
    int newsockfd, clilen;
    struct sockaddr cli_addr;
    clilen = sizeof(cli_addr);

    clients = malloc(0);
    channels = malloc(0);

    while (1 == 1)
    {
        // TODO: use select and a semaphore
        newsockfd = accept(sockfd, &cli_addr, (socklen_t*)&clilen);
        if (newsockfd < 0)
        {
            fprintf(stderr, "Error while accepting client\n");
            sem_post(&shutdown_sem);
            return;
        }


        pthread_t thread;
        pthread_create(&thread, NULL, handle_client, &newsockfd);

    }
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

    pthread_t client_listener;
    pthread_create(&client_listener, NULL, listen_for_clients, &sockfd);

    sem_wait(&shutdown_sem);

    close_server(sockfd);
    return 0;
}


void close_server(int sockfd)
{
    printf("Shutting down server\n");
    close_clients();
    close(sockfd);
}
