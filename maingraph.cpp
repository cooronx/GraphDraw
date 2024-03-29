#include "maingraph.h"
#include "ui_maingraph.h"



int f[10005];
int dist[10005];
bool book[10005];
int g[105][105];
int oriG[105][105];
const int INF = 0x3f3f3f3f;


bool cmp(const customLine* a,const customLine* b){
    return a->getWeight() < b->getWeight();
}


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
    //saveBtn = new textButton("保存",ui->widget);
    readBtn = new textButton("读入",ui->widget);
    clearBtn = new textButton("清空",ui->widget);
    doPrimBtn = new textButton("Prim算法",ui->widget);
    doKruskalBtn = new textButton("Kruskal算法",ui->widget);
    QFont m_font("Corbel Light", 20);
    m_font.setPixelSize(30);//解决不同分辨率下字体显示不全的问题
    closeBtn->setFont(m_font);
    clearBtn->setFont(m_font);
    readBtn->setFont(m_font);
    //saveBtn->setFont(m_font);
    doPrimBtn->setFont(m_font);
    doKruskalBtn->setFont(m_font);
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
    //ui->verticalLayout_2->addWidget(saveBtn);
    ui->verticalLayout_2->addWidget(readBtn);
    ui->verticalLayout_2->addWidget(doPrimBtn);
    ui->verticalLayout_2->addWidget(doKruskalBtn);
    ui->verticalLayout_2->addWidget(clearBtn);
    ui->verticalLayout_2->addWidget(closeBtn);
    ui->widget->setFixedSize(300,600);
    this->setFixedSize(800,700);//按钮大小初始化
    drawAxis();
    estConnection();//信号与槽连接
}

MainGraph::~MainGraph()
{
    delete ui;
}

void MainGraph::estConnection()
{
    connect(closeBtn,&textButton::clicked,this,[=]{
        readyforClose();
    });//关闭
    connect(readBtn,&textButton::clicked,this,[=]{
       QString filename = QFileDialog::getOpenFileName(this,"打开文件","./finalTestData","网络配置文件(*.dat)");
       readGraph(filename);
    });//读取文件
    connect(clearBtn,&textButton::clicked,this,[=](){
       view->clearAll();
       drawAxis();
       view->setChanged(true);
    });//清空

    connect(doKruskalBtn,&textButton::clicked,this,[=]{
            loglist.clear();
            logShowClear();//清空scLayout布局内的所有元素
            view->clearAni();
            viewLog *headLog = new viewLog("开始Prim算法");
            emit logAdd(headLog);
            int ans = Kruskal();
            view->setGraphvisited(true);
            viewLog *ansLog = new viewLog(QString("最小生成树的值为%1").arg(ans));
            emit logAdd(ansLog);
            viewLog *curLog = loglist.front();
            loglist.pop_front();
            scLayout->addWidget(curLog);
            curLog = loglist.front();
            loglist.pop_front();
            scLayout->addWidget(curLog);//先把前两句先输出
            update();
            nextAni();
            update();
        });


    connect(doPrimBtn,&textButton::clicked,this,[=]{
            loglist.clear();
            logShowClear();//清空scLayout布局内的所有元素
            view->clearAni();
            viewLog *headLog = new viewLog("开始Prim算法");
            emit logAdd(headLog);
            int ans = Prim();
            view->setGraphvisited(true);
            viewLog *ansLog = new viewLog(QString("最小生成树的值为%1").arg(ans));
            emit logAdd(ansLog);
            viewLog *curLog = loglist.front();
            loglist.pop_front();
            scLayout->addWidget(curLog);
            curLog = loglist.front();
            loglist.pop_front();
            scLayout->addWidget(curLog);//先把前两句先输出
            update();
            nextAni();
            update();
        });


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
            QString filename = QFileDialog::getSaveFileName(this,"保存文件","./finalTestData","网络配置文件(*.dat)");
            saveGraph(filename);
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
    Q_UNUSED(event)
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

void MainGraph::init()
{
    for(int i = 1;i<=view->getvexlist().size();++i){
        f[i] = i;
        book[i] = false;
    }
    for(int i = 0;i<105;++i){
        for(int j = 0;j<105;++j){
            g[i][j] = oriG[i][j];
        }
    }
}

int MainGraph::find(int x)
{
    if(x != f[x])f[x] = find(f[x]);
    return f[x];
}

void MainGraph::merge(int x, int y)
{
    int fx = find(x);
    int fy = find(y);
    if(fx != fy){
        f[fy] = fx;
    }
}



int MainGraph::Kruskal()
{
    int sum = 0;
    int cnt = 0;
    init();
    std::sort(view->getlinelist().begin(),view->getlinelist().end(),cmp);
     for(auto& line:view->getlinelist()){
         if(find(line->sourceNode()->nodenum) ==  find(line->destNode()->nodenum)){
             continue;
         }
         else{
             ++cnt;
             VisitingLine(line);
             merge(line->sourceNode()->nodenum,line->destNode()->nodenum);
             sum += line->getWeight();
             qDebug()<<line->getWeight();
         }
     }
     if(cnt != customVex::VexCount-1){
         viewLog *tempLog = new viewLog(QString("该网络出现故障，无法联通"));
         emit logAdd(tempLog);
         QMessageBox msgBox;
         msgBox.setText("生成网络中出现了问题");
         msgBox.setInformativeText("该网络无法正确联通");
         msgBox.setStandardButtons(QMessageBox::Ok);
         msgBox.setButtonText(QMessageBox::Ok,"确定");
         msgBox.exec();
     }
     return sum;
}




int MainGraph::Prim()
{
    init();
          // 记录已选择的边的总权值，仅仅只是为了测试打印验证
          int minTotalWeight = 0;
          // 记录已经选择过的节点
          // 从哪个节点开始，则标识已经被访问
          // 从A节点开始访问
          book[1] = true;

          // 一共要生成 n-1 条边
          for (int i = 2; i <= customVex::VexCount; i++) {
              // 每次循环：选择一条权值最小的边出来

              //记录边的权值
              int minWeight = INT_MAX;
              //记录边
              int x = -1,y = -1;
              customLine* line = nullptr;
              //每次都是从已经选择过的点中去找与该点直连的点，找到权值最小的边
              for (int j = 1; j <= customVex::VexCount; j++) {
                  for (int k = 1; k <= customVex::VexCount; k++) {
                      // 通过 j 来限定已经选择过的点
                      // 通过 k 来遍历匹配，没有选择过的点
                      if (book[j] && !book[k]){
                          // 记录最小权值，与这条边的信息
                          for(auto temp:view->getlinelist()){
                              if(temp->sourceNode()->getNodeNum() == j && temp->destNode()->getNodeNum() == k){
                                  line = temp;
                              }
                          }
                          if(line == nullptr){
                              continue;
                          }
                          if(line->getWeight() < minWeight){
                              minWeight = line->getWeight();
                              x = j;
                              y = k;
                          }

                      }
                  }
              }
              if(x == -1 && y == -1){
                  viewLog *tempLog = new viewLog(QString("该网络出现故障，无法联通"));
                  emit logAdd(tempLog);
                  QMessageBox msgBox;
                  msgBox.setText("生成网络中出现了问题");
                  msgBox.setInformativeText("该网络无法正确联通");
                  msgBox.setStandardButtons(QMessageBox::Ok);
                  msgBox.setButtonText(QMessageBox::Ok,"确定");
                  msgBox.exec();
                  return -1;
              }
              // 当一次循环结束时：就找到了一条权值最小的边
              for(auto temp:view->getlinelist()){
                  if(temp->sourceNode()->getNodeNum() == x && temp->destNode()->getNodeNum() == y){
                      VisitingLine(temp);
                      minTotalWeight += line->getWeight();
                      break;
                  }
              }
              // 统计已选择边权值
              // 记录该点已经被选择
              // 在查找最小权值边的代码中：y=k, k 表示没有被选择过的点，所以，找到之后，这里记录 y 为这条边的另一个点
              book[y] = true;
          }


    return minTotalWeight;
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

void MainGraph::drawAxis()
{
    QPen tempPen;
    tempPen.setWidth(5);
    view->scene()->addEllipse(-0.5,-0.5,1,1,tempPen);
    view->scene()->addLine(-213,0,213,0);
    view->scene()->addLine(0,-335,0,335);
}



void MainGraph::saveGraph(QString filename)//update:加入用户名对应的文件支持
{
    view->setChanged(false);//设置改变已经被记录
    //点全部存入一个文件 按照总共多少个 坐标
    QString vexfilename = filename;
    QFile vexfile(vexfilename);
    vexfile.open(QIODevice::ReadWrite|QIODevice::Text);
    QTextStream vs(&vexfile);
    vs<< view->getvexlist().size()<<" "<< view->getlinelist().size() <<"\n";
    for(auto vex : view->getvexlist()){
        vs<<vex->pos().x() <<" "<<vex->pos().y() << " " <<vex->getNodeNum() << "\n";
    }
    for(auto line : view->getlinelist()){
        vs<<line->sourceNode()->getNodeNum() <<" "<<line->destNode()->getNodeNum()<<"\n";
    }
    vexfile.close();
}

void MainGraph::readGraph(QString filename)
{
    QGraphicsScene *newscene = new QGraphicsScene();
    view->setScene(newscene);//读入文件后，相当于直接把scene换了一个新的
    drawAxis();
    QString vexfilename = filename;
    QFile vexfile(vexfilename);
    vexfile.open(QIODevice::ReadOnly|QIODevice::Text);
    QTextStream vs(&vexfile);
    int tvex = 0,tline = 0;
    vs >> tvex >> tline;
    view->getvexlist().clear();//记得先清空一下
    view->getlinelist().clear();
    for(int i = 1; i<=tvex; ++i){
        qreal x,y;
        int curcount = 0;
        vs >> x >> y >> curcount;
        customVex *newvex = new customVex(QPointF(x,y),customVex::STATE::CREATE);
        QGraphicsSimpleTextItem *showtext = new QGraphicsSimpleTextItem(newvex);
        customVex::VexCount = tvex;
        showtext->setText("PC"+QString("%1").arg(curcount));//给每个点打上标号
        showtext->setPos(showtext->mapToItem(newvex,0,0)+QPointF(10,10));
        newvex->setNodeNum(curcount);//记得给一下每个点编号，坑死了
        view->scene()->addItem(newvex);
        view->addtoVexlist(newvex);
        vs.readLine();//跳过结尾的换行符，贼坑，花费我大量时间找bug
    }
    for(int i = 1; i<=tline; ++i){
        int s,e,w;
        vs >> s >> e >> w;//读入起始点和终点编号
        if(w == 0){
        //这条线路是断开的
            continue;
        }
        g[s][e] = w;
        g[e][s] = w;
        oriG[s][e] = w;
        oriG[e][s] = w;
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
        newline->setWeight(w);
        customLine *newLine1 = new customLine (destNode,sourceNode,false);
        newLine1->setWeight(w);
        view->scene()->addItem(newline);
        view->addtoLinelist(newline);
        view->addtoLinelist(newLine1);
        vs.readLine();
    }
    vexfile.close();
}


