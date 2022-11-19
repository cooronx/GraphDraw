#ifndef MAINGRAPH_H
#define MAINGRAPH_H

#include <QWidget>
#include "customview.h"

namespace Ui {
class MainGraph;
}

class MainGraph : public QWidget
{
    Q_OBJECT

public:
    explicit MainGraph(QWidget *parent = nullptr);
    ~MainGraph();

private:
    Ui::MainGraph *ui;
};

#endif // MAINGRAPH_H
