#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QImage>

class myThread : public QObject
{
    Q_OBJECT
public:
    explicit myThread(QObject *parent = nullptr);

    void drawImage();

signals:
    void updateImage(QImage);
};

#endif // MYTHREAD_H
