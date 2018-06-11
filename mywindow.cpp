#include "mywindow.h"
#include <QDebug>
#include <QtConcurrent>
#include <QThread>
MyWindow::MyWindow():process(nullptr)
{
    this->resize(1280,720);
}

MyWindow::~MyWindow(){
    if(hwnWindow!=0)
        SendMessage(hwnWindow,WM_CLOSE,0,0);
    if(process){
        if(process->state()==QProcess::Running){
            process->terminate();
            process->waitForFinished(30000);
       }
       delete process;
   }
}

void MyWindow::startUe4(){
        connect(this,SIGNAL(insetUe4Complete()),this,SLOT(insetUe4()));
    QtConcurrent::run([this]{
        //启动程序
        QString unreal4Path{"D:/QtProject/QtWithUnreal4/WindowsNoEditor/DemoGame.exe"};
        QStringList arguments;
        arguments << "-WINDOWED";
        process=new QProcess;
        process->start(unreal4Path,arguments);
        while (true) {
            //通过窗口名称取得窗口句柄
            hwnWindow=FindWindow(NULL,L"DemoGame (32-bit, PCD3D_SM5) ");
            qDebug()<<hwnWindow;
            if(hwnWindow!=0)
            {
                QThread::sleep(5000);
                insetUe4();
                break;
            }
        }
    });
}

void MyWindow::insetUe4(){
        //隐藏窗口
        ShowWindow(hwnWindow,SW_HIDE);

       QWindow *win=QWindow::fromWinId(WId(hwnWindow));
       win->setParent(this);

       win->setPosition(0,0);
//    SetParent(hwnWindow,(HWND)QWidget::winId());
//    QRect rect=ui->label->geometry();
//    MoveWindow(hwnWindow,0,0, rect.width(), rect.height(), true);
}

void MyWindow::resizeEvent(QResizeEvent *event){


}
