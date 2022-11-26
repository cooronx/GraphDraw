#include "betteroption.h"
#include "ui_betteroption.h"

betterOption::betterOption(QWidget *parent,int ra) :
    QWidget(parent),
    ui(new Ui::betterOption),
    radius(ra)
{
    ui->setupUi(this);
    //++pagecount;

    QFile file(":/op.qss");
    this->setFixedSize(180,500);
    setParent(parent);
    raise();
    this->move(parent->rect().x()-200,parent->rect().y()+50);
    startPoint.setX(parent->rect().x()-200);
    startPoint.setY(parent->rect().y()+50);
    /*closeBtn = new QPushButton(this);
    closeBtn->setFixedSize(20,20);
    closeBtn->setObjectName("closeBtn");
    closeBtn->move(this->width()-30,10);*/
    closeBtn = new CustomIcon(":/back.png",m_color,this);
    closeBtn->move(this->width()-40,10);
    clearBtn = new textButton("删除用户文件",this);
    colorBtn = new textButton("随机主题颜色",this);
    ui->verticalLayout->addWidget(clearBtn);
    ui->verticalLayout->addWidget(colorBtn);
    connect(clearBtn,&textButton::clicked,this,[=]{clearUserFile();});
    connect(colorBtn,&textButton::clicked,this,[=]{
        QTime time;
        time= QTime::currentTime();
        qsrand(time.msec()+time.second()*1000);//生成1-65的随机数
        int n = qrand() % 179;
        emit colorChanged(n);
    });
    connect(closeBtn,&QPushButton::clicked,this,[=](){
        //绑定动画

        closeMoveAnimate();
        emit isOpenChanged();
    });
    initpage();

}
betterOption::~betterOption()
{
    emit isOpenChanged();
    //--pagecount;
}

void betterOption::closeMoveAnimate()
{
    QPropertyAnimation *slide = new QPropertyAnimation(this,"pos");
    slide->setDuration(850);
    slide->setStartValue(this->pos());
    slide->setEndValue(this->startpoint());
    slide->setEasingCurve(QEasingCurve::InOutQuad);
    slide->start();//这里就是就是实现滑出效果
    isOpen=false;

}

void betterOption::initpage()
{

}

void betterOption::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(m_color);
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect(), radius, radius);
}

void betterOption::enterEvent(QEvent *event)
{
    qDebug()<<"hello"<<endl;
    isInWidget = true;
}

void betterOption::leaveEvent(QEvent *event)
{
    isInWidget = false;

}

void betterOption::showEvent(QShowEvent *event)
{
    setWindowModality(Qt::WindowModal);
    isOpen = true;
    qDebug()<<"isopening"<<endl;
}

void betterOption::closeEvent(QCloseEvent *event)
{
    //isOpen=false;

}

void betterOption::mousePressEvent(QMouseEvent *event)
{

}


void betterOption::clearUserFile()
{
    QFile fs_account("useraccount.txt");
    fs_account.open(QIODevice::WriteOnly);
    QFile pwd_account("userpwd.txt");
    pwd_account.open(QIODevice::WriteOnly);
    QMessageBox msgBox;
    msgBox.setWindowTitle("提示");
    msgBox.setText("用户文件已删除");
    msgBox.exec();
}
