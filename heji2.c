#include "widget.h"
#include "ui_widget.h"

#include <QDebug>

#include <QPixmap>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    ,time(new QTimer(this))
{
    ui->setupUi(this);

    ui->horizontalSlider->setRange(0,9999);


    QPixmap pixmap(":/1.jpg");
    QSize labelSize = ui->label_3->size();
    QPixmap scaledPixmap = pixmap.scaled(labelSize,Qt::KeepAspectRatio,Qt::SmoothTransformation);
    ui->label_3->setPixmap(scaledPixmap);

    connect(&myevent,&fsmpEvents::keyPressed,this,&Widget::pushbuton);

    connect(time,&QTimer::timeout,this,&Widget::timout);
    time->start(1000);//1000毫秒

}

Widget::~Widget()
{
    delete ui;
}

//按钮开灯
void Widget::on_pushButton_clicked()
{
    if(ui->pushButton->text() == "开灯")
    {
        myled.on(fsmpLeds::LED1);

        ui->pushButton->setText("关灯");
    }
    else
    {
        myled.off(fsmpLeds::LED1);
        ui->pushButton->setText("开灯");
    }
}


void Widget::on_pushButton_2_clicked()
{


}

//灯1
void Widget::on_checkBox_stateChanged(int arg1)
{
    if(arg1){
        myled.on(fsmpLeds::LED1);

    }
    else{
        myled.off(fsmpLeds::LED1);
    }
}

//蜂鸣器
void Widget::on_checkBox_2_stateChanged(int arg1)
{
    if(arg1){
        mybeeper.setRate(9999);
        mybeeper.start();
    }
    else{
        mybeeper.stop();
    }
}

//滑动
void Widget::on_horizontalSlider_valueChanged(int value)
{
    qDebug() << ui->horizontalSlider->value();

    mybeeper.setRate(value);
    mybeeper.start();

    ui->progressBar->setValue((ui->horizontalSlider->value()+1)/100);
}


void Widget::on_checkBox_3_stateChanged(int arg1)
{
    if(arg1){
        myfan.setSpeed(100);
        myfan.start();
    }

    else{
        myfan.stop();
    }
}

void Widget::pushbuton(int num)
{
    switch(num){
    case 1:
        ui->checkBox->toggle();
        break;
    case 2:
        ui->checkBox_4->toggle();
        break;
    case 3:
        ui->checkBox_5->toggle();
        break;
    default:
        break;


    }
}
//灯2
void Widget::on_checkBox_4_stateChanged(int arg1)
{
    if(arg1){
        myled.on(fsmpLeds::LED2);

    }
    else{
        myled.off(fsmpLeds::LED2);
    }
}

//灯3
void Widget::on_checkBox_5_stateChanged(int arg1)
{
    if(arg1){
        myled.on(fsmpLeds::LED3);

    }
    else{
        myled.off(fsmpLeds::LED3);
    }
}

void Widget::timout(){
    //定时一次要做的事情
    ui->doubleSpinBox->setValue(myth.temperature());
    ui->doubleSpinBox_2->setValue(myth.humidity());

}


void Widget::on_doubleSpinBox_textChanged(const QString &arg1)
{

}


void Widget::on_doubleSpinBox_2_textChanged(const QString &arg1)
{

}