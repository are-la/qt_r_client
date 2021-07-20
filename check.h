#ifndef CHECK_H
#define CHECK_H

#include <QWidget>
#include "header.h"

namespace Ui {
class check;
}

class check : public QWidget
{
    Q_OBJECT

public:
    explicit check(QWidget *parent = nullptr);
    ~check();
    QString c_num,c_password;

signals:
    void show_widget();
private slots:
    void receive_show_check();

    void receive_check_info(QString num,QString password);

    void on_pushButton_clicked();

private:
    Ui::check *ui;
//    QMovie *movie;
};

#endif // CHECK_H
