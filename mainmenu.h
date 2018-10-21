#ifndef MAINMENU_H
#define MAINMENU_H

#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>

class MainWindow;
class Multiplayer;

namespace Ui {
    class MainMenu;
}

class MainMenu : public QWidget
{
    Q_OBJECT

public:
    explicit MainMenu(QWidget *parent = 0);
    ~MainMenu();

    void setPartner(MainWindow *partner1, Multiplayer *partner2);

private:
    Ui::MainMenu *ui;
    MainWindow *m_Partner1;
    Multiplayer *m_Partner2;
};

#endif // MAINMENU_H
