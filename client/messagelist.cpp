#include "messagelist.h"

#include <iostream>


MessageList::MessageList(QWidget *parent): QTabWidget(parent)
{
    setupUI();
}


MessageList::~MessageList()
{
    delete m_friendsList;
    delete m_groupsList;
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
        if (m_friendsList->findItems(friends[i], Qt::MatchExactly).size() == 0)
        {
            std::cout << friends[i].toStdString() << std::endl;
            m_friendsList->addItem(friends[i]);
        }
    }
}


void MessageList::updateGroups(QStringList groups)
{
    std::cout << "Updating groups" << std::endl;
    for (int i = 0; i < groups.size(); ++i)
    {
        std::cout << groups[i].toStdString() << std::endl;
        m_groupsList->addItem(groups[i]);
    }
}


void MessageList::addFriend(QString user)
{
    m_friendsList->addItem(user);
}


void MessageList::addGroup(QString user)
{
    m_groupsList->addItem(user);
}
