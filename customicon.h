#ifndef CUSTOMICON_H
#define CUSTOMICON_H
#include <qopenglwidget.h>
#include <QObject>
#include <QEnterEvent>
#include <QLabel>
#include <QWidget>
#include <QPushButton>
#include <QPainter>
#include <QPixmap>
#include <QIcon>
#include <QDebug>
#include <QTimer>
#include <QPropertyAnimation>


class CustomIcon : public QPushButton//自定义icon类
{
    //记住一定要update啊！！！！
    //更新功能：加入对svg文件的支持
    Q_OBJECT

    Q_PROPERTY(
            qreal rotateAngle
            READ rotateAngle
            WRITE setrotateAngle
            NOTIFY rotateAngleChanged
            )


private:
    qreal rotation;//旋转的角度
    QPixmap *iconImg;//图片
    int widgetRatio = 0;//
    double rate = 0.9;
    int radius = 5;//弧度
    QColor default_col;
public:
    CustomIcon(const QPixmap&,QColor co,QWidget* parent);
    CustomIcon(const QString& source,QColor co,QWidget* parent);
public:
    qreal rotateAngle()const{return rotation;}
    void setrotateAngle(qreal an){
        rotation = an;
        update();
    }

private:
    void paintEvent(QPaintEvent*);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

signals:
    void rotateAngleChanged();
};
class textButton : public QWidget{//这个类得再观察一下，写的一坨答辩
    Q_OBJECT

private:
    QLabel *btnText;
    QWidget *bgWidget;
    QString defaultColor = "#1a0078d4";//这tm前面是不透明度
    QString hoverColor = "#3a0078d4";
    QString pressedColor = "#5a0078d4";

    bool mousePressed;

    void enterEvent(QEvent *event);//记住在写这个的时候看一下这个版本的文档，每个版本这个参数都不一样
    void leaveEvent(QEvent *event);//再重写函数时最好加上override来打开编译器警告，但是我这里懒得写了
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void resizeEvent(QResizeEvent *event);

public:
    textButton(QString text, QWidget *parent = nullptr, qreal ratio = 0.5);
    //textButton(QString text, QString defC, QString hoverC, QString pressedC, QWidget *parent = nullptr, qreal ratio = 0.5);

signals:
    void clicked();
};
#endif // CUSTOMICON_H
