#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QKeyEvent>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QTreeWidgetItem>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

#include <vector>
#include <map>

#include "messagelist.h"
#include "messageinput.h"
#include "messagehistory.h"
#include "logindialog.h"
#include "network.h"


class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QAction *addFriendAction;
    QAction *createChatAction;
    QWidget *m_chatWidget;
    QGridLayout *m_gridLayout;
    QSplitter *m_chatSplit;
    MessageList *m_messageList;
    QSplitter *m_messageSplit;
    MessageHistory *m_messageHistory;
    MessageInput *m_messageInput;
    QMenuBar *menubar;
    QMenu *friendsMenu;
    QMenu *chatsMenu;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    LoginDialog *m_loginDialog;
    Network *m_network;

public:
    MainWindow();
    ~MainWindow();

    void setupUI();
    void retranslateUI();

};


#endif // MAINWINDOW_H
