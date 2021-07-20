#include "check.h"
#include "ui_check.h"

check::check(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::check)
{
    ui->setupUi(this);
}

check::~check()
{
    delete ui;
}

void check::receive_show_check()
{
    this->show();
}

void check::receive_check_info(QString num, QString password)
{
    c_num = num;
    c_password = password;
}

void check::on_pushButton_clicked()
{
    int flag = 1;
    QString tem = ui->lineEdit_2->text();
    if(ui->lineEdit->text().toInt() == c_num.toInt()&&tem.size() == c_password.size()){
        for(int i = 0;i<c_password.size();i++){
            if(tem[i]!= c_password[i]){
                flag = 0;
                QMessageBox::warning(NULL,"error","验证失败，请重试");
            }
        }
    }
    if(flag == 1){
//        QLabel *label = new QLabel(this);
//        label->setText("tem");

////        label->resize(this->width(),this->height());
//        qDebug()<<" start movie"<<endl;
//        QMovie *movie = new QMovie(":/new/prefix1/background.gif");
//        label->setMovie(movie);
//        movie->start();
//        qDebug()<<label->text();

//        QMutex mutex;
//        QWaitCondition sleep;
//        mutex.lock();
//        sleep.wait(&mutex, 5000);
//        mutex.unlock();
//        this->
        qDebug()<<"end movie"<<endl;
        this->close();
        emit show_widget();
    }
}
