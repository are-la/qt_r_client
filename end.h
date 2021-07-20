#ifndef END_H
#define END_H

#include <QMainWindow>
#include "header.h"

namespace Ui {
class end;
}

class end : public QMainWindow
{
    Q_OBJECT

public:
    explicit end(QWidget *parent = nullptr);
    ~end();

    QString my_id;

private slots:
    //接收从组件群聊界面传来的数据
    void receive_show_end();

    void receive_group_chat_info(QString end_str);

    //这两个是接收登陆界面传来的socket 和传来的服务器的响应
    void receive_socket_group(QTcpSocket *temsocket);

    void receive_from_widget_group(QString chat_info);

    //当点击发送信息按钮
    void on_pushButton_clicked();

    //接收准确id的
    void receive_id(QString sure_id);

private:
    Ui::end *ui;
    QTcpSocket *group_chatsocket;
};

#endif // END_H
