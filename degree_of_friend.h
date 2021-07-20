#ifndef DEGREE_OF_FRIEND_H
#define DEGREE_OF_FRIEND_H

#include <QWidget>
#include "header.h"

namespace Ui {
class degree_of_friend;
}

class degree_of_friend : public QWidget
{
    Q_OBJECT

public:
    explicit degree_of_friend(QWidget *parent = nullptr);
    ~degree_of_friend();
    QString my_id;

private slots:
    void receive_degree_of_friend();

    void receive_who(QString is_who);

    //接收来自widget窗口的socket
    void receive_socket_close_friend(QTcpSocket *temSocket);

    void receive_info(QString close_info);

    void receive_id(QString sure_id);

    void on_pushButton_clicked();

private:
    Ui::degree_of_friend *ui;
    QTcpSocket *close_friend_socket;
};

#endif // DEGREE_OF_FRIEND_H
