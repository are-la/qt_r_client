#ifndef NEWS_H
#define NEWS_H

#include <QWidget>
#include "header.h"

namespace Ui {
class news;
}

class news : public QWidget
{
    Q_OBJECT

public:
    explicit news(QWidget *parent = nullptr);
    ~news();

public slots:

//    void updatevalue();

    void replay_finished(QNetworkReply* networkReply);

    void on_readyRead();


private slots:
    void on_pushButton_clicked();

    void receive_show_news();

    void on_pushButton_2_clicked();

private:
    Ui::news *ui;
    QNetworkAccessManager * manager;
    QTimer * timer;
    QUrl url;
    QNetworkRequest request;
};

#endif // NEWS_H
