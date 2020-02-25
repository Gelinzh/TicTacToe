#include "random_3.h"

Random_3::Random_3(QWidget *parent) : GameImple(3, parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    switch_side = false;
}

void Random_3::Operation()
{
    QPushButton *temp = (QPushButton*)sender();
    if((temp->objectName() != "o") && (temp->objectName() != "x"))
    {
        if(switch_side)
        {
            temp->setObjectName("x");
            temp->setIcon(*icon_x);
        }
        else
        {
            temp->setObjectName("o");
            temp->setIcon(*icon_o);
        }
        temp->setIconSize(QSize(60, 60));
        this->sound_clicked->play();
        finish++;
        if(this->Check())
            this->RandomGo();
    }
}

void Random_3::RandomGo()
{
    int temp;
    bool rand_finish = false;

    while(!rand_finish)
    {
        temp = qrand() % 9;
        if(piece[temp].objectName() != "o" && piece[temp].objectName() != "x")
        {
            if(switch_side)
            {
                piece[temp].setObjectName("o");
                piece[temp].setIcon(*icon_o);
            }
            else
            {
                piece[temp].setObjectName("x");
                piece[temp].setIcon(*icon_x);
            }
            piece[temp].setIconSize(QSize(60, 60));
            rand_finish = true;
        }
    }
    finish++;
    this->Check();
}

bool Random_3::Check()
{
    int Checkerboard[3][3] = { {0} }, x = 0, y = 0, result = 0;

    for(int i = 0; i < 9; i++) //read pieces' states
    {
        x = i % 3;
        y = i / 3;
        if(!piece[i].objectName().compare("o"))
        {
            Checkerboard[x][y] = 1;
        }
        else if(!piece[i].objectName().compare("x"))
        {
            Checkerboard[x][y] = 2;
        }
    }

    for (int i = 0; i < 3; i++) //check horizontal and vertical
    {
        if(Checkerboard[i][0] == Checkerboard[i][1] && Checkerboard[i][0] == Checkerboard[i][2] && Checkerboard[i][0])
        {
            result = Checkerboard[i][0];
            break;
        }
        else if (Checkerboard[0][i] == Checkerboard[1][i] && Checkerboard[0][i] == Checkerboard[2][i] && Checkerboard[0][i])
        {
            result = Checkerboard[0][i];
            break;
        }
    }
    if(Checkerboard[0][0] == Checkerboard[1][1] && Checkerboard[0][0] == Checkerboard[2][2] && Checkerboard[0][0]) //check diagonal
        result = Checkerboard[0][0];
    else if(Checkerboard[0][2] == Checkerboard[1][1] && Checkerboard[0][2] == Checkerboard[2][0] && Checkerboard[0][2])
        result = Checkerboard[0][2];

    if((finish == 9) && (!result)) //reach step 9 but the result have not been concluded
        result = 3;

    if(result)
    {
        if((switch_side && result == 2) || (!switch_side && result == 1))
            msg->setWindowTitle("You Win!");
        else if((!switch_side && result == 2) || (switch_side && result == 1))
            msg->setWindowTitle("You Lost!");
        else
            msg->setWindowTitle("A Draw!");
        msg->show();
        emit gi_stop();

        return false;
    }
    else
        return true;
}

void Random_3::Again(bool isResetSide)
{
    //clean the table
    for (int i = 0; i < 9; i++)
    {
        piece[i].setObjectName(0);
        piece[i].setIcon(icon_temp);
    }
    finish = 0;

    //next round start
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    if(!isResetSide)
    {
        if(switch_side)
            switch_side = false;
        else if(!switch_side)
        {
            switch_side = true;
            RandomGo();
        }
    }
    else
        switch_side = false;
    emit gi_allow();
}
