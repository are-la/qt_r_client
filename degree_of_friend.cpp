#include "degree_of_friend.h"
#include "ui_degree_of_friend.h"

degree_of_friend::degree_of_friend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::degree_of_friend)
{
    ui->setupUi(this);
}

degree_of_friend::~degree_of_friend()
{
    delete ui;
}

void degree_of_friend::receive_degree_of_friend()
{
    this->show();
}

void degree_of_friend::receive_who(QString is_who)
{
    QString close_friend_str = is_who+"^";
    QByteArray ba = close_friend_str.toLatin1();
    char *close_friend_char = ba.data();
    close_friend_socket->write(close_friend_char);
}

void degree_of_friend::receive_socket_close_friend(QTcpSocket *temSocket)
{
    close_friend_socket = temSocket;
}

void degree_of_friend::receive_info(QString close_info)
{
    //先判断是不是应该自己接收
    //首先先拿到传来的id
    QString now_id = close_info.section("#",0,0);
    qDebug()<<now_id<<"  "<<my_id<<endl;
    if(now_id.toInt() == my_id.toInt()){
        //先定义最大亲密度和位置
        int max_close = -1;
        int num;
        //如果匹配上了
        //开始解析
        //先看有多少人
        int total = 0;
        for (int i = 0;i < close_info.size();i++) {
            if(close_info[i] == "#"){
                total++;
            }
        }
        //拿到了有多少人
//        ui->listView
//        QListWidgetItem *pItem1 = new QListWidgetItem(ui->listView);

//        QListWidgetItem *pItem1 = new QListWidgetItem(ui->listWidget);
        for (int i =0;i < total;i++) {
//            if()
            //先拿出这个
            QString temstr = close_info.section("#",1,1);
            QString tem_num =  temstr.section("*",0,0);
            QString tem_weight = temstr.section("*",1,1);
            if(tem_weight.toInt()>max_close){
                max_close = tem_weight.toInt();
                num = tem_num.toInt();
            }
            QListWidgetItem *pItem = new QListWidgetItem(ui->listWidget);
            pItem->setText(close_info.section("#",i+1,i+1));
            pItem->setSizeHint(QSize(150,50));
            pItem->setBackgroundColor(QColor((200-10*i)%100+100,224,251));
            ui->listWidget->addItem(pItem);
        }
        ui->label->setText("和"+my_id+"亲密度最高的用户是"+num);
    }
}

void degree_of_friend::receive_id(QString sure_id)
{
    my_id = sure_id;
}

void degree_of_friend::on_pushButton_clicked()
{
    this->close();
}
