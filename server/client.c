#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#include "client.h"


client_cnt = 0;


void remove_client(int sockfd)
{
    int to_remove = -1;
    for (int i = 0; i < client_cnt; ++i)
    {
        if (clients[i].sockfd == sockfd)
        {
            to_remove = i;
        }
    }

    if (to_remove == -1)
        return;
    printf("Found client to remove\n");

    --client_cnt;
    struct client *new_clients = malloc(sizeof(struct client) * client_cnt);
    for (int i = 0; i < to_remove; ++i)
        new_clients[i] = clients[i];
    for (int i = to_remove; i < client_cnt; ++i)
        new_clients[i] = clients[i + 1];
    free(clients);
    clients = new_clients;
    close(sockfd);
}


// TODO: mutext for clients array
struct client *add_client(int sockfd)
{
    struct client new_client;
    new_client.sockfd = sockfd;

    ++client_cnt;
    clients = realloc(clients, sizeof(struct client) * client_cnt);
    clients[client_cnt - 1] = new_client;

    return &clients[client_cnt - 1];
}


void close_clients()
{
    for (int i = 0; i < client_cnt; ++i)
        close(clients[i].sockfd);
}
