//#include "widget.h"
#include <QApplication>

//方法A通过计算Layout中的占位用Label，来获得geometry，最后通过resize事件设置ue4
#define mothodA 1
//方法B
#define mothodB 0

#if mothodA
#include "calculateandmove.h"
//#include "mainwindow.h"
//#include "widget.h"
//#include "mywindow.h"
#endif

#if mothodB

#endif

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

//    a.setAttribute(Qt::AA_NativeWindows);

#if mothodA
    CalculateAndMove w;
    w.show();
#endif

#if mothodB

#endif
    return a.exec();
}
