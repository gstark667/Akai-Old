#include <QtCore/QCoreApplication>
#include <QtCore/QSettings>
#include <QtNetwork/QHostAddress>
#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <stdlib.h>
#include <iostream>

#include "mainwindow.h"


int main(int argc, char **argv)
{
    QCoreApplication::setOrganizationName("SheilDuck");
    QCoreApplication::setApplicationName("Akai");
    QSettings settings;

    if (!settings.contains("server"))
        settings.setValue("server", "127.0.0.1");
    if (!settings.contains("port"))
        settings.setValue("port", 6667);
    if (!settings.contains("callport"))
        settings.setValue("callport", 6668);

    qDebug() << settings.fileName();

    QHostAddress serverAddr = QHostAddress(settings.value("server").toString());
    quint16      serverPort = settings.value("port").toUInt();
    quint16        callPort = settings.value("callport").toUInt();
    
    QApplication app (argc, argv);
    MainWindow *mainWindow = new MainWindow(serverAddr, serverPort, callPort);
    mainWindow->show();
 
    int return_code = app.exec();
    delete mainWindow;

    return return_code;
}
