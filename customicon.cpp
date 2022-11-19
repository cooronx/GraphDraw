#include "customicon.h"

CustomIcon::CustomIcon(const QPixmap& img,QColor co,QWidget* parent):
    QPushButton(parent),
    default_col(co)
{
    iconImg = new QPixmap(img);
    iconImg->fill(Qt::transparent);
    widgetRatio = iconImg->height()/iconImg->width();
}

CustomIcon::CustomIcon(const QString& source, QColor co,QWidget *parent):
    QPushButton(parent),
    default_col(co)
{
    iconImg = new QPixmap(source);
    widgetRatio = iconImg->height()/iconImg->width();
}


void CustomIcon::paintEvent(QPaintEvent *){
    resize(this->height()/widgetRatio,this->height());
    QPainter bgpainter(this);
    bgpainter.setRenderHint(QPainter::Antialiasing);
    bgpainter.setPen(Qt::NoPen);
    bgpainter.setBrush(default_col);

    bgpainter.drawRoundedRect(this->rect(),radius,radius);


    QPainter pixmapPainter(this);
    pixmapPainter.setRenderHints(QPainter::Antialiasing);
    pixmapPainter.translate(width() / 2, height() / 2);//translate函数就是改变当前坐标轴的原点位置
    pixmapPainter.rotate(rotation);
    pixmapPainter.translate(-width() / 2, -height() / 2);//就是改了坐标原点又要给他改回去
    int w = rate * width();
    int h = rate * height();
    pixmapPainter.drawPixmap(width() / 2 - w / 2, height() / 2 - h / 2,
                             w, h, *iconImg);//前两个参数就是位置 后俩参数就是大小

}

void CustomIcon::mousePressEvent(QMouseEvent *event)
{
    emit clicked();
    setFocus();
    rate -= 0.1;//做出点击的那个效果
    update();

}
void CustomIcon::mouseReleaseEvent(QMouseEvent *event)
{
    rate+=0.1;//记得变成原样
    qDebug()<<"ok +1"<<endl;
    update();
}




textButton::textButton(QString text, QWidget *parent, qreal ratio) :
    QWidget(parent)
{
    QFont textFont = QFont("Corbel", 10);
    QFontMetrics fm(textFont);
    qreal height = fm.lineSpacing();
    btnText = new QLabel(this);
    btnText->setText(text);
    btnText->setFont(textFont);
    btnText->setFixedHeight(height);
    btnText->setFixedWidth(fm.size(Qt::TextSingleLine, text).width() + 2);
    btnText->setStyleSheet("color:#1c1c1c");
    btnText->setAlignment(Qt::AlignCenter);

    bgWidget = new QWidget(this);
    bgWidget->setStyleSheet("background-color:"+defaultColor+";border-radius:5px;");

    this->setFixedHeight(btnText->height() / ratio);
}



void textButton::resizeEvent(QResizeEvent *event){
    bgWidget->resize(this->size());
    btnText->move(this->width() / 2 - btnText->width() / 2, this->height() / 2 - btnText->height() / 2);
}

void textButton::enterEvent(QEvent *event){//太坑了，这里要写成QEvent才行
                                           //写成QEnterEvent要qt6才会起效
    QWidget::enterEvent(event);
    bgWidget->setStyleSheet("background-color:"+hoverColor+";border-radius:5px;");
}

void textButton::leaveEvent(QEvent *event){//其实这里的功能用qss实现更简单，但是我是个脑瘫
    //qDebug()<<"hello"<<endl;
    bgWidget->setStyleSheet("background-color:"+defaultColor+";border-radius:5px;");
}

void textButton::mousePressEvent(QMouseEvent *event){
    bgWidget->setStyleSheet("background-color:"+pressedColor+";border-radius:5px;");
    QPropertyAnimation *shrink = new QPropertyAnimation(bgWidget, "geometry", this);
    shrink->setStartValue(bgWidget->geometry());
    shrink->setEndValue(QRect(0.05 * this->width(), 0.05 * this->height(), this->width() * 0.9, this->height() * 0.9));
    shrink->setDuration(100);
    shrink->setEasingCurve(QEasingCurve::InOutExpo);
    shrink->start();
    mousePressed = true;
    setFocus();
}

void textButton::mouseReleaseEvent(QMouseEvent *event){
    if(mousePressed){
        bgWidget->setStyleSheet("background-color:"+hoverColor+";border-radius:5px;");
        QPropertyAnimation *enlarge = new QPropertyAnimation(bgWidget, "geometry", this);
        enlarge->setStartValue(bgWidget->geometry());
        enlarge->setEndValue(QRect(0, 0, this->width(), this->height()));
        enlarge->setDuration(150);
        enlarge->setEasingCurve(QEasingCurve::OutBounce);
        enlarge->start();
        mousePressed = false;
        emit clicked();
    }
}
