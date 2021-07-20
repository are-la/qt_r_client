#include "firmain.h"
#include "ui_firmain.h"
#include "mybutton.h"
//#include <synchapi.h>

struct peer:QObjectUserData{
    QString num;   //账号
    QString name;  //昵称
    QString style;  //个性签名
    QString want_to_talk_with;
    QString is_on;  //是否在线
};
QVector<peer> detail_peer;

struct request_data{
    myButton *data_btn;
    QString dnum;   //账号
    QString dname;  //昵称
    QString dstyle;  //个性签名
    QString dwant_to_talk_with;
    QString dis_on;  //是否在线
};
QVector<request_data> re_look_data;

struct request_chat{
    myButton *chat_btn;
    QString cnum;   //账号
    QString cname;  //昵称
    QString cstyle;  //个性签名
    QString cwant_to_talk_with;
    QString cis_on;  //是否在线
};
QVector<request_chat> re_chat;

firmain::firmain(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::firmain)
{
    hlayout = new QHBoxLayout();
//    vlayout = new QVBoxLayout();
//    pmark = 0;
    flag = 0;
}

firmain::~firmain()
{
    delete ui;
}

void firmain::receive_firmainshow()
{
    this->show();
}

void firmain::receive_peerlist(QString total_peerlist)
{
    if(flag){
        hlayout->removeItem(vlayout);
        qDebug()<<"remove 原来的vlayout"<<endl;
    }
    flag = 1;
//    先清空vlayout
//    QLayoutItem *child;
//    while ((child = vlayout->takeAt(0)) != 0)
//    {
//        //setParent为NULL，防止删除之后界面不消失
//        if(child->widget())
//        {
//            child->widget()->setParent(NULL);
//        }

//        delete child;
//    }
    //要先更新列表
    detail_peer.clear();
    //在这里打表，看看第二次有没有进入从而更新向量
    qDebug()<<"进入了一次解析列表"<<endl;
    transfer_str = total_peerlist;
    //这里拿到了服务器传回给客户端，然后客户端界面切换，换到这个界面的之后传过来的数据,就是total_peerlist
    //先拿出最后一个-来提取出列表中的总用户的个数，然后在开QVector 来储存这些
    int pos_the_first;  //先定义一个第一个-的位置
    for(int i = 0;i<total_peerlist.size();i++){
        if(total_peerlist[i] == '-'){
            pos_the_first = i;
            break;
        }
    }
    qDebug()<<pos_the_first<<endl;
    int total_peer_num ;   //定义总长度
    //定义切开后的两个字符串
    QString total_peer_num_str,real_peerlist;
    total_peer_num_str = total_peerlist.mid(0,pos_the_first);
    for (int i = pos_the_first+1;i <total_peerlist.size() ;i++) {
        real_peerlist[i-pos_the_first-1] = total_peerlist[i];
    }
    total_peer_num = total_peer_num_str.toInt();
    qDebug()<<total_peer_num_str <<"  "<<real_peerlist<<endl;


    //在然后对拿到的real_peerlist 进行正则拆分
    QVector<QString> all_one_peer; //首先定义

    //第一次正则：是通过 '-' 进行拆分
    for (int i = 0;i < total_peer_num;i++) {
        all_one_peer.push_back(real_peerlist.section('-',i,i));  //将截取到的字符串进行push_back到向量
    }
    //输出向量中的元素检验
    for (int i = 0;i < all_one_peer.size();i++) {
        qDebug()<<all_one_peer[i]<<endl;
    }

    //第二次正则：是通过 '*' 进行拆分
    for (int i = 0;i < total_peer_num;i++) {
        peer tempeer;
        tempeer.num = all_one_peer[i].section('*',0,0);
        tempeer.name = all_one_peer[i].section('*',1,1);
        tempeer.style = all_one_peer[i].section('*',2,2);
        tempeer.want_to_talk_with = all_one_peer[i].section('*',3,3);
        tempeer.is_on = all_one_peer[i].section('*',4,4);
        detail_peer.push_back(tempeer);
    }
    //输出第二次拆分后的所有元素（详细信息）
    for (int i = 0;i < total_peer_num;i++) {
        qDebug()<<"账号："<< detail_peer[i].num<<" 昵称："<<detail_peer[i].name<<" 个性签名："<<detail_peer[i].style<<" 想和谁聊天："<<detail_peer[i].want_to_talk_with<<" 是否在线："<<detail_peer[i].is_on<<endl;
    }


    //添加群聊系统
    //添加一个跳转按钮，让界面跳转
    //添加一个计算亲密度的跳转按钮
    QPushButton *close_friend = new QPushButton();
    close_friend->setStyleSheet("QPushButton{  background-color: rgb(6,157,213); border: none;border-radius:2px;color:white;}"
                                  "QPushButton:hover{ background-color: rgb(75,202,255);}");
    close_friend->setText("好友亲密度");

    QPushButton *news = new QPushButton();
    news->setStyleSheet("QPushButton{  background-color: rgb(6,157,213); border: none;border-radius:2px;color:white;}"
                                  "QPushButton:hover{ background-color: rgb(75,202,255);}");
    news->setText("每日热点");

    QPushButton *group_chat_btn = new QPushButton();
    group_chat_btn->setStyleSheet("QPushButton{  background-color: rgb(6,157,213); border: none;border-radius:2px;color:white;}"
                                  "QPushButton:hover{ background-color: rgb(75,202,255);}");
    group_chat_btn->setText("组建群聊");

    QObject::connect(group_chat_btn,&QPushButton::clicked,this,&firmain::on_click_group_chat_btn);
    QObject::connect(news,&QPushButton::clicked,this,&firmain::on_click_news);
    QObject::connect(close_friend,&QPushButton::clicked,this,&firmain::on_click_close_friend);

//    this->resize(400,55*detail_peer.size());
    //此时要创建QlistWidget类 => 用来展示所有的人的数据
    QListWidget *pListWidget = new QListWidget(this);
    for (int i = 0;i<detail_peer.size();i++) {
        QListWidgetItem *pItem = new QListWidgetItem(pListWidget);
        pItem->setSizeHint(QSize(150,50));
        pItem->setData(Qt::UserRole, detail_peer[i].num);  // 用户数据
        pItem->setData(Qt::UserRole + 1, detail_peer[i].name);  // 用户数据
        pListWidget->addItem(pItem);
        pItem->setText("ID："+detail_peer[i].num+"    昵称："+detail_peer[i].name);  // 文本
        pItem->setBackgroundColor(QColor((200-10*i)%100+100,224,251));
    }
    //按钮纵向排版
    QObject::connect(pListWidget, &QListWidget::itemClicked, this, &firmain::onItemClicked);




    //然后把下面这段转换成用listwidget渲染
    QListWidget *plistWidget2 = new QListWidget(this);
    for (int i = 0;i <detail_peer.size();i++) {
        QListWidgetItem *pItem = new QListWidgetItem(plistWidget2);
        pItem->setSizeHint(QSize(150,50));
        pItem->setData(Qt::UserRole, detail_peer[i].num);  // 用户数据
        pItem->setData(Qt::UserRole + 1, detail_peer[i].name);  // 用户数据
        pItem->setText("chat with "+detail_peer[i].name);
        plistWidget2->addItem(pItem);
        pItem->setBackgroundColor(QColor((200-10*i)%100+100,224,251));
    }

    QObject::connect(plistWidget2,&QListWidget::itemClicked,this,&firmain::onItemClicked2);

    //然后添加所有的数据
    vlayout = new QVBoxLayout;
//    vlayout.
    for (int i = 0;i<detail_peer.size();i++) {
        //        QListWidgetItem *pItem = new QListWidgetItem(pListWidget);
        QPushButton *pbutton = new QPushButton(this);
        pbutton->setStyleSheet("QPushButton{  background-color: rgb(10*i%255,(255-10*i)%255,255); border: none;border-radius:2px;color:white;}"
                               "QPushButton:hover{ background-color: rgb(75,202,255);}");
        pbutton->setText("chat");
        peer *tempeer = new peer();
        tempeer->num = detail_peer[i].num;
        tempeer->name = detail_peer[i].name;
        tempeer->is_on = detail_peer[i].is_on;
        tempeer->style = detail_peer[i].style;
        pbutton->setUserData(Qt::UserRole,tempeer);
        //        pbutton->show();
        vlayout->addWidget(pbutton);


        //        pListWidget->addItem()
        QObject::connect(pbutton, &QPushButton::clicked, this, &firmain::onclick);
    }
    //最后再将 firmain 设布局
    //首先要清空所有原来的布局
    QLayoutItem *child1;
    while ((child1 = hlayout->takeAt(0)) != 0)
    {
        //setParent为NULL，防止删除之后界面不消失
        if(child1->widget())
         {
            child1->widget()->setParent(NULL);
        }

        delete child1;
    }
    hlayout->addWidget(news);
    hlayout->addWidget(close_friend);
    hlayout->addWidget(group_chat_btn);
    hlayout->addWidget(pListWidget);
//    hlayout->removeItem(vlayout);
//    hlayout->addLayout(vlayout);
    hlayout->addWidget(plistWidget2);
    this->setLayout(hlayout);
//    pmark = 0;

}

void firmain::onclick()
{
    //在点击了特定按钮之后输出这个按钮的对应的数据
    QObject *pobject = this->sender();
    QPushButton *pbutton = qobject_cast<QPushButton*>(pobject);
    peer *tempeer = (peer*)(pbutton->userData(Qt::UserRole));
    QString strnum = tempeer->num;
    //定位找到的要查找的位置
    int goal_position = 0,flag = 1;;
    for (int i = 0;i<detail_peer.size();i++) {
        if(strnum.size() == detail_peer[i].num.size()){
            for (int j = 0;j < strnum.size();j++) {
                if(strnum[j] != detail_peer[i].num[j]){
                    break;
                }
                if(j == strnum.size()-1&&flag){
                    goal_position = i;
                    flag = 0;
                }
            }
        }
    }
    //界面跳转
    emit showchat();
    emit send_chat_detail(detail_peer[detail_peer.size()-1].num,detail_peer[detail_peer.size()-1].name,detail_peer[goal_position].num,detail_peer[goal_position].name);
    qDebug()<<tempeer->num<<"  "<<tempeer->name<<endl;
}

void firmain::onItemClicked(QListWidgetItem *item)
{
    QString strnum = item->data(Qt::UserRole).toString();  // 获取用户数据
    QString strname = item->data(Qt::UserRole + 1).toString();  // 获取用户数据
    //定位找到的要查找的位置
    //此时查找到的是要聊天对象的所有信息
    int goal_position = 0,flag = 1;
    for (int i = 0;i<detail_peer.size();i++) {
        if(strnum.size() == detail_peer[i].num.size()){
            for (int j = 0;j < strnum.size();j++) {
                if(strnum[j] != detail_peer[i].num[j]){
                    break;
                }
                if(j == strnum.size()-1&&flag){
                    goal_position = i;
                    flag = 0;
                }
            }
        }
    }
    //界面跳转
    emit showdetail();
    //此时传参的时候要记得把这个客户端的名字发过去
    emit send_detail(detail_peer[goal_position].num,detail_peer[goal_position].name,detail_peer[goal_position].style);
}

void firmain::onItemClicked2(QListWidgetItem *item)
{
    QString strnum = item->data(Qt::UserRole).toString();  // 获取用户数据
    QString strname = item->data(Qt::UserRole + 1).toString();  // 获取用户数据
//    QString strnum ;
    //定位找到的要查找的位置
    int goal_position = 0,flag = 1;;
    for (int i = 0;i<detail_peer.size();i++) {
        if(strnum.size() == detail_peer[i].num.size()){
            for (int j = 0;j < strnum.size();j++) {
                if(strnum[j] != detail_peer[i].num[j]){
                    break;
                }
                if(j == strnum.size()-1&&flag){
                    goal_position = i;
                    flag = 0;
                }
            }
        }
    }
    emit showchat();
    qDebug()<<detail_peer[detail_peer.size()-1].num<<"  "<<detail_peer[detail_peer.size()-1].name<<"  "<<detail_peer[goal_position].num<<"  "<<detail_peer[goal_position].name<<endl;
    emit send_chat_detail(detail_peer[detail_peer.size()-1].num,detail_peer[detail_peer.size()-1].name,detail_peer[goal_position].num,detail_peer[goal_position].name);
//    qDebug()<<tempeer->num<<"  "<<tempeer->name<<endl;
}

void firmain::on_click_group_chat_btn()
{
    emit show_group_select();
    emit send_peer_list(transfer_str);
}

void firmain::receive_id(QString sure_id)
{
    my_id = sure_id;
}

void firmain::on_click_news()
{
    emit show_news();
}

void firmain::on_click_close_friend()
{
    qDebug()<<"kaishiqunliao"<<endl;
    emit show_degree_of_friend();
    emit send_who(my_id);
}
