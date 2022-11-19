#include "customwidget.h"

customwidget::customwidget(const QPixmap &icon,QWidget *parent)
    :QPushButton(parent)
{
    m_icon = new QPixmap(icon);

}
void customwidget::paintEvent(QPaintEvent *){
    QPainter x(this);
    x.drawPixmap(rect(),m_icon);
}
