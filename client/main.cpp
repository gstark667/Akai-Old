#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include <stdlib.h>
#include <iostream>

#include "mainwindow.h"


int main(int argc, char **argv)
{
    if (argc != 3)
    {
        std::cout << argv[0] << " <server-ip> <server-port>" << std::endl;
        return -1;
    }

    char *ip = argv[1];
    int port = atoi(argv[2]);

    QApplication app (argc, argv);
    MainWindow *mainWindow = new MainWindow(QHostAddress(ip), port);
    mainWindow->show();
 
    int return_code = app.exec();
    delete mainWindow;

    return return_code;
}
