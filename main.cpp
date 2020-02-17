#include <QApplication>

#include "src/MyAnalogClock.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QString currentPath = QCoreApplication::applicationDirPath();
    printf("cur dir:%s\n", currentPath.toStdString().data());



    MyAnalogClock *myClock = new MyAnalogClock();
    myClock->show();
    QString filePath = "res/bg.jpg";
    myClock->setBackgroundPicture(filePath);



    return a.exec();
}
