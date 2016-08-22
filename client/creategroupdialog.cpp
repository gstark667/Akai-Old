#include "creategroupdialog.h"


CreateGroupDialog::CreateGroupDialog(QWidget *parent): QDialog(parent)
{
    setupUI();
}


void CreateGroupDialog::setupUI()
{
    if (this->objectName().isEmpty())
	this->setObjectName(QStringLiteral("this"));
    this->resize(614, 267);
    gridLayout = new QGridLayout(this);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_nameLabel = new QLabel(this);
    m_nameLabel->setObjectName(QStringLiteral("m_nameLabel"));

    gridLayout->addWidget(m_nameLabel, 0, 0, 1, 1);

    m_nameField = new QLineEdit(this);
    m_nameField->setObjectName(QStringLiteral("m_nameField"));

    gridLayout->addWidget(m_nameField, 0, 1, 1, 3);

    m_userList = new QListWidget(this);
    m_userList->setObjectName(QStringLiteral("m_userList"));

    gridLayout->addWidget(m_userList, 1, 0, 2, 2);

    m_addButton = new QPushButton(this);
    m_addButton->setObjectName(QStringLiteral("m_addButton"));

    gridLayout->addWidget(m_addButton, 1, 2, 1, 1);

    m_memberList = new QListWidget(this);
    m_memberList->setObjectName(QStringLiteral("m_memberList"));

    gridLayout->addWidget(m_memberList, 1, 3, 2, 1);

    m_removeButton = new QPushButton(this);
    m_removeButton->setObjectName(QStringLiteral("m_removeButton"));

    gridLayout->addWidget(m_removeButton, 2, 2, 1, 1);

    m_createButton = new QPushButton(this);
    m_createButton->setObjectName(QStringLiteral("m_createButton"));

    gridLayout->addWidget(m_createButton, 3, 0, 1, 4);

    m_cancelButton = new QPushButton(this);
    m_cancelButton->setObjectName(QStringLiteral("m_cancelButton"));

    gridLayout->addWidget(m_cancelButton, 4, 0, 1, 4);


    retranslateUI();
}


void CreateGroupDialog::retranslateUI()
{
    setWindowTitle(QApplication::translate("CreateGroupDialog", "this", 0));
    m_nameLabel->setText(QApplication::translate("CreateGroupDialog", "Group Name:", 0));
    m_addButton->setText(QApplication::translate("CreateGroupDialog", ">>", 0));
    m_removeButton->setText(QApplication::translate("CreateGroupDialog", "<<", 0));
    m_createButton->setText(QApplication::translate("CreateGroupDialog", "Create", 0));
    m_cancelButton->setText(QApplication::translate("CreateGroupDialog", "Cancel", 0));
}


void CreateGroupDialog::show()
{
    m_members.clear();
    emit listUsers();
    QDialog::show();
}


void CreateGroupDialog::addMembers()
{
    
    updateLists();
}


void CreateGroupDialog::removeMembers()
{
    updateLists();
}


void CreateGroupDialog::updateLists()
{
    m_userList->clear();
    for (int i = 0; i < m_users.size(); ++i)
        m_userList->addItem(m_users[i]);

    m_memberList->clear();
    for (int i = 0; i < m_members.size(); ++i)
        m_memberList->addItem(m_members[i]);
}


void CreateGroupDialog::updateUsers(QStringList users)
{
    m_users = users;
    updateLists();
}

