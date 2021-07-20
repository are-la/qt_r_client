#include "group_chat.h"
#include "ui_group_chat.h"
#include<QCheckBox>
QVector<QCheckBox*> all_checkbox;

//struct group_peer:QObjectUserData{
//    QString num;   //账号
//    QString name;  //昵称
//    QString style;  //个性签名
//    QString want_to_talk_with;
//    QString is_on;  //是否在线
//};
//QVector<group_peer> detail_peer;
struct group_peer{
    QString num;
    QString name;
    QString style;
    QString want_to_talk_with;
    QString is_on;
};
QVector<group_peer> g_peer;

group_chat::group_chat(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::group_chat)
{
    ui->setupUi(this);
    confirm_btn = new QPushButton();
    confirm_btn->setText("开始群聊");
//    QObject::connect(confirm_btn, &QPushButton::clicked, this, &group_chat::on_click_confirm_btn);
    QObject::connect(confirm_btn,SIGNAL(clicked()),this,SLOT(on_click_confirm_btn()));
}

group_chat::~group_chat()
{
    delete ui;
}

void group_chat::receive_show_group()
{
    this->show();
}

void group_chat::receive_peerlist(QString peerlist)
{
    //在这里接收到了信号首先用主界面相同的方式解析  解析出
    //考虑直接用槽函数把QVector 传过来
    int pos_the_first;  //先定义一个第一个-的位置
    for(int i = 0;i<peerlist.size();i++){
        if(peerlist[i] == '-'){
            pos_the_first = i;
            break;
        }
    }
    qDebug()<<pos_the_first<<endl;
    int total_peer_num ;   //定义总长度
    //定义切开后的两个字符串
    QString total_peer_num_str,real_peerlist;
    total_peer_num_str = peerlist.mid(0,pos_the_first);
    for (int i = pos_the_first+1;i <peerlist.size() ;i++) {
        real_peerlist[i-pos_the_first-1] = peerlist[i];
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
        group_peer tempeer;
        tempeer.num = all_one_peer[i].section('*',0,0);
        tempeer.name = all_one_peer[i].section('*',1,1);
        tempeer.style = all_one_peer[i].section('*',2,2);
        tempeer.want_to_talk_with = all_one_peer[i].section('*',3,3);
        tempeer.is_on = all_one_peer[i].section('*',4,4);
        g_peer.push_back(tempeer);
    }
    //输出第二次拆分后的所有元素（详细信息）
    for (int i = 0;i < total_peer_num;i++) {
        qDebug()<<"群聊  "<<"账号："<< g_peer[i].num<<" 昵称："<<g_peer[i].name<<" 个性签名："<<g_peer[i].style<<" 想和谁聊天："<<g_peer[i].want_to_talk_with<<" 是否在线："<<g_peer[i].is_on<<endl;
    }


    //先手动添加一个按钮

//    QObject::connect(pbutton, &QPushButton::clicked, this, &firmain::onclick);

    //呈现一个待选择的列表+所有待选择的按钮
    QListWidget *pListWidget = new QListWidget(this);
    QVBoxLayout *vlayout = new QVBoxLayout;

    for (int i = 0;i<g_peer.size()-1;i++) {    //注意先排除自己 => 所以要size()-1
        QCheckBox *checkbox = new QCheckBox(this);
        checkbox->setText(g_peer[i].name);
        vlayout->addWidget(checkbox);
        all_checkbox.push_back(checkbox);
        QListWidgetItem *pItem = new QListWidgetItem(pListWidget);
        pListWidget->addItem(pItem);
        pItem->setText(g_peer[i].num+"\n"+g_peer[i].name);  // 文本
    }


    //将上边两个放到一个横向排版中
    QHBoxLayout *hlayout = new QHBoxLayout;
    hlayout->addWidget(confirm_btn);
    hlayout->addWidget(pListWidget);
    hlayout->addLayout(vlayout);
    this->setLayout(hlayout);

}

//当点击确认建群的按钮后
void group_chat::on_click_confirm_btn()
{
    //首先要把群主的名字写在最前面
    QString final_str = g_peer[g_peer.size()-1].num+"*"+g_peer[g_peer.size()-1].name+"*"+g_peer[g_peer.size()-1].style+"-";
    //首先要遍历一遍谁被勾选了
    int count_group_num = 1;//计数，一共有多少人参与了
    for (int i = 0;i < all_checkbox.size()-1;i++) {
        if(all_checkbox[i]->isChecked()){
            count_group_num++;
            QString temstr = g_peer[i].num+"*"+g_peer[i].name+"*"+g_peer[i].style;
            final_str += temstr;
            final_str += "-";
        }
    }
    QString send_info = QString::number(count_group_num)+"-"+final_str.mid(0,final_str.size()-1);
    qDebug()<<final_str<<endl;
    //先关闭
    this->close();
    //开始跳转到群聊界面
    emit showend();
    emit send_group_chat_info(send_info);
    //后弹出提示框
    QMessageBox::warning(NULL,"tip","你已经成功组件群聊，开始聊天吧！");
}

void group_chat::receive_id(QString sure_id)
{
    my_id = sure_id;
}
