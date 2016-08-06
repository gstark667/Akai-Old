#ifndef ACCEPTCALLDIALOG_H
#define ACCEPTCALLDIALOG_H

#include <QtNetwork/QHostAddress>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QGridLayout>

class AcceptCallDialog: public QDialog
{
    Q_OBJECT

private:
    QGridLayout *m_gridLayout;
    QPushButton *m_acceptButton;
    QPushButton *m_declineButton;

    QString      m_name;
    QHostAddress m_peerAddr;
    quint16      m_peerPort;

public:
    AcceptCallDialog(QWidget *parent);
    ~AcceptCallDialog();

public slots:
    void callRequested(QString name, QHostAddress peerAddr, quint16 peerPort);

private slots:
    void callAccepted();
    void callDeclined();

signals:
    void startCall(QHostAddress peerAddr, quint16 peerPort);
    void callFriend(QString name);
};

#endif
