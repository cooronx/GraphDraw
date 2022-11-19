#ifndef REGISTERDIALOG_H
#define REGISTERDIALOG_H

#include <QDialog>
#include <QPainter>
#include <QMouseEvent>
#include <QMessageBox>
#include <QCryptographicHash>

namespace Ui {
class REgisterdialog;
}

class REgisterdialog : public QDialog
{
    Q_OBJECT

private:
    bool m_mousepressed = false;
    QPoint m_curmousepos;

public:
    explicit REgisterdialog(QWidget *parent = nullptr);
    ~REgisterdialog();



private slots:
    void on_closeBtn_clicked();

    void on_registerBtn_clicked();

private:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
private:
    Ui::REgisterdialog *ui;
};

#endif // REGISTERDIALOG_H
