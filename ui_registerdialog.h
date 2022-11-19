/********************************************************************************
** Form generated from reading UI file 'registerdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REGISTERDIALOG_H
#define UI_REGISTERDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_REgisterdialog
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer;
    QPushButton *closeBtn;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QLabel *Titlelabel;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *verticalSpacer_2;
    QLineEdit *actlineEdit;
    QSpacerItem *verticalSpacer;
    QLineEdit *pwdlineEdit;
    QLineEdit *pwdlineEdit_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *registerBtn;

    void setupUi(QDialog *REgisterdialog)
    {
        if (REgisterdialog->objectName().isEmpty())
            REgisterdialog->setObjectName(QString::fromUtf8("REgisterdialog"));
        REgisterdialog->resize(354, 615);
        verticalLayout_2 = new QVBoxLayout(REgisterdialog);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(10);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer);

        closeBtn = new QPushButton(REgisterdialog);
        closeBtn->setObjectName(QString::fromUtf8("closeBtn"));

        horizontalLayout_7->addWidget(closeBtn);


        verticalLayout->addLayout(horizontalLayout_7);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        Titlelabel = new QLabel(REgisterdialog);
        Titlelabel->setObjectName(QString::fromUtf8("Titlelabel"));

        horizontalLayout->addWidget(Titlelabel);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        actlineEdit = new QLineEdit(REgisterdialog);
        actlineEdit->setObjectName(QString::fromUtf8("actlineEdit"));

        verticalLayout->addWidget(actlineEdit);

        verticalSpacer = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer);

        pwdlineEdit = new QLineEdit(REgisterdialog);
        pwdlineEdit->setObjectName(QString::fromUtf8("pwdlineEdit"));

        verticalLayout->addWidget(pwdlineEdit);

        pwdlineEdit_2 = new QLineEdit(REgisterdialog);
        pwdlineEdit_2->setObjectName(QString::fromUtf8("pwdlineEdit_2"));

        verticalLayout->addWidget(pwdlineEdit_2);

        verticalSpacer_3 = new QSpacerItem(20, 100, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_3);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        registerBtn = new QPushButton(REgisterdialog);
        registerBtn->setObjectName(QString::fromUtf8("registerBtn"));

        horizontalLayout_6->addWidget(registerBtn);


        verticalLayout->addLayout(horizontalLayout_6);


        verticalLayout_2->addLayout(verticalLayout);


        retranslateUi(REgisterdialog);

        QMetaObject::connectSlotsByName(REgisterdialog);
    } // setupUi

    void retranslateUi(QDialog *REgisterdialog)
    {
        REgisterdialog->setWindowTitle(QCoreApplication::translate("REgisterdialog", "Dialog", nullptr));
        closeBtn->setText(QString());
        Titlelabel->setText(QCoreApplication::translate("REgisterdialog", "\346\263\250\345\206\214", nullptr));
        actlineEdit->setPlaceholderText(QCoreApplication::translate("REgisterdialog", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\350\264\246\345\217\267", nullptr));
        pwdlineEdit->setPlaceholderText(QCoreApplication::translate("REgisterdialog", "\350\257\267\350\276\223\345\205\245\344\275\240\347\232\204\345\257\206\347\240\201", nullptr));
        pwdlineEdit_2->setPlaceholderText(QCoreApplication::translate("REgisterdialog", "\345\206\215\346\254\241\350\276\223\345\205\245\344\275\240\347\232\204\345\257\206\347\240\201", nullptr));
        registerBtn->setText(QCoreApplication::translate("REgisterdialog", "\346\263\250\345\206\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class REgisterdialog: public Ui_REgisterdialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REGISTERDIALOG_H
