#ifndef CUSTOMOPTION_H
#define CUSTOMOPTION_H

#include <QWidget>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPushButton>
#include <QFile>
#include <QLabel>
#include <QMouseEvent>
#include <QVBoxLayout>
#include "customicon.h"


class SheildLayer : public QWidget{
    Q_OBJECT

private:
    bool pressed = false;
    bool enabled = true;
    QWidget *bg;
    void mousePressEvent(QMouseEvent *event){if(enabled)pressed = true;}
    void mouseReleaseEvent(QMouseEvent *event){if(enabled && pressed)emit clicked();pressed = false;}
    void resizeEvent(QResizeEvent *event){bg->resize(this->parentWidget()->size());}
public:
    SheildLayer(QWidget *parent = nullptr) : QWidget(parent){
        bg = new QWidget(this);
        bg->resize(parent->size());
        qDebug()<<parent->size()<<endl;
        bg->setStyleSheet("background-color:#5a000000");
        bg->setAttribute(Qt::WA_TransparentForMouseEvents);
        bg->show();
    }
    void setEnabled(bool e){enabled = e;}
signals:
    void clicked();
};

class customOption : public QWidget
{
    Q_OBJECT
    static int pagecount;
private:
    int radius;//边框弧度
    bool isOpen = false;//是否打开
    QPoint startPoint;//起始位置
    QVBoxLayout *layout_main;
    QPushButton *clearBtn;
    QColor m_color = QColor(255,255,255);
    CustomIcon *closeBtn;
public:
    explicit customOption(QWidget *parent = nullptr,int ra = 10);
    ~customOption();
    void closeMoveAnimate();
    void initpage();
    void setIsopen(bool ch){isOpen = ch;}
    QPoint startpoint(){return startPoint;}
private:
    void paintEvent(QPaintEvent *event);
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void isOpenChanged();
    void CountMaxed();
};

#endif // CUSTOMOPTION_H
