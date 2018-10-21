#ifndef SERVERWIDGET_H
#define SERVERWIDGET_H

#include <QWidget>
#include <QDebug>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QMessageBox>
#include <QNetworkInterface>
class QNetworkSession;

class Player;
class Multiplayer;

namespace Ui {
class ServerWidget;
}

class ServerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ServerWidget(Multiplayer *mp, QWidget *parent = 0);
    ~ServerWidget();

    QString getAddress() const;
    void setAddress(QString address);
    QString getPort() const;
    void setPort(QString port);

signals:
    void serverIsRunning();
    void serverCrashed();

public slots:
    void onConnection();
    void receiveMessageP1();
    void receiveMessageP2();

private:
    Ui::ServerWidget *ui;
    QTcpServer *m_Server;
    Player *m_Player1;
    Player *m_Player2;
    QString m_address;
    QString m_port;
    Multiplayer *m_mp;
};

#endif // SERVERWIDGET_H
