#ifndef H_CHANNEL
#define H_CHANNEL

#include <string>
#include <vector>
#include <mutex>

class Channel;

#include "user.h"

#define ADMIN_ERROR "ERROR :cannot admin this channel\n"
#define USE_ERROR   "ERROR :cannot use this channel\n"

class Channel
{
private:
    static std::vector<Channel *> s_channels;
    static std::mutex s_channelsMtx;

    std::string m_name;
    User *m_owner;
    std::vector<User *> m_users;
    std::vector<std::string> m_invited;
    std::mutex m_mtx;

public:
    static void addChannel(Channel *);
    static Channel *getChannel(std::string name);
    static void removeChannel(Channel *);
    static std::string disbandChannel(User *user, std::string name);

    Channel(User *owner, std::string name);

    bool canJoin(User *user);
    bool canUse(User *user);
    bool canAdmin(User *user);
    void addUser(User *user);
    void removeUser(User *user);
    std::string join(User *user);
    std::string invite(User *user, std::string name);
    std::string sendMessage(User *user, std::string message);
    std::string part(User *user);
    std::string kick(User *user, std::string name);
    std::string ban(User *user, std::string name);
    std::string disband(User *user);
    std::string remove(User *user);
};

#endif
