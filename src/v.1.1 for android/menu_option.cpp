#include "menu_option.h"

Menu_OPTION::Menu_OPTION(int &rwidth, int &rheight, QWidget *parent) : QWidget(parent)
{
    width = rwidth;
    height = rheight;

    InitMedia();
    InitGUI();

    connect(back, &QPushButton::clicked, [this]()
    {
        emit switch_back();
    });

    connect(time_slider, &QSlider::valueChanged, [this]()
    {
        emit timer_changed();
    });

    connect(volume_checkbox, &QCheckBox::stateChanged, [this]()
    {
        emit volume_changed();
    });

    connect(switch_checkbox, &QCheckBox::stateChanged, [this]()
    {
        emit switch_changed();
    });
}

void Menu_OPTION::InitMedia()
{
    this->arrow_r = new QIcon(":/assets/image/arrow_r.png");
    this->pix_timer = new QPixmap(":/assets/image/timer.png");
    this->pix_volume = new QPixmap(":/assets/image/volume.png");
    this->pix_volume_down = new QPixmap(":/assets/image/volume_down.png");
    this->pix_switch = new QPixmap(":/assets/image/switch.png");
}

void Menu_OPTION::InitGUI()
{
    this->setFixedSize(width, height);
    this->setStyleSheet("Menu_OPTION {background-color: #ffffff;}");

    this->option_title_bar = new QToolBar(this);
    this->option_title_bar->setFixedSize(width * 0.9,  (height / 2) - (width * 0.45) - 100);
    this->option_title_bar->setMovable(false);
    this->option_title_bar->setContextMenuPolicy(Qt::PreventContextMenu);
    this->option_title_bar->move(width * 0.05, 300);
    this->option_title_bar->setStyleSheet("QToolBar {background-color: #f5f5f5;}"
                                          "QToolBar::separator {width: 3px;}"
                                          "QToolBar::separator {background-color: #c1c1c1;}");

    QFont *font_t = new QFont;
    font_t->setFamily("Arial");
    font_t->setPointSize(25);
    this->option_title = new QLabel;
    this->option_title->setFont(*font_t);
    this->option_title->setText("  SETTING");
    this->option_title->setAlignment(Qt::AlignCenter);
    this->option_title->setStyleSheet("QLabel {color: #5f5f5f;}");

    this->back = new QPushButton;
    this->back->setFixedSize(200, 200);
    this->back->setIcon(*arrow_r);
    this->back->setIconSize(QSize(128, 128));
    this->back->setStyleSheet("QPushButton {border-image: url(:/assets/image/piece.png);}");

    QWidget *spacer_1 = new QWidget;
    spacer_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->option_title_bar->addWidget(option_title);
    this->option_title_bar->addWidget(spacer_1);
    this->option_title_bar->addWidget(back);

    //---------------------------------------------------------------------------------------------//

    this->tb_time = new QToolBar(this);
    this->tb_time->setFixedSize(width * 0.9, 200);
    this->tb_time->setMovable(false);
    this->tb_time->setContextMenuPolicy(Qt::PreventContextMenu);
    this->tb_time->move(width * 0.05, (height / 2) - (width * 0.45) + 210);
    this->tb_time->setStyleSheet("QToolBar {background-color: #e1e1e1;}"
                                 "QToolBar::separator {width: 3px;}"
                                 "QToolBar::separator {background-color: #c1c1c1;}");

    this->l_time = new QLabel;
    this->l_time->setFixedSize(128, 128);
    this->l_time->setPixmap(*pix_timer);
    this->l_time->setScaledContents(true);
    this->time_slider = new QSlider;
    this->time_slider->setFixedSize(width * 0.6, 200);
    this->time_slider->setOrientation(Qt::Horizontal);
    this->time_slider->setRange(4, 10);
    this->time_slider->setValue(5);
    this->time_slider->setStyleSheet(
    "QSlider::groove:horizontal {border: 1px solid #c1c1c1; height: 10px; background: #f1f1f1f1;}"
    "QSlider::handle:horizontal {width: 30px; background: #f1f1f1; margin: -50px 0;}");

    QWidget *spacer_2 = new QWidget, *spacer_3 = new QWidget, *spacer_4 = new QWidget, *spacer_5 = new QWidget,
            *spacer_6 = new QWidget, *spacer_7 = new QWidget, *spacer_8 = new QWidget, *spacer_9 = new QWidget,
            *spacer_0 = new QWidget, *spacer_a = new QWidget, *spacer_b = new QWidget, *spacer_c = new QWidget;
    spacer_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_6->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_7->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_8->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_9->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_0->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_a->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_b->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_c->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->tb_time->addWidget(spacer_2);
    this->tb_time->addWidget(l_time);
    this->tb_time->addWidget(spacer_3);
    this->tb_time->addSeparator();
    this->tb_time->addWidget(spacer_4);
    this->tb_time->addWidget(time_slider);
    this->tb_time->addWidget(spacer_5);

    this->tb_volume = new QToolBar(this);
    this->tb_volume->setFixedSize(width * 0.9, 200);
    this->tb_volume->setMovable(false);
    this->tb_volume->setContextMenuPolicy(Qt::PreventContextMenu);
    this->tb_volume->move(width * 0.05, (height / 2) - (width * 0.45) + 415);
    this->tb_volume->setStyleSheet("QToolBar {background-color: #e1e1e1;}"
                                   "QToolBar::separator {width: 3px;}"
                                   "QToolBar::separator {background-color: #c1c1c1;}");

    this->l_volume = new QLabel;
    this->l_volume->setFixedSize(128, 128);
    this->l_volume->setPixmap(*pix_volume);
    this->l_volume->setScaledContents(true);

    this->volume_checkbox = new QCheckBox;
    this->volume_checkbox->setFixedSize(200, 200);
    this->volume_checkbox->setStyleSheet("QCheckBox::indicator {width: 180px; height: 180px;}"
                                         "QCheckBox::indicator:unchecked {image: url(:/assets/image/checkbox-checked.png);}"
                                         "QCheckBox::indicator:checked {image: url(:/assets/image/checkbox-unchecked.png);}");

    QWidget *controller_1 = new QWidget;
    controller_1->setFixedSize(width * 0.6 - 200, 200);
    this->tb_volume->addWidget(spacer_6);
    this->tb_volume->addWidget(l_volume);
    this->tb_volume->addWidget(spacer_7);
    this->tb_volume->addSeparator();
    this->tb_volume->addWidget(spacer_8);
    this->tb_volume->addWidget(controller_1);
    this->tb_volume->addWidget(volume_checkbox);
    this->tb_volume->addWidget(spacer_9);

    this->tb_switch = new QToolBar(this);
    this->tb_switch->setFixedSize(width * 0.9, 200);
    this->tb_switch->setMovable(false);
    this->tb_switch->setContextMenuPolicy(Qt::PreventContextMenu);
    this->tb_switch->move(width * 0.05, (height / 2) - (width * 0.45) + 620);
    this->tb_switch->setStyleSheet("QToolBar {background-color: #e1e1e1;}"
                                   "QToolBar::separator {width: 3px;}"
                                   "QToolBar::separator {background-color: #c1c1c1;}");

    this->l_switch = new QLabel;
    this->l_switch->setFixedSize(128, 128);
    this->l_switch->setPixmap(*pix_switch);
    this->l_switch->setScaledContents(true);

    this->switch_checkbox = new QCheckBox;
    this->switch_checkbox->setFixedSize(200, 200);
    this->switch_checkbox->setStyleSheet("QCheckBox::indicator {width: 180px; height: 180px;}"
                                         "QCheckBox::indicator:unchecked {image: url(:/assets/image/checkbox-unchecked.png);}"
                                         "QCheckBox::indicator:checked {image: url(:/assets/image/checkbox-checked.png);}");

    QWidget *controller_2 = new QWidget;
    controller_2->setFixedSize(width * 0.6 - 200, 200);
    this->tb_switch->addWidget(spacer_0);
    this->tb_switch->addWidget(l_switch);
    this->tb_switch->addWidget(spacer_a);
    this->tb_switch->addSeparator();
    this->tb_switch->addWidget(spacer_b);
    this->tb_switch->addWidget(controller_2);
    this->tb_switch->addWidget(switch_checkbox);
    this->tb_switch->addWidget(spacer_c);

}
