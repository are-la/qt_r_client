#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "header.h"

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    bool is_checked;

signals:
    //这两个是往主好友列表发送
    void fmainshow();

    void sendpeerlist(QString);

    //这两个是往聊天界面发送的
    void sendSocket(QTcpSocket*);

    void sendchat_info(QString);

    //这两个是往群聊界面发送的
    void sendSocket_group(QTcpSocket*);

    void sendchat_info_group(QString);



    //往每个界面发送个人id的
    void send_id(QString);

    //往检查界面发送字串验证是否正确
    void show_check();

    void send_check_info(QString,QString);

    //往亲密度界面发送socket、往亲密度界面传送信息
    void sendSocket_close_friend(QTcpSocket*);

    void send_close_info(QString);


private slots:
    //确认登陆的界面
    void on_pushButton_clicked();

    //接收服务器返回给这个socket的所有消息=>包括返给
    void printServerMes();

    //接收传回来的让开启的信号
    void receive_show_widget();

private:
    Ui::Widget *ui;
    QTcpSocket *client;
    int flag;
};

#endif // WIDGET_H
