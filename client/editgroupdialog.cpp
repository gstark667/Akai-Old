#include "editgroupdialog.h"
#include <iostream>


EditGroupDialog::EditGroupDialog(QWidget *parent): QDialog(parent)
{
    setupUI();
}


void EditGroupDialog::setupUI()
{
    if (this->objectName().isEmpty())
	this->setObjectName(QStringLiteral("this"));
    this->resize(614, 267);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_userList = new QListWidget(this);
    m_userList->setObjectName(QStringLiteral("m_userList"));
    m_userList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    gridLayout->addWidget(m_userList, 1, 0, 2, 2);

    m_addButton = new QPushButton(this);
    m_addButton->setObjectName(QStringLiteral("m_addButton"));

    gridLayout->addWidget(m_addButton, 1, 2, 1, 1);

    m_memberList = new QListWidget(this);
    m_memberList->setObjectName(QStringLiteral("m_memberList"));
    m_memberList->setSelectionMode(QAbstractItemView::ExtendedSelection);

    gridLayout->addWidget(m_memberList, 1, 3, 2, 1);

    m_removeButton = new QPushButton(this);
    m_removeButton->setObjectName(QStringLiteral("m_removeButton"));

    gridLayout->addWidget(m_removeButton, 2, 2, 1, 1);

    m_closeButton = new QPushButton(this);
    m_closeButton->setObjectName(QStringLiteral("m_closeButton"));

    gridLayout->addWidget(m_closeButton, 3, 0, 1, 4);

    connect(m_addButton, &QPushButton::pressed, this, &EditGroupDialog::doAddMembers);
    connect(m_removeButton, &QPushButton::pressed, this, &EditGroupDialog::doRemoveMembers);
    connect(m_closeButton, &QPushButton::pressed, this, &QDialog::close);


    retranslateUI();
}


void EditGroupDialog::retranslateUI()
{
    setWindowTitle(QApplication::translate("EditGroupDialog", "Edit Group", 0));
    m_addButton->setText(QApplication::translate("EditGroupDialog", ">>", 0));
    m_removeButton->setText(QApplication::translate("EditGroupDialog", "<<", 0));
    m_closeButton->setText(QApplication::translate("EditGroupDialog", "Close", 0));
}


void EditGroupDialog::show()
{
    m_members.clear();
    emit listUsers();
    emit listGroupMembers(m_group);
    QDialog::show();
}


void EditGroupDialog::doAddMembers()
{
    std::cout << "add" << std::endl;
    auto addUsers = m_userList->selectedItems();
    for (auto it = addUsers.begin(); it != addUsers.end(); ++it)
    {
        m_members.append((*it)->text());
        emit addMember(m_group, (*it)->text());
    }
    updateLists();
}


void EditGroupDialog::doRemoveMembers()
{
    std::cout << "remove" << std::endl;
    auto removeUsers = m_memberList->selectedItems();
    for (auto it = removeUsers.begin(); it != removeUsers.end(); ++it)
    {
        m_members.removeAll((*it)->text());
        emit removeMember(m_group, (*it)->text());
    }
    updateLists();
}


void EditGroupDialog::updateLists()
{
    m_userList->clear();
    for (int i = 0; i < m_users.size(); ++i)
    {
        if (!m_members.contains(m_users[i]))
            m_userList->addItem(m_users[i]);
    }

    m_memberList->clear();
    for (int i = 0; i < m_members.size(); ++i)
        m_memberList->addItem(m_members[i]);
}


void EditGroupDialog::editGroup(QString group)
{
    m_group = group;
    show();
}


void EditGroupDialog::updateUsers(QStringList users)
{
    m_users = users;
    updateLists();
}


void EditGroupDialog::updateMembers(QString group, QStringList members)
{
    if (m_group == group)
        m_members = members;
    updateLists();
}

