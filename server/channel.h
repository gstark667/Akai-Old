#ifndef H_CHANNEL
#define H_CHANNEL

#include "client.h"

struct channel
{
    char *name;
    struct client *owner;
    struct client **clients;
    int client_cnt;
    char **invited;
    int invited_cnt;
} **channels;
int channel_cnt;

struct channel *get_channel(char *name);

void channel_create(char *name, struct client *client);

char *channel_invite(char *name, char *nick, struct client *client);

char *channel_join(char *name, struct client *client);

char *channel_kick(char *name, char *nick, struct client *client);

char *channel_part(char *name, struct client *client);

char *channel_ban(char *name, char *nick, struct client *client);

void channel_list(char *name, struct client *client);

char *channel_chanmsg(char *name, char *message, struct client *client);


#endif
