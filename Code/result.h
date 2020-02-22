#ifndef RESULT_H
#define RESULT_H

#include <QDialog>
#include <QPushButton>

class Result : public QDialog
{
    Q_OBJECT

public:
    Result(int result, QWidget *parent = Q_NULLPTR);
    ~Result();

private:
    QPushButton *ptr_1;
    QPushButton *ptr_2;

signals:
    void s_again();
    void s_exit();

};

#endif // RESULT_H
