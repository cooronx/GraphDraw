#ifndef OK_H
#define OK_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>

class ok : public QPushButton
{
    Q_OBJECT

    Q_PROPERTY(
            qreal rotationAngle
            READ rotationAngle
            WRITE setrotationAngle
            NOTIFY rotationAngleChanged
            )

public:
    ok();
};

#endif // OK_H
