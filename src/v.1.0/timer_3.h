#ifndef TIMER_3_H
#define TIMER_3_H

#include "gameimple.h"

#include <QTime>
#include <QTimer>
#include <QProgressBar>

class Timer_3 : public GameImple
{
    Q_OBJECT
public:
    explicit Timer_3(QWidget *parent = nullptr);

    void Operation();

    //algorithm part
    void RandomGo();
    void AnalysedGo();
    int GetPriority(int next_move);

    bool Check();
    void Again_t();
    void Again(bool isResetSide = true);

    void TimerControl(const QString &cmd);

    QTimer *Timer, *pgb_clean;
    QProgressBar *pgBar;

    bool switch_side;
    int  switch_dir = 0;

signals:

};

#endif // TIMER_3_H
