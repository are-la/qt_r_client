#ifndef GROUP_CHAT_H
#define GROUP_CHAT_H

#include <QWidget>
#include "header.h"

namespace Ui {
class group_chat;
}

class group_chat : public QWidget
{
    Q_OBJECT

public:
    explicit group_chat(QWidget *parent = nullptr);
    ~group_chat();

    QString my_id;

signals:
    void showend();

    void send_group_chat_info(QString);

private slots:
    //接收主聊天界面点击发起群聊后显示组件好友列表的信息、好友界面向组件好友列表发送列表信息
    void receive_show_group();

    void receive_peerlist(QString peerlist);

    //当点击确定按钮后的操作
    void on_click_confirm_btn();

    //接收准确id的
    void receive_id(QString sure_id);

private:
    Ui::group_chat *ui;
    QPushButton *confirm_btn;
};

#endif // GROUP_CHAT_H
