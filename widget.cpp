#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    flag = 0;
    is_checked = 0;
    ui->setupUi(this);
    ui->lineEdit->setText("a1");  //昵称
    ui->lineEdit_2->setText("1111");  //num  int
    ui->lineEdit_3->setText("m111");  //密码
    ui->textEdit->setText("s111");   //style
    ui->textEdit_2->setText("a2");  //和谁聊天
    ui->radioButton->setChecked(true);
    ui->label_5->hide();
    ui->textEdit_2->hide();
    ui->pushButton_2->hide();
    ui->radioButton->hide();
    ui->radioButton_2->hide();
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_clicked()
{

//    qDebug()<< ui->radioButton->isChecked()<<endl;
//    qDebug()<< ui->radioButton_2->isChecked()<<endl;
    //此处的info要包括很多信息，账号 密码 昵称 个签 (自己的IP 自己的port 目标的IP 目标的port)这四个暂时换成目标name
//    QString info = "a*b*c*d*e*f*g";
//    QString info =ui->lineEdit_2->text()+"*"+ui->lineEdit_3->text()+"*"+ ui->lineEdit->text()+"*"+ui->textEdit->toPlainText()+"*"+ui->textEdit_2->toPlainText();
    QString info;
    if(ui->radioButton->isChecked()){
        //如果在线被选择了
        info = ui->lineEdit_2->text()+"*"+ui->lineEdit_3->text()+"*"+ ui->lineEdit->text()+"*"+ui->textEdit->toPlainText()+"*"+ui->textEdit_2->toPlainText()+"*on+";
    }
    if(ui->radioButton_2->isChecked())
    {
        info = ui->lineEdit_2->text()+"*"+ui->lineEdit_3->text()+"*"+ ui->lineEdit->text()+"*"+ui->textEdit->toPlainText()+"*"+ui->textEdit_2->toPlainText()+"*off+";
    }

    QByteArray ba = info.toLatin1();
    char *c_info = ba.data();
    //一旦连接之后就传输数据 =>所以就要在每次点击的时候做好一切准备工作
    client = new QTcpSocket(this);
    //在此处发送传输socket的信号
    emit sendSocket(client);
    emit sendSocket_group(client);
    emit sendSocket_close_friend(client);
    emit send_id(ui->lineEdit_2->text());
    client->connectToHost("127.0.0.1",9999);
    client->write(c_info);
    //这就已经发送了
    connect(client,SIGNAL(readyRead()),this,SLOT(printServerMes()));
}

void Widget::printServerMes()
{
    QString msg = QString(client->readAll());
//    ui->textEdit_2->setText(msg);
    qDebug()<< "检验在第一阶段是否有往原登录界面发送返回的指令  "<<msg<<endl;
    //在此处会收到本想往聊天界面发送的消息
    if(msg[msg.size()-1] == "^"){    //如果结尾是"^" => 则是往聊天界面发送的
        //先把末尾的区分符号去掉
        QString final_msg = msg.mid(0,msg.size()-1);
        //传此时接收到的往聊天界面发送的值
        emit sendchat_info(final_msg);
    }
    if(msg[msg.size()-1] == "%"){   //如果结尾是"%" => 则是往主好友界面发送的
        //点击之后先给验证界面传数据，用来验证
        //先弹出一个提示
        QString final_msg = msg.mid(0,msg.size()-1);
        //此处对传来的进行分界，如果是1111 就拦截，然后不忘后面的界面传递
        if(final_msg.toInt() == 111){
            QMessageBox::warning(NULL,"error","此账号已被占用，请重新输入账号");
            ui->lineEdit_2->clear();
            ui->lineEdit_2->setFocus();
            qDebug()<<"注册失败的"<<endl;
            return;
        }else {
            qDebug()<<"注册成功的"<<endl;
            if(flag == 0){
                QMessageBox::information(NULL,"success","注册成功！");
                flag = 1;
            }//给群聊界面发送消息
        }
        this->hide();
        emit fmainshow();
//        if(is_checked == 0){
//            QMessageBox::warning(NULL,"check","请重新输入刚才注册的账号和密码来验证身份");

////            emit show_check();
////            emit send_check_info(ui->lineEdit_2->text(),ui->lineEdit_3->text());
//            is_checked = 1;
//        }
        //先把末尾的区分符号去掉

        emit sendpeerlist(final_msg);
    }
    if(msg[msg.size()-1] == "$"){   //如果结尾是"$" =>则是往群聊界面发送的
        QString end_msg = msg.mid(0,msg.size()-1);
        emit sendchat_info_group(end_msg);
    }
    if(msg[msg.size()-1] == "#"){   //如果结尾是"$" =>则是往群聊界面发送的
        QString end_msg = msg.mid(0,msg.size()-1);
        emit send_close_info(end_msg);
    }
}

void Widget::receive_show_widget()
{
    //在这一块准备做界面切换
    //在hide之前可以加载一段动画
    emit fmainshow();
    //然后还要传送信息  把前面加载出来的信息全部发送给新的fir界面，然后让新的界面全部呈现出来

}
