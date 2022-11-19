#ifndef CUSTOMOPTION_TEST_H
#define CUSTOMOPTION_TEST_H

#include <QWidget>

namespace Ui {
class customOption_test;
}

class customOption_test : public QWidget
{
    Q_OBJECT

public:
    explicit customOption_test(QWidget *parent = nullptr);
    ~customOption_test();

private:
    Ui::customOption_test *ui;
};

#endif // CUSTOMOPTION_TEST_H
