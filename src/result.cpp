#include "result.h"

Result::Result(int result, QWidget *parent) : QDialog(parent)
{
    this->setFixedSize(200, 100);
    if(result == 1)
        this->setWindowTitle("\"o\" won the game");
    else if(result == 2)
        this->setWindowTitle("\"x\" won the game");
    else if(result == 3)
        this->setWindowTitle("A Draw!");
    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::WindowTitleHint;
    this->setWindowFlags(flags);
    ptr_1 = new QPushButton(this);
    ptr_1->setText("Again");
    ptr_1->setFixedSize(60, 20);
    ptr_1->move(30, 40);
    ptr_2 = new QPushButton(this);
    ptr_2->setText("Exit");
    ptr_2->setFixedSize(60, 20);
    ptr_2->move(110, 40);

    connect(ptr_1, &QPushButton::clicked, [this]() //C++11 Lambda
    {
        emit s_again();
        this->close();
    });
    connect(ptr_2, &QPushButton::clicked, [this]()
    {
        emit s_exit();
        this->close();
    });
}

Result::~Result()
{
    delete ptr_1;
    delete ptr_2;
}
