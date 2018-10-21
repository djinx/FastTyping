#ifndef PLAYERS_H
#define PLAYERS_H

#include <QObject>
#include <QTcpSocket>
#include <QDataStream>
#include <QHostAddress>
#include <QAbstractSocket>

class TwoPlayerWindow;

class Player : public QObject
{
    Q_OBJECT
public:
    explicit Player(QObject *parent = 0);
    ~Player();

    // Set methods
    void setClient(QTcpSocket *client);
    void setScoreMessage(QString message);
    void setScore(int score);

    // Get methods
    QTcpSocket *getClient() const;
    QString getScoreMessage() const;
    int getScore() const;

signals:
    void startGame();
    void updateScore();
    void COMBO();

public slots:
    void receiveMessage();
    void sendScoreMessage();
    void sendComboMessage();
    void displayError(QAbstractSocket::SocketError socketError);

private:
    QTcpSocket *m_Client;
    QString m_ScoreMessage;
    QString m_ComboMessage;
    int m_Score;
};

#endif // PLAYERS_H
