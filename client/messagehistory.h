#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QListWidgetItem>

#include <map>


class MessageHistory: public QTextBrowser
{
    Q_OBJECT

private:
    std::map<QString, QString> m_userMessages;
    QString m_currentUser;

public:
    MessageHistory(QWidget *parent): QTextBrowser(parent) {};

    void updateMessages();

public slots:
    void changeUser(QListWidgetItem *user);
    void sendMessage(QString message);
    void recvUserMessage(QString user, QString message);

signals:
    void sendUserMessage(QString user, QString message);
    void addUser(QString user);
};
