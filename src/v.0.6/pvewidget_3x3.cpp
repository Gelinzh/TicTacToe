#include "pvewidget_3x3.h"

PVEWidget_3x3::PVEWidget_3x3(QWidget *parent) : Widget(3, parent)
{
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));
    switch_side = false;
}

void PVEWidget_3x3::Operation()
{
    QPushButton *temp = (QPushButton*)sender();
    if((temp->windowTitle() != "o") && (temp->windowTitle() != "x"))
    {
        if(switch_side)
        {
            temp->setWindowTitle("x");
            temp->setIcon(this->GetIcon("x.png"));
        }
        else
        {
            temp->setWindowTitle("o");
            temp->setIcon(this->GetIcon("o.png"));
        }
        temp->setIconSize(QSize(60, 60));
        this->GetSound("clicked.wav").play();
        finish++;
        if(this->Check())
            this->AnalysedGo();
    }
}

void PVEWidget_3x3::RandomGo()
{
    int temp;
    bool rand_finish = false;

    while(!rand_finish)
    {
        temp = qrand() % 9;
        qDebug() << "randnum : "<< temp;
        if(piece[temp].windowTitle() != "o" && piece[temp].windowTitle() != "x")
        {
            if(switch_side)
            {
                piece[temp].setWindowTitle("o");
                piece[temp].setIcon(this->GetIcon("o.png"));
            }
            else
            {
                piece[temp].setWindowTitle("x");
                piece[temp].setIcon(this->GetIcon("x.png"));
            }
            piece[temp].setIconSize(QSize(60, 60));
            rand_finish = true;
        }
    }
    finish++;
    this->Check();
}

void PVEWidget_3x3::AnalysedGo()
{
    int go[9] = { 0 }, target = 0, temp, priority_max[9] = { 0 };
    bool isSingle = true;

    for(int i = 0; i < 9; i++) //获取优先级
    {
        if(piece[i].windowTitle() == "o" || piece[i].windowTitle() == "x")
            continue;
        go[i] = GetPriority(i);
        go[i]++;
    }

    /**=====优先级修正=====**/

    //补充，后手下棋如果对方先手下中间那么只能下四角
    if((finish == 1) && (!switch_side) && piece[4].windowTitle() == "o")
    {
        go[0]++; go[2]++; go[6]++; go[8]++;
    }

    //补充，后手或先手第二步尽量填在中间
    if((((finish == 2) && (switch_side)) || (!switch_side)) && piece[4].windowTitle() == 0)
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
        piece[target].setWindowTitle("o");
        piece[target].setIcon(this->GetIcon("o.png"));
    }
    else
    {
        piece[target].setWindowTitle("x");
        piece[target].setIcon(this->GetIcon("x.png"));
    }
    piece[target].setIconSize(QSize(60, 60));

    finish++;
    if(go[target] >= 100) //如果优先级大于等于100，就说明电脑赢了，就不必再check一遍了
    {
        if(switch_side)
            msg = new Result(1, this);
        else
            msg = new Result(2, this);
        msg->setWindowTitle("You Lost!");
        msg->setModal(true);
        msg->show();

        connect(msg, &Result::s_again, this, &PVEWidget_3x3::Again);
        connect(msg, &Result::s_exit, this, &PVEWidget_3x3::close);
    }
    else
        this->Check();
}

int PVEWidget_3x3::GetPriority(int next_move)
{
    int Checkerboard[3][3] = { {0} }, x = 0, y = 0, priority = 0, result = 0;

    //read states
    if(switch_side) //read next move's state
        Checkerboard[next_move % 3][next_move / 3] = 1;
    else
        Checkerboard[next_move % 3][next_move / 3] = 2;
    for(int i = 0; i < 9; i++, x++) //read pieces' states
    {
        if(x == 3) x = 0;
        if(!(i % 3)&&(i != 0)) y++;
        if(!piece[i].windowTitle().compare("o"))
            Checkerboard[x][y] = 1;
        else if(!piece[i].windowTitle().compare("x"))
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

bool PVEWidget_3x3::Check()
{
    int Checkerboard[3][3] = { {0} }, x = 0, y = 0, result = 0;

    for(int i = 0; i < 9; i++, x++) //read pieces' states
    {
        if(x == 3) x = 0;
        if(!(i % 3)&&(i != 0)) y++;
        if(!piece[i].windowTitle().compare("o"))
        {
            Checkerboard[x][y] = 1;
        }
        else if(!piece[i].windowTitle().compare("x"))
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
        msg = new Result(result, this);

        if((switch_side && result == 2) || (!switch_side && result == 1))
            msg->setWindowTitle("You Win!");
        else if((!switch_side && result == 2) || (switch_side && result == 1))
            msg->setWindowTitle("You Lost!");
        msg->setModal(true);
        msg->show();

        connect(msg, &Result::s_again, this, &PVEWidget_3x3::Again);
        connect(msg, &Result::s_exit, this, &PVEWidget_3x3::close);

        return false;
    }
    else
        return true;
}

void PVEWidget_3x3::Again()
{
    //clean the table
    for (int i = 0; i < 9; i++)
    {
        piece[i].setWindowTitle(0);
        piece[i].setIcon(this->GetIcon());
    }
    finish = 0;

    //next round start
    qsrand(QTime(0, 0, 0).secsTo(QTime::currentTime()));

    if(switch_side)
        switch_side = false;
    else if(!switch_side)
    {
        switch_side = true;
        RandomGo();
    }
}
