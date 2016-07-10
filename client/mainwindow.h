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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

#include <vector>


class MessageInput: public QTextEdit
{
    Q_OBJECT

private:
    bool m_shiftPressed;

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

public:
    MessageInput(QWidget *parent): QTextEdit(parent), m_shiftPressed(false) {};

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


class MainWindow: public QMainWindow
{
    Q_OBJECT

private:
    QAction *addFriendAction;
    QAction *createChatAction;
    QWidget *m_chatWidget;
    QGridLayout *m_gridLayout;
    QSplitter *m_chatSplit;
    QListWidget *m_chatList;
    QSplitter *m_messageSplit;
    MessageHistory *m_messageHistory;
    MessageInput *m_messageInput;
    QMenuBar *menubar;
    QMenu *friendsMenu;
    QMenu *chatsMenu;
    QMenu *menuOptions;
    QStatusBar *statusbar;

public:
    MainWindow();
    ~MainWindow();

    void setupUI();
    void retranslateUI();

};


#endif // MAINWINDOW_H
