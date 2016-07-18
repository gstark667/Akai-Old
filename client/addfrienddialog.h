#ifndef ADDFRIENDDIALOG_H
#define ADDFRIENDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>


class AddFriendDialog: public QDialog
{
private:
    QGridLayout *m_gridLayout;
    QListWidget *m_userList;
    QPushButton *m_addButton;
    QPushButton *m_cancelButton;

public:
    AddFriendDialog(QWidget *parent);
    ~AddFriendDialog();
    void setupUI();
    void retranslateUI();
};


#endif // ADDFRIENDDIALOG_H
