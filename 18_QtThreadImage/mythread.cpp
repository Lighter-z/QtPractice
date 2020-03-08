#include "mythread.h"
#include <QPainter>

myThread::myThread(QObject *parent) : QObject(parent)
{

}

void myThread::drawImage()
{
    QImage image(500,500,QImage::Format_ARGB32);

    QPainter painter(&image);

    QPen pen;
    pen.setWidth(5);
    painter.setPen(pen);

    QBrush brush;
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::green);
    painter.setBrush(brush);

    QPoint point[] = {
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
        QPoint(qrand()%500,qrand()%500),
    };

    painter.drawPolygon(point,5);

    emit updateImage(image);
}
