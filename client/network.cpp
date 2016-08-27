#include "network.h"

#include <iostream>
#include <stdlib.h>


Network::Network(QHostAddress serverHost, quint16 serverPort, QObject *parent): QSslSocket(parent)
{
    m_serverHost = serverHost;
    m_serverPort = serverPort;
    connect(this, &QTcpSocket::readyRead, this, &Network::readMessages);
}


Network::~Network()
{
    close();
}


void Network::login(QString username, QString password)
{
    //connectToHost(m_serverHost, m_serverPort);
    QSettings settings;
    addCaCertificates(settings.value("cert_path").toString());
    connectToHostEncrypted(m_serverHost.toString(), m_serverPort);
    waitForConnected();
    // TODO add some connection error message to the status bar
    sendMessage("USER " + username + " " + password);
    sendMessage("FRIENDS");
    sendMessage("MSGHIST");
    listGroups();
}


void Network::readMessages()
{
    QTextStream stream(this);
    QStringList messages = stream.readAll().split("\r\n");
    for (int i = 0; i < messages.size(); ++i)
        handleMessage(messages[i]);
}


void Network::sendMessage(QString message)
{
    std::cout << "Sending: " << message.toStdString() << std::endl;
    message += "\r\n";
    writeData(message.toStdString().c_str(), message.size());
    flush();
}


void Network::sendUserMessage(QString user, QString message)
{
    sendMessage("USERMSG " + user + " :" + message);
}


void Network::sendGroupMessage(QString group, QString message)
{
    sendMessage("GRPMSG " + group + " :" + message);
}


void Network::listUsers()
{
    sendMessage("USERS");
}


void Network::listFriends()
{
    sendMessage("FRIENDS");
}


void Network::getGroupName(QString group)
{
    sendMessage("GRPNAME " + group);
}


void Network::getGroupHistory(QString group)
{
    sendMessage("GRPHIST " + group);
}


void Network::addFriend(QString name)
{
    sendMessage("FRIEND " + name);
}


void Network::callFriend(QString name, quint16 port)
{
    sendMessage("CALL " + name + " " + QString::number(port));
    std::cout << "calling " << name.toStdString() << std::endl;
}


void Network::removeFriend(QString name)
{
    sendMessage("UNFRIEND " + name);
}


void Network::listGroups()
{
    sendMessage("GROUPS");
}


void Network::listOwnedGroups()
{
    sendMessage("OWNED");
}


void Network::createGroup(QString name, QList<QString> members)
{
    QString message = "CREATE " + name;
    for (auto it = members.begin(); it != members.end(); ++it)
        message += " " + *it;
    sendMessage(message.simplified());
}


void Network::disbandGroup(QString group)
{
    sendMessage("DISBAND " + group);
}


QStringList Network::splitMessage(QString message)
{
    QStringList split = message.split(" ");
    QStringList output;
    for (int i = 0; i < split.size(); ++i)
    {
        if (split.at(i).startsWith(":"))
        {
            QString trailer = split.at(i);
            trailer.remove(0, 1);
            for (int j = i + 1; j < split.size(); ++j)
            {
                trailer += " " + split.at(j);
            }
            output.push_back(trailer);
            return output;
        }
        output.push_back(split.at(i));
    }
    return output;
}


void Network::handleMessage(QString message)
{
    QStringList argv = splitMessage(message);
    int argc = argv.size();

    std::cout << message.toStdString() << std::endl;

    if (argv[0] == "ISAUTH" && argc == 2)
    {
        emit isAuth();
    }
    else if (argv[0] == "USERMSG" && argc == 3)
    {
        emit recvUserMessage(argv[1], argv[2]);
        std::cout << "Message From '" << argv[1].toStdString() << "' :" << argv[2].toStdString() << std::endl;
    }
    else if (argv[0] == "USERMSGSNT" && argc == 3)
    {
        emit sentUserMessage(argv[1], argv[2]);
    }
    else if (argv[0] == "GRPMSG" && argc == 4)
    {
        emit recvGroupMessage(argv[1], argv[2], argv[3]);
    }
    else if (argv[0] == "GRPMSGSNT" && argc == 3)
    {
        emit sentGroupMessage(argv[1], argv[2]);
    }
    else if (argv[0] == "FRIENDS" && argc == 2)
    {
        std::cout << "Network got userlist" << std::endl;
        emit updateFriends(argv[1].simplified().split(" "));
    }
    else if (argv[0] == "USERS" && argc == 2)
    {
        emit updateUsers(argv[1].simplified().split(" "));
    }
    else if (argv[0] == "GROUPS" && argc == 2)
    {
        emit updateGroups(argv[1].simplified().split(" "));
    }
    else if (argv[0] == "OWNED" && argc == 2)
    {
        emit ownGroups(argv[1].simplified().split(" "));
    }
    else if (argv[0] == "GRPNAME" && argc == 3)
    {
        emit nameGroup(argv[1], argv[2]);
    }
    else if (argv[0] == "CREATED" && argc == 3)
    {
        emit updateGroups(argv[1].simplified().split(" "));
    }
    else if (argv[0] == "CALL" && argc == 4)
    {
        emit callRequested(argv[1], QHostAddress(argv[2]), argv[3].toInt());
    }
    else if (argv[0] == "ERROR" && argc == 2)
    {
        std::cout << "Error" << std::endl;
        emit errorMessage(argv[1]);
    }
}
