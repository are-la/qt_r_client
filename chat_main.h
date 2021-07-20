#ifndef CHAT_MAIN_H
#define CHAT_MAIN_H

#include <QMainWindow>
#include"header.h"

namespace Ui {
class chat_main;
}

class chat_main : public QMainWindow
{
    Q_OBJECT

public:
    explicit chat_main(QWidget *parent = nullptr);
    ~chat_main();

    QString goal_num,goal_name,my_num,my_name;

    QString my_id;

signals:
    void showfirmain();

private slots:
    //这两个是好友列表往聊天界面跳转、往聊天界面传信息
    void show_chat_main();

    void receive_chat_detail(QString,QString,QString,QString);

    //两个按钮，一个是回到好友列表界面，另一个发送信息
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    //这两个是用来接收socket、接收服务器返回给登陆界面然后通过登陆界面中转信息的（因为服务器返回时返回给了第一个socket的位置）
    void receive_socket(QTcpSocket *temsocket);

    void receive_from_widget(QString chat_info);

    //接收准确id的
    void receive_id(QString sure_id);

private:
    Ui::chat_main *ui;
    QTcpSocket *chatsocket;
};

#endif // CHAT_MAIN_H
