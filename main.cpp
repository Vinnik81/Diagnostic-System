#include "alarmwindow.h"
#include "imageWindowMap.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AlarmWindow alarmWindow;

    alarmWindow.show();
    return a.exec();
}
