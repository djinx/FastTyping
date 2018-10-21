#include "scorewindow.h"
#include "ui_scorewindow.h"
#include "mainmenu.h"

#include <QDebug>

ScoreWindow::ScoreWindow(int score1, int score2, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ScoreWindow),
    m_Partner(0)
{
    ui->setupUi(this);

    QString s1 = QString("Player 1 score: ") + QString::number(score1) + QString("\n");
    QString s2("");
    if(score2 != -1)
    {
        s2 = QString("Player 2 score: ") + QString::number(score2);
    }

    ui->score->setText(s1+s2);

    setPartner();

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );
}

ScoreWindow::~ScoreWindow()
{
    delete ui;
}

void ScoreWindow::setPartner()
{
    MainMenu* partner;
    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
        if (widget->objectName() == "MainMenu")
        {
            partner = qobject_cast<MainMenu*>(widget);
            break;
        }
    }

    if(m_Partner != 0)
    {
        disconnect(ui->pushButton, SIGNAL(clicked()), this, SLOT(hide()));
        disconnect(ui->pushButton, SIGNAL(clicked()), m_Partner, SLOT(show()));
    }

    m_Partner = partner;

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(hide()));
    connect(ui->pushButton, SIGNAL(clicked()), m_Partner, SLOT(show()));

}
