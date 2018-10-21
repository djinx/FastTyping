#ifndef TWOPLAYERWINDOW_H
#define TWOPLAYERWINDOW_H

// Including Qt libraries
#include <QWidget>
#include <QString>
#include <QObject>
#include <QLabel>
#include <QLineEdit>
#include <QThread>
#include <QTimer>
#include <QFile>
#include <QTextStream>
#include <QDebug>
#include <QPushButton>
#include <QStyle>
#include <QDesktopWidget>

// Including STD C++ libraries
#include <vector>
#include <fstream>
#include <algorithm>
#include <string>
#include <iterator>
#include <random>
#include <cstdlib>

// Including STD C libraries
#include <time.h>

// Including project classes
class Word;
class Game;
class Label;
class Player;

namespace Ui {
class TwoPlayerWindow;
}

class TwoPlayerWindow : public QWidget
{
    Q_OBJECT

public:
    explicit TwoPlayerWindow(Player *player, QWidget *parent = 0);
    ~TwoPlayerWindow();

    // Set methods
    void addWord(Word* word);
    void addLabel(QLabel* label);

    // Color parts of every word that is typed in lineEdit
    void colorWords(QString text);

    // Shows five labels
    void showFive();
    void hideAll();
    void update(int i, int points);
    void moveLine();
    void resetGame();

    // number of hidden labels
    int numOfHidden();

signals:
    void scoreChanged();
    void LEGENDARY();

public slots:
    void changeText(QString);
    void moveLabel();
    void changeTime();
    void showAndStart();
    void updateScore();
    void setInd();

private:
    Ui::TwoPlayerWindow *ui;
    std::vector<Word*> m_words;
    std::vector<Label*> m_labels;
    QLabel *m_time;
    QLineEdit *m_points1;
    QLineEdit *m_points2;
    Game* m_game;
    unsigned m_num;
    Player *m_Player;

    // Timer responsible for starting a game
    QTimer *m_timerLabels;
    QTimer *m_timerTime;
};

#endif // TWOPLAYERWINDOW_H
