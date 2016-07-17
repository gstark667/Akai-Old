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

#include "logindialog.h"
#include "network.h"


class MessageInput: public QLineEdit
{
    Q_OBJECT

private:
    bool m_shiftPressed;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public:
    MessageInput(QWidget *parent): QLineEdit(parent), m_shiftPressed(false) {};

signals:
    void sendMessage(QString message);
};


class MessageHistory: public QTextBrowser
{
    Q_OBJECT

private:
    std::vector<QString> m_messageBuffer;


public:
    MessageHistory(QWidget *parent): QTextBrowser(parent) {};

    void updateMessages();

public slots:
    void sendMessage(QString message);
    void recvMessage(QString message);
};


class ChannelWidget: public QTreeWidget
{
    Q_OBJECT

private:
    QTreeWidgetItem *m_friends;
    QTreeWidgetItem *m_channels;

public:
    ChannelWidget(QWidget *parent);
    ~ChannelWidget();

public slots:
    void updateFriends(QStringList friends);
    void updateChannels(QStringList channels);
};


class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QAction *addFriendAction;
    QAction *createChatAction;
    QWidget *m_chatWidget;
    QGridLayout *m_gridLayout;
    QSplitter *m_chatSplit;
    ChannelWidget *m_chatList;
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
