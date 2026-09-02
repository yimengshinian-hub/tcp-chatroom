#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,server(new QTcpServer)
{
    ui->setupUi(this);
    server->listen(QHostAddress::AnyIPv4,PORT);
    connect(server,&QTcpServer::newConnection,this,&Widget::newClientHandler);
}
// 在 newClientHandler() 中
void Widget::newClientHandler(){
    QTcpSocket* socket = server->nextPendingConnection();//建立TCP连接
    //socket->peerAddress();//客户端地址
    //socket->peerPort();//客户端端口号
    ui->ipLineEdit->setText(socket->peerAddress().toString());
    ui->portLineEdit->setText(QString::number(socket->peerPort()));
    //服务端收到客户端发送的信息socket发出readyread信号
   // connect(socket,&QTcpSocket::readyRead,this,&Widget::clientInfoSlot);
    //启动线程
    myThread* t = new myThread(socket);
    clientList.append(t);   // 添加到列表
    t->start();
    // 显示消息
    connect(t, &myThread::sendToWidget, this, &Widget::threadSlot);
    // 转发给所有客户端
    connect(t, &myThread::sendToAll, this, &Widget::broadcastMessage);
    //客户端断开时清理
    connect(t, &myThread::disconnected, this, &Widget::removeClient);
}
void Widget::broadcastMessage(QByteArray ba){
    // 遍历所有已连接的线程，把消息发出去
    for (myThread* thread : clientList) {
        thread->sendMessage(ba);
    }
}
void Widget::removeClient(){
    myThread* t = qobject_cast<myThread*>(sender());
    if (t) {
        clientList.removeAll(t);
        t->deleteLater();
    }
}
//void Widget::clientInfoSlot(){
//    //获取信号发出者
//    QTcpSocket* s = (QTcpSocket*)sender();
//    QString data(s->readAll());
//    ui->mainLineEdit->setText(data);
//}
void Widget::threadSlot(QByteArray ba){
    ui->mainTextBrowser->append(QString(ba));
}
Widget::~Widget()
{
    delete ui;
}

