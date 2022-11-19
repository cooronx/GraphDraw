/********************************************************************************
** Form generated from reading UI file 'maingraph.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINGRAPH_H
#define UI_MAINGRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGraph
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_4;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer;

    void setupUi(QWidget *MainGraph)
    {
        if (MainGraph->objectName().isEmpty())
            MainGraph->setObjectName(QString::fromUtf8("MainGraph"));
        MainGraph->resize(557, 333);
        horizontalLayout_2 = new QHBoxLayout(MainGraph);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new QWidget(MainGraph);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout_4 = new QVBoxLayout(widget);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        pushButton = new QPushButton(widget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout_4->addWidget(pushButton);


        horizontalLayout->addWidget(widget);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(MainGraph);

        QMetaObject::connectSlotsByName(MainGraph);
    } // setupUi

    void retranslateUi(QWidget *MainGraph)
    {
        MainGraph->setWindowTitle(QCoreApplication::translate("MainGraph", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("MainGraph", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGraph: public Ui_MainGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGRAPH_H
