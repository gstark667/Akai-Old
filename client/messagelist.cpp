#include "messagelist.h"

#include <iostream>


FriendMenu::FriendMenu(QString friendName, QWidget *parent): QMenu(parent)
{
    m_friendName = friendName;
    addAction("Call", this, &FriendMenu::callSelected);
    addAction("Unfriend", this, &FriendMenu::unfriendSelected);
}


void FriendMenu::callSelected()
{
    emit call(m_friendName);
}


void FriendMenu::unfriendSelected()
{
    emit unfriend(m_friendName);
}


GroupOwnerMenu::GroupOwnerMenu(QString group, bool isOwner, QWidget *parent): QMenu(parent)
{
    m_group = group;
    addAction("Call", this, &GroupOwnerMenu::callSelected);
    if (isOwner)
    {
        addAction("Edit", this, &GroupOwnerMenu::editSelected);
        addAction("Disband", this, &GroupOwnerMenu::disbandSelected);
    }
}


void GroupOwnerMenu::callSelected()
{
    emit call(m_group);
}


void GroupOwnerMenu::editSelected()
{
    emit edit(m_group);
}


void GroupOwnerMenu::disbandSelected()
{
    emit disband(m_group);
}


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
    m_friendsList->setContextMenuPolicy(Qt::CustomContextMenu);
    m_groupsList = new QListWidget(this);
    m_groupsList->setContextMenuPolicy(Qt::CustomContextMenu);

    addTab(m_friendsList, "Friends");
    addTab(m_groupsList, "Groups");

    connect(m_friendsList, &QListWidget::customContextMenuRequested, this, &MessageList::showFriendMenu);
    connect(m_groupsList, &QListWidget::customContextMenuRequested, this, &MessageList::showGroupMenu);
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
    emit listOwnedGroups();
}


void MessageList::ownGroups(QStringList groups)
{
    std::cout << "Owning groups" << std::endl;
    for (int i = 0; i < groups.size(); ++i)
    {
        ownGroup(groups[i]);
    }
}


void MessageList::nameGroup(QString group, QString name)
{
    for (int i = 0; i < m_groupsList->count(); ++i)
    {
        if (m_groupsList->item(i)->data(Qt::UserRole) == group)
            m_groupsList->item(i)->setText(name);
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
        if (m_groupsList->item(i)->data(Qt::UserRole) == group)
            return;
    }
    QListWidgetItem *new_group = new QListWidgetItem(m_groupsList);
    new_group->setText(group);
    new_group->setData(Qt::UserRole, group);
    new_group->setData(Qt::UserRole+1, "member");
    m_groupsList->addItem(new_group);
    emit getGroupName(group);
    emit getGroupHistory(group);
}


void MessageList::removeGroup(QString group)
{
    for (int i = 0; i < m_groupsList->count(); ++i)
    {
        if (m_groupsList->item(i)->data(Qt::UserRole) == group)
        {
            m_groupsList->takeItem(i);
            break;
        }
    }
}


void MessageList::ownGroup(QString group)
{
    for (int i = 0; i < m_groupsList->count(); ++i)
    {
        std::cout << m_groupsList->item(i)->text().toStdString() << std::endl;
        if (m_groupsList->item(i)->data(Qt::UserRole) == group)
        {
            m_groupsList->item(i)->setData(Qt::UserRole+1, "owner");
        }
    }
}


void MessageList::showFriendMenu(const QPoint &pos)
{
    QPoint globalPos = m_friendsList->mapToGlobal(pos);

    QListWidgetItem *pointedFriend = m_friendsList->itemAt(pos);
    if (!pointedFriend)
        return;

    FriendMenu friendMenu(pointedFriend->text(), this);
    connect(&friendMenu, &FriendMenu::call, this, &MessageList::callFriend);
    connect(&friendMenu, &FriendMenu::unfriend, this, &MessageList::removeFriend);

    friendMenu.exec(globalPos);

    friendMenu.disconnect();
}


void MessageList::showGroupMenu(const QPoint &pos)
{
    QPoint globalPos = m_groupsList->mapToGlobal(pos);

    QListWidgetItem *pointedGroup = m_groupsList->itemAt(pos);
    if (!pointedGroup)
        return;

    std::cout << pointedGroup->data(Qt::UserRole+1).toString().toStdString() << std::endl;
    if (pointedGroup->data(Qt::UserRole+1) == "owner")
    {
        GroupOwnerMenu groupMenu(pointedGroup->data(Qt::UserRole).toString(), true, this);
        connect(&groupMenu, &GroupOwnerMenu::call, this, &MessageList::callGroup);
        connect(&groupMenu, &GroupOwnerMenu::edit, this, &MessageList::editGroup);
        connect(&groupMenu, &GroupOwnerMenu::disband, this, &MessageList::disbandGroup);
        groupMenu.exec(globalPos);
        groupMenu.disconnect();
    }
    else if (pointedGroup->data(Qt::UserRole+1) == "member")
    {
        GroupOwnerMenu groupMenu(pointedGroup->data(Qt::UserRole).toString(), false, this);
        connect(&groupMenu, &GroupOwnerMenu::call, this, &MessageList::callGroup);
        groupMenu.exec(globalPos);
        groupMenu.disconnect();
    }
}
