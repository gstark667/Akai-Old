#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "server.h"


/*struct channel
{
    struct client **clients;
};*/


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        return -1;
    }

    int portno = atoi(argv[1]);
    return create_server(portno);
}
