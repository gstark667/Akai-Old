#include "messagelist.h"

#include <iostream>


MessageList::MessageList(QWidget *parent): QTabWidget(parent)
{
    setupUI();
}


MessageList::~MessageList()
{
}


void MessageList::setupUI()
{
    m_friendsList = new QListWidget(this);
    m_groupsList = new QListWidget(this);

    addTab(m_friendsList, "Friends");
    addTab(m_groupsList, "Groups");

    connect(m_friendsList, &QListWidget::itemPressed, this, &MessageList::friendSelected);
    connect(m_groupsList, &QListWidget::itemPressed, this, &MessageList::groupSelected);
}


void MessageList::retranslateUI()
{
    setTabText(indexOf(m_friendsList), QApplication::translate("Form", "Friends", 0));
    setTabText(indexOf(m_groupsList), QApplication::translate("Form", "Groups", 0));
}


void MessageList::updateFriends(QStringList friends)
{
    std::cout << "Updating friends" << std::endl;
    for (int i = 0; i < friends.size(); ++i)
    {
        addFriend(friends[i]);
    }
}


void MessageList::updateGroups(QStringList groups)
{
    std::cout << "Updating groups" << std::endl;
    for (int i = 0; i < groups.size(); ++i)
    {
        addGroup(groups[i]);
    }
}


void MessageList::addFriend(QString user)
{
    if (user.size() == 0)
        return;
    for (int i = 0; i < m_friendsList->count(); ++i)
    {
        if (m_friendsList->item(i)->text() == user)
            return;
    }
    m_friendsList->addItem(user);
}


void MessageList::addGroup(QString group)
{
    if (group.size() == 0)
        return;
    for (int i = 0; i < m_groupsList->count(); ++i)
    {
        if (m_friendsList->item(i)->text() == group)
            return;
    }
    m_friendsList->addItem(group);
}
