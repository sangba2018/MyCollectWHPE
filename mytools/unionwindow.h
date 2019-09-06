#ifndef UNIONWINDOW_H
#define UNIONWINDOW_H

#include <QObject>
#include <QWidget>
#include <QSplitter>
#include <QListWidget>
#include <QTableView>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QStackedWidget>
#include <QDockWidget>
#include <QTextBrowser>
#include <QPushButton>

class unionwindow : public QWidget
{
    Q_OBJECT
public:
    explicit unionwindow(QWidget *parent = nullptr);

signals:

public slots:

private:
    QPushButton *pbtn2;

};

#endif // UNIONWINDOW_H
