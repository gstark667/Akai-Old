#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QListWidgetItem>

#include <map>


class MessageHistory: public QTextBrowser
{
    Q_OBJECT

private:
    std::map<QString, QString> m_userMessages;
    std::map<QString, QString> m_groupMessages;
    QString m_currentFriend;
    QString m_currentGroup;

public:
    MessageHistory(QWidget *parent): QTextBrowser(parent) {};

    void updateMessages();

public slots:
    void friendSelected(QListWidgetItem *item);
    void groupSelected(QListWidgetItem *item);
    void sendMessage(QString message);
    void recvUserMessage(QString user, QString message);

signals:
    void sendUserMessage(QString user, QString message);
    void addUser(QString user);
};
