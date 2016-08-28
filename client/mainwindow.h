#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QKeyEvent>
#include <QtNetwork/QHostAddress>
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
#include "creategroupdialog.h"
#include "editgroupdialog.h"
#include "addfrienddialog.h"
#include "acceptcalldialog.h"
#include "network.h"
#include "audio.h"


class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QAction *addFriendAction;
    QAction *createGroupAction;
    QAction *stopCallAction;
    QWidget *m_messageWidget;
    QGridLayout *m_gridLayout;
    QSplitter *m_mainSplit;
    MessageList *m_messageList;
    QSplitter *m_messageSplit;
    MessageHistory *m_messageHistory;
    MessageInput *m_messageInput;
    QMenuBar *menubar;
    QMenu *friendsMenu;
    QMenu *groupsMenu;
    QMenu *callMenu;
    QMenu *menuOptions;
    QStatusBar *m_statusBar;

    LoginDialog *m_loginDialog;
    AddFriendDialog *m_addFriendDialog;
    AcceptCallDialog *m_acceptCallDialog;
    CreateGroupDialog *m_createGroupDialog;
    EditGroupDialog *m_editGroupDialog;
    Network *m_network;
    Audio *m_audio;

public:
    MainWindow(QHostAddress serverHost, quint16 serverPort, quint16 callPort);
    ~MainWindow();

    void setupUI();
    void retranslateUI();

};


#endif // MAINWINDOW_H
