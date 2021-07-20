#include "mybutton.h"
#include <QtDebug>
#include "QKeyEvent"
#include"QMouseEvent"

//构造函数
myButton::myButton(const QString &text,QWidget *parent):QPushButton (text,parent),m_mouseType(0),mark(0),count(0){

}

void myButton::mousePressEvent(QMouseEvent *e){
    mark = 1;
    if(count == 0){
        //写一个发送数据的信号
//        myButton tembtn = e->buttons();/
//        myButton tembtn = e->button();
    }
}
