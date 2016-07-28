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
    void sendMessage(QString message);

private slots:
    void readMessage();

public slots:
    void login(QString username, QString password);
    void sendUserMessage(QString user, QString message);

signals:
    void recvUserMessage(QString user, QString message);
    void sentUserMessage(QString user, QString message);

    void updateFriends(QStringList friends);
};
