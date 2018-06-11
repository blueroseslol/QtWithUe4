#include "mywindow.h"
#include <QDebug>
#include <QtConcurrent>
MyWindow::MyWindow()
{
    //启动程序
    QString unreal4Path{"D:/QtProject/QtWithUnreal4/WindowsNoEditor/DemoGame.exe"};
    QStringList arguments;
    arguments << "-WINDOWED";
    process=new QProcess;
    process->start(unreal4Path,arguments);

        while (true) {
            //通过窗口名称取得窗口句柄
            //hwnWindow=FindWindow(NULL,L"DemoGame  ");
            hwnWindow=FindWindow(NULL,L"DemoGame (32-bit, PCD3D_SM5) ");
            qDebug()<<hwnWindow;
            if(hwnWindow!=0)
            {
//                connect(this,SIGNAL(insetUe4Complete()),this,SLOT(repaint()));
//                emit insetUe4Complete();

                break;
            }
        }
insetUe4();
}

void MyWindow::insetUe4(){
        //隐藏窗口
        ShowWindow(hwnWindow,SW_HIDE);

       QWindow *win=QWindow::fromWinId(WId(hwnWindow));
       win->setParent(this);

//    SetParent(hwnWindow,(HWND)QWidget::winId());
//    QRect rect=ui->label->geometry();
//    MoveWindow(hwnWindow,0,0, rect.width(), rect.height(), true);
}
