#include <iostream>

#include <strings.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>

#include <sstream>

#include "server.h"


using namespace std;


Server::Server(int port)
{
    m_port = port;
    start();
}


vector<string> Server::splitMessage(string message)
{
    vector<string> argv;
    stringstream ss(message);
    string cur = "";
    while (ss >> cur)
    {
        if (cur[0] == ':')
        {
            string trailer = cur.substr(1);
            cur = ss.get();
            trailer += cur + "\n";
            argv.push_back(trailer);
            break;
        }

        argv.push_back(cur);
    }
    return argv;
}


void Server::handleMessage(string message, User *user)
{
    vector<string> argv = splitMessage(message);
    size_t argc = argv.size();

    string error = "";

    if (argv[0] == "USER" && argc == 3)
        error = user->setName(argv[1]);
    else if (argv[0] == "USERLIST" && argc == 1)
        error = user->list();
    else if (argv[0] == "FRIEND" && argc == 2)
        error = user->addFriend(argv[1]);
    else if (argv[0] == "USERMSG" && argc == 3)
        error = user->sendMessage(argv[1], argv[2]);
    else if (argv[0] == "CREATE" && argc == 2)
        error = user->createChannel(argv[1]);
    else if (argv[0] == "JOIN" && argc == 2)
        error = user->joinChannel(argv[1]);
    else if (argv[0] == "INVITE" && argc == 3)
        error = user->inviteChannel(argv[1], argv[2]);
    else if (argv[0] == "CHANMSG" && argc == 3)
        error = user->sendChannelMessage(argv[1], argv[2]);
    else if (argv[0] == "PART" && argc == 2)
        error = user->partChannel(argv[1]);
    else if (argv[0] == "KICK" && argc == 3)
        error = user->kickChannel(argv[1], argv[2]);
    else if (argv[0] == "BAN" && argc == 3)
        error = user->banChannel(argv[1], argv[2]);
    else if (argv[0] == "DISBAND" && argc == 2)
        error = user->disbandChannel(argv[1]);
    else if (argv[0] == "QUIT")
        user->quit();

    if (error != "")
        user->sendRaw(error);
}


void Server::handleUser(int sockfd)
{
    User *user = new User(sockfd);
    cout << "handling client" << endl;
    while (true)
    {
        char buffer[256] = "";
        int n = recv(sockfd, buffer, 256, 0);
        if (n <= 0)
            break;
        
        string message(buffer);
        stringstream ss(message);
        for (string line; getline(ss, line); )
        {
            cout << "MESSAGE:" << line << endl;
            handleMessage(line, user);
        }
    }
    user->quit();
    delete user;
}


void Server::listenForUsers()
{
    int newsockfd, clilen;
    struct sockaddr cliaddr;
    clilen = sizeof(cliaddr);

    while (true)
    {
        newsockfd = accept(m_sockfd, &cliaddr, (socklen_t*)&clilen);
        m_clientHandlers.push_back(new std::thread(&Server::handleUser, this, newsockfd));
    }
}


int Server::start()
{
    int newsockfd;
    struct sockaddr_in serv_addr;

    m_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (m_sockfd < 0)
    {
        fprintf(stderr, "Unable to create socket\n");
        return -1;
    }

    int reuse = 1;
    if (setsockopt(m_sockfd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) < 0)
    {
        std::cerr << "Unable to set socket option" << std::endl;
        return -1;
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(m_port);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(m_sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    {
        std::cerr << "Unable to bind socket" << std::endl;
        return -1;
    }

    listen(m_sockfd, 5);

    listenForUsers();

    return 0;
}


void Server::stop()
{
    close(m_sockfd);
}
