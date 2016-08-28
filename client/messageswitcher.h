#ifndef MESSAGESWITCHER_H
#define MESSAGESWITCHER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QListView>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QGridLayout *m_switcherLayout;
    QTabWidget *m_messageSwitcher;
    QWidget *m_friendsTab;
    QGridLayout *m_friendsLayout;
    QListView *m_friendsList;
    QWidget *m_channelsTab;
    QGridLayout *m_channelsLayout;
    QListWidget *m_channelsList;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QStringLiteral("Form"));
        Form->resize(400, 300);
        m_switcherLayout = new QGridLayout(Form);
        m_switcherLayout->setObjectName(QStringLiteral("m_channelsLayout"));
        m_messageSwitcher = new QTabWidget(Form);
        m_messageSwitcher->setObjectName(QStringLiteral("m_messageSwitcher"));
        m_friendsTab = new QWidget();
        m_friendsTab->setObjectName(QStringLiteral("m_friendsTab"));
        m_friendsLayout = new QGridLayout(m_friendsTab);
        m_friendsLayout->setObjectName(QStringLiteral("m_channelsLayout"));
        m_friendsList = new QListView(m_friendsTab);
        m_friendsList->setObjectName(QStringLiteral("m_friendsList"));

        m_friendsLayout->addWidget(m_friendsList, 0, 0, 1, 1);

        m_messageSwitcher->addTab(m_friendsTab, QString());
        m_channelsTab = new QWidget();
        m_channelsTab->setObjectName(QStringLiteral("m_channelsTab"));
        m_channelsLayout = new QGridLayout(m_channelsTab);
        m_channelsLayout->setObjectName(QStringLiteral("gridLayout"));
        m_channelsList = new QListWidget(m_channelsTab);
        m_channelsList->setObjectName(QStringLiteral("m_channelsList"));

        m_channelsLayout->addWidget(m_channelsList, 0, 0, 1, 1);

        m_messageSwitcher->addTab(m_channelsTab, QString());

        m_switcherLayout->addWidget(m_messageSwitcher, 0, 0, 1, 1);


        retranslateUi(Form);

        m_messageSwitcher->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QApplication::translate("Form", "Form", 0));
        m_messageSwitcher->setTabText(m_messageSwitcher->indexOf(m_friendsTab), QApplication::translate("Form", "Friends", 0));
        m_messageSwitcher->setTabText(m_messageSwitcher->indexOf(m_channelsTab), QApplication::translate("Form", "Channels", 0));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // MESSAGESWITCHER_H
