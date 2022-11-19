/********************************************************************************
** Form generated from reading UI file 'betteroption.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_BETTEROPTION_H
#define UI_BETTEROPTION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_betterOption
{
public:
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButton;

    void setupUi(QWidget *betterOption)
    {
        if (betterOption->objectName().isEmpty())
            betterOption->setObjectName(QString::fromUtf8("betterOption"));
        betterOption->resize(286, 509);
        horizontalLayout_6 = new QHBoxLayout(betterOption);
        horizontalLayout_6->setSpacing(0);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButton = new QPushButton(betterOption);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 250);"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout_6->addLayout(verticalLayout);


        retranslateUi(betterOption);

        QMetaObject::connectSlotsByName(betterOption);
    } // setupUi

    void retranslateUi(QWidget *betterOption)
    {
        betterOption->setWindowTitle(QCoreApplication::translate("betterOption", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("betterOption", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class betterOption: public Ui_betterOption {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_BETTEROPTION_H
