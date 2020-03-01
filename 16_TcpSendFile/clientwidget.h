#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QFile>

namespace Ui {
class clientwidget;
}

class clientwidget : public QWidget
{
    Q_OBJECT

public:
    explicit clientwidget(QWidget *parent = nullptr);
    ~clientwidget();

private slots:
    void on_connectButton_clicked();

private:
    Ui::clientwidget *ui;
    QTcpSocket * tcp_socket;

    QFile file;
    QString fileName;
    qint64 fileSize;
    qint64 recvSize;

    bool isStart;
};

#endif // CLIENTWIDGET_H
