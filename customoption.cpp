#include "customoption.h"

int customOption::pagecount = 0;


customOption::customOption(QWidget *parent,int ra)
    : QWidget(parent),
      radius(ra)
{

    ++pagecount;
    if(pagecount>=1){
        emit CountMaxed();
    }
    QFile file(":/op.qss");
    this->setFixedSize(300,500);
    setParent(parent);
    this->move(parent->rect().x()-300,parent->rect().y()+50);
    startPoint.setX(parent->rect().x()-300);
    startPoint.setY(parent->rect().y()+50);
    /*closeBtn = new QPushButton(this);
    closeBtn->setFixedSize(20,20);
    closeBtn->setObjectName("closeBtn");
    closeBtn->move(this->width()-30,10);*/
    closeBtn = new CustomIcon(":/back.png",m_color,this);
    closeBtn->move(this->width()-30,10);
    connect(closeBtn,&QPushButton::clicked,this,[=](){
        //绑定动画

        closeMoveAnimate();
        emit isOpenChanged();
    });
    initpage();
    clearBtn = new QPushButton(this);
    this->clearBtn->setFixedSize(100,30);
    clearBtn->setStyleSheet("QPushButton{font: 12 14pt '微软雅黑 Light';color: rgb(255,255,255);background-color: rgb(20,196,188);"
                                    "border: none;border-radius:15px;}"
                                    "QPushButton:hover{background-color: rgb(22,218,208);}"//hover
                                    "QPushButton:pressed{background-color: rgb(17,171,164);}");//pressed
    this->clearBtn->setText("清空用户文件");
    this->clearBtn->move(this->width()-100,50);
    layout_main = new QVBoxLayout(this);
    layout_main->setAlignment(Qt::AlignVCenter);
    this->setLayout(layout_main);
    layout_main->addWidget(closeBtn);
    layout_main->addWidget(clearBtn);
}

customOption::~customOption()
{
    --pagecount;
}

void customOption::closeMoveAnimate()
{
    QPropertyAnimation *slide = new QPropertyAnimation(this,"pos");
    slide->setDuration(850);
    slide->setStartValue(this->pos());
    slide->setEndValue(this->startpoint());
    slide->setEasingCurve(QEasingCurve::InOutQuad);
    slide->start();//这里就是就是实现滑出效果
    isOpen=false;

}

void customOption::initpage()
{

}

void customOption::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect(), radius, radius);
}

void customOption::showEvent(QShowEvent *event)
{
    setWindowModality(Qt::WindowModal);
    isOpen = true;
    qDebug()<<"isopening"<<endl;
}

void customOption::closeEvent(QCloseEvent *event)
{
    //isOpen=false;
}

void customOption::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"鼠标"<<endl;
    if(event->button() == Qt::LeftButton){

    }
}

