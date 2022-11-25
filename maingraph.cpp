#include "maingraph.h"
#include "ui_maingraph.h"

MainGraph::MainGraph(QWidget *parent,QString name) :
    QWidget(parent),
    username(name),
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
    readBtn = new textButton("读入",ui->widget);
    ui->verticalLayout_2->setAlignment(Qt::AlignVCenter);
    scLayout = new QVBoxLayout();
    //ui->verticalLayout_2->addWidget(scrolltext);
    /*for(int i = 1;i<=20;++i){
        QLabel *tt = new QLabel("这是一次测试");
        scLayout->addWidget(tt);
    }*/
    ui->scrollAreaWidget->setLayout(scLayout);
    ui->scrollArea->setStyleSheet(
                                         "QScrollArea{border:none;background-color:transparent;}"
                                         "QScrollArea QScrollBar:vertical{width:8px;"
                                         "background:transparent;margin:0px,1px,0px,1px;"
                                         "padding-top:0px;padding-bottom:0px;border-radius:4px;}"
                                         "QScrollArea QScrollBar::handle:vertical{background:#808080;"
                                         "border-radius:4px;}"
                                         "QScrollArea QScrollBar::handle:vertical:hover{background:#47d5d5;"
                                         "border-radius:4px;}"
                                         "QScrollArea QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{"
                                         "background:transparent;border-radius:4px;}"//设置滑块滑动后一端槽的背景透明
                                         "QScrollArea QScrollBar::add-line:vertical,QScrollBar::sub-line:vertical{"
                                         "height:0px;width:0px;}");//去掉上下箭头
            ui->scrollAreaWidget->setStyleSheet("background-color:transparent;border:none;");//设置滚动区域自带的中心窗口的背景色透明
    //完成滚动区域的样式表的设置
    ui->verticalLayout_2->addWidget(saveBtn);
    ui->verticalLayout_2->addWidget(readBtn);
    ui->verticalLayout_2->addWidget(doBfsBtn);
    ui->verticalLayout_2->addWidget(doDfsBtn);
    ui->verticalLayout_2->addWidget(closeBtn);
    ui->widget->setFixedSize(300,600);
    this->setFixedSize(800,700);//按钮大小初始化
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
        view->setGraphvisited(true);//标记整张图已经被遍历过
        nextAni();

    });//实现dfs
    connect(saveBtn,&textButton::clicked,this,[=]{saveGraph();});//保存文件
    connect(readBtn,&textButton::clicked,this,[=]{readGraph();});//读取文件
    connect(this,SIGNAL(newAni(QTimeLine*)),this,SLOT(addAni(QTimeLine *)));
}

void MainGraph::nextAni()
{
    if(aniQueue.size()>0){
        QTimeLine *curAni = aniQueue.front();
        aniQueue.pop_front();
        connect(curAni,&QTimeLine::finished,this,[=](){nextAni();curAni->deleteLater();});
        curAni->start();
    }
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
    curline->setVisible(false);
    QTimeLine *accessEffect = new QTimeLine;
    accessEffect->setDuration(1000);
    accessEffect->setFrameRange(0, 200);
    QEasingCurve curve = QEasingCurve::InOutQuad;
    connect(accessEffect, &QTimeLine::frameChanged, this, [=](int frame){
        qreal curProgress = curve.valueForProgress(frame / 200.0);
        curline->setLengthrate(curProgress);
        curline->drawline();
    });
    emit newAni(accessEffect);
}


void MainGraph::addAni(QTimeLine *curAni)
{
    aniQueue.push_back(curAni);
}






void MainGraph::saveGraph()//update:加入用户名对应的文件支持
{
    //点全部存入一个文件 按照总共多少个 坐标
    QString vexfilename = username + "vex.dat";
    QFile vexfile(vexfilename);
    vexfile.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream vs(&vexfile);
    vs<< view->getvexlist().size()<<"\n";
    for(auto vex : view->getvexlist()){
        vs<<vex->pos().x() <<" "<<vex->pos().y() << " " <<vex->getNodeNum() << "\n";
    }
    vexfile.close();
    //将边全部读入一个文件里面 按照 总共多少条 起点的编号 终点的编号
    QString linefilename = username + "line.dat";
    QFile linefile(linefilename);
    linefile.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream ls(&linefile);
    ls<< view->getlinelist().size()<<"\n";
    for(auto line : view->getlinelist()){
        ls<<line->sourceNode()->getNodeNum() <<" "<<line->destNode()->getNodeNum()<<"\n";
    }
    linefile.close();
}

void MainGraph::readGraph()
{
    QGraphicsScene *newscene = new QGraphicsScene();
    view->setScene(newscene);//读入文件后，相当于直接把scene换了一个新的
    QString vexfilename = username + "vex.dat";
    QFile vexfile(vexfilename);
    vexfile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream vs(&vexfile);
    int tvex = 0;
    tvex = vs.readLine().toInt();
    view->getvexlist().clear();//记得先清空一下
    for(int i = 1; i<=tvex; ++i){
        qreal x,y;
        int curcount = 0;
        vs >> x >> y >> curcount;
        customVex *newvex = new customVex(QPointF(x,y),customVex::STATE::CREATE);
        QGraphicsSimpleTextItem *showtext = new QGraphicsSimpleTextItem(newvex);
        customVex::VexCount = tvex;
        showtext->setText("V"+QString("%1").arg(curcount));//给每个点打上标号
        showtext->setPos(showtext->mapToItem(newvex,0,0)+QPointF(10,10));
        newvex->setNodeNum(curcount);//记得给一下每个点编号，坑死了
        view->scene()->addItem(newvex);
        view->addtoVexlist(newvex);
        vs.readLine();//跳过结尾的换行符，贼坑，花费我大量时间找bug
    }
    vexfile.close();

    QString linefilename = username + "line.dat";
    QFile linefile(linefilename);
    linefile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream ls(&linefile);
    int tline = 0;
    tline = ls.readLine().toInt();
    view->getlinelist().clear();
    for(int i = 1; i<=tline; ++i){
        int s,e;
        ls >> s >> e;//读入起始点和终点编号
        customVex *sourceNode = nullptr;
        customVex *destNode = nullptr;
        for(auto tempvex : view->getvexlist()){
            if(tempvex->getNodeNum() == s){
                sourceNode = tempvex;
            }
            if(tempvex->getNodeNum() == e){
                destNode = tempvex;
            }
        }
        customLine *newline = new customLine(sourceNode,destNode);
        view->scene()->addItem(newline);
        view->addtoLinelist(newline);
        vs.readLine();//跳过结尾的换行符，贼坑，花费我大量时间找bug
    }


}


