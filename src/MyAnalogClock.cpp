/*********************************************************************/
/* Filename:    MyAnalogClock.cpp                                                                           	   */
/*                                                                                                                  */
/*                                                                                                                  */
/* Description: A analog clock widget component  of QT                     */
/*                                                                   */
/*                                                                                               */
/*                                                                                                                  */
/*  Author:      wangyunjin                                                                                */
/*  Email:      wyj0617mail@aliyun.com                                                             */
/*   Create:   2020-02-17                                                          		          */
/**********************************************************************/

/*********************************************************************/
/* Change History:                                                                                          */
/*     2020-02-17     wangyunjin  Created                                                             */
/*********************************************************************/

#define TAG "MyAnalogClock"
#include "MyAnalogClock.h"
#include "QPainter"
#include "QTime"
#include "QFile"


#define LOGI(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__,__func__,__LINE__, ##__VA_ARGS__);}
#define LOGW(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}
#define LOGE(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}
#define LOGT(fmt, ...) {printf("OS_" TAG "[%s]%s(%d) " fmt "\n", __FILE__, __func__,__LINE__, ##__VA_ARGS__);}

MyAnalogClock::MyAnalogClock(QWidget *parent)
    : QWidget(parent)
{
    LOGI("enter")
    setGeometry(100, 100, 500, 500);

    mBackgroudPixmap = nullptr;

    mTimer = new QTimer(this);
    connect(mTimer, SIGNAL(timeout()), this, SLOT(tipsSlots()));
    mTimer->start(1000);
}

MyAnalogClock::~MyAnalogClock()
{
    if (mBackgroudPixmap != nullptr)
        delete mBackgroudPixmap;
    mTimer->stop();
    delete mTimer;
}

bool MyAnalogClock::setBackgroundPicture(QString filePath) {

//    QString filePath = "D:\\project\\qt_workspace\\res\\black.jpg";
    QFile file(filePath);
    if (!file.exists()) {
        LOGI("file not exist")
        return false;
    }
    if (mBackgroudPixmap != nullptr) {
        delete mBackgroudPixmap;
    }
    mBackgroudPixmap = new QPixmap(filePath);
    return true;
}

void MyAnalogClock::tipsSlots() {
    LOGI("enter")
    this->update();
}


void MyAnalogClock::paintEvent(QPaintEvent *) {
    LOGI("enter")
    QPainter painter(this);

    if (mBackgroudPixmap != nullptr) {
        QRect rec(QPoint(0,0), QPoint(this->width(), this->height()));
        painter.drawPixmap(rec, *mBackgroudPixmap);
    }

    int hourHandSize = 5;
    int miniteHandSize = 4;
    int secondHandSize = 3;

    static const QPoint hourHand[3] = {
            QPoint(hourHandSize, 8),
            QPoint(-1*hourHandSize, 8),
            QPoint(0, -40)
        };
        static const QPoint minuteHand[3] = {
            QPoint(miniteHandSize, 8),
            QPoint(-1*miniteHandSize, 8),
            QPoint(0, -70)
        };

        static const QPoint secondHand[3] = {
            QPoint(secondHandSize, 8),
            QPoint(-1*secondHandSize, 8),
            QPoint(0, -90)
        };

        QColor hourColor(127, 0, 127);
        QColor minuteColor(0, 127, 127, 191);
        QColor secondColor(0, 0, 255, 191);

        painter.setRenderHint(QPainter::Antialiasing);
        painter.translate(width() / 2, height() / 2);

        int side = qMin(width(), height());
        painter.scale(side / 200.0, side / 200.0);

        painter.setPen(Qt::NoPen);
        painter.setBrush(hourColor);

        QTime time = QTime::currentTime();

        painter.save();
        painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
        painter.drawConvexPolygon(hourHand, 3);
        painter.restore();

        painter.setPen(hourColor);

        for (int i = 0; i < 12; ++i) {
            painter.drawLine(88, 0, 96, 0);
            painter.rotate(30.0);
        }

        painter.setPen(Qt::NoPen);
        painter.setBrush(minuteColor);

        painter.save();
        painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
        painter.drawConvexPolygon(minuteHand, 3);
        painter.restore();

        painter.setPen(Qt::NoPen);
        painter.setBrush(secondColor);

        painter.save();
        painter.rotate(6.0 * (time.second()));
        painter.drawConvexPolygon(secondHand, 3);
        painter.restore();

        painter.setPen(minuteColor);

        for (int j = 0; j < 60; ++j) {
            if ((j % 5) != 0)
                painter.drawLine(92, 0, 96, 0);
            painter.rotate(6.0);
        }
}


void MyAnalogClock::resizeEvent(QResizeEvent *resizeEvent)
{
    LOGI("enter");
}
