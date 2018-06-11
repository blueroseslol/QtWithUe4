#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QWindow>
#include <QProcess>
#include "windows.h"
#include <QResizeEvent>
class MyWindow : public QWindow
{
public:
    MyWindow();
    ~MyWindow();
    QProcess *process;
     HWND hwnWindow;
signals:
    void insetUe4Complete();

private slots:
    void on_insetUe4_clicked();

    void on_deleteUe4_clicked();

    void on_pushButton_clicked();

    void startUe4();

    void insetUe4();

    void resizeEvent(QResizeEvent *event);
};

#endif // MYWINDOW_H
