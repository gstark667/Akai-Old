#include <iostream>

#include "mainwindow.h"


MainWindow::MainWindow()
{
    setupUI();
}


MainWindow::~MainWindow()
{
    delete addFriendAction;
    delete createChatAction;
    delete m_chatWidget;
    delete m_gridLayout;
    delete m_chatSplit;
    delete m_messageList;
    delete m_messageSplit;
    delete m_messageHistory;
    delete m_messageInput;
    delete menubar;
    delete friendsMenu;
    delete chatsMenu;
    delete menuOptions;
    delete statusbar;
}


void MainWindow::setupUI()
{
    setObjectName(QStringLiteral("MainWindow"));
    resize(800, 600);

    addFriendAction = new QAction(this);
    createChatAction = new QAction(this);

    m_chatWidget = new QWidget(this);
    m_gridLayout = new QGridLayout(m_chatWidget);

    m_chatSplit = new QSplitter(m_chatWidget);
    m_chatSplit->setOrientation(Qt::Horizontal);

    m_messageList = new MessageList(m_chatSplit);

    m_chatSplit->addWidget(m_messageList);

    m_messageSplit = new QSplitter(m_chatSplit);
    m_messageSplit->setOrientation(Qt::Vertical);
    m_messageHistory = new MessageHistory(m_messageSplit);
    m_messageSplit->addWidget(m_messageHistory);
    m_messageInput = new MessageInput(m_messageSplit);
    m_messageSplit->addWidget(m_messageInput);
    m_chatSplit->addWidget(m_messageSplit);

    connect(m_messageInput, SIGNAL(sendMessage(QString)),
            m_messageHistory, SLOT(sendMessage(QString)));

    m_gridLayout->addWidget(m_chatSplit, 0, 0, 1, 1);

    setCentralWidget(m_chatWidget);
    menubar = new QMenuBar(this);
    friendsMenu = new QMenu(menubar);
    chatsMenu = new QMenu(menubar);
    menuOptions = new QMenu(menubar);
    setMenuBar(menubar);
    statusbar = new QStatusBar(this);
    setStatusBar(statusbar);

    menubar->addAction(friendsMenu->menuAction());
    menubar->addAction(chatsMenu->menuAction());
    menubar->addAction(menuOptions->menuAction());
    friendsMenu->addAction(addFriendAction);
    chatsMenu->addAction(createChatAction);

    retranslateUI();

    m_loginDialog = new LoginDialog(this);
    m_network     = new Network();
    connect(m_loginDialog, SIGNAL(login(QString, QString)),
            m_network,       SLOT(login(QString, QString)));
    connect(m_network,      SIGNAL(recvUserMessage(QString, QString)),
            m_messageHistory, SLOT(recvUserMessage(QString, QString)));
    connect(m_messageHistory, SIGNAL(sendUserMessage(QString, QString)),
            m_network,          SLOT(sendUserMessage(QString, QString)));
    connect(m_messageList,    SIGNAL(friendSelected(QListWidgetItem *)),
            m_messageHistory, SLOT(friendSelected(QListWidgetItem *)));
    connect(m_messageHistory, SIGNAL(addUser(QString)),
            m_messageList,      SLOT(addUser(QString)));
    connect(m_network,     SIGNAL(updateFriends(QStringList)),
            m_messageList,   SLOT(updateFriends(QStringList)));

    m_loginDialog->show();
}


void MainWindow::retranslateUI()
{
    setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
    addFriendAction->setText(QApplication::translate("MainWindow", "Add Friend", 0));
    createChatAction->setText(QApplication::translate("MainWindow", "Create Chat", 0));
    friendsMenu->setTitle(QApplication::translate("MainWindow", "&Friends", 0));
    chatsMenu->setTitle(QApplication::translate("MainWindow", "&Chats", 0));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0));
}
