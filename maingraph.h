#ifndef MAINGRAPH_H
#define MAINGRAPH_H

#include <QWidget>
#include <QLabel>
#include <QTime>
#include <QPropertyAnimation>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QSequentialAnimationGroup>
#include <QQueue>
#include <QMessageBox>
#include "customview.h"
#include "customicon.h"


namespace Ui {
class MainGraph;
}


class MainGraph : public QWidget
{
    Q_OBJECT
    //2022.11.23 加入用户名，实现用户名对应的图的生成

public:
    QString username;
    CustomView *view;
    bool m_mousepressed = false;
    QPoint m_curmousepos;
    textButton *closeBtn = nullptr;
    textButton *saveBtn = nullptr;
    textButton *doBfsBtn = nullptr;
    textButton *doDfsBtn = nullptr;
    textButton *readBtn = nullptr;
    textButton *clearBtn = nullptr;
    QVBoxLayout *scLayout = nullptr;
    int themecolor = 2;
    QVector <viewLog*> loglist;
    QQueue <QTimeLine*> aniQueue;
public:
    explicit MainGraph(QWidget *parent = nullptr,QString name = "",int c = 2);
    ~MainGraph();

    void estConnection();//信号连接
    void nextAni();//线性动画遍历
    void readyforClose();
    void logShowClear();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;


signals:
    void newAni(QTimeLine*);
    void logAdd(viewLog*);
public slots:
    void GraphDfs(customVex *startvex);
    void GraphBfs(customVex *startvex);
    void VisitingLine(customLine *);//线的动画
    void saveGraph();//保存文件
    void readGraph();//读入文件
    void addAni(QTimeLine*);
private:
    Ui::MainGraph *ui;
};

#endif // MAINGRAPH_H
