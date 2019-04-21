
#include <QApplication>
#include "mainwindow2D.h"
#include "firstwindowconfig.h"
#include "windowchoice.h"
#include "firstwindow2d.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FirstWindowConfig windowConfig;
    windowConfig.show();

    return a.exec();
}
