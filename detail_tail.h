#ifndef DETAIL_TAIL_H
#define DETAIL_TAIL_H

#include <QWidget>
#include "header.h"

namespace Ui {
class detail_tail;
}

class detail_tail : public QWidget
{
    Q_OBJECT

public:
    explicit detail_tail(QWidget *parent = nullptr);
    ~detail_tail();

    QString my_id;


private slots:
    //这两个是有好友列表往资料卡跳转、接收发送的信息
    void receive_detail_show();

    void receive_detail_info(QString num,QString name,QString style);

    //资料卡内部的隐藏的函数
    void on_pushButton_clicked();

    //接收准确id的
    void receive_id(QString sure_id);

private:
    Ui::detail_tail *ui;
};

#endif // DETAIL_TAIL_H
