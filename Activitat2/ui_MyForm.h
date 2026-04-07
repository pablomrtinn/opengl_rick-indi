/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout;
    QCheckBox *videocameraCheckBox;
    QCheckBox *rickAutomaticCheckBox;
    QSpacerItem *verticalSpacer;
    QPushButton *resetPushButton;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(819, 726);
        horizontalLayout = new QHBoxLayout(MyForm);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QString::fromUtf8("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        videocameraCheckBox = new QCheckBox(MyForm);
        videocameraCheckBox->setObjectName(QString::fromUtf8("videocameraCheckBox"));

        verticalLayout->addWidget(videocameraCheckBox);

        rickAutomaticCheckBox = new QCheckBox(MyForm);
        rickAutomaticCheckBox->setObjectName(QString::fromUtf8("rickAutomaticCheckBox"));

        verticalLayout->addWidget(rickAutomaticCheckBox);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        resetPushButton = new QPushButton(MyForm);
        resetPushButton->setObjectName(QString::fromUtf8("resetPushButton"));

        verticalLayout->addWidget(resetPushButton);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(pushButton);


        horizontalLayout->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(videocameraCheckBox, SIGNAL(toggled(bool)), widget, SLOT(activaVideocamera(bool)));
        QObject::connect(resetPushButton, SIGNAL(clicked()), widget, SLOT(Reset()));
        QObject::connect(rickAutomaticCheckBox, SIGNAL(toggled(bool)), widget, SLOT(activaRickAutomatic(bool)));
        QObject::connect(widget, SIGNAL(modificaCheckBoxAutomatic(bool)), rickAutomaticCheckBox, SLOT(setChecked(bool)));
        QObject::connect(widget, SIGNAL(modificaCheckBoxVideocamera(bool)), videocameraCheckBox, SLOT(setChecked(bool)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "IDI-Lab", nullptr));
        videocameraCheckBox->setText(QCoreApplication::translate("MyForm", "Videoc\303\240mera activada", nullptr));
        rickAutomaticCheckBox->setText(QCoreApplication::translate("MyForm", "Rick Autom\303\240tic", nullptr));
        resetPushButton->setText(QCoreApplication::translate("MyForm", "Reset", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "Sortir", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
