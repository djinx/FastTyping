#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// Including Qt libraries
#include <QMainWindow>
#include <QString>
#include <QObject>
#include <QLabel>
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

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

public slots:
    void changeText(QString);
    void moveLabel();
    void changeTime();
    void showAndStart();

private:
    Ui::MainWindow *ui;
    std::vector<Word*> m_words;
    std::vector<Label*> m_labels;
    QLabel *m_time;
    QLabel *m_points;
    Game* m_game;
    unsigned m_num;

    // Timer responsible for starting a game
    QTimer *m_timerLabels;
    QTimer *m_timerTime;
};

#endif // MAINWINDOW_H
