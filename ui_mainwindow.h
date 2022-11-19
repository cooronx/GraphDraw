/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *mainupLayout;
    QHBoxLayout *titleLayout;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *funcLayout;
    QPushButton *minButton;
    QPushButton *maxButton;
    QPushButton *closebutton;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *loginLayout;
    QLineEdit *actEdit;
    QLineEdit *pwdEdit;
    QHBoxLayout *BtnLayout;
    QPushButton *loginBtn;
    QPushButton *registerBtn;
    QSpacerItem *horizontalSpacer_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        mainupLayout = new QHBoxLayout();
        mainupLayout->setObjectName(QString::fromUtf8("mainupLayout"));
        titleLayout = new QHBoxLayout();
        titleLayout->setObjectName(QString::fromUtf8("titleLayout"));
        horizontalSpacer = new QSpacerItem(168, 38, QSizePolicy::Expanding, QSizePolicy::Minimum);

        titleLayout->addItem(horizontalSpacer);


        mainupLayout->addLayout(titleLayout);

        funcLayout = new QHBoxLayout();
        funcLayout->setObjectName(QString::fromUtf8("funcLayout"));
        minButton = new QPushButton(centralwidget);
        minButton->setObjectName(QString::fromUtf8("minButton"));

        funcLayout->addWidget(minButton);

        maxButton = new QPushButton(centralwidget);
        maxButton->setObjectName(QString::fromUtf8("maxButton"));

        funcLayout->addWidget(maxButton);

        closebutton = new QPushButton(centralwidget);
        closebutton->setObjectName(QString::fromUtf8("closebutton"));
        closebutton->setIconSize(QSize(20, 16));
        closebutton->setAutoRepeatDelay(297);
        closebutton->setFlat(false);

        funcLayout->addWidget(closebutton);


        mainupLayout->addLayout(funcLayout);


        verticalLayout->addLayout(mainupLayout);


        verticalLayout_2->addLayout(verticalLayout);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_3 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);

        loginLayout = new QVBoxLayout();
        loginLayout->setSpacing(40);
        loginLayout->setObjectName(QString::fromUtf8("loginLayout"));
        actEdit = new QLineEdit(widget);
        actEdit->setObjectName(QString::fromUtf8("actEdit"));

        loginLayout->addWidget(actEdit);

        pwdEdit = new QLineEdit(widget);
        pwdEdit->setObjectName(QString::fromUtf8("pwdEdit"));

        loginLayout->addWidget(pwdEdit);

        BtnLayout = new QHBoxLayout();
        BtnLayout->setSpacing(10);
        BtnLayout->setObjectName(QString::fromUtf8("BtnLayout"));
        loginBtn = new QPushButton(widget);
        loginBtn->setObjectName(QString::fromUtf8("loginBtn"));

        BtnLayout->addWidget(loginBtn);

        registerBtn = new QPushButton(widget);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));

        BtnLayout->addWidget(registerBtn);


        loginLayout->addLayout(BtnLayout);


        horizontalLayout->addLayout(loginLayout);

        horizontalSpacer_2 = new QSpacerItem(200, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);


        verticalLayout_3->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_2->addWidget(widget);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        minButton->setText(QString());
        maxButton->setText(QString());
        closebutton->setText(QString());
        actEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\344\275\240\347\232\204\350\264\246\345\217\267", nullptr));
        pwdEdit->setPlaceholderText(QCoreApplication::translate("MainWindow", "\350\276\223\345\205\245\344\275\240\347\232\204\345\257\206\347\240\201", nullptr));
        loginBtn->setText(QCoreApplication::translate("MainWindow", "\347\231\273\345\275\225", nullptr));
        registerBtn->setText(QCoreApplication::translate("MainWindow", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
