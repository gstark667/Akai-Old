#include <QtCore/QThread>
#include <QtCore/QSettings>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QSslSocket>
#include <QtNetwork/QHostAddress>


class Network: public QSslSocket
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
    void sendGroupMessage(QString group, QString message);
    void listUsers();
    void listFriends();
    void getGroupName(QString group);
    void getGroupHistory(QString group);
    void addFriend(QString name);
    void callFriend(QString name, quint16 port);
    void removeFriend(QString name);
    void listGroups();
    void listOwnedGroups();
    void createGroup(QString name, QList<QString> members);
    void disbandGroup(QString name);

signals:
    void isAuth();

    void recvUserMessage(QString user, QString message);
    void sentUserMessage(QString user, QString message);
    void recvGroupMessage(QString group, QString user, QString message);
    void sentGroupMessage(QString group, QString message);

    void updateFriends(QStringList friends);
    void updateGroups(QStringList groups);
    void ownGroups(QStringList groups);
    void nameGroup(QString group, QString name);
    void updateUsers(QStringList friends);

    void callRequested(QString name, QHostAddress peerAddress, quint16 peerPort);

    void errorMessage(QString message, int timeout=0);
};
