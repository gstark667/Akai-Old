#ifndef H_USER
#define H_USER

#include <vector>
#include <string>
#include <mutex>

class User;

#include "channel.h"

#define INVALID_CHANNEL "ERROR :invalid channel\n"
#define CHANNEL_EXISTS  "ERROR :channel already exists\n"

class User
{
private:
    static std::vector<User*> s_users;
    static std::mutex s_usersMtx;

    int m_sockfd;
    std::string m_name;
    std::vector<std::string> m_friends;

public:
    static void list();
    static User *getUser(std::string name);
    static void addUser(User *user);

    User(int sockfd);

    void sendRaw(std::string message);

    std::string setName(std::string name);
    std::string addFriend(std::string name);
    std::string sendMessage(std::string name, std::string message);

    std::string createChannel(std::string name);
    std::string joinChannel(std::string name);
    std::string inviteChannel(std::string name, std::string user);
    std::string sendChannelMessage(std::string name, std::string message);
    std::string partChannel(std::string name);
    std::string kickChannel(std::string name, std::string user);
    std::string banChannel(std::string name, std::string user);
    std::string disbandChannel(std::string name);

    void quit();
    void remove();

    int getSock() { return m_sockfd; };
    std::string getName() { return m_name; }

    bool isFriend(std::string name);
};

#endif
