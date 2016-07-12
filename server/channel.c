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


char *channel_chanmsg(char *name, char *message, struct client *client)
{
    struct channel *channel = get_channel(name);
    char request[256];
    int n = sprintf(request, "CHANMSG %s %s :%s\n", name, client->nick, message);
    if (!channel)
        return "ERROR: Invalid channel\n";
    for (int i = 0; i < channel->client_cnt; ++i)
    {
        if (channel->clients[i] == client)
        {
            for (int j = 0; j < channel->client_cnt; ++j)
            {
                if (i == j)
                    continue;
                send(channel->clients[j]->sockfd, request, n, 0);
            }
            return NULL;
        }
    }
    return "ERROR: Not in channel\n";
}


char *channel_invite(char *name, char *nick, struct client *client)
{
    struct channel *channel = get_channel(name);
    if (client != channel->owner)
        return "ERROR: You do not own this channel\n";
    if (!channel)
        return "ERROR: Invalid channel\n";
    ++channel->invited_cnt;
    channel->invited = realloc(channel->invited, sizeof(char *) * channel->invited_cnt);
    channel->invited[channel->invited_cnt - 1] = strdup(nick);
    return NULL;
}


char *channel_join(char *name, struct client *client)
{
    struct channel *channel = get_channel(name);
    if (!channel)
        return "ERROR: Invalid channel\n";
    for (int i = 0; i < channel->invited_cnt; ++i)
    {
        if (strcmp(client->nick, channel->invited[i]) == 0)
        {
            ++channel->client_cnt;
            channel->clients = realloc(channel->clients, sizeof(struct client *) * channel->client_cnt);
            channel->clients[client_cnt - 1] = client;
            return NULL;
        }
    }
    return "ERROR: Not invited to channel\n";
}


// utility for removing users from a channel (used in kick and pass)
void channel_remove_client(struct channel *channel, struct client *client)
{
    for (int i = 0; i < channel->client_cnt; ++i)
    {
        if (client == channel->clients[i])
        {
            for (int j = i + 1; j < channel->client_cnt; ++i)
            {
                channel->clients[j - 1] = channel->clients[j];
            }
            --channel->client_cnt;
            channel->clients = realloc(channel->clients, sizeof(struct client *) * channel->client_cnt);
            return;
        }
    }
}


char *channel_kick(char *name, char *nick, struct client *client)
{
    struct client *to_kick = get_client(nick);
    struct channel *channel = get_channel(name);
    if (client != channel->owner)
        return "ERROR: You do not own this channel\n";
    if (!client)
        return "ERROR: Invalid client\n";
    if (!channel)
        return "ERROR: Invalid channel\n";
    channel_remove_client(channel, to_kick);
    return NULL;
}


char *channel_part(char *name, struct client *client)
{
    struct channel *channel = get_channel(name);
    if (!channel)
        return "ERROR: Invalid channel\n";
    channel_remove_client(channel, client);
    return NULL;
}
