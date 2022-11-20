#include "maingraph.h"
#include "ui_maingraph.h"

MainGraph::MainGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainGraph)
{
    ui->setupUi(this);
    view = new CustomView();
    setWindowFlag(Qt::FramelessWindowHint);
    setAttribute(Qt::WA_TranslucentBackground);//无边框必备
    ui->GraphLayout->addWidget(view);
    closeBtn = new textButton("退出",ui->widget);
    saveBtn = new textButton("保存",ui->widget);
    doBfsBtn = new textButton("广度优先搜索",ui->widget);
    doDfsBtn = new textButton("深度优先搜索",ui->widget);
    ui->verticalLayout_2->setAlignment(Qt::AlignVCenter);
    ui->verticalLayout_2->addWidget(saveBtn);
    ui->verticalLayout_2->addWidget(doBfsBtn);
    ui->verticalLayout_2->addWidget(doDfsBtn);
    ui->verticalLayout_2->addWidget(closeBtn);
    ui->widget->setFixedSize(300,600);
    this->setFixedSize(800,600);//按钮大小初始化
    estConnection();//信号与槽连接
}

MainGraph::~MainGraph()
{
    delete ui;
}

void MainGraph::estConnection()
{
    connect(closeBtn,&textButton::clicked,this,[=]{close();});

    connect(doDfsBtn,&textButton::clicked,this,[=]{
        view->getCurrentSel()->setVisited(true);
        GraphDfs(view->getCurrentSel());
        for(auto tempvex : view->getvexlist()){
            tempvex->setVisited(false);
        }
    });


}

void MainGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QGradient(static_cast<QGradient::Preset>(2))));
    painter.setPen(Qt::transparent);
    painter.drawRoundedRect(rect(), 20, 20);
}

void MainGraph::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousepressed&&(event->button() == Qt::NoButton)){

        this->move(event->globalPos() - m_curmousepos);//这里鼠标的坐标变化
        //思考一下，如果这里鼠标不动，那就还是会move到刚刚的原位置，
        //一旦鼠标动了一个像素点，这个之间的差值就会增加，随之move到新的位置
        event->accept();
    }
}

void MainGraph::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        m_mousepressed = true;
        //qDebug()<<event->globalPos();
        m_curmousepos = event->globalPos() - this->pos();//相当于鼠标和部件边框之间差了多少
        //qDebug()<<m_curmousepos;
        event->accept();
    }
}

void MainGraph::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event);
    m_mousepressed = false;
}


void MainGraph::GraphDfs(customVex *startvex)
{
    qDebug()<<"起始点为"<<startvex->getNodeNum()<<endl;
    startvex->setVisited(true);
    for(auto curline : startvex->edgeList()){
        if(!curline->destNode()->getVisited()){//要检测是否访问过了
            VisitingLine(curline);
            GraphDfs(curline->destNode());
        }
        else continue;
    }
}

void MainGraph::VisitingLine(customLine *curline)
{
    qDebug()<<"正在访问这条线"<<curline->sourceNode()->getNodeNum()
           <<"     "<<curline->destNode()->getNodeNum()<<endl;
}

