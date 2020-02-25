#ifndef OPTIONMENU_H
#define OPTIONMENU_H

#include <QPushButton>
#include <QRadioButton>
#include <QLabel>
#include <QLayout>
#include <QSpinBox>

#include <QCloseEvent>
#include <QDebug>

class OptionMenu : public QWidget //layout part
{
    Q_OBJECT
public:
    explicit OptionMenu(QWidget *parent = nullptr);

    void diffSwitch();

    //Element
    QHBoxLayout *hLayout, *dLayout;
    QVBoxLayout *vLayout;

    QRadioButton *r3x3;
    QRadioButton *r5x5;
    QRadioButton *temp;
    QFrame *line_1;

    QPushButton *switch_diff;
    QSpinBox *switch_scale;
    QPushButton *ok;

    int diff = 1;

protected:
    void closeEvent(QCloseEvent *event);

signals:
    void om_close();
    void om_change();

};

#endif // OPTIONMENU_H
