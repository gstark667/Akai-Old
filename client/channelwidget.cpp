#include "channelwidget.h"

#include <iostream>


ChannelWidget::ChannelWidget(QWidget *parent): QListWidget(parent)
{
}


ChannelWidget::~ChannelWidget()
{
    delete m_friends;
    delete m_channels;
}


void ChannelWidget::updateFriends(QStringList friends)
{
    std::cout << "Updating friends" << std::endl;
    for (int i = 0; i < friends.size(); ++i)
    {
        std::cout << friends[i].toStdString() << std::endl;
        addItem(friends[i]);
    }
}


void ChannelWidget::updateChannels(QStringList channels)
{

}


void ChannelWidget::addUser(QString user)
{
    addItem(user);
}
