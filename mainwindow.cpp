#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtConcurrent>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


    //启动程序
    QString unreal4Path{"D:/QtProject/QtWithUnreal4/WindowsNoEditor/DemoGame.exe"};
    QStringList arguments;
    arguments << "-WINDOWED";
    process=new QProcess;
    process->start(unreal4Path,arguments);

    QtConcurrent::run([this]{
        while (true) {
            //通过窗口名称取得窗口句柄
            //hwnWindow=FindWindow(NULL,L"DemoGame  ");
            hwnWindow=FindWindow(NULL,L"DemoGame (32-bit, PCD3D_SM5) ");
            qDebug()<<hwnWindow;
            if(hwnWindow!=0)
            {
                SetParent(hwnWindow,(HWND)QWidget::winId());
                QRect rect=ui->label->geometry();
                MoveWindow(hwnWindow,0,0, rect.width(), rect.height(), true);

//                connect(this,SIGNAL(insetUe4Complete()),this,SLOT(repaint()));
//                emit insetUe4Complete();

                break;
            }
        }
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}
