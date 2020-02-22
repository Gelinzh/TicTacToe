#include "pvpwidget_3x3.h"

PVPWidget_3x3::PVPWidget_3x3(QWidget *parent) : Widget(3, parent)
{
    this->player  =  true;                                                    //switch side
}

void PVPWidget_3x3::Operation()
{
    QPushButton *temp = (QPushButton*)sender();
    if((temp->windowTitle() != "o") && (temp->windowTitle() != "x"))
    {
        if(player)
        {
            temp->setWindowTitle("o");
            temp->setIcon(this->GetIcon("o.png"));
            player = false;
        }
        else
        {
            temp->setWindowTitle("x");
            temp->setIcon(this->GetIcon("x.png"));
            player = true;
        }
        temp->setIconSize(QSize(60, 60));
        //QSound::play(dir + "/asset/sounds/clicked.wav");
        this->GetSound("clicked.wav").play();
        finish++;

        //Check
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
            msg->setModal(true);
            msg->show();

            connect(msg, &Result::s_again, this, &PVPWidget_3x3::Again);
            connect(msg, &Result::s_exit, this, &PVPWidget_3x3::close);
        }
    }
}

void PVPWidget_3x3::Again()
{
    for (int i = 0; i < 9; i++)
    {
        piece[i].setWindowTitle(0);
        piece[i].setIcon(this->GetIcon());
    }
    player = true;
    finish = 0;
}
