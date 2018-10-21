#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "word.h"
#include "game.h"
#include "label.h"
#include "scorewindow.h"

#include <QPoint>

int gameCounter;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow),
      m_words(0),
      m_game(new Game(0, 0)),
      m_num(10)
{
    ui->setupUi(this);

    // Setting a background
    this->centralWidget()->setStyleSheet(
             "background-image:url(\":/backgrounds/MainWindow.png\");"
             "background-position: center;"
    );

    ui->lineEdit->setStyleSheet(
        "border-radius: 0px;"
        "border: 5px solid white;"
        "background-color: rgba(0, 0, 0, 0);"
        "background: transparent;"
        "padding: 5px;"
        "color: black"
    );
    ui->lineEdit->setMinimumHeight(50);
    ui->lineEdit->setAttribute(Qt::WA_TranslucentBackground);

    ui->time->setStyleSheet(
        "color: white"
    );
    ui->time->setAttribute(Qt::WA_TranslucentBackground);

    ui->points->setStyleSheet(
        "color: white"
    );
    ui->points->setAttribute(Qt::WA_TranslucentBackground);

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAndStart()
{
    gameCounter++;

    qDebug() << "==================";
    qDebug() << "Game counter:" << gameCounter;

    int ii = 0;
    for(unsigned i = 0; i<m_labels.size(); i++)
        ii++;
    qDebug() << "Number of labels is" << ii;
    ii = 0;
    for(unsigned i = 0; i<m_words.size(); i++)
        ii++;
    qDebug() << "Number of words is" << ii;
    qDebug() << "Class variable m_num is" << m_num;

    // Loading words from file
    m_game->readWords(":/data/plants.txt");

    // Adding words
    int brojLabela = 10;
    for(int i=0; i<brojLabela; i++)
    {
        addWord(new Word(m_game->nextWord(i), QString("black")));
    }

    if(gameCounter == 1)
    {
        // Adding labels
        addLabel(ui->label);
        addLabel(ui->label_2);
        addLabel(ui->label_3);
        addLabel(ui->label_4);
        addLabel(ui->label_5);
        addLabel(ui->label_6);
        addLabel(ui->label_7);
        addLabel(ui->label_8);
        addLabel(ui->label_9);
        addLabel(ui->label_10);
    }

    for(unsigned i=0; i<m_labels.size()/2; i++)
    {
        m_labels[i]->getLabel()->setText(m_words[i]->getColoredWord());
        m_labels[i]->setSpeed(m_words[i]->length());
        m_labels[i]->setHidden(false);
        m_labels[i]->getLabel()->move(m_labels[i]->getLabel()->x(), 70);
    }

    // Initializing values for time and points
    m_time = ui->time;
    QString str;
    str.setNum(TIMEOUT);
    m_time->setText(str);

    m_points = ui->points;
    m_points->setText(m_game->getScoreP1());

    QObject::connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(changeText(QString)));

    // Starting timers
    m_timerTime = new QTimer();
    connect(m_timerTime, SIGNAL(timeout()), this, SLOT(changeTime()));
    m_timerTime->start(1000);
    m_timerLabels = new QTimer();
    connect(m_timerLabels, SIGNAL(timeout()), this, SLOT(moveLabel()));
    m_timerLabels->start(50);

    ui->lineEdit->setText("");

    this->show();

    // TODO: mapirati dugme ESC na pauzu (Qtimer->stop())
}

void MainWindow::addWord(Word* word)
{
    m_words.push_back(word);
}

void MainWindow::addLabel(QLabel* label)
{
    Label* l = new Label(label);
    l->setHidden(true);
    m_labels.push_back(l);
}

int MainWindow::numOfHidden()
{
    return std::count_if(m_labels.begin(), m_labels.end(), [](Label* l) {return l->getHidden();});
}

void MainWindow::colorWords(QString text){
    int pos;
    for(Word* word: m_words){
        word->setNotColored(word->getWord());
        word->setColored("");
        if(word->getWord().indexOf(text) == 0)
        {
            pos = text.length();
            QString tmp = word->getWord();
            int length = tmp.length();
            word->setColored(tmp.left(pos));
            word->setNotColored(tmp.right(length-pos));
        }
    }

    for(unsigned i=0; i<m_labels.size(); i++)
    {
        m_labels[i]->getLabel()->setText(m_words[i]->getColoredWord());
    }

}

void MainWindow::moveLabel()
{
    showFive();
    moveLine();
    for(unsigned i=0; i<m_labels.size(); i++)
    {
        if(m_game->numOfWords() - m_num < 6)
        {
            m_game->readWords(":/data/animals.txt");
        }

        if(!m_labels[i]->getHidden())
        {
            bool moved;
            moved = m_labels[i]->moveLabel(ui->line->y());
            if(!moved)
            {
                update(i, -m_words[i]->length()*m_labels[i]->getSpeed());
                m_game->setCombo(0);
            }
        }
    }
    m_points->setText(m_game->getScoreP1());
}

void MainWindow::showFive()
{
    unsigned k;
    while(numOfHidden() != 5)
    {
        k = std::floor(std::rand()/(RAND_MAX*1.0)*10);
        if(m_labels[k]->getHidden()){
            m_labels[k]->getLabel()->setText(m_words[k]->getColoredWord());
            m_labels[k]->setSpeed(m_words[k]->length());
            m_labels[k]->setHidden(false);
            m_labels[k]->getLabel()->move(m_labels[k]->getLabel()->x(), 70);
        }
    }
}

void MainWindow::hideAll()
{
    for(unsigned i=0; i < m_labels.size(); i++)
    {
        m_labels[i]->setHidden(true);
    }
}

void MainWindow::resetGame()
{
    hideAll();
    m_timerTime->stop();
    m_timerLabels->stop();
    disconnect(m_timerTime, SIGNAL(timeout()), this, SLOT(changeTime()));
    disconnect(m_timerLabels, SIGNAL(timeout()), this, SLOT(moveLabel()));
    delete m_timerLabels;
    delete m_timerTime;
    if(!m_words.empty())
    {
        m_words.clear();
    }
    m_num = 10;
    ui->line->move(ui->line->x(), 550);
    // Loading words from file
    m_game->readWords(":/data/animals.txt");
    ui->lineEdit->setText("");
    m_game->setScoreP1(0);
    ui->line->move(ui->line->x(), 550);

}

void MainWindow::changeText(QString text)
{
    for(unsigned i=0; i<m_words.size(); i++)
    {
        colorWords(text);
        if(m_words[i]->getNotColored().isEmpty()){
            if(m_game->numOfWords() - m_num < 6){
                m_game->readWords(":/data/animals.txt");
            }
            update(i, m_words[i]->length()*m_labels[i]->getSpeed());
            m_game->setCombo(m_game->getCombo() + 1);
            ui->lineEdit->setText("");
        }
        colorWords(text);
    }
}

void MainWindow::update(int i, int points)
{
    m_labels[i]->setHidden(true);
    m_labels[i]->getLabel()->move(m_labels[i]->getLabel()->x(), 0);
    m_game->updateScore(points);
    m_points->setText(m_game->getScoreP1());

    Word* w = new Word(m_game->nextWord(m_num), QString("black"));
    replace(m_words.begin(), m_words.end(), m_words[i], w);
    m_labels[i]->setSpeed(w->length());
    m_num++;

}

void MainWindow::moveLine()
{
    if(m_game->getCombo() == 10)
    {
        m_game->setCombo(0);
        ui->line->move(ui->line->x(), ui->line->y() - 25);
    }
}

void MainWindow::changeTime()
{
    static int time = TIMEOUT;
    time--; // decrement counter
    if (time==0) // countdown has finished
    {
        qDebug() << "Game ended!";
        time = TIMEOUT;
        ScoreWindow *sw = new ScoreWindow(ui->points->text().toInt(), -1);
        resetGame();
        sw->show();
        this->close();
    }
    else
    {
        QString str;
        str.setNum(time);
        m_time->setText(str);
    }
}
