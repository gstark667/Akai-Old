#include <QtWidgets/QApplication>
#include <QtGui/QIcon>
#include "mainwindow.h"
 
int main(int argc, char **argv)
{
    QApplication app (argc, argv);

    MainWindow *mainWindow = new MainWindow();
    mainWindow->show();
 
    return app.exec();
}
