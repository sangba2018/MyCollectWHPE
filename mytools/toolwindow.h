#ifndef TOOLWINDOW_H
#define TOOLWINDOW_H

#include <QObject>
#include <QWidget>
#include <QPushButton>

class toolwindow : public QWidget
{
    Q_OBJECT
public:
    explicit toolwindow(QWidget *parent = nullptr);

signals:

public slots:

private:
     QPushButton *pbtn3;
};

#endif // TOOLWINDOW_H
