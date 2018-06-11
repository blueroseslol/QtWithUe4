#include "calculateandmove.h"
#include "ui_calculateandmove.h"
#include <QDebug>
#include <QtConcurrent>
#include <QThread>
CalculateAndMove::CalculateAndMove(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CalculateAndMove),process(nullptr)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
}

CalculateAndMove::~CalculateAndMove()
{
    if(hwnWindow!=0)
        SendMessage(hwnWindow,WM_CLOSE,0,0);
    if(process){
        if(process->state()==QProcess::Running){
            process->terminate();
            process->waitForFinished(30000);
       }
       delete process;
   }
    delete ui;
}

void CalculateAndMove::on_insetUe4_clicked()
{
    startUe4();
}

void CalculateAndMove::on_deleteUe4_clicked()
{
    if(hwnWindow==0)
        return;
    SendMessage(hwnWindow,WM_CLOSE,0,0);
}

void CalculateAndMove::startUe4(){
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

                connect(this,SIGNAL(insetUe4Complete()),this,SLOT(repaint()));
                emit insetUe4Complete();

                break;
            }
        }
    });
}

void CalculateAndMove::on_pushButton_clicked()
{
        BringWindowToTop (hwnWindow);
        SetForegroundWindow(hwnWindow);
}

//void CalculateAndMove::resizeEvent(QResizeEvent *event){

//    QPoint pos=ui->label->mapToGlobal(ui->label->pos());
//    SetParent(hwnWindow,(HWND)QWidget::winId());
//    QRect rect=ui->label->geometry();
////    MoveWindow(hwnWindow,pos.x(), pos.y(), rect.width()-ui->label->pos().x(), rect.height()-ui->label->pos().y(), false);

//    SetWindowPos(hwnWindow,       // handle to window
//                                                                                   HWND_TOPMOST,  // placement-order handle
//                                                                                   pos.x(), pos.y(), rect.width()-ui->label->pos().x(), rect.height()-ui->label->pos().y(),
//                                                                                   SWP_SHOWWINDOW);
//    event->accept();
//}

//void CalculateAndMove::moveEvent(QMoveEvent *event){
//    QPoint pos=ui->label->mapToGlobal(ui->label->pos());
//    //SetParent(hwnWindow,(HWND)QWidget::winId());
//    QRect rect=ui->label->geometry();
////    MoveWindow(hwnWindow,pos.x(), pos.y(), rect.width()-ui->label->pos().x(), rect.height()-ui->label->pos().y(), false);

//    SetWindowPos(hwnWindow,       // handle to window
//                                                                                   HWND_TOPMOST,  // placement-order handle
//                                                                                   pos.x(), pos.y(), rect.width()-ui->label->pos().x(), rect.height()-ui->label->pos().y(),
//                                                                                   SWP_SHOWWINDOW);
//    event->accept();
//}
