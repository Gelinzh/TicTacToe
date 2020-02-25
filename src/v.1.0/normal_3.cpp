#include "normal_3.h"

Normal_3::Normal_3(QWidget *parent) : GameImple(3, parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    switch_side = false;
}

void Normal_3::Operation()
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

void Normal_3::RandomGo()
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

void Normal_3::AnalysedGo()
{
    int go[9] = { 0 }, target = 0, temp, priority_max[9] = { 0 };
    bool isSingle = true;

    for(int i = 0; i < 9; i++) //获取优先级
    {
        if(piece[i].objectName() == "o" || piece[i].objectName() == "x")
            continue;
        go[i] = GetPriority(i);
        go[i]++;
    }

    /**=====优先级修正=====**/

    //补充，后手下棋如果对方先手下中间那么只能下四角
    if((finish == 1) && (!switch_side) && piece[4].objectName() == "o")
    {
        go[0]++; go[2]++; go[6]++; go[8]++;
    }

    //补充，后手或先手第二步尽量填在中间
    if((((finish == 2) && (switch_side)) || (!switch_side)) && piece[4].objectName() == 0)
        go[4]++;

    priority_max[0] = 1;
    for(int i = 1; i < 9; i++) //求最大优先级的位置和个数
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
            temp = (qrand() % 9);
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

int Normal_3::GetPriority(int next_move)
{
    int Checkerboard[3][3] = { {0} }, x = 0, y = 0, priority = 0, result = 0;

    //read states
    if(switch_side) //read next move's state
        Checkerboard[next_move % 3][next_move / 3] = 1;
    else
        Checkerboard[next_move % 3][next_move / 3] = 2;
    for(int i = 0; i < 9; i++) //read pieces' states
    {
        x = i % 3;
        y = i / 3;
        if(!piece[i].objectName().compare("o"))
            Checkerboard[x][y] = 1;
        else if(!piece[i].objectName().compare("x"))
            Checkerboard[x][y] = 2;
    }

    //determine priority

    for(int i = -1; i < 2; i++) //附近有我方棋子加1优先级
    {
        for(int j = -1; j < 2; j++)
        {
            if((next_move % 3 + i) > 2 || (next_move % 3 + i) < 0 || (next_move / 3 + j) > 2 || (next_move / 3 + j) < 0 || (i == 1 && j == 1))
                continue;
            if(Checkerboard[next_move % 3 + i][next_move / 3 + j] == Checkerboard[next_move % 3][next_move / 3])
                priority++;
        }
    }

    /**=====赢棋检测=====**/

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

    /**=====双杀检测=====**/

    if((finish <= 6) && (finish >= 3) && (priority < 100)) //完成度在可能出现双杀，且下一步未能直接赢棋的情况
    {
        for(int i = 0; i < 9; i++)
        {
            if(Checkerboard[i % 3][i / 3] != 0)
                continue;
            if(switch_side)
                Checkerboard[i % 3][i / 3] = 1;
            else
                Checkerboard[i % 3][i / 3] = 2;

            for (int i = 0; i < 3; i++) //check horizontal and vertical
            {
                if(Checkerboard[i][0] == Checkerboard[i][1] && Checkerboard[i][0] == Checkerboard[i][2] && Checkerboard[i][0])
                {
                    result++;
                    break;
                }
                else if (Checkerboard[0][i] == Checkerboard[1][i] && Checkerboard[0][i] == Checkerboard[2][i] && Checkerboard[0][i])
                {
                    result++;
                    break;
                }
            }
            if(Checkerboard[0][0] == Checkerboard[1][1] && Checkerboard[0][0] == Checkerboard[2][2] && Checkerboard[0][0]) //check diagonal
                result++;
            else if(Checkerboard[0][2] == Checkerboard[1][1] && Checkerboard[0][2] == Checkerboard[2][0] && Checkerboard[0][2])
                result++;

            Checkerboard[i % 3][i / 3] = 0;
        }
        if(result >= 2) //双杀加30优先级
            priority += 30;
    }
    result = 0;

    /**=====反防检测=====**/

    if(Checkerboard[next_move % 3][next_move / 3] == 1) //switch view of side
        Checkerboard[next_move % 3][next_move / 3] = 2;
    else
        Checkerboard[next_move % 3][next_move / 3] = 1;

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

    if(switch_side) //反防加60优先级
    {
        if(result == 2)
            priority += 60;
    }
    else
    {
        if(result == 1)
            priority += 60;
    }

    return priority;
}

bool Normal_3::Check()
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

void Normal_3::Again(bool isResetSide)
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
