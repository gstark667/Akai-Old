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
    connectToHost("localhost", 6667);
    sendMessage("USER " + username + " " + password);
    sendMessage("USERLIST");
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
    QTextStream stream(this);
    stream << message << "\n";
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
    if (argv[0].compare("USERMSG") == 0 && argc == 3)
    {
        emit recvMessage(argv[2]);
        std::cout << "Message From '" << argv[1].toStdString() << "' :" << argv[2].toStdString() << std::endl;
    }
    if (argv[0].compare("USERLIST") == 0 && argc == 2)
    {
        emit updateFriends(argv[1].split(" "));
    }
}
