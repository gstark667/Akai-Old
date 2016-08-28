#ifndef EDITGROUPDIALOG_H
#define EDITGROUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include <QtWidgets/QDialog>


class EditGroupDialog: public QDialog
{
    Q_OBJECT

private:
    QGridLayout *gridLayout;
    QListWidget *m_userList;
    QPushButton *m_addButton;
    QListWidget *m_memberList;
    QPushButton *m_removeButton;
    QPushButton *m_closeButton;
    QString     m_group;
    QStringList m_users;
    QStringList m_members;

public:
    EditGroupDialog(QWidget *parent);

    void setupUI();
    void retranslateUI();
    void show();

private slots:
    void doAddMembers();
    void doRemoveMembers();
    void updateLists();

public slots:
    void editGroup(QString group);
    void updateUsers(QStringList users);
    void updateMembers(QString group, QStringList members);

signals:
    void listUsers();
    void listGroupMembers(QString group);
    void addMember(QString group, QString member);
    void removeMember(QString group, QString member);

};

#endif
