#ifndef MULTIPLAYER_H
#define MULTIPLAYER_H

#include <QDialog>
#include <QDebug>
#include <QTcpSocket>
#include <QTcpServer>
#include <QtNetwork>
#include <QMessageBox>

class ServerWidget;
class TwoPlayerWindow;
class Player;
class ServerWidget;
class MainMenu;

namespace Ui {
class Multiplayer;
}

class Multiplayer : public QDialog
{
    Q_OBJECT

public:
    explicit Multiplayer(QWidget *parent = 0);
    ~Multiplayer();

    void setPartner(TwoPlayerWindow *mw);

public slots:
    void startServer();
    void startGame();
    void connectToHost();
    void closeWindow();

private:
    Ui::Multiplayer *ui;
    Player *m_Player;
    TwoPlayerWindow *m_PartnerMW;
    MainMenu *m_PartnerMM;
    ServerWidget *m_sw;
};

#endif // MULTIPLAYER_H
