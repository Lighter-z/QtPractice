#ifndef CLIENTWIDGET_H
#define CLIENTWIDGET_H

#include <QWidget>
#include <QTcpSocket>

namespace Ui {
class ClientWidget;
}

class ClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ClientWidget(QWidget *parent = nullptr);
    ~ClientWidget();

private slots:
    void on_connectBtn_clicked();

    void on_sendBtn_clicked();

    void on_closeBtn_clicked();

private:
    Ui::ClientWidget *ui;
public:
    QTcpSocket * tcp_socket;
};

#endif // CLIENTWIDGET_H
