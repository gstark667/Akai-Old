#include "mainwindow.h"

MainWindow::MainWindow()
{
    setupUI();
}

MainWindow::~MainWindow()
{
    delete addFriendAction;
    delete createChatAction;
    delete ChatWidget;
    delete gridLayout;
    delete ChatSplit;
    delete ChatList;
    delete MessageSplit;
    delete MessageHistory;
    delete MessageInput;
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
    addFriendAction->setObjectName(QStringLiteral("addFriendAction"));
    createChatAction = new QAction(this);
    createChatAction->setObjectName(QStringLiteral("createChatAction"));
    ChatWidget = new QWidget(this);
    ChatWidget->setObjectName(QStringLiteral("ChatWidget"));
    gridLayout = new QGridLayout(ChatWidget);
    gridLayout->setObjectName(QStringLiteral("gridLayout"));
    ChatSplit = new QSplitter(ChatWidget);
    ChatSplit->setObjectName(QStringLiteral("ChatSplit"));
    ChatSplit->setOrientation(Qt::Horizontal);
    ChatList = new QListWidget(ChatSplit);
    ChatList->setObjectName(QStringLiteral("ChatList"));
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(ChatList->sizePolicy().hasHeightForWidth());
    ChatList->setSizePolicy(sizePolicy);
    ChatSplit->addWidget(ChatList);
    MessageSplit = new QSplitter(ChatSplit);
    MessageSplit->setObjectName(QStringLiteral("MessageSplit"));
    MessageSplit->setOrientation(Qt::Vertical);
    MessageHistory = new QTextBrowser(MessageSplit);
    MessageHistory->setObjectName(QStringLiteral("MessageHistory"));
    QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Maximum);
    sizePolicy1.setHorizontalStretch(0);
    sizePolicy1.setVerticalStretch(0);
    sizePolicy1.setHeightForWidth(MessageHistory->sizePolicy().hasHeightForWidth());
    MessageHistory->setSizePolicy(sizePolicy1);
    MessageSplit->addWidget(MessageHistory);
    MessageInput = new QTextEdit(MessageSplit);
    MessageInput->setObjectName(QStringLiteral("MessageInput"));
    MessageInput->setEnabled(true);
    QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Minimum);
    sizePolicy2.setHorizontalStretch(0);
    sizePolicy2.setVerticalStretch(0);
    sizePolicy2.setHeightForWidth(MessageInput->sizePolicy().hasHeightForWidth());
    MessageInput->setSizePolicy(sizePolicy2);
    MessageSplit->addWidget(MessageInput);
    ChatSplit->addWidget(MessageSplit);

    gridLayout->addWidget(ChatSplit, 0, 0, 1, 1);

    setCentralWidget(ChatWidget);
    menubar = new QMenuBar(this);
    menubar->setObjectName(QStringLiteral("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 30));
    friendsMenu = new QMenu(menubar);
    friendsMenu->setObjectName(QStringLiteral("friendsMenu"));
    chatsMenu = new QMenu(menubar);
    chatsMenu->setObjectName(QStringLiteral("chatsMenu"));
    menuOptions = new QMenu(menubar);
    menuOptions->setObjectName(QStringLiteral("menuOptions"));
    setMenuBar(menubar);
    statusbar = new QStatusBar(this);
    statusbar->setObjectName(QStringLiteral("statusbar"));
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
