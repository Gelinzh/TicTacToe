#include "menu_about.h"

Menu_ABOUT::Menu_ABOUT(int &rwidth, int &rheight, QWidget *parent) : QWidget(parent)
{
    width = rwidth;
    height = rheight;

    InitMedia();
    InitGUI();

    connect(back, &QPushButton::clicked, [this]()
    {
        emit switch_back();
    });

}

void Menu_ABOUT::InitMedia()
{
    this->arrow_l = new QIcon(":/assets/image/arrow_l.png");
    this->logo = new QPixmap(":/assets/image/logo.png");
}

void Menu_ABOUT::InitGUI()
{
    this->setFixedSize(width, height);
    this->setStyleSheet("Menu_ABOUT {background-color: #ffffff;}");

    this->about_title_bar = new QToolBar(this);
    this->about_title_bar->setFixedSize(width * 0.9,  (height / 2) - (width * 0.45) - 100);
    this->about_title_bar->setMovable(false);
    this->about_title_bar->setContextMenuPolicy(Qt::PreventContextMenu);
    this->about_title_bar->move(width * 0.05, 300);
    this->about_title_bar->setStyleSheet("QToolBar {background-color: #f5f5f5;}"
                                         "QToolBar::separator {width: 3px;}"
                                         "QToolBar::separator {background-color: #c1c1c1;}");

    QFont *font_t = new QFont;
    font_t->setFamily("Arial");
    font_t->setPointSize(25);
    this->about_title = new QLabel;
    this->about_title->setFont(*font_t);
    this->about_title->setText("  ABOUT");
    this->about_title->setAlignment(Qt::AlignCenter);
    this->about_title->setStyleSheet("QLabel {color: #5f5f5f;}");

    this->back = new QPushButton;
    this->back->setFixedSize(200, 200);
    this->back->setIcon(*arrow_l);
    this->back->setIconSize(QSize(128, 128));
    this->back->setStyleSheet("QPushButton {border-image: url(:/assets/image/piece.png);}");

    QWidget *spacer_1 = new QWidget;
    spacer_1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    this->about_title_bar->addWidget(about_title);
    this->about_title_bar->addWidget(spacer_1);
    this->about_title_bar->addWidget(back);

    //-----------------------------------------------------//

    this->l_logo = new QLabel;
    this->l_logo->setFixedSize(256, 256);
    this->l_logo->setPixmap(*logo);
    this->l_logo->setScaledContents(true);

    QFont *projectFont = new QFont, *normalFont = new QFont;
    projectFont->setFamily("Arial");
    projectFont->setBold(true);
    projectFont->setPointSize(20);
    normalFont->setFamily("Arial");
    normalFont->setPointSize(12);
    this->l_title = new QLabel;
    this->l_title->setText("TicTacToe 1.1");
    this->l_title->setFont(*projectFont);
    this->l_title->setStyleSheet("QLabel {color: #5f5f5f;}");
    this->l_date = new QLabel;
    this->l_date->setText("Built On 2020.02.29");
    this->l_date->setFont(*normalFont);
    this->l_date->setStyleSheet("QLabel {color: #888888;}");
    this->l_author = new QLabel;
    this->l_author->setText("Written By Acelych");
    this->l_author->setFont(*normalFont);
    this->l_author->setStyleSheet("QLabel {color: #888888;}");

    this->vLayout = new QVBoxLayout;
    this->vLayout->addStretch(3);
    this->vLayout->addWidget(l_title);
    this->vLayout->addStretch(1);
    this->vLayout->addWidget(l_date);
    this->vLayout->addWidget(l_author);
    this->vLayout->addStretch(4);

    this->hLayout = new QHBoxLayout;
    this->hLayout->addStretch(3);
    this->hLayout->addWidget(l_logo);
    this->hLayout->addStretch(3);
    this->hLayout->addLayout(vLayout);
    this->hLayout->addStretch(4);

    this->info = new QWidget(this);
    this->info->setLayout(hLayout);
    this->info->setFixedSize(width * 0.9, width * 0.45);
    this->info->setStyleSheet("QWidget {background-color: #e1e1e1;}");
    this->info->move(width * 0.05, (height / 2) - (width * 0.45) + 210);

    this->tb_link = new QToolBar(this);
    this->tb_link->setFixedSize(width * 0.9, 150);
    this->tb_link->setMovable(false);
    this->tb_link->setContextMenuPolicy(Qt::PreventContextMenu);
    this->tb_link->move(width * 0.05, (height / 2) + 215);
    this->tb_link->setStyleSheet("QToolBar {background-color: #e1e1e1;}"
                                 "QToolBar::separator {width: 3px;}"
                                 "QToolBar::separator {background-color: #c1c1c1;}");

    this->b_github = new QPushButton;
    this->b_github->setFixedSize(80, 80);
    this->b_github->setStyleSheet("QPushButton {width: 80px; height: 80px; border-image: url(:/assets/image/github_logo.png);}");
    this->b_bili = new QPushButton;
    this->b_bili->setFixedSize(80, 80);
    this->b_bili->setStyleSheet("QPushButton {width: 80px; height: 80px; border-image: url(:/assets/image/bili_logo.png);}");

    QWidget *spacer_2 = new QWidget, *spacer_3 = new QWidget, *spacer_4 = new QWidget, *spacer_5 = new QWidget;
    spacer_2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    spacer_5->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->tb_link->addWidget(spacer_2);
    this->tb_link->addWidget(b_github);
    this->tb_link->addWidget(spacer_3);
    this->tb_link->addSeparator();
    this->tb_link->addWidget(spacer_4);
    this->tb_link->addWidget(b_bili);
    this->tb_link->addWidget(spacer_5);

    connect(b_github, &QPushButton::clicked, []() { QDesktopServices::openUrl(QUrl("https://www.github.com/Gelinzh/TicTacToe")); });
    connect(b_bili , &QPushButton::clicked, []() { QDesktopServices::openUrl(QUrl("https://space.bilibili.com/6504720")); });
}
