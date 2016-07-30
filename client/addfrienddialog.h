#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QListWidgetItem>


class AddFriendDialog: public QDialog
{
    Q_OBJECT

private:
    QGridLayout *m_gridLayout;
    QListWidget *m_userList;
    QPushButton *m_addFriendButton;
    QPushButton *m_closeButton;
    QStringList m_users;
    QStringList m_friends;

public:
    AddFriendDialog(QWidget *parent);
    ~AddFriendDialog();

    void setupUI();
    void retranslateUI();
    void show();

public slots:
    void updateUsers(QStringList users);
    void updateFriends(QStringList friends);
    void updateNonFriends();
    void getFriends();

signals:
    void listUsers();
    void listFriends();
    void addFriend(QString username);

};


#endif // LOGINDIALOG_H
