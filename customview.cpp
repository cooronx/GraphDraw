#include "customview.h"

CustomView::CustomView()
{
    myscene = new QGraphicsScene();
    this->setScene(myscene);
    this->setStyleSheet("background-color: #FFFFFF;border:1px solid #cfcfcf;border-radius:10px;");
    this->setScene(myscene);
    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);//设置各种变换的锚点永远在鼠标
    this->setMouseTracking(true);
    this->setBackgroundBrush(Qt::transparent);
    this->setRenderHint(QPainter::Antialiasing);
    this->setCursor(Qt::CrossCursor);
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    this->setResizeAnchor(QGraphicsView::AnchorUnderMouse);
}

void CustomView::drawLine(QPointF start, QPointF end)
{
    QGraphicsLineItem *temp_line = new QGraphicsLineItem(start.x(),start.y(),end.x(),end.y());
    QPen pen;
    pen.setWidth(3);
    pen.setStyle(Qt::DashLine);
    pen.setBrush(Qt::red);
    pen.setCapStyle(Qt::RoundCap);
    temp_line->setPen(pen);
    myscene->addItem(temp_line);
    temp_line->setZValue(selectitem->zValue()-1);//控制z轴让线画在球形的下面
    m_drawingline = temp_line;
}

void CustomView::clearDraw()
{
    if(m_drawingline){
        myscene->removeItem(m_drawingline);//文档中有写到只是转交控制权给当初add的资源，并非删除
        m_drawingline = nullptr;//所以要手动
    }
}

void CustomView::setCurrentSel(customVex *cur_sel)
{
    selectitem = cur_sel;
}

void CustomView::mouseDoubleClickEvent(QMouseEvent *event)
{
    QPoint temp_pos = event->pos();
    QTransform trans;
    customVex *cur_sel = static_cast<customVex*>(myscene->itemAt(mapToScene(temp_pos),trans));
    if(cur_sel!=nullptr){
        setCurrentSel(cur_sel);
        doubleClick = true;
    }
}



void CustomView::wheelEvent(QWheelEvent *event)//实现滚轮对其缩放
{
    QPointF angle = event->angleDelta();//angleDelta()后面那个值y>0就是向前滚
    qDebug()<<event->angleDelta()<<endl;
    if(angle.y()>0){
        this->scale(1.1,1.1);

    }
    else {
        this->scale(1.0/1.1,1.0/1.1);
    }
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    //qDebug()<<scene()->items()<<endl;
    //这个地方应该写dynamic_cast，因为这个bug程序崩溃了好久都没找出来
    //to do，看一下dynamic_cast和static_cast的区别

    if(event->button() == Qt::LeftButton && !doubleClick){//处理新建的点项目
        //bool in = true;
        QPoint temp_pos = event->pos();
        QTransform trans;
        customVex *cur_sel = dynamic_cast<customVex*>(myscene->itemAt(mapToScene(temp_pos),trans));
        if(cur_sel != nullptr){
            //啥也不做
        }
        else{
        customVex *vex = new customVex(mapToScene(temp_pos),customVex::STATE::CREATE);
        QGraphicsSimpleTextItem *showtext = new QGraphicsSimpleTextItem(vex);
        showtext->setText("V"+QString("%1").arg(customVex::VexCount));
        showtext->setPos(showtext->mapToItem(vex,0,0)+QPointF(10,10));
        myscene->addItem(vex);
        }
    }


    if(event->button() == Qt::LeftButton && doubleClick){//画线成功了，现在要连线
        QPoint temp_pos = event->pos();
        QTransform trans;
        //返回一个指向当前item的指针
        customVex *cur_sel = dynamic_cast<customVex*>(myscene->itemAt(mapToScene(temp_pos),trans));
        if(cur_sel!=nullptr){
            qDebug()<<cur_sel->pos()<<endl;
            customLine *newline = new customLine(selectitem,cur_sel);
            myscene->addItem(newline);//记住新建完成以后要即时清除
            clearDraw();
            doubleClick = false;
        }
        else{
            clearDraw();
            doubleClick = false;
        }
    }
    if(event->button() == Qt::MiddleButton){
        pressed = true;
        last_pos = mapToScene(event->pos());
    }



    QGraphicsView::mousePressEvent(event);
}

void CustomView::mouseMoveEvent(QMouseEvent *event)
{
    if(pressed){
    QPointF move_now = mapToScene(event->pos()) - last_pos;
    setSceneRect(sceneRect().x() - move_now.x(), sceneRect().y() - move_now.y(),
                 sceneRect().width(), sceneRect().height());//也是同样的道理，算差值，然后移动
    }
    if(doubleClick&&selectitem){//如果双击到了一个item上面
        clearDraw();//这里一定要清楚一下，不然动一下就是新的一条边

        drawLine(selectitem->pos(),mapToScene(event->pos()));
    }
    QGraphicsView::mouseMoveEvent(event);
}

void CustomView::mouseReleaseEvent(QMouseEvent *event)
{
     pressed = false;
     QGraphicsView::mouseReleaseEvent(event);
}






//自定义点的实现
int customVex::VexCount = 0;

customVex::customVex(QPointF coor,int state)

{
    setPos(coor);
    setFlag(ItemIsMovable);
    setFlag(ItemSendsGeometryChanges);
    setFlag(ItemIsSelectable);
    setAcceptHoverEvents(true);
    ++VexCount;
    setZValue(-1);
}

QVariant customVex::itemChange(QGraphicsItem::GraphicsItemChange change, const QVariant &value)
{
    switch (change) {
        case ItemPositionHasChanged : {
            for(auto edge : qAsConst(InEdgeList)){
                edge->adjust();//入边调整
            }
            for(auto edge : qAsConst(outEdgeList)){
                edge->adjust();//出边调整
            }
            break;
        }
        default:break;
    }
    return QGraphicsItem::itemChange(change,value);
}





void customVex::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::darkGray);
    painter->drawEllipse(-7, -7, 20, 20);

    QRadialGradient gradient(-3, -3, 10);
    if (option->state & QStyle::State_Sunken) {//Sunken是按下的状态
        gradient.setCenter(3, 3);
        gradient.setFocalPoint(3, 3);
        gradient.setColorAt(1, QColor(Qt::yellow).lighter(120));
        gradient.setColorAt(0, QColor(Qt::darkYellow).lighter(120));
    } else {
        gradient.setColorAt(0, Qt::yellow);
        gradient.setColorAt(1, Qt::darkYellow);
    }
    painter->setBrush(gradient);
    painter->setPen(QPen(Qt::black, 0));
    painter->drawEllipse(-10, -10, 20, 20);
}

QRectF customVex::boundingRect() const
{
    qreal adjust = 2;
    return QRectF( -10 - adjust, -10 - adjust, 23 + adjust, 23 + adjust);
}

void customVex::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(cur_state != SELECTED){
        cur_state = SELECTED;

    }
    //qDebug()<<"测试成功"<<endl;
    update();
    QGraphicsItem::mousePressEvent(event);

}

void customVex::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    //下次有时间再来实现了

}



//自定义线的实现

customLine::customLine(customVex *sourceNode, customVex *destNode):
    sourceVex(sourceNode),
    destVex(destNode),
    arrowSize(10)
{
    setAcceptedMouseButtons(nullptr);
    sourceNode->addOutedge(this);//起点加出边
    destNode->addInedge(this);//终点加入边
    sourceNode->setNext(destNode);//前驱 后继设置
    destNode->setLast(sourceNode);
    this->adjust();//完成首次的调整
}

void customLine::adjust()//完成拖动时候的线的变化
{

    QLineF line(mapFromItem(sourceVex, 0, 0), mapFromItem(destVex, 0, 0));//准备一条移动过后的线
    qreal length = line.length();

    prepareGeometryChange();

    if (length > qreal(20.)) {//如果长度合理（也就是大于半径）
        qDebug()<<line.dx()<<endl;
        QPointF edgeOffset((line.dx() * 10) / length, (line.dy() * 10) / length);
        //算出应该补偿多少，不然就边就会指到中心处去
        //这里计算建议最好动手画一下，其实说白了就是line.dx()/length是那个角的cos值，10是半径，也就是算出x需要调整的值
        sourcePoint = line.p1() + edgeOffset;
        destPoint = line.p2() - edgeOffset;
    } else {
        sourcePoint = destPoint = line.p1();
    }
}

QRectF customLine::boundingRect() const
{
    qreal penWidth = 1;
    qreal extra = (penWidth + arrowSize) / 2.0;

    return QRectF(sourcePoint, QSizeF(destPoint.x() - sourcePoint.x(),
                                      destPoint.y() - sourcePoint.y()))
        .normalized()//返回一个正常的矩形 保证高度宽度都大于0 会自动换位置计算 类似与abs绝对值了
        .adjusted(-extra, -extra, extra, extra);//为箭头做出调整
}

void customLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    QLineF line(sourcePoint, destPoint);
    if (qFuzzyCompare(line.length(), qreal(0.)))
        return;

    // Draw the line itself
    painter->setPen(QPen(Qt::black, 1, Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin));
    painter->drawLine(line);

    // 画线很简单，重点是画箭头有点难
    double angle = std::atan2(-line.dy(), line.dx());


    QPointF destArrowP1 = destPoint + QPointF(sin(angle - M_PI / 3) * arrowSize,
                                              cos(angle - M_PI / 3) * arrowSize);
    QPointF destArrowP2 = destPoint + QPointF(sin(angle - M_PI + M_PI / 3) * arrowSize,
                                              cos(angle - M_PI + M_PI / 3) * arrowSize);

    painter->setBrush(Qt::black);
    painter->drawPolygon(QPolygonF() << line.p1());
    painter->drawPolygon(QPolygonF() << line.p2() << destArrowP1 << destArrowP2);
}