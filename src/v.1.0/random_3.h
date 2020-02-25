#ifndef RANDOM_3_H
#define RANDOM_3_H

#include "gameimple.h"

#include <QTime>

class Random_3 : public GameImple
{
    Q_OBJECT
public:
    explicit Random_3(QWidget *parent = nullptr);

    void Operation();

    //algorithm part
    void RandomGo();

    bool Check();
    void Again(bool isResetSide = false);


    bool switch_side;

signals:

};

#endif // RANDOM_3_H
