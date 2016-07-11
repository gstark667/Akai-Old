#ifndef H_CLINET
#define H_CLINET

struct client
{
    char *nick;
    int sockfd;
    int is_authenticated;
} **clients;
int client_cnt;

void remove_client(int sockfd);

void add_client(struct client *client);

void close_clients();

struct client *get_client(char *name);


void client_ison(char *name);

void client_quit(struct client *client);

void client_user(char *name, char *pass, struct client *client);

void client_usermsg(char *name, char *message, struct client *client);

#endif
