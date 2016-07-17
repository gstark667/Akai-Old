#include "channel.h"

#include <iostream>
#include <algorithm>


using namespace std;


vector<Channel *> Channel::s_channels;
mutex Channel::s_channelsMtx;


Channel::Channel(User *owner, string name)
{
    m_owner = owner;
    m_name = name;

    cout << "Creating channel " << name << endl;
    addChannel(this);


    string request = "CREATE " + name + "\n";
    owner->sendRaw(request);
}


void Channel::addChannel(Channel *channel)
{
    lock_guard<mutex> guard(s_channelsMtx);
    s_channels.push_back(channel);
}


Channel *Channel::getChannel(string name)
{
    lock_guard<mutex> guard(s_channelsMtx);
    for (vector<Channel *>::iterator it = s_channels.begin(); it != s_channels.end(); ++it)
    {
        if ((*it)->m_name == name)
            return *it;
    }
    return NULL;
}


void Channel::removeChannel(Channel *channel)
{
    vector<Channel *>::iterator it = find(s_channels.begin(), s_channels.end(), channel);
    if (it != s_channels.end()) 
        s_channels.erase(it);
}


bool Channel::canJoin(User *user)
{
    for (vector<string>::iterator it = m_invited.begin(); it != m_invited.end(); ++it)
    {
        if (*it == user->getName())
            return true;
    }
    return false;
}


bool Channel::canUse(User *user)
{
    lock_guard<mutex> guard(m_mtx);
    if (user == m_owner)
        return true;
    for (vector<User *>::iterator it = m_users.begin(); it != m_users.end(); ++it)
    {
        if ((*it) == user)
            return true;
    }
    return false;
}


bool Channel::canAdmin(User *user)
{
    return user == m_owner;
}


void Channel::addUser(User *user)
{
    lock_guard<mutex> guard(m_mtx);
    vector<User *>::iterator it = find(m_users.begin(), m_users.end(), user);
    if (it != m_users.end())
        return;
    m_users.push_back(user);
}


void Channel::removeUser(User *user)
{
    lock_guard<mutex> guard(m_mtx);
    vector<User *>::iterator it = find(m_users.begin(), m_users.end(), user);
    if (it != m_users.end())
        m_users.erase(it);
}


string Channel::join(User *user)
{
    if (!canJoin(user))
        return USE_ERROR;
    addUser(user);

    string request = "JOIN " + m_name + "\n";
    user->sendRaw(request);
    return "";
}


string Channel::invite(User *user, string name)
{
    if (!canAdmin(user))
        return ADMIN_ERROR;
    lock_guard<mutex> guard(m_mtx);
    m_invited.push_back(name);
    return "";
}


string Channel::sendMessage(User *user, string message)
{
    if (!canUse(user))
        return USE_ERROR;
    lock_guard<mutex> guard(m_mtx);
    string request = "CHANMSG " + user->getName() + " :" + message + "\n";
    for (vector<User *>::iterator it = m_users.begin(); it != m_users.end(); ++it)
    {
        (*it)->sendRaw(request);
    }
    return "";
}


string Channel::part(User *user)
{
    if (!canUse(user))
        return USE_ERROR;
    removeUser(user);
    string request = "PART " + m_name + "\n";
    user->sendRaw(request);
    return "";
}


string Channel::kick(User *user, string name)
{
    if (!canAdmin(user))
        return USE_ERROR;
    User *to_kick = User::getUser(name);
    if (!to_kick)
        return "ERROR :invalid user\n";
    removeUser(to_kick);
    string request = "KICK " + user->getName() + " " + m_name + "\n";
    to_kick->sendRaw(request);
    return "";
}


string Channel::ban(User *user, string name)
{
    if (!canAdmin(user))
        return ADMIN_ERROR;
    vector<string>::iterator it = find(m_invited.begin(), m_invited.end(), name);
    if (it != m_invited.end())
        m_invited.erase(it);
    kick(user, name);
    return "";
}


string Channel::disband(User *user)
{
    if (!canAdmin(user))
        return ADMIN_ERROR;
    string request = "DISBAND " + m_name + "\n";
    for (vector<User *>::iterator it = m_users.begin(); it != m_users.end(); ++it)
    {
        (*it)->sendRaw(request);
    }
    removeChannel(this);
    return "";
}
