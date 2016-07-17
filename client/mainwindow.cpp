#include <iostream>

#include "mainwindow.h"


void MessageInput::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        m_shiftPressed = true;
        event->accept();
    }
    if (event->key() == Qt::Key_Return && !m_shiftPressed)
    {
        event->accept();
        emit sendMessage(text());
        clear();
    }
    else
    {
        QLineEdit::keyPressEvent(event);
    }
}


void MessageInput::keyReleaseEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Shift)
    {
        m_shiftPressed = false;
        event->accept();
    }
    else
    {
        QLineEdit::keyReleaseEvent(event);
    }
}


void MessageHistory::updateMessages()
{
    QString html = "<html><head><style>p.sent-message { width: 100%; text-align: right; } p.recv-message { width: 100%; text-align: left; }</style></head><body>";
    for (std::vector<QString>::iterator it = m_messageBuffer.begin(); it != m_messageBuffer.end(); ++it)
        html += *it;
    html += "</body>";
    setHtml(html);
}


void MessageHistory::sendMessage(QString message)
{
    m_messageBuffer.push_back("<p class='sent-message'>" + message + "</p>");
    updateMessages();
}


void MessageHistory::recvMessage(QString message)
{
    m_messageBuffer.push_back("<p class='recv-message'>" + message + "</p>");
    updateMessages();
}


ChannelWidget::ChannelWidget(QWidget *parent): QTreeWidget(parent)
{
    m_friends = new QTreeWidgetItem();
    m_friends->setText(0, "Friends");

    m_channels = new QTreeWidgetItem();
    m_channels->setText(0, "Channels");

    addTopLevelItem(m_friends);
    addTopLevelItem(m_channels);
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
        QTreeWidgetItem *new_friend = new QTreeWidgetItem();
        new_friend->setText(1, friends[i]);
        m_friends->addChild(new_friend);
    }
}


void ChannelWidget::updateChannels(QStringList channels)
{

}


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
    delete m_chatList;
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

    m_chatList = new ChannelWidget(m_chatSplit);

    m_chatSplit->addWidget(m_chatList);

    m_messageSplit = new QSplitter(m_chatSplit);
    m_messageSplit->setOrientation(Qt::Vertical);
    m_messageHistory = new MessageHistory(m_messageSplit);
    m_messageSplit->addWidget(m_messageHistory);
    m_messageInput = new MessageInput(m_messageSplit);
    m_messageSplit->addWidget(m_messageInput);
    m_chatSplit->addWidget(m_messageSplit);

    QObject::connect(m_messageInput, SIGNAL(sendMessage(QString)),
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
            m_network,     SLOT(login(QString, QString)));
    connect(m_network,        SIGNAL(recvMessage(QString)),
            m_messageHistory, SLOT(recvMessage(QString)));
    connect(m_network,     SIGNAL(updateFriends(QStringList)),
            m_chatList,    SLOT(updateFriends(QStringList)));

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
