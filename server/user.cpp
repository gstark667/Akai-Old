#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>

#include <string.h>
#include <algorithm>

#include "user.h"


using namespace std;


vector<User *> User::s_users;
mutex User::s_usersMtx;


User *User::getUser(string name)
{
    lock_guard<mutex> guard(s_usersMtx);
    for (vector<User *>::iterator it = s_users.begin(); it != s_users.end(); ++it)
    {
        if ((*it)->m_name == name)
            return *it;
    }
    return NULL;
}


void User::addUser(User *user)
{
    lock_guard<mutex> guard(s_usersMtx);
    s_users.push_back(user);
}


User::User(int sockfd)
{
    m_sockfd = sockfd;
    addUser(this);
}


void User::sendRaw(string message)
{
    send(m_sockfd, message.c_str(), message.size(), 0);
}


string User::setName(string name)
{
    if (getUser(name))
        return "ERROR :user with name already exists\n";
    m_name = name;
    return "";
}


string User::addFriend(string name)
{
    if (name == m_name)
        return "ERROR :you cannot friend yourself\n";
    m_friends.push_back(name);
    return "";
}


string User::sendMessage(string name, string message)
{
    User *user = getUser(name);
    if (!user)
        return "ERROR :User does not exist\n";

    string request = "USERMSG " + m_name + " :" + message + "\n";
    user->sendRaw(request);
    return "";
}


string User::createChannel(string name)
{
    if (Channel::getChannel(name))
        return CHANNEL_EXISTS;
    Channel *channel = new Channel(this, name);
    return "";
}


string User::joinChannel(string name)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    return channel->join(this);
}


string User::inviteChannel(string name, string user)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    return channel->invite(this, user);
}


string User::sendChannelMessage(string name, string message)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    return channel->sendMessage(this, message);
}


string User::partChannel(string name)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    return channel->part(this);
}


string User::kickChannel(string name, string user)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    return channel->kick(this, user);
}


string User::banChannel(string name, string user)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    return channel->ban(this, user);
}


string User::disbandChannel(string name)
{
    Channel *channel = Channel::getChannel(name);
    if (!channel)
        return INVALID_CHANNEL;
    string error = channel->disband(this);
    if (error == "")
        delete channel;
    return error;
}


void User::quit()
{
    close(m_sockfd);
    remove();
}


void User::remove()
{
    lock_guard<mutex> guard(s_usersMtx);
    vector<User *>::iterator it = find(s_users.begin(), s_users.end(), this);
    if (it != s_users.end())
        s_users.erase(it);
}
