#ifndef SCOREWINDOW_H
#define SCOREWINDOW_H

#include <QWidget>
#include <QStyle>
#include <QDesktopWidget>

class MainMenu;

namespace Ui {
class ScoreWindow;
}

class ScoreWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ScoreWindow(int score1, int score2, QWidget *parent = 0);
    ~ScoreWindow();

    void setPartner();

private:
    Ui::ScoreWindow *ui;
    MainMenu *m_Partner;
};

#endif // SCOREWINDOW_H
