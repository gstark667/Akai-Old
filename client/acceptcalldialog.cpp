#include "acceptcalldialog.h"


AcceptCallDialog::AcceptCallDialog(QWidget *parent): QDialog(parent)
{
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setObjectName(QStringLiteral("m_gridLayout"));

    m_acceptButton = new QPushButton(this);
    m_acceptButton->setObjectName(QStringLiteral("m_acceptButton"));
    m_acceptButton->setText(QApplication::translate("AcceptCallDialog", "Accept", 0));
    m_gridLayout->addWidget(m_acceptButton, 0, 0, 1, 1);

    m_declineButton = new QPushButton(this);
    m_declineButton->setObjectName(QStringLiteral("m_declineButton"));
    m_declineButton->setText(QApplication::translate("AccpetCallDialog", "Decline", 0));
    m_gridLayout->addWidget(m_declineButton, 0, 1, 1, 1);

    resize(256, height());

    connect(m_acceptButton, &QPushButton::pressed, this, &AcceptCallDialog::callAccepted);
    connect(m_declineButton, &QPushButton::pressed, this, &AcceptCallDialog::callDeclined);
}


AcceptCallDialog::~AcceptCallDialog()
{

}


void AcceptCallDialog::callRequested(QString name, QHostAddress peerAddr, quint16 peerPort)
{
    setWindowTitle("Call From " + name);
    m_name = name;
    m_peerAddr = peerAddr;
    m_peerPort = peerPort;

    show();
}


void AcceptCallDialog::callAccepted()
{
    emit startCall(m_peerAddr, m_peerPort);
    emit callFriend(m_name);
    close();
}


void AcceptCallDialog::callDeclined()
{
    close();
}
