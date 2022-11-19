/********************************************************************************
** Form generated from reading UI file 'customoption_test.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CUSTOMOPTION_TEST_H
#define UI_CUSTOMOPTION_TEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_customOption_test
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton_2;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButton;

    void setupUi(QWidget *customOption_test)
    {
        if (customOption_test->objectName().isEmpty())
            customOption_test->setObjectName(QString::fromUtf8("customOption_test"));
        customOption_test->resize(294, 505);
        verticalLayout_2 = new QVBoxLayout(customOption_test);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        pushButton_2 = new QPushButton(customOption_test);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        verticalLayout->addWidget(pushButton_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        pushButton = new QPushButton(customOption_test);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        verticalLayout->addWidget(pushButton);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(customOption_test);

        QMetaObject::connectSlotsByName(customOption_test);
    } // setupUi

    void retranslateUi(QWidget *customOption_test)
    {
        customOption_test->setWindowTitle(QCoreApplication::translate("customOption_test", "Form", nullptr));
        pushButton_2->setText(QCoreApplication::translate("customOption_test", "PushButton", nullptr));
        pushButton->setText(QCoreApplication::translate("customOption_test", "PushButton", nullptr));
    } // retranslateUi

};

namespace Ui {
    class customOption_test: public Ui_customOption_test {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CUSTOMOPTION_TEST_H
