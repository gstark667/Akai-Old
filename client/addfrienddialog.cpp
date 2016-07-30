#include "addfrienddialog.h"

#include <iostream>


AddFriendDialog::AddFriendDialog(QWidget *parent): QDialog(parent)
{
   setupUI();
}


AddFriendDialog::~AddFriendDialog()
{
    delete m_gridLayout;
    delete m_userList;
    delete m_addFriendButton;
    delete m_closeButton;
}


void AddFriendDialog::setupUI()
{
    if (objectName().isEmpty())
	setObjectName(QStringLiteral("AddFriendDialog"));
    resize(330, 190);
    setWindowModality(Qt::ApplicationModal);
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));

    m_userList = new QListWidget(this);
    m_userList->setObjectName(QStringLiteral("m_userList"));

    m_gridLayout->addWidget(m_userList, 0, 1, 1, 1);

    m_addFriendButton = new QPushButton(this);
    m_addFriendButton->setObjectName(QStringLiteral("m_addFriendButton"));

    m_gridLayout->addWidget(m_addFriendButton, 2, 0, 1, 2);

    m_closeButton = new QPushButton(this);
    m_closeButton->setObjectName(QStringLiteral("m_closeButton"));

    m_gridLayout->addWidget(m_closeButton, 3, 0, 1, 2);


    retranslateUI();

    connect(m_addFriendButton, &QPushButton::pressed, this, &AddFriendDialog::getFriends);
    connect(m_closeButton, &QPushButton::pressed, this, &QDialog::close);
}


void AddFriendDialog::retranslateUI()
{
    setWindowTitle(QApplication::translate("AddFriendDialog", "Dialog", 0));
    m_addFriendButton->setText(QApplication::translate("AddFriendDialog", "Add Friend", 0));
    m_closeButton->setText(QApplication::translate("AddFriendDialog", "Close", 0));
}


void AddFriendDialog::show()
{
    emit listUsers();
    emit listFriends();
    QDialog::show();
}


void AddFriendDialog::updateUsers(QStringList users)
{
    m_users = users;
    updateNonFriends();
}


void AddFriendDialog::updateFriends(QStringList friends)
{
    m_friends = friends;
    updateNonFriends();
}


void AddFriendDialog::updateNonFriends()
{
    m_userList->clear();
    for (auto it = m_users.begin(); it != m_users.end(); ++it)
    {
        if (!m_friends.contains(*it))
            m_userList->addItem(*it);
    }
}


void AddFriendDialog::getFriends()
{
    auto selected = m_userList->selectedItems();
    for (auto it = selected.begin(); it != selected.end(); ++it)
    {
        emit addFriend((*it)->text());
    }
    emit listUsers();
    emit listFriends();
}
