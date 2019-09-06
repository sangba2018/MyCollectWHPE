#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QAction>
#include <QStackedWidget>
#include <QDebug>
#include "motwindow.h"
#include "unionwindow.h"
#include "toolwindow.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QMenuBar *menubar;
    QMenu *menu;
    QToolBar *toolbar;
    QAction *actmot;
    QAction *actunion;
    QAction *acttrans;
    QStackedWidget *chose;
    motwindow *motwiget;
    unionwindow *unionwiget;
    toolwindow *toolwiget;


public slots:
    void chagePage(QAction*);

signals:
    void pagenum(int n);
};

#endif // MAINWINDOW_H
