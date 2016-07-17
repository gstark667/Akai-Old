#ifndef H_SERVER
#define H_SERVER

#include <vector>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

#include "user.h"


class Server
{
private:

    int m_sockfd, m_port;
    std::vector<std::thread*> m_clientHandlers;

    std::mutex m_shutdownMtx;
    std::condition_variable m_shutdownCondition;

    std::vector<std::string> splitArgs(std::string);

public:
    Server(int port);

    std::vector<std::string> splitMessage(std::string message);
    void handleMessage(std::string message, User *user);
    void handleUser(int sockfd);
    void listenForUsers();

    int start();
    void stop();
};

#endif
