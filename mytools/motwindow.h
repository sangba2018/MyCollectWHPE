#ifndef MOTWINDOW_H
#define MOTWINDOW_H

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
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTextEdit>
#include <Qt>
#include <QList>
#include <QMessageBox>
#include <QDebug>
#include <QLabel>



class motwindow : public QWidget
{
    Q_OBJECT
public:
    explicit motwindow(QWidget *parent = nullptr);
    void buildfirstpage();
    void buildsecondpage();
    void buildthirdpage();
    void buildfourthpage();
    void buildfifthpage();

signals:
//    void sendPage(int);

public slots:
    void pageChanged(int);
//    void showeachdockw(int);
    void showfifthfile();
    void showsevefile();
    void showeightfile();
    void showoneefile();
    void showoneafile();


private:
    //15 file
    QWidget *firstpage;
    QSplitter *splt;
    QListWidget *lst;
    QStandardItemModel *stdmod;
    QStandardItem *stdit;
    QTableView *tbvw;
    QTextEdit *textbw;
    QPushButton *pbtn;
    QList<QStandardItem*> ist;
//17 file
    QWidget *secondpage;
    QStandardItemModel *stdmod1;
    QStandardItem *stdit1;
    QTableView *tbvw1;
    QTextEdit *textbw1;
    QPushButton *pbtn1;
    QStringList strlseveteenfiletips;
    QList<QStandardItem*> ist1;

    QWidget *thirdpage;
    QStandardItemModel *stdmod2;
    QStandardItem *stdit2;
    QTableView *tbvw2;
    QTextEdit *textbw2;
    QPushButton *pbtn2;
    QStringList strleightteenfiletips;
    QList<QStandardItem*> ist2;

    QWidget *forthpage;
    QStandardItemModel *stdmod3;
    QStandardItem *stdit3;
    QTableView *tbvw3;
    QTextEdit *textbw3;
    QPushButton *pbtn3;
    QStringList strloneefiletips;
    QList<QStandardItem*> ist3;


    QWidget *fifthpage;
    QStandardItemModel *stdmod4;
    QStandardItem *stdit4;
    QTableView *tbvw4;
    QTextEdit *textbw4;
    QPushButton *pbtn4;
    QStringList strloneafiletips;
    QList<QStandardItem*> ist4;
    //useless
    QDockWidget *dckw1;
    QDockWidget *dckw2;
    QDockWidget *dckw3;
    QDockWidget *dckw4;
    QDockWidget *dckw5;
    QStackedWidget *stkw;
    QList<QStandardItem*> ist5;

    QHBoxLayout *hbly;
    QVBoxLayout *vbly;
    QGridLayout *gly;
    QHBoxLayout *hblydoc1;
    QHBoxLayout *hblydoc2;
    QVBoxLayout *vblydoc1;

    QSplitter *firstpagespl;
    QSplitter *secondpagespl;
    QSplitter *thirdpagespl;
    QSplitter *forthpagespl;
    QSplitter *fifthpagespl;

};

#endif // MOTWINDOW_H
