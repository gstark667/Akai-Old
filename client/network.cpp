#include "network.h"

#include <iostream>
#include <stdlib.h>


Network::Network(): QTcpSocket()
{
    connect(this, SIGNAL(readyRead()), SLOT(readMessage()));
}


Network::~Network()
{

}


void Network::login(QString username, QString password)
{
    connectToHost("162.243.175.235", 6667);
    waitForConnected();
    sendMessage("USER " + username + " " + password + "\r\n");
    sendMessage("FRIENDS\r\n");
}


void Network::readMessage()
{
    QTextStream stream(this);
    while (canReadLine())
    {
        QString message = stream.readLine();
        handleMessage(message);
    }
}


void Network::sendMessage(QString message)
{
    std::cout << "Sending: " << message.toStdString() << std::endl;
    write(message.toStdString().c_str());
    flush();
}


void Network::sendUserMessage(QString user, QString message)
{
    std::cout << "Sending " + message.toStdString() + " to " + user.toStdString() << std::endl;
    sendMessage("USERMSG " + user + " :" + message + "\n");
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
    for (int i = 0; i < argc; ++i)
    {
        std::cout << argv[i].toStdString() << std::endl;
    }
    if (argv[0] == "USERMSG" && argc == 3)
    {
        emit recvUserMessage(argv[1], argv[2]);
        std::cout << "Message From '" << argv[1].toStdString() << "' :" << argv[2].toStdString() << std::endl;
    }
    else if (argv[0] == "FRIENDS" && argc == 2)
    {
        std::cout << "Network got userlist" << std::endl;
        emit updateFriends(argv[1].simplified().split(" "));
    }
}
