#include "optionmenu.h"

OptionMenu::OptionMenu(QWidget *parent) : QWidget(parent)
{

    /*=====New=====*/

    //--new Layout
    hLayout = new QHBoxLayout;
    dLayout = new QHBoxLayout;
    vLayout = new QVBoxLayout;

    //--new hLayout
    r3x3 = new QRadioButton;
    r5x5 = new QRadioButton;
    temp = new QRadioButton;
    line_1 = new QFrame;

    //--new dLayout
    //diff part
    switch_diff  = new QPushButton("Random");
    //scale part
    switch_scale = new QSpinBox;
    //ok part
    ok           = new QPushButton;

    /*=====Setting=====*/

    //--hLayout
    r3x3->setFixedSize(100, 100);
    r3x3->setChecked(true);
    r5x5->setFixedSize(100, 100);
    temp->setVisible(false);

    //scale
    switch_scale->setFixedSize(35, 21);
    switch_scale->setMinimum(3);
    switch_scale->setMaximum(9);
    switch_scale->setEnabled(false);
    ok->setText("OK");

    //--integrate and vLayout
    line_1->setFrameShape(QFrame::VLine);
    line_1->setFixedSize(20, 100);

    hLayout->addStretch(1);
    hLayout->addWidget(r3x3);
    hLayout->addWidget(line_1);
    hLayout->addWidget(r5x5);
    hLayout->addWidget(temp);
    hLayout->addStretch(1);


    dLayout->addStretch(1);
    dLayout->addWidget(ok);
    dLayout->addWidget(switch_diff);
    dLayout->addWidget(switch_scale);
    dLayout->addStretch(1);

    vLayout->addLayout(hLayout);
    vLayout->addLayout(dLayout);

    this->setLayout(vLayout);

    connect(switch_diff, &QPushButton::clicked, this, &OptionMenu::diffSwitch);

    connect(ok, &QPushButton::clicked, [this]()
    {
        emit om_change();
        this->close();
    });
}

void OptionMenu::diffSwitch()
{
    if(++diff == 4)
        diff = 0;
    switch (diff)
    {
    case 0:
    {
        switch_diff->setText("Random");
        r3x3->setChecked(true);
        r3x3->setEnabled(true);
        r5x5->setEnabled(true);
        switch_scale->setEnabled(false);
        break;
    }
    case 1:
    {
        switch_diff->setText("Normal");
        break;
    }
    case 2:
    {
        switch_diff->setText("Timer");
        r3x3->setChecked(true);
        r5x5->setEnabled(false);
        break;
    }
    case 3:
    {
        switch_diff->setText("Custom");
        temp->setChecked(true);
        r3x3->setEnabled(false);
        switch_scale->setEnabled(true);
        break;
    }
    default:
        break;
    }
}

void OptionMenu::closeEvent(QCloseEvent *event)
{
    emit om_close();
    event->accept();
}
