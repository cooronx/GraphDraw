#ifndef CustomView_H
#define CustomView_H

#include <QWidget>
#include <cmath>
#include <QVector>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QTimeLine>
#include <QStyleOption>
#include <QDebug>
#include <QLabel>
#include "customscene.h"
class customVex;
class customLine;
class ViewLog;



class CustomView : public QGraphicsView//重写view
{
    Q_OBJECT
    //2022.11.20加入了点集和边集（为什么一开始的时候没设计呢）
    //2022.11.26 加入清空功能
private:
    QVector <customVex*> vexlist;//整个view的点集
    QVector <customLine*> linelist;//整个view的边集
    QGraphicsScene *myscene;
    QPointF last_pos;
    bool pressed = false;
    bool test = true;
    bool doubleClick = false;//是否双击
    customVex *selectitem = nullptr;//当前选中了啥
    QGraphicsLineItem *m_drawingline = nullptr;//当前正在画的那条线
    bool Graphvisited = false;//判断是否经过了一次遍历
    bool changed = false;//文件是否有改动
    QVector <QGraphicsLineItem*> AniLineList;
public:
    CustomView();
    void drawLine(QPointF start,QPointF end);
    void clearDraw();//清除掉画的那条线
    void setCurrentSel(customVex *);//设置当前选择项
    void setChanged(bool x){changed = x;}
    bool getChanged(){return changed;}
    customVex* getCurrentSel(){return selectitem;}
    void addtoVexlist(customVex *v){this->vexlist.push_back(v);}
    void addtoLinelist(customLine *l){this->linelist.push_back(l);}
    QVector <customVex*>& getvexlist(){return this->vexlist;}
    QVector <customLine*>& getlinelist(){return this->linelist;}
    void setGraphvisited(bool state){this->Graphvisited = state;}
    QVector <QGraphicsLineItem*>& getAniLineList(){return this->AniLineList;}
    void pushAniLineList(QGraphicsLineItem* tl){this->AniLineList.push_back(tl);}
    void clearAni();//清空动画序列，记得每次都要调用
    void clearAll();
private:
    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void wheelEvent(QWheelEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event){this->setSceneRect(-this->width()/2,-this->height()/2,
                                                             this->width(),this->height());}
    //这个函数前俩参数是设置这个scene的坐标源点，而scene里面的item都是依据这个坐标来设置的，如果此时我把源点设置在view的中央，那即使view变化，这个相对坐标系也不会变化
    //后俩坐标是可视区域的长宽

};

class customVex : public QObject,public QGraphicsItem//自定义点item
                                                     //必须实现两个纯虚函数paint和boundingrect，前者定义图形，后者定义判定位置
{
    //已经彻底写晕了，来思考一下，一个点有三种状态 没被选中 被创建 被选中
    //2022.11.8重新构建这个点类，加入连接到这个点的边集
    //2022.11.19 加入了每个点的编号属性
public:
    enum STATE{NONE = -1,CREATE = 0,SELECTED = 1};//暂时没用上，用了中简单但不安全的办法实现
    static int VexCount;//统计一下有多少个点便于进行标号
    int cur_state = -1;
    customVex *lastVex = nullptr;//前驱
    customVex *nextVex = nullptr;//后继
    customLine *nextLine = nullptr;
    QVector <customLine*> InEdgeList;//用入边边集的第一条边的起点作为前驱
    QVector <customLine*> OutEdgeList;//用出边边集的第一条边的终点作为后继
    int nodenum = 0;
    bool visited = false;
//请以后设计类的时候，读写函数都要设计 2022.11.19
public:
    customVex(QPointF,int state);
    ~customVex();
    customLine* getnextline(){return this->nextLine;}
    void setVisited(bool state){visited = state;}
    void setNodeNum(int x){nodenum = x;}
    int  getNodeNum(){return this->nodenum;}
    bool getVisited(){return this->visited;}
    void setLast(customVex *lt){lastVex = lt;}
    void setNext(customVex *nt,customLine *nl){nextVex = nt;nextLine = nl;}
    void addInedge(customLine *line){InEdgeList.push_back(line);}
    void addOutedge(customLine *line){OutEdgeList.push_back(line);}
    QVector <customLine*> edgeList(){return this->OutEdgeList;}//返回出边集
    //QVector <customLine*> OedgeList(){return this->OutedgeList();}
    customVex* LastVex(){return this->lastVex;}//返回前驱
    customVex* NextVex(){return this->lastVex;}//返回后继
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;
    QRectF boundingRect() const override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event) override;

signals:

};




//自定义边集，这次是继承于QGraphicsLineItem，方便一点，上面那个点啥都要自己重新写
class customLine : public QObject,public QGraphicsLineItem{
    Q_OBJECT
    //2022.11.23 提供一个新的属性 length

public:
    customLine(customVex *sourceNode, customVex *destNode,int type = 0);
    customVex *sourceNode() const{return sourceVex;}
    customVex *destNode() const{return destVex;}
    void adjust();
    void drawline();//在这里画出遍历时候的线
    void setLengthrate(qreal r = 1);//用这个动画来控制线长度大小的变化
    void drawarr();
    void del();//删除动画边
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QGraphicsPathItem *arrow = nullptr;
    QPen curPen;//遍历时候用的笔
    int Linetype = 0;
    qreal m_len;
    customVex *sourceVex, *destVex;
    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;

    QGraphicsLineItem *line1 = nullptr;//画画的那条线
    qreal angle = 0;
    QPointF center;
    QPointF sP, eP, dP;

};


/*class testLine : public customLine{
    Q_OBJECT
    Q_PROPERTY(qreal len READ len WRITE setLen NOTIFY lenChanged)
public:
    explicit testLine(customVex*,customVex*);
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    qreal len(){return this->m_len;}
    void setLen(qreal x){m_len = x;prepareGeometryChange();this->update();}
private:
    qreal m_len = 1.0;
    customVex *sourceVex, *destVex;
    qreal arrowSize;
    QPointF sourcePoint;
    QPointF destPoint;
signals:
    void lenChanged();
};*/







//用来展示遍历的数据
class viewLog : public QLabel{
        Q_OBJECT
    private:
        QFont logFont = QFont("Corbel", 12);
        QString logText;
        void resizeEvent(QResizeEvent *event);
    public:
        viewLog(QString log, QWidget *parent = nullptr);

};


#endif // CustomView_H
