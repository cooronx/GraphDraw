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
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainGraph
{
public:
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QVBoxLayout *GraphLayout;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *BtnLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;

    void setupUi(QWidget *MainGraph)
    {
        if (MainGraph->objectName().isEmpty())
            MainGraph->setObjectName(QString::fromUtf8("MainGraph"));
        MainGraph->resize(802, 562);
        horizontalLayout_2 = new QHBoxLayout(MainGraph);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        GraphLayout = new QVBoxLayout();
        GraphLayout->setObjectName(QString::fromUtf8("GraphLayout"));

        horizontalLayout->addLayout(GraphLayout);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        BtnLayout = new QVBoxLayout();
        BtnLayout->setObjectName(QString::fromUtf8("BtnLayout"));
        widget = new QWidget(MainGraph);
        widget->setObjectName(QString::fromUtf8("widget"));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));

        verticalLayout->addLayout(verticalLayout_2);


        BtnLayout->addWidget(widget);


        horizontalLayout->addLayout(BtnLayout);


        horizontalLayout_2->addLayout(horizontalLayout);


        retranslateUi(MainGraph);

        QMetaObject::connectSlotsByName(MainGraph);
    } // setupUi

    void retranslateUi(QWidget *MainGraph)
    {
        MainGraph->setWindowTitle(QCoreApplication::translate("MainGraph", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainGraph: public Ui_MainGraph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINGRAPH_H
