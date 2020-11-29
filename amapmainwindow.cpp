#pragma execution_character_set("utf-8")//防止中文乱码
#include "amapmainwindow.h"
#include "ui_amapmainwindow.h"
#include <QNetworkProxyFactory>
#include <QSize>
AMapMainWindow::AMapMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::AMapMainWindow)
{
    ui->setupUi(this);
    setWindowTitle("AMapMarkTools地图打点小工具");
    p_AmapViewWedget = new QMainWindow();//用于放置webView
    p_AmapView=new QWebEngineView(p_AmapViewWedget);//将QWebEngineView的父Widget为p_AmapViewWedget
    p_AmapViewWedget->setCentralWidget(p_AmapView);
    p_AmapHLayoutWidget = new QWidget(this);//用于将webView放置在AMapMainWindow
    p_AmapHLayoutWidget->setObjectName(QString::fromUtf8("p_AmapHLayoutWidget"));
    p_AmapHLayoutWidget->setGeometry(QRect(0, 0, 720, 480));//窗口大小为720*480
    p_AmapHLayoutWidget->move(200,0);
    p_AmapHLayout=new QHBoxLayout(p_AmapHLayoutWidget);
    p_AmapHLayout->addWidget((QWidget *)p_AmapViewWedget);
    setLayout(p_AmapHLayout);
    p_AmapChannel = new QWebChannel(this);   //创建通道,与JS交互
    p_AmapBridge=new JSWebBridge(); //创建通道,与JS交互
    p_AmapChannel->registerObject("amap_bridge",(QObject*)p_AmapBridge);// 注册名"amap_bridge"与JS中用到的名称保持相同
    QNetworkProxyFactory::setUseSystemConfiguration(false);
    p_AmapView->page()->setWebChannel(p_AmapChannel);//View与chanel建立连接关系
    QString htmlFilePath =QApplication::applicationDirPath()+"/amapmarktools.html";
    p_AmapView->page()->load(QUrl(htmlFilePath));
    p_AmapView->page()->setBackgroundColor(Qt::transparent);//背景透明
    this->setMinimumWidth(720);
    this->setMinimumHeight(480);
    p_operaterLayoutWidget=new QWidget(this);
    p_addOneMark=new QPushButton(p_operaterLayoutWidget);
    p_addOneMark->setFixedSize(QSize(100,30));
    p_addOneMark->setText("增加标记");
    p_addMarkFromFile=new QPushButton(p_operaterLayoutWidget);
    p_addMarkFromFile->setFixedSize(QSize(100,30));
    p_addMarkFromFile->setText("从文件导入标记");
    p_removeAllMark=new QPushButton(p_operaterLayoutWidget);
    p_removeAllMark->setFixedSize(QSize(100,30));
    p_removeAllMark->setText("删除所有标记");
    p_saveAllMarkToFile=new QPushButton(p_operaterLayoutWidget);
    p_saveAllMarkToFile->setFixedSize(QSize(100,30));
    p_saveAllMarkToFile->setText("导出所有标记");
    p_operaterLayout=new QVBoxLayout(p_operaterLayoutWidget);
    p_operaterLayoutWidget->setGeometry(QRect(0, 0, 200, 480));
    p_operaterLayoutWidget->move(0,0);
    p_operaterLayout->addWidget(p_addOneMark);
    p_operaterLayout->addWidget(p_addMarkFromFile);
    p_operaterLayout->addWidget(p_saveAllMarkToFile);
    p_operaterLayout->addWidget(p_removeAllMark);
    setLayout(p_operaterLayout);
    p_operaterLayout->setAlignment(Qt::AlignJustify);
}

AMapMainWindow::~AMapMainWindow()
{
    delete ui;
}

void AMapMainWindow::resizeEvent(QResizeEvent* size)
{
    QSize m_size= this->size();
    p_AmapHLayoutWidget->setGeometry(QRect(0, 0, m_size.width()-200,m_size.height()));//窗口大小为720*480
    p_AmapHLayoutWidget->move(200,0);
    p_operaterLayoutWidget->setGeometry(QRect(0, 0, 200, m_size.height()));
    p_operaterLayoutWidget->move(0,0);
}
