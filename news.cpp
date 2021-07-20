#include "news.h"
#include "ui_news.h"

QVector<QString> all_news;

news::news(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::news)
{
    ui->setupUi(this);
    //创建请求
    QUrl url("http://www.chinanews.com/");

    request.setUrl(url);
    manager = new QNetworkAccessManager(this);

    this->url = url;
    connect(manager, SIGNAL(finished(QNetworkReply*)),
            this, SLOT(replay_finished(QNetworkReply*)));
    manager->get(QNetworkRequest(this->url));

    QNetworkReply * reply = manager->get(request);
    connect(reply,SIGNAL(readyRead()),this,SLOT(on_readyRead()));

    timer = new QTimer(this);
//    connect(timer, SIGNAL(timeout()), this, SLOT(updatevalue()));
//    timer->start(1000);



}

news::~news()
{
    delete ui;
}

//void Widget::updatevalue()
//{
//    QUrl ur;
//    ur = this->url;
//    if (ur.isEmpty())
//        qDebug() << "url is empty";
//    manager->get(QNetworkRequest(ur));
//    ur.clear();
//}

void news::replay_finished(QNetworkReply *networkReply)
{
//    networkReply = manager->get(request);
    QByteArray data = networkReply->readAll();
    QString msg = data.append(data).mid(0,10000000);
    int bg = 0,ed = 0;
    int flag1 = 0,flag2 = 0;
    for (int i = 0; i < msg.size();i++) {
        if(msg[i] == 't'&&msg[i+1] == "i"&&msg[i+2] == "t"&&msg[i+3] == "l"&&msg[i+4] == "e"&&msg[i+5] == "="){
            bg = i+7;
            flag1 = 1;
        }
        if(msg[i] == "."&&msg[i+1] == "."&&msg[i+2] == "."&&msg[i+3] == "<"){
            ed = i;
            flag2 = 1;
        }
        if(flag1&&flag2){
            qDebug()<<msg.mid(bg,ed-bg);
            flag1 = 0;
            flag2 = 0;
            for (int i = 0;i < msg.mid(bg,ed-bg).size();i++) {
                if(msg.mid(bg,ed-bg)[i] == ">"){
                    all_news.push_back(msg.mid(bg,ed-bg).mid(0,i-1));
                }
            }
        }
    }
    for (int i = 0; i < all_news.size(); i++) {
        //在此处对爬取的信息进行展示
        qDebug()<<all_news[i]<<endl;
        //       QListWidget *listwidget;
    }
    QListWidgetItem *pItem1 = new QListWidgetItem(ui->listWidget);
    for (int i =0;i < 20;i++) {
        QListWidgetItem *pItem = new QListWidgetItem(ui->listWidget);
        pItem->setText(all_news[((rand())%100+i)%all_news.size()]);
        ui->listWidget->addItem(pItem);
    }
    //    qDebug()<<msg;
}

void news::on_readyRead()
{
    //
    qDebug()<<"111"<<endl;
}

void news::on_pushButton_clicked()
{
    ui->listWidget->clear();
    QListWidgetItem *pItem1 = new QListWidgetItem(ui->listWidget);
    for (int i =0;i < 20;i++) {
        QListWidgetItem *pItem = new QListWidgetItem(ui->listWidget);
        pItem->setSizeHint(QSize(100,40));
        pItem->setText(all_news[((rand())%100+i)%all_news.size()]);
        ui->listWidget->addItem(pItem);
    }
}

void news::receive_show_news()
{
    //用来展示新闻
    this->show();
}

void news::on_pushButton_2_clicked()
{
    this->close();
}
