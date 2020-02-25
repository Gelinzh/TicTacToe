#include "random_5.h"

Random_5::Random_5(QWidget *parent) : GameImple(5, parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    switch_side = false;
}

void Random_5::Operation()
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
            this->AnalysedGo();
    }
}

void Random_5::RandomGo()
{
    int temp;
    bool rand_finish = false;

    while(!rand_finish)
    {
        temp = qrand() % 25;
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

void Random_5::AnalysedGo()
{
    int go[25] = { 0 }, target = 0, temp, priority_max[25] = { 0 };
    bool isSingle = true;

    for(int i = 0; i < 25; i++) //获取优先级
    {
        if(piece[i].objectName() == "o" || piece[i].objectName() == "x")
            continue;
        go[i] = GetPriority(i);
        go[i]++;
    }

    priority_max[0] = 1;
    for(int i = 1; i < 25; i++) //求最大优先级的位置和个数
    {
        if(go[i] > go[target])
        {
            target = i;
            memset(priority_max, 0, sizeof(priority_max));
            priority_max[i]++;
            isSingle = true;
        }
        else if(go[i] == go[target])
        {
            priority_max[i]++;
            isSingle = false;
        }
    }

    if(!isSingle) //考虑到可能优先级最大有数个，随机选一个
    {
        while (true)
        {
            temp = (qrand() % 25);
            if(priority_max[temp] == 0)
                continue;
            else
            {
                target = temp;
                break;
            }
        }
    }

    if(switch_side) //下棋
    {
        piece[target].setObjectName("o");
        piece[target].setIcon(*icon_o);
    }
    else
    {
        piece[target].setObjectName("x");
        piece[target].setIcon(*icon_x);
    }
    piece[target].setIconSize(QSize(60, 60));

    finish++;
    if(go[target] >= 100) //如果优先级大于等于100，就说明电脑赢了，就不必再check一遍了
    {
        msg->setWindowTitle("You Lost!");
        msg->show();
        emit gi_stop();
    }
    else
        this->Check();
}

int Random_5::GetPriority(int next_move)
{
    int Checkerboard[5][5] = { {0} }, x = 0, y = 0, priority = 0, result = 0;

    for(int i = 0; i < 25; i++) //read pieces' states
    {
        x = i % 5;
        y = i / 5;
        if(!piece[i].objectName().compare("o"))
            Checkerboard[x][y] = 1;
        else if(!piece[i].objectName().compare("x"))
            Checkerboard[x][y] = 2;
    }

    /**=====赢棋检测=====**/

    if(switch_side) //set next move's position
        Checkerboard[next_move % 5][next_move / 5] = 1;
    else
        Checkerboard[next_move % 5][next_move / 5] = 2;

    result = CheckerBoard(Checkerboard);

    if(switch_side) //能赢加100优先级，直接跳过双杀检测
    {
        if(result == 1)
            priority += 100;
    }
    else
    {
        if(result == 2)
            priority += 100;
    }
    result = 0;

    /*=====附近棋子检测=====*/

    for(int i = -1; i < 2; i++) //附近有我方棋子加2优先级，有敌方则加1
    {
        for(int j = -1; j < 2; j++)
        {
            if(((next_move % 5) + i) > 4 || ((next_move % 5) + i) < 0 || ((next_move / 5) + j) > 4 || ((next_move / 5) + j) < 0 || (i == 0 && j == 0))
                continue;

            if((switch_side && Checkerboard[(next_move % 5) + i][(next_move / 5) + j] == 1) ||
              (!switch_side && Checkerboard[(next_move % 5) + i][(next_move / 5) + j] == 2))
                priority ++;
            else if((switch_side && Checkerboard[(next_move % 5) + i][(next_move / 5) + j] == 2) ||
                   (!switch_side && Checkerboard[(next_move % 5) + i][(next_move / 5) + j] == 1))
            {
                if(!i || !j)
                    priority += 3;
                else
                    priority += 2;
            }
        }
    }

    return priority;
}

bool Random_5::Check()
{
    int Checkerboard[5][5] = { {0} }, x = 0, y = 0, result = 0;

    for(int i = 0; i < 5 * 5; i++) //read pieces' states
    {
        x = i % 5;
        y = i / 5;
        if(!piece[i].objectName().compare("o"))
        {
            Checkerboard[x][y] = 1;
        }
        else if(!piece[i].objectName().compare("x"))
        {
            Checkerboard[x][y] = 2;
        }
    }

    result = CheckerBoard(Checkerboard);

    if((finish == 25) && (!result)) //reach step 9 but the result have not been concluded
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

int Random_5::CheckerBoard(int Checkerboard[5][5])
{
    int result;

    for(int i = 0; i < 5; i++) //check horizontal and vertical
    {
        for(int j = 0; j < 4; j++) //horizon
        {
            if(Checkerboard[j][i] == Checkerboard[j + 1][i] && Checkerboard[0][i])
            {
                if(j == 3)
                    result = Checkerboard[0][i];
            }
            else
                break;
        }
        if(result)
            break;
        for(int j = 0; j < 4; j++) //vertical
        {
            if(Checkerboard[i][j] == Checkerboard[i][j + 1] && Checkerboard[i][0])
            {
                if(j == 3)
                    result = Checkerboard[i][0];
            }
            else
                break;
        }
        if(result)
            break;
    }

    for(int i = 0; i < 4; i++) //diagonal
    {
        if(Checkerboard[i][i] == Checkerboard[i + 1][i + 1] && Checkerboard[0][0])
        {
            if(i == 3)
                result = Checkerboard[0][0];
        }
        else
            break;
    }

    for (int i = 0; i < 4; i++) //diagonal - another one
    {
        if(Checkerboard[5 - i - 1][i] == Checkerboard[5 - i - 2][i + 1] && Checkerboard[5 - i - 1][i])
        {
            if(i == 3)
                result = Checkerboard[0][0];
        }
        else
            break;
    }
    return result;
}

void Random_5::Again(bool isResetSide)
{
    //clean the table
    for (int i = 0; i < 25; i++)
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


