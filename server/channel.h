#ifndef H_CHANNEL
#define H_CHANNEL

#include "client.h"

struct channel
{
    char *name;
    struct client *owner;
    struct client **clients;
    int client_cnt;
    struct client **invited;
    int invited_cnt;
} **channels;
int channel_cnt;

struct channel *get_channel(char *name);

void channel_create(char *name, struct client *client);

void channel_join(char *name, struct client *client);

void channel_part(char *name, struct client *client);

void channel_invite(char *name, struct client *client);

void channel_list(char *name, struct client *client);

void channel_message(char *name, char *message);


#endif
