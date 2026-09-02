#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include <QList>
#include"mythread.h"
#define PORT 2025
QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();
private slots:
    void newClientHandler();
    //void clientInfoSlot();
    void threadSlot(QByteArray b);
    void broadcastMessage(QByteArray ba);
    void removeClient();
private:
    Ui::Widget *ui;
    QTcpServer* server;
    QList<myThread*> clientList;
};
#endif // WIDGET_H
