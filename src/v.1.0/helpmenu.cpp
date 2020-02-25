#include "helpmenu.h"

#define _VERSION_ "1.0"
#define _DATE_ "2020 02 26"

HelpMenu::HelpMenu(QWidget *parent) : QWidget(parent)
{
    vLayout = new QVBoxLayout;
    hLayout = new QHBoxLayout;
    bLayout = new QHBoxLayout;

    l_logo         = new QLabel;
    l_projectName  = new QLabel;
    l_buildDate    = new QLabel;
    l_author       = new QLabel;
    b_githubUrl    = new QPushButton;
    b_biliUrl      = new QPushButton;
    b_line         = new QPushButton;

    l_logo->setFixedSize(128, 128);

    QFont *projectFont = new QFont;
    projectFont->setBold(true);
    projectFont->setPointSize(10);
    l_projectName->setText("TicTacToe " _VERSION_);
    l_projectName->setFont(*projectFont);
    l_buildDate->setText("Built on " _DATE_);
    l_author->setText("Written by Acelych");
    b_githubUrl->setFixedSize(32, 32);
    b_biliUrl->setFixedSize(32, 32);
    b_line->setFixedSize(1, 30);
    b_line->setEnabled(false);

    bLayout->addWidget(b_githubUrl);
    bLayout->addWidget(b_line);
    bLayout->addWidget(b_biliUrl);

    vLayout->addStretch(3);
    vLayout->addWidget(l_projectName);
    vLayout->addStretch(1);
    vLayout->addWidget(l_buildDate);
    vLayout->addWidget(l_author);
    vLayout->addStretch(1);
    vLayout->addLayout(bLayout);
    vLayout->addStretch(3);

    hLayout->addStretch(3);
    hLayout->addWidget(l_logo);
    hLayout->addStretch(3);
    hLayout->addLayout(vLayout);
    hLayout->addStretch(4);

    this->setLayout(hLayout);

    connect(b_githubUrl, &QPushButton::clicked, []() { QDesktopServices::openUrl(QUrl("https://www.github.com/Gelinzh/TicTacToe")); });
    connect(b_biliUrl  , &QPushButton::clicked, []() { QDesktopServices::openUrl(QUrl("https://space.bilibili.com/6504720")); });
}

void HelpMenu::closeEvent(QCloseEvent *event)
{
    emit hm_close();
    event->accept();
}

