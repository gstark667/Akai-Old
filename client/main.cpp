#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <stdlib.h>
#include <iostream>

#include "mainwindow.h"


int main(int argc, char **argv)
{
    if (argc != 4)
    {
        std::cout << argv[0] << " <server-ip> <server-port> <call-port>" << std::endl;
        return -1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);
    int mport = atoi(argv[3]);

    QApplication app (argc, argv);
    MainWindow *mainWindow = new MainWindow(QHostAddress(ip), port, mport);
    mainWindow->show();
 
    int return_code = app.exec();
    delete mainWindow;

    return return_code;
}
