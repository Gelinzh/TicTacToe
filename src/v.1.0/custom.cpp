#include "custom.h"

Custom::Custom(int size_in, QWidget *parent) : GameImple(size_in, parent), size(size_in)
{
    switch_side = false;
}

void Custom::Operation()
{
    QPushButton *temp = (QPushButton*)sender();
    if((temp->objectName() != "o") && (temp->objectName() != "x"))
    {
        if(switch_side)
        {
            temp->setObjectName("x");
            temp->setIcon(*icon_x);
            switch_side = false;
        }
        else
        {
            temp->setObjectName("o");
            temp->setIcon(*icon_o);
            switch_side = true;
        }
        temp->setIconSize(QSize(60, 60));
        this->sound_clicked->play();
        finish++;
        Check();
    }
}

bool Custom::Check()
{
    int x = 0, y = 0, result = 0;
    int **Checkerboard = new int *[size];
    for(int i = 0; i < size; i++)
        Checkerboard[i] = new int [size]();

    for(int i = 0; i < size * size; i++) //read pieces' states
    {
        x = i % size;
        y = i / size;
        if(!piece[i].objectName().compare("o"))
        {
            Checkerboard[x][y] = 1;
        }
        else if(!piece[i].objectName().compare("x"))
        {
            Checkerboard[x][y] = 2;
        }
    }

    for(int i = 0; i < size; i++) //check horizontal and vertical
    {
        for(int j = 0; j < size - 1; j++) //horizon
        {
            if(Checkerboard[j][i] == Checkerboard[j + 1][i] && Checkerboard[0][i])
            {
                if(j == size - 2)
                    result = Checkerboard[0][i];
            }
            else
                break;
        }
        if(result)
            break;
        for(int j = 0; j < size - 1; j++) //vertical
        {
            if(Checkerboard[i][j] == Checkerboard[i][j + 1] && Checkerboard[i][0])
            {
                if(j == size - 2)
                    result = Checkerboard[i][0];
            }
            else
                break;
        }
        if(result)
            break;
    }

    for(int i = 0; i < size - 1; i++) //diagonal
    {
        if(Checkerboard[i][i] == Checkerboard[i + 1][i + 1] && Checkerboard[0][0])
        {
            if(i == size - 2)
                result = Checkerboard[0][0];
        }
        else
            break;
    }

    for (int i = 0; i < size - 1; i++) //diagonal - another one
    {
        if(Checkerboard[size - i - 1][i] == Checkerboard[size - i - 2][i + 1] && Checkerboard[size - i - 1][i])
        {
            if(i == size - 2)
                result = Checkerboard[0][0];
        }
        else
            break;
    }

    if((finish == size * size) && (!result)) //reach step 9 but the result have not been concluded
        result = 3;

    //delete checkerboard
    for(int i = 0; i < size; i++)
        delete[] Checkerboard[i];
    delete[] Checkerboard;

    if(result)
    {
        if(result == 1)
            msg->setWindowTitle("\"O\" Win!");
        else if(result == 2)
            msg->setWindowTitle("\"X\" Win!");
        else
            msg->setWindowTitle("A Draw!");
        msg->show();
        emit gi_stop();

        return false;
    }
    else
        return true;
}

void Custom::Again(bool isResetSide)
{
    //clean the table
    for (int i = 0; i < size * size; i++)
    {
        piece[i].setObjectName(0);
        piece[i].setIcon(icon_temp);
    }
    finish = 0;

    //next round start
    if(!isResetSide)
    {
        if(switch_side)
            switch_side = false;
        else if(!switch_side)
            switch_side = true;
    }
    else
        switch_side = false;
    emit gi_allow();
}
