#include "motwindow.h"
#include <QSizePolicy>
//交通部一卡通数据解析界面初始化，建立相关静态部件，监听动态数据

motwindow::motwindow(QWidget *parent) : QWidget(parent)
{
    gly = new QGridLayout(this);
    hbly = new QHBoxLayout();
    vbly = new QVBoxLayout();

    splt = new QSplitter(Qt::Horizontal,this);//splitter qlist and stacked windows
    lst = new QListWidget();
    lst->addItem("15 file");
    lst->addItem("17 file");
    lst->addItem("18 file");
    lst->addItem("1E file");
    lst->addItem("1A file");


//    lst->setSizePolicy(QSizePolicy::Fixed);
    stkw = new QStackedWidget();//add 5 qwidget to stacked

    firstpage  = new QWidget();//15 file
    secondpage = new QWidget();
    thirdpage  = new QWidget();
    forthpage  = new QWidget();
    fifthpage  = new QWidget();

    secondpagespl = new QSplitter(Qt::Vertical,secondpage);
    thirdpagespl = new QSplitter(Qt::Vertical,thirdpage);
    forthpagespl = new QSplitter(Qt::Vertical,forthpage);
    fifthpagespl = new QSplitter(Qt::Vertical,fifthpage);


#if 0
    dckw1 = new QDockWidget(tr("15file"));
    dckw2 = new QDockWidget(tr("17file"));
    dckw3 = new QDockWidget(tr("18file"));
    dckw4 = new QDockWidget(tr("1Efile"));
    dckw5 = new QDockWidget(tr("1Afile"));

    dckw1->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dckw1->setAllowedAreas(Qt::RightDockWidgetArea|Qt::BottomDockWidgetArea);

    dckw2->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dckw3->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dckw4->setFeatures(QDockWidget::AllDockWidgetFeatures);
    dckw5->setFeatures(QDockWidget::AllDockWidgetFeatures);


    stkw->addWidget(dckw1);
    stkw->addWidget(dckw2);
    stkw->addWidget(dckw3);
    stkw->addWidget(dckw4);
    stkw->addWidget(dckw5);

    dckw1->setWidget(firstpage);
    dckw2->setWidget(secondpage);
    dckw3->setWidget(thirdpage);
    dckw4->setWidget(forthpage);
    dckw5->setWidget(fifthpage);
#else

    stkw->addWidget(firstpage);//firstpagespl
    stkw->addWidget(secondpage);
    stkw->addWidget(thirdpage);
    stkw->addWidget(forthpage);
    stkw->addWidget(fifthpage);
#endif
//    dckw1->setFloating(true);
//    qDebug()<<dckw1->isFloating();



#if 0
//    splt->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
//    dckw1->setSizePolicy(QSizePolicy::Fixed);
     //为了分割比例，为啥不用setStretchFactor,因为我旁边的stkw窗口中布局了，使其无效
    QSizePolicy wd1 =lst->sizePolicy();
    wd1.setHorizontalStretch(1);
    lst->setSizePolicy(wd1);
    QSizePolicy wd2 =stkw->sizePolicy();
    wd2.setHorizontalStretch(255);
    stkw->setSizePolicy(wd2);
//    splt->setStretchFactor(0,4);
//    splt->setStretchFactor(1,8);
#endif
    splt->addWidget(lst);
    splt->addWidget(stkw);
    splt->setStretchFactor(0,1);
    splt->setStretchFactor(1,6);
    buildfirstpage();
    buildsecondpage();
    buildthirdpage();
    buildfourthpage();
    buildfifthpage();
//    QGridLayout *dock1lay = new QGridLayout(dckw1);
//    dock1lay->addWidget(firstpage);
//pageChanged setCurrentIndex
//    connect(lst,SIGNAL(currentRowChanged(int)),this,SLOT(pageChanged(int)));
    connect(lst,SIGNAL(currentRowChanged(int)),stkw,SLOT(setCurrentIndex(int)));
//    connect(pbtn,SIGNAL(clicked()),this,SLOT( showfifthfile()));
    gly->addWidget(splt);
}

void motwindow::pageChanged(int pageIndex)
{

    qDebug()<<pageIndex;
    stkw->setCurrentIndex(pageIndex);
    if(pageIndex == 0)
        buildfirstpage();
    else if(pageIndex == 1)
        buildsecondpage();
}



 void motwindow::buildfirstpage()//add to widget dock
 {
    int j=0;
    int colunm=0;
    pbtn = new QPushButton(firstpage);
    pbtn->setText("解析");
    textbw = new QTextEdit(firstpage);
    textbw->setPlaceholderText("请输入十六进制的15文件数据");
    QStringList strlfifthfiletips={
    "15公共应用信息文件",
    "文件标识(FID)","0x15",
    "文件类型","二进制数据文件",
    "文件大小","30",
    "文件存取控制","读=自由",
    "字节","数据元","长度(字节)","格式","值","解析数据",
    "1~8","发卡机构标识","8","cn","组成方式:00010001+FFFFFFFF"," ",
    "9","应用类型标识（标准版本）","1","cn","当前为：02"," ",
    "10","发卡机构应用版本（启用标识）","1","cn","00：初始值\n01:已启用\n与08的启用标识同步"," ",
    "11~20","应用序列号","10","n","6位IIN+2位扩展+11位自定义"," ",
    "21~24","应用启用日期（YYYYMMDD）","4","cn","与电子现金08文件数据同步"," ",
    "25~28","应用有效日期（YYYYMMDD）","4","cn","与电子现金08文件数据同步"," ",
    "29~30","发卡机构自定义FCI数据","2","b"," "," "
                              };

    QLabel * coscmd = new QLabel(firstpage);
    coscmd->setText("cos cmd:00b095000005");
    QStandardItem* item;
    tbvw = new QTableView(firstpage);
    stdmod = new QStandardItemModel(firstpage);
    tbvw->setModel(stdmod);
    stdmod->setColumnCount(6);

    for(int i= 0;i<strlfifthfiletips.count();i++)
    {
         //ist[i]
         item = new QStandardItem(QString("%1").arg(strlfifthfiletips[i]));
         ist.append(item);
         ist[i]->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         //ist.append()
         if(i == 0)
         {
            stdmod->setItem(0,0,ist[i]);
            j++;
         }
         else if (i <= 8)
         {
             if(i%2)
             {
                 stdmod->setItem(j,0,ist[i]);

             }
             else
             {
                 stdmod->setItem(j,4,ist[i]);
                  j++;
             }
         }
         else
         {
             stdmod->setItem(j,colunm,ist[i]);
             colunm++;
             if(colunm >= 6)
             {
                 j++;
                 colunm=0;
             }
         }
    }

    tbvw->setSpan(0,0,1,6);//合并第一行6列
    tbvw->setSpan(1,0,1,4);//合并第二行0~3列
    tbvw->setSpan(1,4,1,2);//合并第二行4~6列
    tbvw->setSpan(2,0,1,4);
    tbvw->setSpan(2,4,1,2);
    tbvw->setSpan(3,0,1,4);
    tbvw->setSpan(3,4,1,2);
    tbvw->setSpan(4,0,1,4);
    tbvw->setSpan(4,4,1,2);
    tbvw->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbvw->resizeColumnsToContents();
    tbvw->resizeRowsToContents();

//    stdmod->setHeaderData(0,Qt::Horizontal,"15 file");
//    stdmod->setHeaderData(1,Qt::Horizontal,"data");
//    stdmod->setHeaderData(2,Qt::Horizontal,"lenth");

//    stdmod->appendRow(new QStandardItem("15file"));
    firstpagespl = new QSplitter(Qt::Vertical,firstpage);//
    QWidget *wup = new QWidget(firstpage);
    QHBoxLayout * layout1 = new QHBoxLayout(wup);//铺满布局
    layout1->addWidget(textbw,5);
    layout1->addWidget(pbtn,1);
    QWidget *wup1 = new QWidget(firstpage);
    QVBoxLayout * layout2 = new QVBoxLayout(wup1);//铺满布局
    layout2->addWidget(wup,6);
    layout2->addWidget(coscmd,1);
//    QSplitter *firstpagethirdspl = new QSplitter(Qt::Horizontal,firstpagespl);
//    firstpagethirdspl->addWidget(textbw);//pbtn,tbvw
//    firstpagethirdspl->addWidget(pbtn);
//    firstpagethirdspl->setStretchFactor(0,2);
//    firstpagethirdspl->setStretchFactor(1,5);
    firstpagespl->addWidget(wup1);//firstpagethirdspl,textbw
    firstpagespl->addWidget(tbvw);
    firstpagespl->setStretchFactor(0,2);
    firstpagespl->setStretchFactor(1,8);
    layout1->setContentsMargins(0,0,0,0);
    layout2->setContentsMargins(0,0,0,0);
    //定义item

//   for(int i = 0;i < 10;i++)
//   {
//       item = new QStandardItem(QString("%1").arg(i));
//       stdmod->setItem(i,0,item);
//       item = new QStandardItem(QString("%1").arg(i*2));
//       stdmod->setItem(i,1,item);
//       item = new QStandardItem(QString("%1").arg(i*3));
//       stdmod->setItem(i,2,item);
//   }

#if 0
      QSizePolicy policy = textbw->sizePolicy();
      policy.setVerticalStretch(2);
      textbw->setSizePolicy(policy);
//      QWidget *widget1 = firstpagespl->widget(2);
        QSizePolicy policy1 = pbtn->sizePolicy();
  //      policy.setHorizontalStretch(1);
        policy1.setVerticalStretch(1);
        pbtn->setSizePolicy(policy1);
//        QWidget *widget2 = firstpagespl->widget(3);
          QSizePolicy policy2 = tbvw->sizePolicy();
    //      policy.setHorizontalStretch(1);
          policy2.setVerticalStretch(9);
          tbvw->setSizePolicy(policy2);
#endif
//    hblydoc1 = new QHBoxLayout();
//    hblydoc1->addWidget(textbw,8);
//    hblydoc1->addWidget(pbtn,1);
//    hblydoc2 = new QHBoxLayout();
//    hblydoc2->addWidget(tbvw,1);

//    vblydoc1 = new QVBoxLayout(firstpage);
//    vblydoc1->addLayout(hblydoc1);
//    vblydoc1->addLayout(hblydoc2);

    QGridLayout *wdgt=new QGridLayout(firstpage);
//    wdgt->addWidget(firstpagethirdspl);
//    wdgt->addWidget(wup);
    wdgt->addWidget(firstpagespl);
    wdgt->setContentsMargins(0,0,0,0);
//    wdgt->addWidget(textbw,0,0,2,1);
//    wdgt->addWidget(pbtn,0,1,1,1);
//    wdgt->addWidget(tbvw);

    connect(pbtn,SIGNAL(clicked()),this,SLOT( showfifthfile()));
 }

 //0x12,23 a5,25,0x33 99 0x88,,0x34,
 //0x11,0x12,0x13,0x14,0x15,0x11,0x12,0x13,0x14,0x15,0x11,0x12,0x13,0x14,0x15,0x11,0x12,0x13,0x14,0x15
 void motwindow::showfifthfile()
 {
     QString fifthFileContent = textbw->toPlainText().trimmed();
     QString strRx("(0x)?|,| |，| ");//("^[0x]+|,| ");这里不能要^,否则后面的0x检测不到
     QString textinput("[a-fA-F0-9,x ， ]+");//^[a-fA-F0-9,x]+
     QRegExp rxlen(textinput);
     qDebug()<<fifthFileContent;
     bool mt = rxlen.exactMatch(fifthFileContent);
     if(mt)
     {
         fifthFileContent.replace(QRegExp(strRx),"");
     }
     else
     {
         QMessageBox::warning(this,"警告","输入格式错误");
         return ;
     }
     qDebug()<<fifthFileContent;
     QString str1= fifthFileContent.mid(0,16);//1~8
     ist[20]->setText(str1);
//     stdmod->setItem(7,6,ist[21]);
     QString str2= fifthFileContent.mid(16,2);//9
     ist[26]->setText(str2);
     QString str3= fifthFileContent.mid(18,2);//10
     ist[32]->setText(str3);
     QString str4= fifthFileContent.mid(20,20);//11~20
     ist[38]->setText(str4);
     QString str5= fifthFileContent.mid(40,8);//21~24
     ist[44]->setText(str5);
     QString str6= fifthFileContent.mid(48,8);//25~28
     ist[50]->setText(str6);
     QString str7= fifthFileContent.mid(56,4);//29 30
     ist[56]->setText(str7);
//     stdmod->setItem(7,6,ist[26]);
     tbvw->resizeColumnsToContents();
     tbvw->resizeRowsToContents();
//     int pos = rxlen.indexIn(fifthFileContent);

//     if (pos > -1)
//     {
//         QString value = rxlen.cap(0); //
//         QString unit = rxlen.cap(1);  //
//         qDebug() << value << unit << pos <<"match over";
//     }


 }
/*
void motwindow::showeachdockw(int stackpage)
{
    stkw->setCurrentIndex(stackpage);

}
*/

 void motwindow::showsevefile()
 {
     QString fifthFileContent = textbw1->toPlainText().trimmed();
     QString strRx("(0x)?|,| |，| ");//("^[0x]+|,| ");这里不能要^,否则后面的0x检测不到
     QString textinput("[a-fA-F0-9,x ， ]+");//^[a-fA-F0-9,x]+
     QRegExp rxlen(textinput);
     qDebug()<<fifthFileContent;
     bool mt = rxlen.exactMatch(fifthFileContent);
     if(mt)
     {
         fifthFileContent.replace(QRegExp(strRx),"");
     }
     else
     {
         QMessageBox::warning(this,"警告","输入格式错误");
         return ;
     }
     qDebug()<<fifthFileContent;
     QString str1= fifthFileContent.mid(0,8);//1~4
     ist1[20]->setText(str1);
     QString str2= fifthFileContent.mid(8,4);//
     ist1[26]->setText(str2);
     QString str3= fifthFileContent.mid(12,4);//
     ist1[32]->setText(str3);
     QString str4= fifthFileContent.mid(16,4);//
     ist1[38]->setText(str4);
     QString str5= fifthFileContent.mid(20,2);//
     ist1[44]->setText(str5);
     QString str6= fifthFileContent.mid(22,98);//25~28
     ist1[50]->setText(str6);
//     stdmod->setItem(7,6,ist[26]);
     tbvw1->resizeColumnsToContents();
     tbvw1->resizeRowsToContents();
//     int pos = rxlen.indexIn(fifthFileContent);

//     if (pos > -1)
//     {
//         QString value = rxlen.cap(0); //
//         QString unit = rxlen.cap(1);  //
//         qDebug() << value << unit << pos <<"match over";
//     }


 }


 void motwindow::buildsecondpage()//17 file page
 {
    int j=0;
    int colunm=0;
    pbtn1 = new QPushButton(secondpage);
    pbtn1->setText("解析");
    textbw1 = new QTextEdit(secondpage);
    textbw1->setPlaceholderText("请输入十六进制的17文件数据");
    strlseveteenfiletips << QList<QString>{"17管理信息文件",
    "文件标识(FID)","0x17",
    "文件类型","二进制数据文件",
    "文件大小","60",
    "文件存取控制","读=自由",
    "字节","数据元","长度(字节)","格式","值","解析数据",
    "1~4","国际代码","4","n","00000156"," ",
    "5~6","省级代码","2","n","《全国清算中心代码》(GB\n13497-92)省级代码"," ",
    "7~8","城市代码","2","n","《全国清算中心代码》(GB\n13497-92)城市代码"," ",
    "9~10","互通卡种","2","n","与电子现金08文件数据同步\n0000:非互通卡\n0001:互通卡"," ",
    "11","卡种类型","1","an","与电子现金08文件数据同步"," ",
    "12~60","预留","49","b"," "," ",
    "注:卡种类型同发卡机构特殊数据元(标签“DF11”)"
                              };
//    QList<QStandardItem*> ist;
    QStandardItem* item;
    tbvw1 = new QTableView(secondpage);
    stdmod1 = new QStandardItemModel(secondpage);
    tbvw1->setModel(stdmod1);
    stdmod1->setColumnCount(6);

    qDebug()<<strlseveteenfiletips.count();
    for(int i= 0;i<strlseveteenfiletips.count();i++)
    {
         //ist[i]
         item = new QStandardItem(QString("%1").arg(strlseveteenfiletips[i]));
         ist1.append(item);
         ist1[i]->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         //ist.append()
         if(i == 0)
         {
            stdmod1->setItem(0,0,ist1[i]);
            j++;
         }
         else if (i <= 8)
         {
             if(i%2)
             {
                 stdmod1->setItem(j,0,ist1[i]);

             }
             else
             {
                 stdmod1->setItem(j,4,ist1[i]);
                  j++;
             }
         }
         else if (i < 51)
         {
             stdmod1->setItem(j,colunm,ist1[i]);
             colunm++;
             if(colunm >= 6)
             {
                 j++;
                 colunm=0;
             }
         }
         else
         {
             stdmod1->setItem(j,0,ist1[i]);
         }
    }

    tbvw1->setSpan(0,0,1,6);//合并第一行0~5列
    tbvw1->setSpan(1,0,1,4);//合并第二行0~2列
    tbvw1->setSpan(1,4,1,2);//合并第二行3~5列
    tbvw1->setSpan(2,0,1,4);
    tbvw1->setSpan(2,4,1,2);
    tbvw1->setSpan(3,0,1,4);
    tbvw1->setSpan(3,4,1,2);
    tbvw1->setSpan(4,0,1,4);
    tbvw1->setSpan(4,4,1,2);
    tbvw1->setSpan(12,0,1,6);//合并第12行
    tbvw1->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbvw1->resizeColumnsToContents();
    tbvw1->resizeRowsToContents();

    secondpagespl = new QSplitter(Qt::Vertical,secondpage);//
    QWidget *wup = new QWidget(secondpage);
    QHBoxLayout * layout1 = new QHBoxLayout(wup);//铺满布局

    layout1->addWidget(textbw1,5);
    layout1->addWidget(pbtn1,1);
    secondpagespl->addWidget(wup);//firstpagethirdspl,textbw
    secondpagespl->addWidget(tbvw1);
    secondpagespl->setStretchFactor(0,2);
    secondpagespl->setStretchFactor(1,8);
    QGridLayout *wdgt=new QGridLayout(secondpage);
    wdgt->addWidget(secondpagespl);

    connect(pbtn1,SIGNAL(clicked()),this,SLOT(showsevefile()));
 }


 void motwindow::buildthirdpage()//18 file page
 {
    int j=0;
    int colunm=0;
    pbtn2 = new QPushButton(thirdpage);
    pbtn2->setText("解析");
    textbw2 = new QTextEdit(thirdpage);
    textbw2->setPlaceholderText("请输入十六进制的18文件数据");
    strleightteenfiletips << QList<QString>{"18交易明细文件",
    "文件标识(FID)","0x18",
    "文件类型","循环文件",
    "文件大小","10x23",
    "文件存取控制","读=自由",
    "字节","数据元","长度(字节)","格式","值","解析数据",
    "1~2","EP联机或脱机交易序号","2"," "," "," ",
    "3~5","透支限额","3"," "," "," ",
    "6~9","交易金额","4"," "," "," ",
    "10","交易类型标识","1"," "," "," ",
    "11~16","终端机编号","6"," "," "," ",
    "17~20","交易日期（终端）","4"," "," "," ",
    "21~23","交易时间（终端）","3"," "," "," "};
//    QList<QStandardItem*> ist;
    QStandardItem* item;
    tbvw2 = new QTableView(thirdpage);
    stdmod2 = new QStandardItemModel(thirdpage);
    tbvw2->setModel(stdmod2);
    stdmod2->setColumnCount(6);

    qDebug()<<strleightteenfiletips.count();
    for(int i= 0;i<strleightteenfiletips.count();i++)
    {
         //ist[i]
         item = new QStandardItem(QString("%1").arg(strleightteenfiletips[i]));
         ist2.append(item);
         ist2[i]->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
         //ist.append()
         if(i == 0)
         {
            stdmod2->setItem(0,0,ist2[i]);
            j++;
         }
         else if (i <= 8)
         {
             if(i%2)
             {
                 stdmod2->setItem(j,0,ist2[i]);

             }
             else
             {
                 stdmod2->setItem(j,4,ist2[i]);
                  j++;
             }
         }
         else
         {
             stdmod2->setItem(j,colunm,ist2[i]);
             colunm++;
             if(colunm >= 6)
             {
                 j++;
                 colunm=0;
             }
         }
    }

    tbvw2->setSpan(0,0,1,6);//合并第一行0~5列
    tbvw2->setSpan(1,0,1,4);//合并第二行0~2列
    tbvw2->setSpan(1,4,1,2);//合并第二行3~5列
    tbvw2->setSpan(2,0,1,4);
    tbvw2->setSpan(2,4,1,2);
    tbvw2->setSpan(3,0,1,4);
    tbvw2->setSpan(3,4,1,2);
    tbvw2->setSpan(4,0,1,4);
    tbvw2->setSpan(4,4,1,2);
//    tbvw2->setSpan(12,0,1,6);//合并第12行
    tbvw2->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbvw2->resizeColumnsToContents();
    tbvw2->resizeRowsToContents();

    thirdpagespl = new QSplitter(Qt::Vertical,thirdpage);//
    QWidget *wup = new QWidget(thirdpage);
    QHBoxLayout * layout1 = new QHBoxLayout(wup);//铺满布局

    layout1->addWidget(textbw2,5);
    layout1->addWidget(pbtn2,1);
    thirdpagespl->addWidget(wup);//firstpagethirdspl,textbw
    thirdpagespl->addWidget(tbvw2);
    thirdpagespl->setStretchFactor(0,2);
    thirdpagespl->setStretchFactor(1,8);
    QGridLayout *wdgt=new QGridLayout(thirdpage);
    wdgt->addWidget(thirdpagespl);

    connect(pbtn2,SIGNAL(clicked()),this,SLOT(showeightfile()));
 }

 void motwindow::showeightfile()
{
     QString fifthFileContent = textbw2->toPlainText().trimmed();
     QString strRx("(0x)?|,| |，| ");//("^[0x]+|,| ");这里不能要^,否则后面的0x检测不到
     QString textinput("[a-fA-F0-9,x ， ]+");//^[a-fA-F0-9,x]+
     QRegExp rxlen(textinput);
     qDebug()<<fifthFileContent;
     bool mt = rxlen.exactMatch(fifthFileContent);
     if(mt)
     {
         fifthFileContent.replace(QRegExp(strRx),"");
     }
     else
     {
         QMessageBox::warning(this,"警告","输入格式错误");
         return ;
     }
     qDebug()<<fifthFileContent;
     QString str1= fifthFileContent.mid(0,4);//1~2
     ist2[20]->setText(str1);
     QString str2= fifthFileContent.mid(4,6);//3
     ist2[26]->setText(str2);
     QString str3= fifthFileContent.mid(10,8);//4
     ist2[32]->setText(str3);
     QString str4= fifthFileContent.mid(18,2);//1
     ist2[38]->setText(str4);
     QString str5= fifthFileContent.mid(20,12);//6
     ist2[44]->setText(str5);
     QString str6= fifthFileContent.mid(32,8);//
     ist2[50]->setText(str6);
     QString str7= fifthFileContent.mid(40,6);//
     ist2[56]->setText(str7);
     tbvw2->resizeColumnsToContents();
     tbvw2->resizeRowsToContents();
}


 void motwindow::buildfourthpage()//1e file page
 {
    int j=0;//line
    int colunm=0;
    pbtn3 = new QPushButton(forthpage);
    pbtn3->setText("解析");
    textbw3 = new QTextEdit(forthpage);
    textbw3->setPlaceholderText("请输入十六进制的1e文件数据");
    strloneefiletips << QList<QString>{
    "文件名称","1E 公共交通过程信息循环记录文件--交易信息记录文件",
    "文件类型","循环记录文件", "文件标识(FID)","0x1E",
    "文件大小","48x30",
    "文件权限","读取","自由","更新","保护",
    "字节","数据元","长度(字节)","格式","值","解析数据",
    "1","交易类型","1","HEX","00:初始值\n01:EC入站/上车/进场等\n"
    "02:EC出站/下车/出场等\n03:EP入站/上车/进场等\n04:EP出站/下车/出场等\n"
    "05:EC单次消费\n06:EP单次消费\n07:EC补票\n08:EP补票\n09:EC充值\n0A:EP充值\n其他预留"," ",
    "2~9","终端编号","8","BCD"," "," ",
    "10","行业代码","1","HEX","01地铁 02公交 03城市水上客运 04出租汽车 \n"
    "05租赁汽车 06公共自行车 07停车收费 08长途客运\n09轮渡 0A城际高速铁路 0B民航 0C高速公路收费\n0E市郊城铁（慢速） 0F~12本规范预留"," ",
    "11~12","线路","2","HEX"," "," ",
    "13~14","站点","2","HEX"," "," ",
    "15~16","运营代码","2","HEX"," "," ",
    "17","预留","1","HEX"," "," ",
    "18~21","交易金额","4","HEX\n(高字节在前)"," "," ",
    "22~25","交易后余额","4","HEX\n(高字节在前)"," "," ",
    "26~32","交易日期时间","7","YYYYMMDDhhmmss"," "," ",
    "33~34","受理方城市代码","2","BCD"," "," ",
    "35~42","受理方机构标识","8","BCD"," "," ",
    "43~48","本规范预留","6"," ","初始为00"," "
    };
//    QList<QStandardItem*> ist;
    QStandardItem* item;
    tbvw3 = new QTableView(forthpage);
    stdmod3 = new QStandardItemModel(forthpage);
    tbvw3->setModel(stdmod3);
    stdmod3->setColumnCount(6);

    qDebug()<<strloneefiletips.count()<<"buildfourthpage";
    for(int i= 0;i<strloneefiletips.count();i++)
    {
         item = new QStandardItem(QString("%1").arg(strloneefiletips[i]));
         ist3.append(item);
         ist3[i]->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
    }

    for(int i= 0;i<strloneefiletips.count();i++)
    {

         if (j == 0)
         {
               stdmod3->setItem(j,0,ist3[i++]);//i=0
               stdmod3->setItem(j,1,ist3[i]);
               j++;
         }
         else if(j == 1)
         {
             stdmod3->setItem(j,0,ist3[i++]);
             stdmod3->setItem(j,1,ist3[i++]);//
             stdmod3->setItem(j,3,ist3[i++]);
             stdmod3->setItem(j,4,ist3[i]);
             j++;
         }
         else if(j == 2)
         {
             stdmod3->setItem(j,0,ist3[i++]);
             stdmod3->setItem(j,1,ist3[i++]);//
             stdmod3->setItem(j,3,ist3[i++]);
             stdmod3->setItem(j,4,ist3[i++]);//读取
             stdmod3->setItem(j,5,ist3[i++]);//自由
             j++;
             stdmod3->setItem(j,4,ist3[i++]);//更新
             stdmod3->setItem(j,5,ist3[i]);//保护
             j++;
         }
         else if (j <= 17)
         {
//              qDebug()<<"j"<<j<<"i"<<i<<"colunm"<<colunm;
             stdmod3->setItem(j,colunm,ist3[i]);
             colunm++;
             if(colunm >= 6)
             {
                 j++;
                 colunm=0;
             }
         }


    }

    tbvw3->setSpan(0,1,1,5);//合并第一行0~1列
//    tbvw3->setSpan(0,3,1,4);
    tbvw3->setSpan(1,1,1,2);//合并第二行0~3列
    tbvw3->setSpan(1,4,1,2);//合并第二行4~5列

    tbvw3->setSpan(2,0,2,1);//文件大小
    tbvw3->setSpan(2,1,2,2);//
    tbvw3->setSpan(2,3,2,1);//文件权限

//    tbvw3->setSpan(4,0,1,4);
//    tbvw3->setSpan(4,4,1,2);

    tbvw3->setEditTriggers(QAbstractItemView::NoEditTriggers);
    tbvw3->resizeColumnsToContents();
    tbvw3->resizeRowsToContents();

    forthpagespl = new QSplitter(Qt::Vertical,forthpage);//
    QWidget *wup = new QWidget(forthpage);
    QHBoxLayout * layout1 = new QHBoxLayout(wup);//铺满布局

    layout1->addWidget(textbw3,5);
    layout1->addWidget(pbtn3,1);
    forthpagespl->addWidget(wup);//firstpagethirdspl,textbw
    forthpagespl->addWidget(tbvw3);
    forthpagespl->setStretchFactor(0,2);
    forthpagespl->setStretchFactor(1,8);
    QGridLayout *wdgt=new QGridLayout(forthpage);
    wdgt->addWidget(forthpagespl);

    connect(pbtn3,SIGNAL(clicked()),this,SLOT(showoneefile()));
 }

void motwindow::showoneefile()
{
  QString fifthFileContent = textbw3->toPlainText().trimmed();
  QString strRx("(0x)?|,| |，| ");//("^[0x]+|,| ");这里不能要^,否则后面的0x检测不到
  QString textinput("[a-fA-F0-9,x ， ]+");//^[a-fA-F0-9,x]+
  QRegExp rxlen(textinput);
  qDebug()<<fifthFileContent;
  bool mt = rxlen.exactMatch(fifthFileContent);
  if(mt)
  {
      fifthFileContent.replace(QRegExp(strRx),"");
  }
  else
  {
      QMessageBox::warning(this,"警告","输入格式错误");
      return ;
  }
  qDebug()<<fifthFileContent;
  QString str1= fifthFileContent.mid(0,2);//
  ist3[24]->setText(str1);
  QString str2= fifthFileContent.mid(2,16);//
  ist3[30]->setText(str2);
  QString str3= fifthFileContent.mid(18,2);//
  ist3[36]->setText(str3);
  QString str4= fifthFileContent.mid(20,4);//
  ist3[42]->setText(str4);
  QString str5= fifthFileContent.mid(24,4);//
  ist3[48]->setText(str5);
  QString str6= fifthFileContent.mid(28,4);//
  ist3[54]->setText(str6);
  QString str7= fifthFileContent.mid(32,2);//
  ist3[60]->setText(str7);
  QString str8= fifthFileContent.mid(34,8);//
  ist3[66]->setText(str8);
  QString str9= fifthFileContent.mid(42,8);//
  ist3[72]->setText(str9);
  QString str10= fifthFileContent.mid(50,14);//
  ist3[78]->setText(str10);
  QString str11= fifthFileContent.mid(64,4);//
  ist3[84]->setText(str11);
  QString str12= fifthFileContent.mid(68,16);//
  ist3[90]->setText(str12);
  QString str13= fifthFileContent.mid(84,12);//
  ist3[96]->setText(str13);
  tbvw3->resizeColumnsToContents();
  tbvw3->resizeRowsToContents();

}

void motwindow::buildfifthpage()
{
       int j=0;
       int colunm=0;
       pbtn4 = new QPushButton(fifthpage);
       pbtn4->setText("解析");
       textbw4 = new QTextEdit(fifthpage);
       textbw4->setPlaceholderText("请输入十六进制的1A文件数据,记录号为2");
       strloneafiletips << QList<QString>{"1A-02 公共汽电车应用信息记录",
       "字节","数据元","长度\n(字节)","数据格式","数据解析",
       "1~2","记录ID标识","2","2701"," ",
       "3","记录长度","1","固定为0x7D"," ",
       "4","应用有效标识","1","固定为0x01"," ",
       "5","互联互通交易标识","1","1-采用分时分段扣费/复合消费\n2-采用预授权消费"," ",
       "6","应用锁定标志(0-\n应用没有锁定；1-应用锁定)","1","BCD"," ",
       "7~14","交易流水号","8","BCD"," ",
       "15","交易状态","1","00:初始值\n01：上车\n02：下车 "," ",
       "16~17","上车城市代码","2","BCD"," ",
       "18~25","上车机构标识","8","BCD"," ",
       "26~27","上车运营商代码","2","HEX(高字节在前)"," ",
       "28~29","上车线路号","2","HEX(高字节在前)"," ",
       "30","上车站点","1","HEX(高字节在前)"," ",
       "31~38","上车车辆号","8","ASCII"," ",
        "39~46","上车终端编号","8","BCD"," ",
        "47~53","上车时间","7","YYYYMMDDhhmmss"," ",
        "54~57","标注金额","4","用于逃票追缴HEX(高字节在前)"," ",
        "58","方向标识","1","AB:上行/BA:下行"," ",
        "59~60","下车城市代码","2","BCD"," ",
        "61~68","下车机构标识","8","BCD"," ",
        "69~70","下车运营商代码","2","HEX(高字节在前)"," ",
        "71~72","下车线路号","2","HEX(高字节在前)"," ",
        "73","下车站点","1","HEX(高字节在前)"," ",
        "74~81","下车车辆号","8","ASCII"," ",
        "82~89","下车终端编号","8","BCD"," ",
        "90~96","下车时间","7","YYYYMMDDhhmmss"," ",
        "97~100","交易金额","4","HEX(高字节在前)"," ",
        "101~102","乘车里程","2","HEX(高字节在前)"," ",
        "103~128","预留","26"," "," "
        };
   //    QList<QStandardItem*> ist;
       QStandardItem* item;
       tbvw4 = new QTableView(fifthpage);
       stdmod4 = new QStandardItemModel(fifthpage);
       tbvw4->setModel(stdmod4);
       stdmod4->setColumnCount(5);

       qDebug()<<strloneafiletips.count();
       for(int i= 0;i<strloneafiletips.count();i++)
       {
            item = new QStandardItem(QString("%1").arg(strloneafiletips[i]));
            ist4.append(item);
            ist4[i]->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

            if(i == 0)
            {
               stdmod4->setItem(0,0,ist4[i]);
               j++;
            }
            else if (j <= 29)
            {
                stdmod4->setItem(j,colunm,ist4[i]);
                colunm++;
                if(colunm >= 5)
                {
                    j++;
                    colunm=0;
                }
            }
       }

       tbvw4->setSpan(0,0,1,5);//合并第一行0~5列
//       tbvw2->setSpan(1,0,1,4);//合并第二行0~2列
//       tbvw2->setSpan(1,4,1,2);//合并第二行3~5列
//       tbvw2->setSpan(2,0,1,4);
//       tbvw2->setSpan(2,4,1,2);
//       tbvw2->setSpan(3,0,1,4);
//       tbvw2->setSpan(3,4,1,2);
//       tbvw2->setSpan(4,0,1,4);
//       tbvw2->setSpan(4,4,1,2);
   //    tbvw2->setSpan(12,0,1,6);//合并第12行
       tbvw4->setEditTriggers(QAbstractItemView::NoEditTriggers);
       tbvw4->resizeColumnsToContents();
       tbvw4->resizeRowsToContents();

       fifthpagespl = new QSplitter(Qt::Vertical,fifthpage);//
       QWidget *wup = new QWidget(fifthpage);
       QHBoxLayout * layout1 = new QHBoxLayout(wup);//铺满布局

       layout1->addWidget(textbw4,5);
       layout1->addWidget(pbtn4,1);
       fifthpagespl->addWidget(wup);//firstpagethirdspl,textbw
       fifthpagespl->addWidget(tbvw4);
       fifthpagespl->setStretchFactor(0,2);
       fifthpagespl->setStretchFactor(1,8);
       QGridLayout *wdgt=new QGridLayout(fifthpage);
       wdgt->addWidget(fifthpagespl);

       connect(pbtn4,SIGNAL(clicked()),this,SLOT(showoneafile()));

}
void motwindow::showoneafile()
{
      QString fifthFileContent = textbw4->toPlainText().trimmed();
      QString strRx("(0x)?|,| |，| ");//("^[0x]+|,| ");这里不能要^,否则后面的0x检测不到
      QString textinput("[a-fA-F0-9,x ， ]+");//^[a-fA-F0-9,x]+
      QRegExp rxlen(textinput);
      qDebug()<<fifthFileContent;
      bool mt = rxlen.exactMatch(fifthFileContent);
      if(mt)
      {
          fifthFileContent.replace(QRegExp(strRx),"");
      }
      else
      {
          QMessageBox::warning(this,"警告","输入格式错误");
          return ;
      }
      qDebug()<<fifthFileContent;
      QString str1= fifthFileContent.mid(0,4);//2
      ist4[10]->setText(str1);
      QString str2= fifthFileContent.mid(4,2);//1
      ist4[15]->setText(str2);
      QString str3= fifthFileContent.mid(6,2);//1
      ist4[20]->setText(str3);
      QString str4= fifthFileContent.mid(8,2);//1
      ist4[25]->setText(str4);
      QString str5= fifthFileContent.mid(10,2);//1
      ist4[30]->setText(str5);
      QString str6= fifthFileContent.mid(12,16);//8
      ist4[35]->setText(str6);
      QString str7= fifthFileContent.mid(28,2);//1
      ist4[40]->setText(str7);
      QString str8= fifthFileContent.mid(30,4);//2
      ist4[45]->setText(str8);
      QString str9= fifthFileContent.mid(34,16);//8
      ist4[50]->setText(str9);
      QString str10= fifthFileContent.mid(50,4);//2
      ist4[55]->setText(str10);
      QString str11= fifthFileContent.mid(54,4);//2
      ist4[60]->setText(str11);
      QString str12= fifthFileContent.mid(58,2);//1
      ist4[65]->setText(str12);
      QString str13= fifthFileContent.mid(60,16);//8
      ist4[70]->setText(str13);
      QString str14= fifthFileContent.mid(76,16);//8
      ist4[75]->setText(str14);
      QString str15= fifthFileContent.mid(92,14);//7
      ist4[80]->setText(str15);
      QString str16= fifthFileContent.mid(106,8);//4
      ist4[85]->setText(str16);
      QString str17= fifthFileContent.mid(114,2);//1
      ist4[90]->setText(str17);
      QString str18= fifthFileContent.mid(116,4);//下车城市代码 2
      ist4[95]->setText(str18);
      QString str19= fifthFileContent.mid(120,16);//8
      ist4[100]->setText(str19);
      QString str20= fifthFileContent.mid(136,4);//2
      ist4[105]->setText(str20);
      QString str21= fifthFileContent.mid(140,4);//2
      ist4[110]->setText(str21);
      QString str22= fifthFileContent.mid(144,2);//1
      ist4[115]->setText(str22);
      QString str23= fifthFileContent.mid(146,16);//8
      ist4[120]->setText(str23);
      QString str24= fifthFileContent.mid(162,16);//8
      ist4[125]->setText(str24);
      QString str25= fifthFileContent.mid(178,14);//7
      ist4[130]->setText(str25);
      QString str26= fifthFileContent.mid(192,8);//4
      ist4[135]->setText(str26);
      QString str27= fifthFileContent.mid(200,4);//2
      ist4[140]->setText(str27);
      QString str28= fifthFileContent.mid(204,52);//26
      ist4[145]->setText(str28);
      tbvw4->resizeColumnsToContents();
      tbvw4->resizeRowsToContents();

}
