#include <QtCore/QThread>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>


class Network: public QTcpSocket
{
    Q_OBJECT
private:
    QHostAddress m_serverHost;
    quint16       m_serverPort;

public:
    Network(QHostAddress serverHost, quint16 serverPort, QObject *parent);
    ~Network();
    void handleMessage(QString message);
    QStringList splitMessage(QString message);
    void sendMessage(QString message);

private slots:
    void readMessages();

public slots:
    void login(QString username, QString password);
    void sendUserMessage(QString user, QString message);
    void listUsers();
    void listFriends();
    void addFriend(QString name);
    void callFriend(QString name, quint16 port);
    void removeFriend(QString name);

signals:
    void recvUserMessage(QString user, QString message);
    void sentUserMessage(QString user, QString message);

    void updateFriends(QStringList friends);
    void updateUsers(QStringList friends);

    void callRequested(QString name, QHostAddress peerAddress, quint16 peerPort);
};
