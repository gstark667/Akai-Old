/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtCore/QVariant>
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


class MainWindow: public QMainWindow
{
private:
    QAction *addFriendAction;
    QAction *createChatAction;
    QWidget *ChatWidget;
    QGridLayout *gridLayout;
    QSplitter *ChatSplit;
    QListWidget *ChatList;
    QSplitter *MessageSplit;
    QTextBrowser *MessageHistory;
    QTextEdit *MessageInput;
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
