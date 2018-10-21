#include "mainmenu.h"
#include "mainwindow.h"
#include "multiplayer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainMenu mm;
    MainWindow mw;
    Multiplayer mp;

    mm.setPartner(&mw, &mp);

    mm.show();

    return a.exec();
}
