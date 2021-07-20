#include "chat_main.h"
#include "ui_chat_main.h"

chat_main::chat_main(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::chat_main)
{
    ui->setupUi(this);
}

chat_main::~chat_main()
{
    delete ui;
}

void chat_main::show_chat_main()
{
    this->show();
}

//                传的这几个元素分别为    自己的id    自己的name     别人的id         别人的name
void chat_main::receive_chat_detail(QString tem_my_num, QString tem_my_name, QString tem_goal_num, QString tem_goal_name)
{
//    ui->textEdit->setText(num+name+style+want_to_chat_with);
    //此处得到了聊天信息了
    //建立tcpsocket 发送信息
    //还是往原来的那个服务器发送，因为还要在里边匹配对应的目标聊天对象
    //在此处还不能进行传输，要再添加一个按钮 点击那个按钮之后再进行传输
    qDebug()<<"检验是否得到了四个目标值"<<my_num<<"  "<<my_name<<"  "<<my_name<<"  "<<goal_name<<endl;
    ui->textEdit_2->setFocus();
    my_num = tem_my_num;
    my_name = tem_my_name;
    goal_num = tem_goal_num;
    goal_name = tem_goal_name;
}

void chat_main::on_pushButton_clicked()
{
    this->hide();
}

void chat_main::on_pushButton_2_clicked()
{
    qDebug()<<my_id<<" "<<goal_num<<endl;
    //在这里要整理好往服务器打包发送的所有消息
    //获取当前的时间
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date = current_date_time.toString("yyyy.MM.dd hh:mm:ss");

    //先检验一下
    QString chat_all_info;
    chat_all_info = my_id+"$"+goal_num+"$"+ui->textEdit_2->toPlainText()+"$"+current_date+"-";
    QByteArray ba = chat_all_info.toLatin1();
    char *chat_all_info_char = ba.data();
    qDebug()<<"发送前输出要发送的内容"<<chat_all_info<<endl;
    chatsocket->write(chat_all_info_char);
    qDebug()<<"2"<<endl;


    //清空输入栏
    ui->textEdit_2->clear();
    ui->textEdit_2->setFocus();
    //现阶段已经完成了聊天界面往服务器传数据的要求
    //先完成通过虚拟模块进行跳转

}

void chat_main::receive_socket(QTcpSocket *temsocket)
{
    //成功的把登陆界面的转换器
    chatsocket = temsocket;
}

void chat_main::receive_from_widget(QString chat_info)
{
    ui->textBrowser->clear();
//    qDebug()<<"在这里输出聊天记录  "<<chat_info<<endl;
    //先遍历一下前两个元素，看看是否有与自己相关的
    QString num1,num2;
    num1 = chat_info.section('$',0,0);
    num2 = chat_info.section('$',1,1);
    qDebug()<<"验证所有的id  "<<num1<<"  "<<num2<<"  "<<my_id<<endl;
    if(num1.toInt()!=my_num.toInt()&&num2.toInt()!=my_id.toInt()){
        return;
    }
    this->show();
//    ui->listWidget->clear();
    if(my_id.toInt() == num1.toInt()){
        goal_num = num2;
    }
    else {
        goal_num = num1;
    }
//    qDebug()<<"检查在第二阶段是否服务器直接把返回信息发到了聊天界面端  "<<tem_msg<<endl;
    //对接收到的all_chat 进行解析
//    ui->textEdit->setText(chat_info);
    //然后用第一次正则  拆分出几个
    //先遍历一遍，看看有多少个
    int total_chat_request = 1;
    for(int i = 0; i < chat_info.size();i++){
        if(chat_info[i] == "^"){
            total_chat_request++;
        }
    }
    //先解析出来，然后在布局
//    QListWidget *pListWidget = new QListWidget(this);
//    pListWidget->resize(500,500);

    for (int i = 0;i<total_chat_request;i++) {
        QString single_chat_info = chat_info.section('^',i,i);
        // src='qrc:/img/img/headimg1.jpg'   导入特定位置的图片
        //如果等于自己的id
        QString s1;
        if(single_chat_info.section('$',0,0).toInt() == my_id.toInt()){
            s1="<img width='30' height='30'  style='float:right;margin-left:15px;margin-right:15px;'>"
               "<div style='background:rgb(205,215,226);padding-top:8px;float:right;margin-top:10px;margin-right:45px;padding:10px;margin-left:60px;'>"
               "<span style='font-size:15px;font-family:'Microsoft YaHei';margin-top:2px;'>"
                    +single_chat_info.section('$',3,3)+"\n"+single_chat_info.section('$',0,0)+":"+single_chat_info.section('$',2,2)+"</span></div><br><br><br>";
        }
        else {
            s1="<img width='30' height='30'  style='float:left;margin-left:10px;margin-right:20、px;'>"
                       "<div style='background:rgb(205,215,226); padding-top:5px; float:left; margin-top:5px; margin-right:80px; padding:5px;margin-left:10px;'>"
                       "<span style='font-size:15px;font-family:'Microsoft YaHei'; border-radius:10px;margin-top:2px;'>"
                    +single_chat_info.section('$',3,3)+"\n"+single_chat_info.section('$',0,0)+":"+single_chat_info.section('$',2,2)
                    +"</span></div><br><br><br>";
        }
        ui->textBrowser->insertHtml(s1);
    }
    //    setCentralWidget(pListWidget);
    //先利用qlist
    //再第二次正则  把每一个都拆分
}

void chat_main::receive_id(QString sure_id)
{
    my_id = sure_id;
}
