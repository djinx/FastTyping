#include "multiplayer.h"
#include "ui_multiplayer.h"
#include "twoplayerwindow.h"
#include "serverwidget.h"
#include "players.h"
#include "mainmenu.h"

Multiplayer::Multiplayer(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Multiplayer)
{
    ui->setupUi(this);

    ui->label_3->hide();

    //create new Player, player is client and he handles messages from server
    m_Player = new Player();

    //connect two player window with multiplayer window
    TwoPlayerWindow *mw = new TwoPlayerWindow(m_Player);
    setPartner(mw);

    //connect multiplayer window with main menu
    MainMenu* partner;
    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
        if (widget->objectName() == "MainMenu")
        {
            partner = qobject_cast<MainMenu*>(widget);
            break;
        }
    }
    m_PartnerMM = partner;

    //starts server when hosting
    connect(ui->hostButton, SIGNAL(clicked()), this, SLOT(startServer()));

    //handles messages
    connect(m_Player->getClient(), SIGNAL(readyRead()), m_Player, SLOT(receiveMessage()));

    connect(ui->guestButton, SIGNAL(clicked()), this, SLOT(connectToHost()));

    connect(m_Player, SIGNAL(startGame()), this, SLOT(startGame()));

    //handles connection to main menu
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(closeWindow()));
}

Multiplayer::~Multiplayer()
{
    delete ui;
    delete m_Player;
    delete m_PartnerMW;
    delete m_PartnerMM;
    delete m_sw;
}

//starts server and connects host to it
void Multiplayer::startServer()
{
    m_sw = new ServerWidget(this);
    ui->label_3->setStyleSheet("font-size:24pt; color:blue;");
    ui->label_3->setText("Server is running");
    ui->label_3->show();
    ui->lineIp->setText(m_sw->getAddress());
    ui->lineIp->setEnabled(false);
    ui->linePort->setText(m_sw->getPort());
    ui->linePort->setEnabled(false);

}

//handles connections
void Multiplayer::connectToHost()
{

    QString ipAddress = ui->lineIp->text();
    QString port = ui->linePort->text();

    m_Player->getClient()->connectToHost(ipAddress, port.toInt());


    if(!m_Player->getClient()->waitForConnected(5000))
    {
        //connection failed
        ui->label_3->show();
    }
    else{
        //connected
        ui->label_3->setStyleSheet("font-size:24pt; color:#f30610;");
        ui->label_3->setText("Connected!");
        ui->label_3->show();
    }
}

//starts game for client
void Multiplayer::startGame()
{
    this->hide();
    m_PartnerMW->showAndStart();
}

void Multiplayer::closeWindow()
{
    ui->label_3->hide();
    ui->lineIp->setText("");
    ui->lineIp->setEnabled(true);
    ui->linePort->setText("");
    ui->linePort->setEnabled(true);
    m_PartnerMM->show();
    m_Player->getClient()->disconnect();
    this->close();
}

//set method
void Multiplayer::setPartner(TwoPlayerWindow *mw)
{
    m_PartnerMW = mw;
}

