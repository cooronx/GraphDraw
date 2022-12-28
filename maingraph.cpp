#include "maingraph.h"
#include "ui_maingraph.h"

MainGraph::MainGraph(QWidget *parent,QString name,int c) :
    QWidget(parent),
    username(name),
    themecolor(c),
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
    clearBtn = new textButton("清空",ui->widget);
    QFont m_font("Corbel Light", 20);
    m_font.setPixelSize(30);//解决不同分辨率下字体显示不全的问题
    closeBtn->setFont(m_font);
    clearBtn->setFont(m_font);
    doBfsBtn->setFont(m_font);
    doDfsBtn->setFont(m_font);
    readBtn->setFont(m_font);
    saveBtn->setFont(m_font);
    ui->verticalLayout_2->setAlignment(Qt::AlignVCenter);
    scLayout = new QVBoxLayout();
    scLayout->setMargin(2);
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
    ui->verticalLayout_2->addWidget(clearBtn);
    ui->verticalLayout_2->addWidget(closeBtn);
    ui->widget->setFixedSize(300,600);
    this->setFixedSize(800,700);//按钮大小初始化
    readGraph();
    estConnection();//信号与槽连接
}

MainGraph::~MainGraph()
{
    delete ui;
}

void MainGraph::estConnection()
{
    connect(closeBtn,&textButton::clicked,this,[=]{
        if(view->getChanged()){
            readyforClose();
        }
        else{
            close();//没有改动或改动已经被保存，直接退出
        }
    });//关闭
    connect(saveBtn,&textButton::clicked,this,[=]{saveGraph();});//保存文件
    connect(readBtn,&textButton::clicked,this,[=]{readGraph();});//读取文件
    connect(clearBtn,&textButton::clicked,this,[=](){
       view->clearAll();
       view->setChanged(true);
    });//清空

    //update: 记得在每次循环开始前，清空一下整个动画序列，清空一下遍历的记录
    connect(doDfsBtn,&textButton::clicked,this,[=]{
        loglist.clear();
        logShowClear();//清空scLayout布局内的所有元素
        view->clearAni();
        view->getCurrentSel()->setVisited(true);
        viewLog *log = new viewLog(QString("在%1号点执行深度优先搜索").arg(view->getCurrentSel()->getNodeNum()));
        emit logAdd(log);
        GraphDfs(view->getCurrentSel());
        for(auto tempvex : view->getvexlist()){
            tempvex->setVisited(false);
        }
        view->setGraphvisited(true);//标记整张图已经被遍历过
        viewLog *curLog = loglist.front();
        loglist.pop_front();
        scLayout->addWidget(curLog);//先把第一句先输出
        nextAni();

    });//实现dfs
    connect(doBfsBtn,&textButton::clicked,this,[=]{
        loglist.clear();
        logShowClear();//清空scLayout布局内的所有元素
        view->clearAni();
        view->getCurrentSel()->setVisited(true);
        viewLog *log = new viewLog(QString("在%1号点执行广度优先搜索").arg(view->getCurrentSel()->getNodeNum()));
        emit logAdd(log);
        GraphBfs(view->getCurrentSel());
        for(auto tempvex : view->getvexlist()){
            tempvex->setVisited(false);
        }
        view->setGraphvisited(true);//标记整张图已经被遍历过
        viewLog *curLog = loglist.front();
        loglist.pop_front();
        scLayout->addWidget(curLog);//先把第一句先输出
        nextAni();
    });//实现bfs
    connect(this,&MainGraph::logAdd,this,[=](viewLog *text){
        loglist.push_back(text);
    });//将刚刚遍历的日志输入进去
    connect(this,SIGNAL(newAni(QTimeLine*)),this,SLOT(addAni(QTimeLine*)));
}

void MainGraph::nextAni()//实现前一个动画结束，才能执行下一个，日志同样的道理
{

    if(aniQueue.size()>0){
        QTimeLine *curAni = aniQueue.front();
        viewLog *curLog = loglist.front();
        aniQueue.pop_front();
        loglist.pop_front();
        connect(curAni,&QTimeLine::finished,this,[=](){scLayout->addWidget(curLog);nextAni();curAni->deleteLater();});
        curAni->start();
    }
}

void MainGraph::readyforClose()
{
    QMessageBox msgBox;
    msgBox.setText("你有未保存的修改");
    msgBox.setInformativeText("你是否要保留修改？");
    msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Save);
    msgBox.setButtonText(QMessageBox::Save,"保存");
    msgBox.setButtonText(QMessageBox::Discard,"不保存");
    msgBox.setButtonText(QMessageBox::Cancel,"取消");
    int ret = msgBox.exec();
    switch (ret) {
        case QMessageBox::Save : {
            saveGraph();
            close();
            break;
        }
        case QMessageBox::Discard :{
            //啥也不干
            close();
            break;
        }
        default:break;
    }
}

void MainGraph::logShowClear()
{
    QLayoutItem *child;
     while ((child = scLayout->takeAt(0)) != 0)
     {
            //setParent为NULL，防止删除之后界面不消失
            if(child->widget())
            {
                child->widget()->setParent(NULL);
            }

            delete child;
     }
}

void MainGraph::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setBrush(QBrush(QGradient(static_cast<QGradient::Preset>(themecolor))));
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

void MainGraph::GraphBfs(customVex *startvex)
{
     QQueue <customVex*> bfsq;
     bfsq.push_back(startvex);
     while(!bfsq.empty()){
         customVex *head = bfsq.head();
         bfsq.pop_front();
         for(auto l : head->edgeList()){
             if(!l->destNode()->getVisited()){
                 VisitingLine(l);
                 l->destNode()->setVisited(true);
                 bfsq.push_back(l->destNode());
             }
         }
     }
}

void MainGraph::VisitingLine(customLine *curline)//访问线时候的函数
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
    viewLog *log = new viewLog(QString("从%1号点到%2号点").arg(curline->sourceNode()->getNodeNum()).arg(curline->destNode()->getNodeNum()));
    emit newAni(accessEffect);
    emit logAdd(log);
}


void MainGraph::addAni(QTimeLine *curAni)
{
    aniQueue.push_back(curAni);
}



void MainGraph::saveGraph()//update:加入用户名对应的文件支持
{
    view->setChanged(false);//设置改变已经被记录
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


