struct client
{
    char *nick;
    int nick_len;
    int sockfd;
} *clients;
int client_cnt;

void remove_client(int sockfd);

struct client *add_client(int sockfd);

void close_clients();
