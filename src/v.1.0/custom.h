#ifndef CUSTOM_H
#define CUSTOM_H

#include "gameimple.h"

class Custom : public GameImple
{
    Q_OBJECT
public:
    explicit Custom(int size_in, QWidget *parent = nullptr);

    void Operation();

    bool Check();
    void Again(bool isResetSide = true);

    int size;
    bool switch_side;

signals:

};

#endif // CUSTOM_H
