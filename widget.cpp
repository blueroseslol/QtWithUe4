#pragma comment(lib, "User32.lib")

#include "widget.h"
#include "ui_widget.h"
#include <QWindow>
#include <QDebug>
#include <QtConcurrent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),process(nullptr)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    //进程无法直接关闭,因为Ue4会启动另一个UeGame进程，如果是发布模式名字会改变
//    process->terminate();
//    process->waitForFinished();
    if(process){
        if(process->state()==QProcess::Running){
            process->terminate();
            process->waitForFinished(30000);
       }
    }
       delete process;
    delete ui;
}

void Widget::on_pushButton_clicked()
{
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


                 connect(this,SIGNAL(insetUe4Complete()),this,SLOT(insetQt()));
                 emit insetUe4Complete();

                break;
            }
        }
    });
}

void Widget::insetQt(){

    qDebug()<<hwnWindow;
    QWindow *window=QWindow::fromWinId((WId)hwnWindow);
    window->requestActivate();
    window->setKeyboardGrabEnabled(true);
    window->setMouseGrabEnabled(true);

//    QWidget *windowWidget=QWidget::createWindowContainer(window);
    window->show();
    //windowWidget->show();

//        qDebug()<<state;
//    if(state!=QProcess::Running)
//        return;

//    Sleep(3000);
//    //可以在项目设置中修改窗口显示标题，可以把讨厌的(32-bit, PCD3D_SM5)去掉
//    //强烈推荐使用窗口句柄查看工具，我是网上下了句柄精灵
//    HWND hwnWindow=FindWindow(NULL,L"DemoGame  ");

//    qDebug()<<hwnWindow;
//    QWindow *window=QWindow::fromWinId((WId)hwnWindow);

////方法一
////        SetParent(hwnWindow,(HWND)QWidget::winId());
////        window->showFullScreen();
////方法二
//     window->requestActivate();
////     //嵌入Qt窗口,需要设置焦点让Ue4接受按键事件
//     QWidget *windowWidget=QWidget::createWindowContainer(window,nullptr,Qt::Window);
////     QWidget *windowWidget=QWidget::createWindowContainer(window);

//     //获取键盘与鼠标的输入
//     window->setKeyboardGrabEnabled(true);
//     window->setMouseGrabEnabled(true);
//     ui->verticalLayout->insertWidget(0,windowWidget,1);
////     windowWidget->setFocusPolicy(Qt::StrongFocus);
////     windowWidget->setFocus();
////     windowWidget->grabKeyboard();
////     windowWidget->grabMouse();
//     this->setFocusPolicy(Qt::NoFocus);

}

