#include "end.h"
#include "ui_end.h"

struct group_member{
    int gm_num;
    QString gm_name;
    QString gm_style;
};
QVector<group_member> all_gm;

end::end(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::end)
{
    ui->setupUi(this);
}

end::~end()
{
    delete ui;
}

void end::receive_show_end()
{
    this->show();
}

//此处是用来展示群聊界面的群成员组成的栏目
void end::receive_group_chat_info(QString end_str)
{
    //先解析，再展示，解析的话解析到一个vector中
    qDebug()<<"最后的群聊界面 "<<end_str;
    int pos_the_first;  //先定义一个第一个-的位置
    for(int i = 0;i<end_str.size();i++){
        if(end_str[i] == '-'){
            pos_the_first = i;
            break;
        }
    }
    qDebug()<<pos_the_first<<endl;
    int total_peer_num;   //定义总长度
    //定义切开后的两个字符串
    QString total_peer_num_str,real_peerlist;
    total_peer_num_str = end_str.mid(0,pos_the_first);
    for (int i = pos_the_first+1;i <end_str.size() ;i++) {
        real_peerlist[i-pos_the_first-1] = end_str[i];
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
    QListWidgetItem *pItem1 = new QListWidgetItem(ui->listWidget);
    //先单独列出群主的
    pItem1->setText("群主");
    ui->listWidget->addItem(pItem1);
    group_member tem_gm;
    tem_gm.gm_num = all_one_peer[0].section('*',0,0).toInt();
    tem_gm.gm_name = all_one_peer[0].section('*',1,1);
    tem_gm.gm_style = all_one_peer[0].section('*',2,2);
    QListWidgetItem *pItem2 = new QListWidgetItem(ui->listWidget);
    pItem2->setText(QString::number(tem_gm.gm_num)+"  "+tem_gm.gm_name);
    ui->listWidget->addItem(pItem2);
    all_gm.push_back(tem_gm);
    QListWidgetItem *pItem3 = new QListWidgetItem(ui->listWidget);
    pItem3->setText("群成员");
    ui->listWidget->addItem(pItem3);
    for (int i = 1;i < total_peer_num;i++) {
        QListWidgetItem *pItem = new QListWidgetItem(ui->listWidget);
        group_member tem_gm;
        tem_gm.gm_num = all_one_peer[i].section('*',0,0).toInt();
        tem_gm.gm_name = all_one_peer[i].section('*',1,1);
        tem_gm.gm_style = all_one_peer[i].section('*',2,2);
        pItem->setText(QString::number(tem_gm.gm_num)+"  "+tem_gm.gm_name);
        ui->listWidget->addItem(pItem);
        all_gm.push_back(tem_gm);
    }
    //输出第二次拆分后的所有元素（详细信息）
    for (int i = 0;i < total_peer_num;i++) {
        qDebug()<<"账号："<< all_gm[i].gm_num<<" 昵称："<<all_gm[i].gm_name<<" 个性签名："<<all_gm[i].gm_style<<endl;
    }
}

void end::receive_socket_group(QTcpSocket *temsocket)
{
    group_chatsocket = temsocket;
}

void end::receive_from_widget_group(QString chat_info)
{
    qDebug()<<"接收到了群聊信息     "<<chat_info<<endl;
    int flag = 0;
    //在此处接收到了群聊的消息
    //先遍历一遍看看是否应该接
    qDebug()<<"1"<<endl;
    int total_member = chat_info.section("#",0,0).toInt()+1;  //加上的一应该是群主的那个数量
    for(int i = 1; i <= total_member;i++){
        if(chat_info.section("#",i,i).toInt() == my_id.toInt()){
            flag = 1;
        }
    }
    qDebug()<<"2"<<endl;
    if(flag == 0){
        return;
    }else {
        ui->textBrowser->clear();
        //首先要读取整段信息
        qDebug()<<chat_info<<endl;
        this->show();
        //读取信息并赋到结构体向量中
        QString group_leader;
        QString whole_reply_msg,info;
        info = chat_info.section('*',0,0);
        group_leader = info.section('#',1,1);
        qDebug()<<"3"<<endl;
        for(int i = 0;i < info.section('#',0,0).toInt();i++){
            group_member tem_group_member;
            tem_group_member.gm_num = info.section('#',i+1,i+1).toInt();
            all_gm.push_back(tem_group_member);
        }
        qDebug()<<"4"<<endl;



        //然后解读整段信息开始往text1里边显示

        int all_chat =1;
        //首先遍历一遍都有那些元素  看看一共有多少个消息
        for(int i = 0;i < chat_info.size();i++){
            if(chat_info[i] == "$"){
                all_chat++;
                qDebug()<<"is counting $" <<all_chat<<endl;
            }
        }

        for (int i = 0;i<all_chat;i++) {
            qDebug()<<"is setting list item"<<endl;
            QString single_chat_info = chat_info.section('$',i,i);
            //现在拿到了每句话
            //然后应该对每句话进行分割，得到id
            QString tem1,tem2;
            tem1 = single_chat_info.section(':',2,2);
            tem2 = tem1.section(' ',1,1);
            qDebug()<<tem1<<"  "<<tem2<<endl;
            QString s1;
            if(tem2.toInt() == my_id.toInt()){
                s1="<img width='30' height='30'  style='float:right;margin-left:15px;margin-right:15px;'><div style='background:rgb(205,215,226);padding-top:8px;float:right;margin-top:10px;margin-right:45px;padding:10px;margin-left:60px;'><span style='font-size:15px;font-family:'Microsoft YaHei';margin-top:2px;'>"+single_chat_info.section('*',1,1)+"</span></div><br><br><br>";
            }
            else {
                s1="<img width='30' height='30'  style='float:left;margin-left:10px;margin-right:20、px;'>"
                           "<div style='background:rgb(205,215,226); padding-top:5px; float:left; margin-top:5px; margin-right:80px; padding:5px;margin-left:10px;'>"
                           "<span style='font-size:15px;font-family:'Microsoft YaHei'; border-radius:10px;margin-top:2px;'>"
                        +single_chat_info.section('*',1,1)
                        +"</span></div><br><br><br>";
            }
            ui->textBrowser->insertHtml(s1);
//            QListWidgetItem *pItem = new QListWidgetItem(ui->listWidget_2);
//            ui->listWidget_2->addItem(pItem);
//            pItem->setText(single_chat_info.section('*',1,1));  // 文本
//            qDebug()<<single_chat_info.section('<',2,2)<<endl;
        }
    }
}

//此处是管发送群聊的东西
void end::on_pushButton_clicked()
{

    //先获取当前时间
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd hh:mm:ss ");
    qDebug()<<"5"<<endl;
    for (int i = 0;i < all_gm.size();i++) {
        qDebug()<<all_gm[i].gm_num<<" "<<all_gm[i].gm_name<<"  "<<all_gm[i].gm_style<<endl;
    }
    qDebug()<<"6"<<endl;
    //先封装好要发送的信息
    //把所有在群组中的人的信息放进去
    //群主在最前面 , 然后是除了群主以外还有多少人
    QString end_str = QString::number(all_gm[0].gm_num)+"<"+QString::number(all_gm.size())+"#";
    qDebug()<<"7"<<endl;
    for (int i = 0;i < all_gm.size();i++) {
        end_str += QString::number(all_gm[i].gm_num);
        end_str += "#";    //群聊用#分割
    }
    qDebug()<<"8"<<endl;
    end_str += "<";
    end_str += current_date;
    end_str += my_id;
    end_str += ":";
    end_str += ui->textEdit->toPlainText();
    end_str += "#";  //这个用来区分是群聊的

    //发送群消息之前输出
    qDebug()<<"发送群消息的时候检验一下"<<end_str<<endl;    //输出一下
    //再通过登陆界面传来的socket 进行发送
    //首先要先转化为char
    QByteArray ba = end_str.toLatin1();
    char *end_char = ba.data();
    //然后再发送
    group_chatsocket->write(end_char);
    //然后再清空所有内容
    ui->textEdit->clear();
    ui->textEdit->setFocus();
}

void end::receive_id(QString sure_id)
{
    my_id = sure_id;
}
