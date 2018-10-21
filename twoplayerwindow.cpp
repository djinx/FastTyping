#include "twoplayerwindow.h"
#include "ui_twoplayerwindow.h"
#include "word.h"
#include "game.h"
#include "label.h"
#include "scorewindow.h"
#include "players.h"
bool ind = false;

int gameCounter2;

TwoPlayerWindow::TwoPlayerWindow(Player *player, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TwoPlayerWindow),
    m_words(0),
    m_game(new Game(0, 0)),
    m_num(10)
{
    ui->setupUi(this);

    m_Player = player;

    //connected score changed with send message
    connect(this, SIGNAL(scoreChanged()), m_Player, SLOT(sendScoreMessage()));
    connect(m_Player, SIGNAL(updateScore()), this, SLOT(updateScore()));
    //connect combo with sendcombo
    connect(this, SIGNAL(LEGENDARY()), m_Player, SLOT(sendComboMessage()));
    connect(m_Player, SIGNAL(COMBO()), this, SLOT(setInd()));

    // Setting a background
    this->setStyleSheet(
             "background-image:url(\":/backgrounds/TwoPlayerWindow.png\");"
             "background-position: center;"
    );

    ui->lineEdit->setStyleSheet(
        "border-radius: 0px;"
        "border: 5px solid white;"
        "background-color: white;"
        "background: transparent;"
        "padding: 5px;"
        "color: yellow"
    );
    ui->lineEdit->setMinimumHeight(50);
    ui->lineEdit->setAttribute(Qt::WA_TranslucentBackground);

    ui->time->setStyleSheet(
        "color: white"
    );
    ui->time->setAttribute(Qt::WA_TranslucentBackground);

    ui->score1->setStyleSheet(
        "color: blue"
    );
    ui->score1->setAttribute(Qt::WA_TranslucentBackground);

    ui->score2->setStyleSheet(
        "color: blue"
    );
    ui->score2->setAttribute(Qt::WA_TranslucentBackground);

    this->setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            this->size(),
            qApp->desktop()->availableGeometry()
        )
    );

}

TwoPlayerWindow::~TwoPlayerWindow()
{
    delete ui;
}

void TwoPlayerWindow::showAndStart()
{
    gameCounter2++;

    qDebug() << "==================";
    qDebug() << "Game counter:" << gameCounter2;

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
        addWord(new Word(m_game->nextWord(i), QString("white")));
    }

    if(gameCounter2 == 1)
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

    m_points1 = ui->score1;
    m_points2 = ui->score2;
    m_points1->setText(m_game->getScoreP1());
    m_points2->setText(m_game->getScoreP2());

    QObject::connect(ui->lineEdit, SIGNAL(textEdited(QString)), this, SLOT(changeText(QString)));

    // Starting timers
    m_timerTime = new QTimer();
    connect(m_timerTime, SIGNAL(timeout()), this, SLOT(changeTime()));
    m_timerTime->start(1000);
    m_timerLabels = new QTimer();
    connect(m_timerLabels, SIGNAL(timeout()), this, SLOT(moveLabel()));
    m_timerLabels->start(50);

    this->show();
}

void TwoPlayerWindow::addWord(Word* word)
{
    m_words.push_back(word);
}

void TwoPlayerWindow::addLabel(QLabel* label)
{
    Label* l = new Label(label);
    l->setHidden(true);
    m_labels.push_back(l);
}

int TwoPlayerWindow::numOfHidden()
{
    return std::count_if(m_labels.begin(), m_labels.end(), [](Label* l) {return l->getHidden();});
}

void TwoPlayerWindow::colorWords(QString text){
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

void TwoPlayerWindow::moveLabel()
{
    showFive();
    // pomera liniju
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
    m_points1->setText(m_game->getScoreP1());
}

void TwoPlayerWindow::showFive()
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

void TwoPlayerWindow::hideAll()
{
    for(unsigned i=0; i < m_labels.size(); i++)
    {
        m_labels[i]->setHidden(true);
    }
}

void TwoPlayerWindow::changeText(QString text)
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
            //if we are on winning streak send garbage to the other player
            if(m_game->getCombo()==10){
                m_game->setCombo(0);
                emit LEGENDARY();
            }
            ui->lineEdit->setText("");
        }
        colorWords(text);
    }
}

void TwoPlayerWindow::update(int i, int points)
{
    m_labels[i]->setHidden(true);
    m_labels[i]->getLabel()->move(m_labels[i]->getLabel()->x(), 0);
    m_game->updateScore(points);
    m_points1->setText(m_game->getScoreP1());

    //notify server that score changed

    QString message = "s,";
    m_Player->setScoreMessage(message.append(m_points1->text()).append("\n"));
    emit scoreChanged();
    //

    Word* w = new Word(m_game->nextWord(m_num), QString("white"));
    replace(m_words.begin(), m_words.end(), m_words[i], w);
    m_labels[i]->setSpeed(w->length());
    m_num++;

}

void TwoPlayerWindow::updateScore()
{
    m_points2->setText(QString::number(m_Player->getScore()));
}

//move line cause other player did combo
void TwoPlayerWindow::moveLine()
{
    if(ind){
        ind =false;
        ui->line->move(ui->line->x(), ui->line->y() - 25);
    }
}

void TwoPlayerWindow::setInd(){
    ind = true;
}

void TwoPlayerWindow::changeTime()
{
    static int time = TIMEOUT;
    time--; // decrement counter
    if (time==0) // countdown has finished
    {
        qDebug() << "Game ended!";
        time = TIMEOUT;
        ScoreWindow *sw = new ScoreWindow(ui->score1->text().toInt(), ui->score2->text().toInt());
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

void TwoPlayerWindow::resetGame()
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
    // Loading words from file
    m_game->readWords(":/data/animals.txt");
    ui->lineEdit->setText("");
    m_game->setScoreP1(0);
    m_game->setScoreP2(0);
}
