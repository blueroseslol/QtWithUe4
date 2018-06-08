#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QProcess>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_clicked();

    void insetQt(QProcess::ProcessState state);

private:
    Ui::Widget *ui;
    QProcess *process;
};

#endif // WIDGET_H
