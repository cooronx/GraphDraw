#ifndef MAINGRAPH_H
#define MAINGRAPH_H

#include <QWidget>
#include <QLabel>
#include "customview.h"
#include "customicon.h"


namespace Ui {
class MainGraph;
}

class MainGraph : public QWidget
{
    Q_OBJECT
public:
    CustomView *view;
    bool m_mousepressed = false;
    QPoint m_curmousepos;
    textButton *closeBtn = nullptr;
    textButton *saveBtn = nullptr;
    textButton *doBfsBtn = nullptr;
    textButton *doDfsBtn = nullptr;
public:
    explicit MainGraph(QWidget *parent = nullptr);
    ~MainGraph();

    void estConnection();
protected:
    void paintEvent(QPaintEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;



public slots:
    void GraphDfs(customVex *startvex);
    void VisitingLine(customLine *);//线的动画
private:
    Ui::MainGraph *ui;
};

#endif // MAINGRAPH_H
