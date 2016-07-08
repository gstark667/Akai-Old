#include "mainwindow.h"

#include <iostream>

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
        std::cout << toPlainText().toStdString() << std::endl;
        emit sendMessage(toPlainText());
    }
    else
    {
        QTextEdit::keyPressEvent(event);
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
        QTextEdit::keyPressEvent(event);
    }
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

    m_chatList = new QListWidget(m_chatSplit);

    m_chatSplit->addWidget(m_chatList);

    m_messageSplit = new QSplitter(m_chatSplit);
    m_messageSplit->setOrientation(Qt::Vertical);
    m_messageHistory = new QTextBrowser(m_messageSplit);
    m_messageSplit->addWidget(m_messageHistory);
    m_messageInput = new MessageInput(m_messageSplit);
    m_messageSplit->addWidget(m_messageInput);
    m_chatSplit->addWidget(m_messageSplit);

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
