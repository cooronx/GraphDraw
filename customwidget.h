#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPushButton>
#include <QPixmap>
#include <QPainter>

class customwidget : public QPushButton
{
    Q_OBJECT;

    Q_PROPERTY(
            qreal rotationAngle
            READ rotationAngle
            WRITE setrotationAngle
            NOTIFY rotationAngleChanged
            )


private:
    qreal rotate = 0;
    QPixmap *m_icon;

public:
    customwidget(const QPixmap &icon,QWidget *parent);
private:
    void paintEvent(QPaintEvent*);
private:
    qreal rotationAngle() const {
        return rotate;
    }
    void setrotationAngle(qreal a){
        rotate = a;
    }
signals:
    void rotationAngleChanged();
};

#endif // CUSTOMWIDGET_H
