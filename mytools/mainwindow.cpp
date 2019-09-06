#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
//    menubar = new QMenuBar(this);
    //注意这里不能用上面的new方式，因为QMainwindow中本来就自带，再建的话会重新布局吧（个人猜测）
    menubar = menuBar();    menu = new QMenu("操作");
    menubar->addMenu(menu);
    actmot = new QAction("交通部");
    actunion = new QAction("银联");
    acttrans = new QAction("小工具");
//    actmot->setCheckable(true);
//    actunion->setCheckable(true);
//    acttrans->setCheckable(true);
    menu->addAction(actmot);
    menu->addAction(actunion);
    menu->addAction(acttrans);

    toolbar = new QToolBar(this);
    toolbar->addAction(actmot);
    toolbar->addAction(actunion);
    toolbar->addAction(acttrans);
    this->addToolBar(toolbar);//这里也不能掉

    resize(800,700);
    chose = new QStackedWidget(this);
    motwiget = new motwindow();
    unionwiget = new unionwindow();
    toolwiget = new toolwindow();
    chose->addWidget(motwiget);
    chose->addWidget(unionwiget);
    chose->addWidget(toolwiget);
    this->setCentralWidget(chose);
    connect(menu,SIGNAL(triggered(QAction*)),this,SLOT(chagePage(QAction*)));
    connect(this,SIGNAL(pagenum(int)),chose,SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{

}

void MainWindow::chagePage(QAction *act)
{
    qDebug()<<act->text();
    if(act == actmot)
    {
        emit pagenum(0);
         qDebug()<<"actmot";
    }
    else if(act == actunion)
    {
        emit pagenum(1);
         qDebug()<<"actunion";
    }
    else if(act == acttrans)
    {
        emit pagenum(2);
        qDebug()<<"acttrans";
    }
    else
    {
        emit pagenum(0);
        qDebug()<<"nothing";
    }
}




