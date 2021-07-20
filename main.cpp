#include "widget.h"
#include <QApplication>
#include "firmain.h"
#include "detail_tail.h"
#include "chat_main.h"
#include "group_chat.h"
#include "end.h"
#include "check.h"
#include "news.h"
#include "degree_of_friend.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    //先定义好六个要跳转的界面
    firmain f;      //好友列表
    detail_tail d;  //资料卡
    chat_main c;    //聊天
    group_chat g;   //组件群聊
    end e;          //群聊的聊天界面
    check ck;       //登陆后的验证界面
    news n;         //新闻界面
    degree_of_friend df;//好友亲密度界面

    //这一部分是登录界面往主好友页跳转的界面、登陆界面把信息传给主好友页
    QObject::connect(&w,SIGNAL(fmainshow()),&f,SLOT(receive_firmainshow()));
    QObject::connect(&w,SIGNAL(sendpeerlist(QString)),&f,SLOT(receive_peerlist(QString)));

    //这一部分是主好友页往资料卡页面跳转、主好友页把信息给信息展示页
    QObject::connect(&f,SIGNAL(showdetail()),&d,SLOT(receive_detail_show()));
    QObject::connect(&f,SIGNAL(send_detail(QString,QString,QString)),&d,SLOT(receive_detail_info(QString,QString,QString)));

    //这一部分是主好友界面往聊天窗体跳转、主好友页把信息传给聊天窗体、不聊天之后再次退出聊天窗体
    QObject::connect(&f,SIGNAL(showchat()),&c,SLOT(show_chat_main()));
    QObject::connect(&f,SIGNAL(send_chat_detail(QString,QString,QString,QString)),&c,SLOT(receive_chat_detail(QString,QString,QString,QString)));

    //这一部分是登陆界面的socket传给需要发送信息往服务器的、服务器本想往聊天界面发送但是只能通过登陆界面中专再传给
    QObject::connect(&w,SIGNAL(sendSocket(QTcpSocket*)),&c,SLOT(receive_socket(QTcpSocket*)));
    QObject::connect(&w,SIGNAL(sendchat_info(QString)),&c,SLOT(receive_from_widget(QString)));

    //这一部分是主聊天界面向组件群聊界面跳转的、主聊天界面向组件群聊界面发送列表
    QObject::connect(&f,SIGNAL(show_group_select()),&g,SLOT(receive_show_group()));
    QObject::connect(&f,SIGNAL(send_peer_list(QString)),&g,SLOT(receive_peerlist(QString)));

    //这一部分是组件群聊界面向群聊界面跳转、组件群聊界面向群聊聊天界面发送信息
    QObject::connect(&g,SIGNAL(showend()),&e,SLOT(receive_show_end()));
    QObject::connect(&g,SIGNAL(send_group_chat_info(QString)),&e,SLOT(receive_group_chat_info(QString)));

    //这一部分是登陆界面的socket传给群聊界面使用、服务器本想往群聊界面发送信息通过登陆界面中转
    //这一部分是登陆界面的socket传给需要发送信息往服务器的、服务器本想往聊天界面发送但是只能通过登陆界面中专再传给
    QObject::connect(&w,SIGNAL(sendSocket_group(QTcpSocket*)),&e,SLOT(receive_socket_group(QTcpSocket*)));
    QObject::connect(&w,SIGNAL(sendchat_info_group(QString)),&e,SLOT(receive_from_widget_group(QString)));

    //发送准确id的
    QObject::connect(&w,SIGNAL(send_id(QString)),&f,SLOT(receive_id(QString)));
    QObject::connect(&w,SIGNAL(send_id(QString)),&d,SLOT(receive_id(QString)));
    QObject::connect(&w,SIGNAL(send_id(QString)),&c,SLOT(receive_id(QString)));
    QObject::connect(&w,SIGNAL(send_id(QString)),&g,SLOT(receive_id(QString)));
    QObject::connect(&w,SIGNAL(send_id(QString)),&e,SLOT(receive_id(QString)));
    QObject::connect(&w,SIGNAL(send_id(QString)),&df,SLOT(receive_id(QString)));

    //登陆界面与验证界面的相互切换
    QObject::connect(&w,SIGNAL(show_check()),&ck,SLOT(receive_show_check()));
    QObject::connect(&w,SIGNAL(send_check_info(QString,QString)),&ck,SLOT(receive_check_info(QString,QString)));
    QObject::connect(&ck,SIGNAL(show_widget()),&w,SLOT(receive_show_widget()));

    //新闻界面与好友界面之间的跳转
    QObject::connect(&f,SIGNAL(show_news()),&n,SLOT(receive_show_news()));

    //主好友界面与好友亲密度之间的界面跳转、传信息
    QObject::connect(&f,SIGNAL(show_degree_of_friend()),&df,SLOT(receive_degree_of_friend()));
    QObject::connect(&f,SIGNAL(send_who(QString)),&df,SLOT(receive_who(QString)));

    //widget界面给好友亲密度界面传送信息
    QObject::connect(&w,SIGNAL(sendSocket_close_friend(QTcpSocket*)),&df,SLOT(receive_socket_close_friend(QTcpSocket *)));
    QObject::connect(&w,SIGNAL(send_close_info(QString)),&df,SLOT(receive_info(QString)));


    return a.exec();
}
