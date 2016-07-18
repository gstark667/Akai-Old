#include "addfrienddialog.h"


AddFriendDialog::AddFriendDialog(QWidget *parent): QDialog(parent)
{
    setupUI();
}


AddFriendDialog::~AddFriendDialog()
{
    delete m_gridLayout;
    delete m_userList;
    delete m_addButton;
    delete m_cancelButton;
}


void AddFriendDialog::setupUI()
{
    if (objectName().isEmpty())
	setObjectName(QStringLiteral("AddFriendDialog"));
    resize(400, 300);
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setObjectName(QStringLiteral("gridLayout"));
    m_userList = new QListWidget(this);
    m_userList->setObjectName(QStringLiteral("m_userList"));

    m_gridLayout->addWidget(m_userList, 0, 0, 1, 1);

    m_addButton = new QPushButton(this);
    m_addButton->setObjectName(QStringLiteral("m_addButton"));

    m_gridLayout->addWidget(m_addButton, 1, 0, 1, 1);

    m_cancelButton = new QPushButton(this);
    m_cancelButton->setObjectName(QStringLiteral("m_cancelButton"));

    m_gridLayout->addWidget(m_cancelButton, 2, 0, 1, 1);


    retranslateUI();

    QMetaObject::connectSlotsByName(this);
}


void AddFriendDialog::retranslateUI()
{
    setWindowTitle(QApplication::translate("Form", "Form", 0));
    m_addButton->setText(QApplication::translate("Form", "Add", 0));
    m_cancelButton->setText(QApplication::translate("Form", "Cancel", 0));
}
