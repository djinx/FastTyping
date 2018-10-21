#include "players.h"


Player::Player(QObject *parent) : QObject(parent),
    m_Client(new QTcpSocket(this))
{
    //This signal is emitted once every time new data is available for reading
    connect(m_Client, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    //handle socket error
    typedef void (QAbstractSocket::*QAbstractSocketErrorSignal)(QAbstractSocket::SocketError);
    connect(m_Client, static_cast<QAbstractSocketErrorSignal>(&QAbstractSocket::error),this, &Player::displayError);
}

Player::~Player(){
    m_Client->disconnect();
    m_Client->deleteLater();
    delete m_Client;
}

//this function handles messages from server
void Player::receiveMessage()
{
    connect(m_Client, SIGNAL(readyRead()), this, SLOT(receiveMessage()));
    //read message sent by server
    QByteArray data = m_Client->readLine();
    QString dataAsString(data);
    QStringList message = dataAsString.split(",");

    //If two players are in lobby start game.
        if (message[0] == "n"){
            if (message[1] == "2")
                emit startGame();
        }

        if (message[0] == "s"){
            setScore(message[1].simplified().toInt());
            emit updateScore();
        }

        if(message[0] == "c"){
            emit COMBO();
        }
}

void Player::setScore(int score)
{
    m_Score = score;
}

int Player::getScore() const
{
    return m_Score;
}

void Player::sendScoreMessage()
{
    QByteArray block;
    block.append(this->getScoreMessage());
    m_Client->write(block, block.size());
    m_Client->flush();
}

void Player::sendComboMessage()
{
    QByteArray block;
    block.append("c,\n");

    m_Client->write(block, block.size());
    m_Client->flush();
}

void Player::displayError(QAbstractSocket::SocketError socketError)
{
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        qDebug() << "The host was not found. Please check the "
                   << "host name and port settings.";
        break;

    case QAbstractSocket::ConnectionRefusedError:
        qDebug() << "The connection was refused by the peer. "
                 << "Make sure the server is running, "
                 << "and check that the host name and port "
                 << "settings are correct.";
        break;
    default:
        qDebug() << "The following error occurred: "
                 << m_Client->errorString();
    }
}

// getters and setters
void Player::setClient(QTcpSocket *client)
{
    m_Client = client;
}

QTcpSocket *Player::getClient() const
{
    return m_Client;
}

void Player::setScoreMessage(QString message)
{
    m_ScoreMessage = message;
}

QString Player::getScoreMessage() const
{
    return m_ScoreMessage;
}

