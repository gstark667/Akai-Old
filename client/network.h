#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>


class Network: public QTcpSocket
{
    Q_OBJECT
private:

public:
    Network();
    ~Network();
    void handleMessage(QString message);
    QStringList splitMessage(QString message);

private slots:
    void login(QString username, QString password);

    void readMessage();
    void sendMessage(QString message);

signals:
    void recvMessage(QString message);

    void updateFriends(QStringList friends);
};
