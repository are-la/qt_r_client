#ifndef FIRMAIN_H
#define FIRMAIN_H

#include <QWidget>
#include"header.h"

namespace Ui {
class firmain;
}

class firmain : public QWidget
{
    Q_OBJECT

public:
    explicit firmain(QWidget *parent = nullptr);
    ~firmain();

    //用于中转并传递好友列表的中间字符串
    QString transfer_str;

    QString my_id;

//    int pmark;

signals:
    //这两个是给资料卡发送信号、发送字串的
    void showdetail();

    void send_detail(QString,QString,QString);

    //与聊天页通信的信号
    void showchat();

    void send_chat_detail(QString,QString,QString,QString);//与聊天页主要传四个数据，自己的num name  要聊天对象的num name

    //这两个是给创建群聊界面
    void show_group_select();

    void send_peer_list(QString);

    //给展示资料界面
    void show_news();

    //给好友亲密度界面发送是谁的一个信号
    void show_degree_of_friend();

    void send_who(QString);


private slots:
    //这两个是接收登陆界面的传来的展示主好友界面信号、好友界面接收信号的
    void receive_firmainshow();

    void receive_peerlist(QString total_peerlist);

    //这两个是对好友列表分别查资料和发起聊天的
    void onclick();

    void onItemClicked(QListWidgetItem *item);

    void onItemClicked2(QListWidgetItem *item);

    //这个是当点击组件群聊按钮的
    void on_click_group_chat_btn();

    //接收准确id的
    void receive_id(QString sure_id);

    //这个是当点击查看每日热点按钮
    void  on_click_news();

    //这个是当点击好友亲密度的按钮
    void on_click_close_friend();

private:
    Ui::firmain *ui;

    QHBoxLayout *hlayout;

    QVBoxLayout *vlayout;

    int flag;
};

#endif // FIRMAIN_H
