#include "channellist.h"

#include <iostream>


ChannelList::ChannelList(QWidget *parent): QListWidget(parent)
{
}


ChannelList::~ChannelList()
{
    delete m_friends;
    delete m_channels;
}


void ChannelList::updateFriends(QStringList friends)
{
    std::cout << "Updating friends" << std::endl;
    for (int i = 0; i < friends.size(); ++i)
    {
        std::cout << friends[i].toStdString() << std::endl;
        addItem(friends[i]);
    }
}


void ChannelList::updateChannels(QStringList channels)
{

}


void ChannelList::addUser(QString user)
{
    addItem(user);
}
