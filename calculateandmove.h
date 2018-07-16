#ifndef CALCULATEANDMOVE_H
#define CALCULATEANDMOVE_H

#include <QWidget>
#include <QProcess>
#include "windows.h"
#include <QResizeEvent>
namespace Ui {
class CalculateAndMove;
}

class CalculateAndMove : public QWidget
{
    Q_OBJECT

public:
    explicit CalculateAndMove(QWidget *parent = 0);
    ~CalculateAndMove();
signals:
    void insetUe4Complete();

private slots:
    void on_insetUe4_clicked();

    void on_deleteUe4_clicked();

    void on_pushButton_clicked();

    void insetUe4();
private:
    Ui::CalculateAndMove *ui;
    QProcess *process;
     HWND hwnWindow;

    void startUe4();

    QWindow *ue4Window;

    void moveEvent(QMoveEvent *event);
};

#endif // CALCULATEANDMOVE_H
