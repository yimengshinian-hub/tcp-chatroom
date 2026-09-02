#include "mythread.h"

myThread::myThread(QTcpSocket* s,QObject *parent):QThread(parent)
{
    socket = s;
}
void myThread::run(){
    connect(socket,&QTcpSocket::readyRead,this,&myThread::clientInfoSlot);
    connect(socket, &QTcpSocket::disconnected, this, &myThread::clientDisconnected);
}
void myThread::clientInfoSlot(){
    QByteArray ba = socket->readAll();
    emit sendToWidget(ba);          // 显示在服务器界面
    emit sendToAll(ba);             // 转发给所有客户端
}
void myThread::clientDisconnected(){
    socket->deleteLater();
    socket = nullptr;
    // 通知 Widget 移除自己
    emit disconnected();
}
void myThread::sendMessage(const QByteArray& ba){
    if (socket) {
        socket->write(ba);
    }
}
