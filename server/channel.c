#include "channel.h"

#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct channel *get_channel(char *name)
{
    for (int i = 0; i < channel_cnt; ++i)
    {
        if (strcmp(channels[i]->name, name) == 0)
            return channels[i];
    }
    printf("Cant find channel\n");
    return NULL;
}


void channel_create(char *name, struct client *client)
{
    struct channel *channel = malloc(sizeof(struct channel));
    channel->name = strdup(name);
    channel->owner = client;
    channel->clients = malloc(sizeof(struct client *));
    channel->clients[0] = client;
    channel->client_cnt = 1;
    channel->invited = malloc(0);
    channel->invited_cnt = 0;

    ++channel_cnt;
    channels = realloc(channels, sizeof(struct channel*) * channel_cnt);
    channels[channel_cnt - 1] = channel;

    printf("Created channel: %s\n", channel->name);
}


void channel_list(char *name, struct client *client)
{
    char response[256] = "CHANLIST :";
    for (int i = 0; i < channel_cnt; ++i)
        strcat(response, channels[i]->name);
    strcat(response, "\n");

    send(client->sockfd, response, strlen(response), 0);
}


void channel_chanmsg(char *name, char *message, struct client *client)
{
    struct channel *channel = get_channel(name);
    char request[256];
    int n = sprintf(request, "CHANMSG %s %s :%s\n", name, client->nick, message);
    for (int i = 0; i < channel->client_cnt; ++i)
    {
        //if (channel->clients[i] == client)
        //    continue;
        send(channel->clients[i]->sockfd, request, n, 0);
    }
}
