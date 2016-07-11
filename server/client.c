#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

#include <string.h>

#include "client.h"


client_cnt = 0;


void remove_client(int sockfd)
{
    int to_remove = -1;
    for (int i = 0; i < client_cnt; ++i)
    {
        if (clients[i]->sockfd == sockfd)
        {
            free(clients[i]->nick);
            to_remove = i;
        }
    }

    if (to_remove == -1)
        return;
    printf("Found client to remove\n");

    --client_cnt;
    struct client **new_clients = malloc(sizeof(struct client) * client_cnt);
    for (int i = 0; i < to_remove; ++i)
        new_clients[i] = clients[i];
    for (int i = to_remove; i < client_cnt; ++i)
        new_clients[i] = clients[i + 1];
    free(clients);
    clients = new_clients;
    close(sockfd);
}


// TODO: mutext for clients array
void add_client(struct client *client)
{
    ++client_cnt;
    clients = realloc(clients, sizeof(struct client*) * client_cnt);
    clients[client_cnt - 1] = client;

    printf("Creating client: %s\n", client->nick);
}


void close_clients()
{
    for (int i = 0; i < client_cnt; ++i)
        close(clients[i]->sockfd);
}


struct client *get_client(char *name)
{
    for (int i = 0; i < client_cnt; ++i)
    {
        printf("Searching: %s == %s\n", name, clients[i]->nick);
        if (strcmp(clients[i]->nick, name) == 0)
        {
            printf("Found the user\n");
            return clients[i];
        }
    }
    printf("COuldn't find the user\n");
    return NULL;
}


void client_quit(struct client *client)
{
    close(client->sockfd);
}


void client_user(char *nick, char *pass, struct client *client)
{
    // TODO: check the password against a db
    client->nick = strdup(nick);
    client->is_authenticated = 1;
    add_client(client);
}


void client_usermsg(char *nick, char *message, struct client *client)
{
    struct client *user = get_client(nick);
    if (!user)
        return;
    printf("Sending message to %s\n", user->nick);
    char request[256];
    sprintf(request, "USERMSG %s :%s\n", client->nick, message);
    // TODO: check if the user is a friend
    send(user->sockfd, request, strlen(request), 0);
}

void client_list(struct client *client)
{

}
