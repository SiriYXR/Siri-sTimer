/********************************************************************************
** Form generated from reading UI file 'SirisTimer.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIRISTIMER_H
#define UI_SIRISTIMER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SirisTimerClass
{
public:

    void setupUi(QWidget *SirisTimerClass)
    {
        if (SirisTimerClass->objectName().isEmpty())
            SirisTimerClass->setObjectName(QStringLiteral("SirisTimerClass"));
        SirisTimerClass->resize(600, 400);

        retranslateUi(SirisTimerClass);

        QMetaObject::connectSlotsByName(SirisTimerClass);
    } // setupUi

    void retranslateUi(QWidget *SirisTimerClass)
    {
        SirisTimerClass->setWindowTitle(QApplication::translate("SirisTimerClass", "SirisTimer", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SirisTimerClass: public Ui_SirisTimerClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIRISTIMER_H
