#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>


class LoginDialog: public QDialog
{
    Q_OBJECT

private:
    QGridLayout *m_gridLayout;
    QLabel *m_usernameLabel;
    QLineEdit *m_usernameInput;
    QLabel *m_passwordLabel;
    QLineEdit *m_passwordInput;
    QPushButton *m_loginButton;
    QPushButton *m_cancelButton;

public:
    LoginDialog(QWidget *parent);
    ~LoginDialog();

    void setupUI();
    void retranslateUI();

private slots:
    void validateLogin();
    void cancelLogin();

signals:
    void login(QString username, QString password);
    void cancel();

};


#endif // LOGINDIALOG_H
