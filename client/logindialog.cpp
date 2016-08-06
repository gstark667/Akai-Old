#include "logindialog.h"

#include <iostream>


LoginDialog::LoginDialog(QWidget *parent): QDialog(parent)
{
   setupUI();
}


LoginDialog::~LoginDialog()
{
    delete m_gridLayout;
    delete m_usernameLabel;
    delete m_usernameInput;
    delete m_passwordLabel;
    delete m_passwordInput;
    delete m_loginButton;
    delete m_cancelButton;
}


void LoginDialog::setupUI()
{
    if (objectName().isEmpty())
	setObjectName(QStringLiteral("LoginDialog"));
    resize(330, 190);
    setWindowModality(Qt::ApplicationModal);
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_usernameLabel = new QLabel(this);
    m_usernameLabel->setObjectName(QStringLiteral("m_usernameLabel"));

    m_gridLayout->addWidget(m_usernameLabel, 0, 0, 1, 1);

    m_usernameInput = new QLineEdit(this);
    m_usernameInput->setObjectName(QStringLiteral("m_usernameInput"));

    m_gridLayout->addWidget(m_usernameInput, 0, 1, 1, 1);

    m_passwordLabel = new QLabel(this);
    m_passwordLabel->setObjectName(QStringLiteral("m_passwordLabel"));

    m_gridLayout->addWidget(m_passwordLabel, 1, 0, 1, 1);

    m_passwordInput = new QLineEdit(this);
    m_passwordInput->setObjectName(QStringLiteral("m_passwordInput"));
    m_passwordInput->setEchoMode(QLineEdit::Password);

    m_gridLayout->addWidget(m_passwordInput, 1, 1, 1, 1);

    m_loginButton = new QPushButton(this);
    m_loginButton->setObjectName(QStringLiteral("m_loginButton"));

    m_gridLayout->addWidget(m_loginButton, 2, 0, 1, 2);

    m_cancelButton = new QPushButton(this);
    m_cancelButton->setObjectName(QStringLiteral("m_cancelButton"));

    m_gridLayout->addWidget(m_cancelButton, 3, 0, 1, 2);


    retranslateUI();

    connect(m_loginButton, SIGNAL(pressed()), this, SLOT(validateLogin())),
    connect(m_cancelButton, SIGNAL(pressed()), this, SLOT(cancelLogin()));
}


void LoginDialog::retranslateUI()
{
    setWindowTitle(QApplication::translate("LoginDialog", "Dialog", 0));
    m_usernameLabel->setText(QApplication::translate("LoginDialog", "Username", 0));
    m_passwordLabel->setText(QApplication::translate("LoginDialog", "Password", 0));
    m_loginButton->setText(QApplication::translate("LoginDialog", "Login", 0));
    m_cancelButton->setText(QApplication::translate("LoginDialog", "Cancel", 0));
}


void LoginDialog::validateLogin()
{
    std::cout << m_usernameInput->text().toStdString() << std::endl;
    emit login(m_usernameInput->text(), m_passwordInput->text());
}


void LoginDialog::cancelLogin()
{
    emit cancel();
}
