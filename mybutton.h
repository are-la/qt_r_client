#ifndef MYBUTTON_H
#define MYBUTTON_H

#include<QPushButton>
#include"header.h"

class myButton:public QPushButton
{
    Q_OBJECT
public:
    myButton(const QString & text,QWidget * parent = 0);

    virtual void mousePressEvent(QMouseEvent *e);

    int mark;
    int count;

private:
    int m_mouseType;
    QPoint bg_point;
    QPoint ed_point;


signals:

public slots:
};

#endif // MYBUTTON_H
