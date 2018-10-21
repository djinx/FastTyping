#include "mainmenu.h"
#include "ui_mainmenu.h"
#include "mainwindow.h"
#include "multiplayer.h"

MainMenu::MainMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainMenu),
    m_Partner1(0), m_Partner2(0)
{
    ui->setupUi(this);

//    qDebug() << "novi main menu";

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

MainMenu::~MainMenu()
{
    delete ui;
}

void MainMenu::setPartner(MainWindow *partner1, Multiplayer *partner2)
{
//    qDebug() << partner1->objectName();
//    qDebug() << partner2->objectName();
    if(partner1 == 0)
        return;

    if(m_Partner1 != partner1)
    {
        if(m_Partner1 != 0)
        {
            disconnect(ui->pushButton, SIGNAL(clicked()), this, SLOT(hide()));
            disconnect(ui->pushButton, SIGNAL(clicked()), m_Partner1, SLOT(show()));
        }

        m_Partner1 = partner1;

        connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(hide()));
        connect(ui->pushButton, SIGNAL(clicked()), m_Partner1, SLOT(showAndStart()));
    }

    if(partner2 == 0)
        return;

    if(m_Partner2 != partner2)
    {
        if(m_Partner2 != 0)
        {
            disconnect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(hide()));
            disconnect(ui->pushButton_3, SIGNAL(clicked()), m_Partner2, SLOT(show()));
        }

        m_Partner2 = partner2;

        connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(hide()));
        connect(ui->pushButton_3, SIGNAL(clicked()), m_Partner2, SLOT(show()));
    }
}
