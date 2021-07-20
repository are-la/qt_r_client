#include "detail_tail.h"
#include "ui_detail_tail.h"

detail_tail::detail_tail(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::detail_tail)
{
    ui->setupUi(this);
    ui->pushButton_2->hide();
}

detail_tail::~detail_tail()
{
    delete ui;
}

void detail_tail::receive_detail_show()
{
    this->show();
}

void detail_tail::receive_detail_info(QString num, QString name, QString style)
{
    ui->label_5->setText(num);
    ui->label_6->setText(name);
    ui->label_7->setText(style);
}

void detail_tail::on_pushButton_clicked()
{
    this->close();
}

void detail_tail::receive_id(QString sure_id)
{
    my_id = sure_id;
}
