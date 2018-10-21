#include "serverwidget.h"
#include "ui_serverwidget.h"
#include "players.h"
#include "multiplayer.h"

#define PORT 4321
int playersNumber = 0;

ServerWidget::ServerWidget(Multiplayer *mp,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ServerWidget)
{
    ui->setupUi(this);

    m_mp = mp;
    setPort(QString::number(PORT));

    //try running server
    m_Server = new QTcpServer(this);
    if (!m_Server->listen(QHostAddress::Any, PORT)) {
            emit serverCrashed();
    }

    QList<QHostAddress> ipAddressesList;
    ipAddressesList = QNetworkInterface::allAddresses();

    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
                ipAddressesList.at(i).toIPv4Address()) {
            this->setAddress(ipAddressesList.at(i).toString());
            break;
        }
    }

    // if we did not find one, use IPv4 localhost
    if (getAddress().isEmpty())
        this->setAddress(QHostAddress(QHostAddress::LocalHost).toString());

    ui->lineIp->setText(getAddress());
    ui->lineIp->setEnabled(false);
    ui->linePort->setText(getPort());
    ui->linePort->setEnabled(false);

    //if we came here, server is running
    emit serverIsRunning();
    //handle messages
    m_Player1 = new Player();
    m_Player2 = new Player();

    //handle new connection
    connect(m_Server, SIGNAL(newConnection()), this, SLOT(onConnection()));

}

ServerWidget::~ServerWidget()
{
    delete ui;
    delete m_Server;
    delete m_Player1;
    delete m_Player2;
}

void ServerWidget::onConnection()
{
    if(m_Server->hasPendingConnections())
        {
        //add first player to lobby
            if(playersNumber == 0)
            {
                m_Player1->setClient(m_Server->nextPendingConnection());
                playersNumber++;
                //qDebug() << "Player1 connected";

            }//add second player to lobby
            else if(playersNumber == 1)
            {
                m_Player2->setClient(m_Server->nextPendingConnection());
                playersNumber++;
                //qDebug() << "Player2 connected";

                //notify clients that game is ready to start
                QByteArray block;
                block.append("n,");
                block.append(QString::number(playersNumber));

                m_Player1->getClient()->write(block);
                m_Player1->getClient()->flush();
                m_Player2->getClient()->write(block);
                m_Player2->getClient()->flush();

                emit m_Player1->getClient()->readyRead();
                emit m_Player2->getClient()->readyRead();
                connect(m_Player1->getClient(), SIGNAL(readyRead()), this, SLOT(receiveMessageP1()));
                connect(m_Player2->getClient(), SIGNAL(readyRead()), this, SLOT(receiveMessageP2()));
            }
        }
}

void ServerWidget::receiveMessageP1()
{
    QByteArray block;

    //if Player1 sent message, send it to Player2
    QString message1 = m_Player1->getClient()->readAll();
    block.append(message1);
    m_Player2->getClient()->write(block);
    m_Player2->getClient()->flush();
}

void ServerWidget::receiveMessageP2()
{
    QByteArray block;

    //if Player2 sent message, send it to Player1
    QString message2 = m_Player2->getClient()->readAll();
    block.append(message2);
    m_Player1->getClient()->write(block);
    m_Player1->getClient()->flush();
}

QString ServerWidget::getAddress() const
{
    return m_address;
}

void ServerWidget::setAddress(QString address)
{
    m_address = address;
}

QString ServerWidget::getPort() const
{
    return m_port;
}

void ServerWidget::setPort(QString port)
{
    m_port = port;
}
