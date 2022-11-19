#ifndef CustomView_H
#define CustomView_H

#include <QWidget>
#include <cmath>
#include <QVector>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsEllipseItem>
#include <QStyleOption>
#include <QDebug>
#include "customscene.h"
class customVex;
class customLine;
class ViewLog;



class CustomView : public QGraphicsView//重写view
{
    Q_OBJECT
private:
    QVector <customVex*> vexlist;
    QGraphicsScene *myscene;
    QPointF last_pos;
    bool pressed = false;
    bool test = true;
    bool doubleClick = false;//是否双击
    customVex *selectitem = nullptr;//当前选中了啥
    QGraphicsLineItem *m_drawingline = nullptr;//当前正在画的那条线
public:
    CustomView();
    void drawLine(QPointF start,QPointF end);
    void clearDraw();
    void setCurrentSel(customVex *);//设置当前选择项
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
public:
    enum STATE{NONE = -1,CREATE = 0,SELECTED = 1};//暂时没用上，用了中简单但不安全的办法实现
    static int VexCount;//统计一下有多少个点便于进行标号
    int cur_state = -1;
    customVex *lastVex = nullptr;//前驱
    customVex *nextVex = nullptr;//后继
    QVector <customLine*> InEdgeList;//用入边边集的第一条边的起点作为前驱
    QVector <customLine*> outEdgeList;//用出边边集的第一条边的终点作为后继
//请以后设计类的时候，读写函数都要设计 2022.11.19
public:
    customVex(QPointF,int state);
    void setLast(customVex *lt){lastVex = lt;}
    void setNext(customVex *nt){nextVex = nt;}
    void setLast(){lastVex = InEdgeList}
    void addInedge(customLine *line){InEdgeList.push_back(line);}
    void addOutedge(customLine *line){outEdgeList.push_back(line);}
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
public:
    customLine(customVex *sourceNode, customVex *destNode);

    customVex *sourceNode() const{return sourceVex;}
    customVex *destNode() const{return destVex;}
    void adjust();
protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    customVex *sourceVex, *destVex;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize;
};

class ViewLog{

};


#endif // CustomView_H
