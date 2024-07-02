#include "alarmwindowsvg.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlarmWindowSvg w;
    w.show();
    return a.exec();
}
