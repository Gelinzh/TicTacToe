#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QApplication>
#include <QPushButton>
#include <QtMultimedia/QMediaPlayer>
//#include <QSound>

#include "result.h"

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(int fp_pieceScale, QWidget *parent = nullptr);
    ~Widget();

    virtual void Operation();

    //Setters
    void InitPiece(int pieceScale);
    void InitMedia();

    //Getters
    QIcon &GetIcon(QString iconName = "null");
    QMediaPlayer &GetSound(QString soundName);

    //Elements
    QPushButton *piece;
    Result *msg;
    int finish;

private:
    QIcon icon_x, icon_o, icon_temp;
    QMediaPlayer *sound, sound_temp;
//    QFont *font;

};
#endif // WIDGET_H
