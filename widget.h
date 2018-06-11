#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
#include "windows.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
     HWND hwnWindow;
signals:
    void insetUe4Complete();
private slots:
    void on_pushButton_clicked();

    void insetQt();

private:
    Ui::Widget *ui;
    QProcess *process;

};

#endif // WIDGET_H
