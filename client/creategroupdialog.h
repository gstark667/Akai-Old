#ifndef CREATEGROUPDIALOG_H
#define CREATEGROUPDIALOG_H

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


class CreateGroupDialog: public QDialog
{
    Q_OBJECT

private:
    QGridLayout *gridLayout;
    QLabel *m_nameLabel;
    QLineEdit *m_nameField;
    QListWidget *m_userList;
    QPushButton *m_addButton;
    QListWidget *m_memberList;
    QPushButton *m_removeButton;
    QPushButton *m_createButton;
    QPushButton *m_cancelButton;
    QStringList m_users;
    QStringList m_members;

public:
    CreateGroupDialog(QWidget *parent);

    void setupUI();
    void retranslateUI();
    void show();

private slots:
    void addMembers();
    void removeMembers();
    void updateLists();
    void doCreateGroup();

public slots:
    void updateUsers(QStringList users);

signals:
    void listUsers();
    void createGroup(QString name, QStringList members);
    
};

#endif
