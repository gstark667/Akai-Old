#include <iostream>

#include "mainwindow.h"


MainWindow::MainWindow(QHostAddress serverHost, quint16 serverPort, quint16 callPort)
{
    m_network = new Network(serverHost, serverPort, this);
    m_audio   = new Audio(serverHost, callPort, this);
    setupUI();
}


MainWindow::~MainWindow()
{
}


void MainWindow::setupUI()
{
    setObjectName(QStringLiteral("MainWindow"));
    resize(800, 600);

    addFriendAction = new QAction(this);
    createGroupAction = new QAction(this);
    stopCallAction = new QAction(this);

    m_messageWidget = new QWidget(this);
    m_gridLayout = new QGridLayout(m_messageWidget);

    m_mainSplit = new QSplitter(m_messageWidget);
    m_mainSplit->setOrientation(Qt::Horizontal);

    m_messageList = new MessageList(m_mainSplit);

    m_mainSplit->addWidget(m_messageList);

    m_messageSplit = new QSplitter(m_mainSplit);
    m_messageSplit->setOrientation(Qt::Vertical);
    m_messageHistory = new MessageHistory(m_messageSplit);
    m_messageSplit->addWidget(m_messageHistory);
    m_messageInput = new MessageInput(m_messageSplit);
    m_messageSplit->addWidget(m_messageInput);
    m_mainSplit->addWidget(m_messageSplit);

    m_gridLayout->addWidget(m_mainSplit, 0, 0, 1, 1);

    setCentralWidget(m_messageWidget);
    menubar = new QMenuBar(this);
    friendsMenu = new QMenu(menubar);
    groupsMenu = new QMenu(menubar);
    callMenu = new QMenu(menubar);
    menuOptions = new QMenu(menubar);
    setMenuBar(menubar);
    m_statusBar = new QStatusBar(this);
    setStatusBar(m_statusBar);

    menubar->addAction(friendsMenu->menuAction());
    menubar->addAction(groupsMenu->menuAction());
    menubar->addAction(callMenu->menuAction());
    menubar->addAction(menuOptions->menuAction());
    friendsMenu->addAction(addFriendAction);
    groupsMenu->addAction(createGroupAction);
    callMenu->addAction(stopCallAction);

    retranslateUI();

    m_loginDialog = new LoginDialog(this);
    m_addFriendDialog = new AddFriendDialog(this);
    m_acceptCallDialog = new AcceptCallDialog(this);
    m_createGroupDialog = new CreateGroupDialog(this);
    m_editGroupDialog = new EditGroupDialog(this);

    connect(m_loginDialog, &LoginDialog::login, m_network, &Network::login);
    connect(m_network, &Network::isAuth, m_loginDialog, &LoginDialog::close);

    connect(m_network, &Network::errorMessage, m_statusBar, &QStatusBar::showMessage);

    connect(m_messageInput, &MessageInput::sendMessage, m_messageHistory, &MessageHistory::sendMessage);
    connect(m_messageHistory, &MessageHistory::sendUserMessage, m_network, &Network::sendUserMessage);
    connect(m_network, &Network::recvUserMessage, m_messageHistory, &MessageHistory::recvUserMessage);
    connect(m_network, &Network::sentUserMessage, m_messageHistory, &MessageHistory::sentUserMessage);

    connect(m_messageList, &MessageList::friendSelected, m_messageHistory, &MessageHistory::friendSelected);
    connect(m_messageHistory, &MessageHistory::addUser, m_messageList, &MessageList::addFriend);
    connect(m_network, &Network::updateFriends, m_messageList, &MessageList::updateFriends);

    // Groups
    connect(m_network,     &Network::updateGroups,     m_messageList,       &MessageList::updateGroups);
    connect(m_messageList, &MessageList::getGroupName, m_network,           &Network::getGroupName);
    connect(m_messageList, &MessageList::listOwnedGroups,m_network,         &Network::listOwnedGroups);
    connect(m_messageList, &MessageList::getGroupHistory, m_network,        &Network::getGroupHistory);
    connect(m_network,     &Network::nameGroup,        m_messageList,       &MessageList::nameGroup);
    connect(m_network,     &Network::ownGroups,        m_messageList,       &MessageList::ownGroups);
    connect(m_network,     &Network::addGroup,         m_messageList,       &MessageList::addGroup);
    connect(m_network,     &Network::removeGroup,      m_messageList,       &MessageList::removeGroup);
    connect(m_messageList, &MessageList::groupSelected,m_messageHistory,    &MessageHistory::groupSelected);
    connect(m_messageList, &MessageList::disbandGroup, m_network,           &Network::disbandGroup);
    connect(m_messageList, &MessageList::editGroup,    m_editGroupDialog,   &EditGroupDialog::editGroup);
    connect(m_messageHistory, &MessageHistory::sendGroupMessage, m_network, &Network::sendGroupMessage);
    connect(m_network,     &Network::recvGroupMessage, m_messageHistory,    &MessageHistory::recvGroupMessage);
    connect(m_network,     &Network::sentGroupMessage, m_messageHistory,    &MessageHistory::sentGroupMessage);
    connect(m_network,     &Network::updateUsers,      m_createGroupDialog, &CreateGroupDialog::updateUsers);
    connect(m_network,     &Network::updateUsers,      m_editGroupDialog,   &EditGroupDialog::updateUsers);
    connect(m_network,   &Network::updateGroupMembers, m_editGroupDialog,   &EditGroupDialog::updateMembers);
    connect(m_createGroupDialog, &CreateGroupDialog::listUsers, m_network,  &Network::listUsers);
    connect(m_editGroupDialog,   &EditGroupDialog::listUsers, m_network,  &Network::listUsers);
    connect(m_editGroupDialog,   &EditGroupDialog::listGroupMembers, m_network, &Network::listGroupMembers);
    connect(m_editGroupDialog,   &EditGroupDialog::addMember, m_network,    &Network::addGroupMember);
    connect(m_editGroupDialog,   &EditGroupDialog::removeMember, m_network, &Network::removeGroupMember);
    connect(m_createGroupDialog, &CreateGroupDialog::createGroup, m_network,&Network::createGroup);

    connect(addFriendAction, &QAction::triggered, m_addFriendDialog, &AddFriendDialog::show);
    connect(createGroupAction, &QAction::triggered, m_createGroupDialog, &CreateGroupDialog::show);
    connect(m_network, &Network::updateUsers, m_addFriendDialog, &AddFriendDialog::updateUsers);
    connect(m_network, &Network::updateFriends, m_addFriendDialog, &AddFriendDialog::updateFriends);
    connect(m_addFriendDialog, &AddFriendDialog::listUsers, m_network, &Network::listUsers);
    connect(m_addFriendDialog, &AddFriendDialog::listFriends, m_network, &Network::listFriends);
    connect(m_addFriendDialog, &AddFriendDialog::addFriend, m_network, &Network::addFriend);

    connect(m_messageList, &MessageList::callFriend, m_audio, &Audio::startListen);
    connect(m_audio, &Audio::callFriend, m_network, &Network::callFriend);
    connect(m_messageList, &MessageList::removeFriend, m_network, &Network::removeFriend);
    // TODO there needs to be a middleman here where the user accepts or decline's the call
    connect(m_network, &Network::callRequested, m_acceptCallDialog, &AcceptCallDialog::callRequested);
    connect(m_acceptCallDialog, &AcceptCallDialog::startCall, m_audio, &Audio::startCall);
    connect(m_acceptCallDialog, &AcceptCallDialog::callFriend, m_audio, &Audio::startListen);
    connect(stopCallAction, &QAction::triggered, m_audio, &Audio::stopCall);

    m_loginDialog->show();
}


void MainWindow::retranslateUI()
{
    setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    addFriendAction->setText(QApplication::translate("MainWindow", "Add Friend", 0));
    createGroupAction->setText(QApplication::translate("MainWindow", "Create Group", 0));
    stopCallAction->setText(QApplication::translate("MainWindow", "Stop Call", 0));
    friendsMenu->setTitle(QApplication::translate("MainWindow", "&Friends", 0));
    groupsMenu->setTitle(QApplication::translate("MainWindow", "&Groups", 0));
    callMenu->setTitle(QApplication::translate("MainWindow", "&Call", 0));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
}
