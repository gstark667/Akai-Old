#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "server.h"


int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        return -1;
    }

    int portno = atoi(argv[1]);

    Server *server = new Server(portno);
    return server->start();
}
