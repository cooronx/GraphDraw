#include "customoption_test.h"
#include "ui_customoption_test.h"

customOption_test::customOption_test(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::customOption_test)
{
    ui->setupUi(this);
}

customOption_test::~customOption_test()
{
    delete ui;
}
