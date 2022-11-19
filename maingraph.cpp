#include "maingraph.h"
#include "ui_maingraph.h"

MainGraph::MainGraph(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainGraph)
{
    ui->setupUi(this);
    CustomView *view = new CustomView();
    view->setParent(ui->horizontalLayout->widget());
    ui->horizontalLayout->addWidget(view);
}

MainGraph::~MainGraph()
{
    delete ui;
}
