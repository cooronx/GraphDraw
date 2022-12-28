#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCryptographicHash>
#include <QPainter>
#include <QPropertyAnimation>
#include <QPixmap>
#include <QRegion>
#include <QColor>
#include <QDebug>
#include <QMouseEvent>
#include <QLabel>
#include <QTimer>
#include <QHBoxLayout>
#include <QGraphicsBlurEffect>
#include <QGradient>
#include "customicon.h"
#include "betteroption.h"
#include "registerdialog.h"
#include "customview.h"
#include "maingraph.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


private:
    QMenuBar *bar = nullptr;
    int cornerradius = 20;//边框的弧度
    bool m_mousepressed = false;
    QPoint m_curmousepos;
    bool ismaxed = false;
    int optioncount = 0;
    int themecolor = 2;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool checklogin();//登录检查函数
    void setTheme(int x){themecolor = x;}
    int getTheme(){return themecolor;}
private slots:
    void on_closebutton_clicked();
    void on_minButton_clicked();
    void on_maxButton_clicked();
    //void animate();
    void init();
    void on_loginBtn_clicked();

    void on_registerBtn_clicked();

private:
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *event);
private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
