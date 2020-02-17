/*********************************************************************/
/* Filename:    MyAnalogClock.h                                                                           	   */
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

#ifndef MYANALOGCLOCK_H
#define MYANALOGCLOCK_H

#include <QWidget>
#include "QTimer"

class MyAnalogClock : public QWidget
{
    Q_OBJECT
public:
    explicit MyAnalogClock(QWidget *parent = 0);
    ~MyAnalogClock();

    bool setBackgroundPicture(QString filePath);

public slots:
    void tipsSlots();

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);

private:
    QTimer *mTimer;
    QPixmap *mBackgroudPixmap;
};



#endif // MYANALOGCLOCK_H
