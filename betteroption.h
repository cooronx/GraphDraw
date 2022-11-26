#ifndef BETTEROPTION_H
#define BETTEROPTION_H

#include <QWidget>
#include <QMessageBox>
#include <QFile>
#include <QMouseEvent>
#include <QPropertyAnimation>
#include <QTime>
#include "customicon.h"

namespace Ui {
class betterOption;
}

/*
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
        this->setFixedSize(parent->size());
        qDebug()<<"父亲的"<<parent->size()<<endl;
        qDebug()<<"自己的"<<bg->size()<<endl;
        bg->setStyleSheet("background-color:#5a000000");
        bg->setAttribute(Qt::WA_TransparentForMouseEvents);
        bg->show();
    }
    void setEnabled(bool e){enabled = e;}
signals:
    void clicked();
};
*/
class betterOption : public QWidget
{
    Q_OBJECT

    static int pagecount;
private:
    int radius;//边框弧度
    bool isOpen = false;//是否打开
    QPoint startPoint;//起始位置
    QColor m_color = QColor(245,245,245);
    CustomIcon *closeBtn;
    textButton *clearBtn;
    textButton *colorBtn;
    bool isInWidget = false;
public:
    explicit betterOption(QWidget *parent = nullptr,int ra = 10);
    ~betterOption();
    void closeMoveAnimate();
    void initpage();
    void setIsopen(bool ch){isOpen = ch;}
    QPoint startpoint(){return startPoint;}
private:
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    void showEvent(QShowEvent *event);
    void closeEvent(QCloseEvent *event);
    void mousePressEvent(QMouseEvent *event);
signals:
    void isOpenChanged();
    void CountMaxed();
    void colorChanged(int);
private slots:
    void clearUserFile();
private:
    Ui::betterOption *ui;
};

#endif // BETTEROPTION_H
