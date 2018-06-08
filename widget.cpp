#pragma comment(lib, "User32.lib")

#include "widget.h"
#include "ui_widget.h"
#include "windows.h"
#include <QWindow>
#include <QDebug>

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
    if(process)
        delete process;
    delete ui;
}

void Widget::on_pushButton_clicked()
{
//      //因为启动的进程并非游戏进程，所以通过QProcess的状态来判断Ue4是否启动是不对的
//      //推荐使用WINAPI来获取对应线程
    QString unreal4Path{"D:/QtProject/QtWithUnreal4/WindowsNoEditor/DemoGame.exe"};
    QStringList arguments;
    arguments << "-WINDOWED";
    process=new QProcess;
    connect(process,SIGNAL(stateChanged(QProcess::ProcessState)),this,SLOT(insetQt(QProcess::ProcessState)));
    process->start(unreal4Path,arguments);

//    WinExec("D:\\QtProject\\QtWithUnreal4\\WindowsNoEditor\\DemoGame.exe",SW_HIDE);

}

void Widget::insetQt(QProcess::ProcessState state){
        qDebug()<<state;
    if(state!=QProcess::Running)
        return;

    Sleep(3000);
    //可以在项目设置中修改窗口显示标题，可以把讨厌的(32-bit, PCD3D_SM5)去掉
    //强烈推荐使用窗口句柄查看工具，我是网上下了句柄精灵
    HWND hwnWindow=FindWindow(NULL,L"DemoGame  ");

    qDebug()<<hwnWindow;
    QWindow *window=QWindow::fromWinId((WId)hwnWindow);

//方法一
//        SetParent(hwnWindow,(HWND)QWidget::winId());
//        window->showFullScreen();
//方法二
     window->requestActivate();
//     //嵌入Qt窗口,需要设置焦点让Ue4接受按键事件
     QWidget *windowWidget=QWidget::createWindowContainer(window,nullptr,Qt::Window);
//     QWidget *windowWidget=QWidget::createWindowContainer(window);

     //获取键盘与鼠标的输入
     window->setKeyboardGrabEnabled(true);
     window->setMouseGrabEnabled(true);
     ui->verticalLayout->insertWidget(0,windowWidget,1);
//     windowWidget->setFocusPolicy(Qt::StrongFocus);
//     windowWidget->setFocus();
//     windowWidget->grabKeyboard();
//     windowWidget->grabMouse();
     this->setFocusPolicy(Qt::NoFocus);

}

