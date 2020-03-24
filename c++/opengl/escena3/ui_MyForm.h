/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.9.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyGLWidget.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QHBoxLayout *horizontalLayout_4;
    MyGLWidget *widget;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *radioButton;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QSpacerItem *horizontalSpacer;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_5;
    QSpacerItem *horizontalSpacer_3;
    QSlider *horizontalSlider_5;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_4;
    QSpacerItem *horizontalSpacer_2;
    QSlider *horizontalSlider_4;
    QSpacerItem *verticalSpacer;
    QPushButton *pushButton;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QStringLiteral("MyForm"));
        MyForm->resize(1075, 756);
        horizontalLayout_4 = new QHBoxLayout(MyForm);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        widget = new MyGLWidget(MyForm);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);

        horizontalLayout_4->addWidget(widget);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setChecked(false);

        verticalLayout_3->addWidget(radioButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(MyForm);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        horizontalSlider = new QSlider(MyForm);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setMaximum(100);
        horizontalSlider->setSingleStep(1);
        horizontalSlider->setValue(80);
        horizontalSlider->setOrientation(Qt::Horizontal);

        horizontalLayout->addWidget(horizontalSlider);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_5 = new QLabel(MyForm);
        label_5->setObjectName(QStringLiteral("label_5"));

        horizontalLayout_3->addWidget(label_5);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        horizontalSlider_5 = new QSlider(MyForm);
        horizontalSlider_5->setObjectName(QStringLiteral("horizontalSlider_5"));
        horizontalSlider_5->setMaximum(100);
        horizontalSlider_5->setOrientation(Qt::Horizontal);

        horizontalLayout_3->addWidget(horizontalSlider_5);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_4 = new QLabel(MyForm);
        label_4->setObjectName(QStringLiteral("label_4"));

        horizontalLayout_2->addWidget(label_4);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalSlider_4 = new QSlider(MyForm);
        horizontalSlider_4->setObjectName(QStringLiteral("horizontalSlider_4"));
        horizontalSlider_4->setMaximum(100);
        horizontalSlider_4->setValue(80);
        horizontalSlider_4->setOrientation(Qt::Horizontal);

        horizontalLayout_2->addWidget(horizontalSlider_4);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);


        verticalLayout->addLayout(verticalLayout_3);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        verticalLayout->addWidget(pushButton);


        horizontalLayout_4->addLayout(verticalLayout);


        retranslateUi(MyForm);
        QObject::connect(radioButton, SIGNAL(toggled(bool)), widget, SLOT(changeCamara(bool)));
        QObject::connect(widget, SIGNAL(changeRadio()), radioButton, SLOT(toggle()));
        QObject::connect(pushButton, SIGNAL(clicked()), MyForm, SLOT(close()));
        QObject::connect(horizontalSlider_5, SIGNAL(valueChanged(int)), widget, SLOT(changeG(int)));
        QObject::connect(horizontalSlider, SIGNAL(valueChanged(int)), widget, SLOT(changeR(int)));
        QObject::connect(horizontalSlider_4, SIGNAL(valueChanged(int)), widget, SLOT(changeB(int)));

        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QApplication::translate("MyForm", "Form", Q_NULLPTR));
        radioButton->setText(QApplication::translate("MyForm", "1\302\252Persona", Q_NULLPTR));
        label->setText(QApplication::translate("MyForm", "R", Q_NULLPTR));
        label_5->setText(QApplication::translate("MyForm", "G", Q_NULLPTR));
        label_4->setText(QApplication::translate("MyForm", "B", Q_NULLPTR));
        pushButton->setText(QApplication::translate("MyForm", "Sortir", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
