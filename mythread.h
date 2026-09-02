#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include<QThread>
#include<QTcpSocket>
#include<QDebug>
class myThread :public QThread
{
    Q_OBJECT
public:
    explicit myThread(QTcpSocket* s,QObject *parent = nullptr);
    void run() override;
    void sendMessage(const QByteArray& ba);
signals:
    void sendToWidget(QByteArray b);
    void sendToAll(QByteArray ba);
    void disconnected();
public slots:
    void clientInfoSlot();
    void clientDisconnected();
private:
    QTcpSocket* socket;
};

#endif // MYTHREAD_H
