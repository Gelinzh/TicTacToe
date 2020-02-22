#include "widget.h"

Widget::Widget(int fp_pieceScale, QWidget *parent)
    : QWidget(parent)
{
    //get path
//    dir = QCoreApplication::applicationDirPath();

    //initialize
    this->setWindowTitle("TicTacToe");                                        //title
    this->setFixedSize(fp_pieceScale * 100, fp_pieceScale * 100);             //frame size
    this->finish  =  0;                                                       //step to a draw
    this->InitPiece(fp_pieceScale);
    this->InitMedia();
}

Widget::~Widget()
{
}

void Widget::Operation()
{
    //virtual function waiting to be replaced.
}

void Widget::InitPiece(int pieceScale)
{
    this->piece   =  new QPushButton[pieceScale * pieceScale];                                      //piece to place
    for(int i = 0, j = 0, k = 0; i < (pieceScale * pieceScale); i++, k++)
    {
        if(!(i % pieceScale)&&(i != 0)) j++;
        if(k == pieceScale) k = 0;
        piece[i].setParent(this);
        piece[i].setFixedSize(100, 100);
//        piece[i].setFont(*font);
        piece[i].move(k * 100,j * 100);
        connect(&piece[i], &QPushButton::clicked, this, &Widget::Operation);
    }
}

void Widget::InitMedia()
{
    this->sound   =  new QMediaPlayer;
    this->sound->setMedia(QUrl("asset/sounds/clicked.wav"));
    this->sound->setVolume(100);
    icon_o.addFile("asset/image/o.png");
    icon_x.addFile("asset/image/x.png");

    //    font    =  new QFont;
    //    font->setPointSize(25);
    //    font->setBold(true);
}

QIcon &Widget::GetIcon(QString iconName)
{
    if(iconName == "o.png")
        return icon_o;
    else if(iconName == "x.png")
        return icon_x;
    else
        return icon_temp;
}

QMediaPlayer &Widget::GetSound(QString soundName)
{
    if(soundName == "clicked.wav")
        return *sound;
    else
        return sound_temp;
}



