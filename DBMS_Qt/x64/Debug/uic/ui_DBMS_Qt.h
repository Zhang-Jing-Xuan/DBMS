/********************************************************************************
** Form generated from reading UI file 'DBMS_Qt.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DBMS_QT_H
#define UI_DBMS_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DBMS_QtClass
{
public:
    QWidget *centralWidget;
    QFrame *frame;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *line_username;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *line_password;
    QPushButton *button_login;

    void setupUi(QMainWindow *DBMS_QtClass)
    {
        if (DBMS_QtClass->objectName().isEmpty())
            DBMS_QtClass->setObjectName(QString::fromUtf8("DBMS_QtClass"));
        DBMS_QtClass->resize(500, 305);
        centralWidget = new QWidget(DBMS_QtClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        frame = new QFrame(centralWidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(80, 30, 331, 241));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        widget = new QWidget(frame);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(70, 70, 197, 81));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        line_username = new QLineEdit(widget);
        line_username->setObjectName(QString::fromUtf8("line_username"));

        horizontalLayout->addWidget(line_username);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        line_password = new QLineEdit(widget);
        line_password->setObjectName(QString::fromUtf8("line_password"));
        line_password->setEchoMode(QLineEdit::Password);

        horizontalLayout_2->addWidget(line_password);


        verticalLayout->addLayout(horizontalLayout_2);

        button_login = new QPushButton(widget);
        button_login->setObjectName(QString::fromUtf8("button_login"));

        verticalLayout->addWidget(button_login);

        DBMS_QtClass->setCentralWidget(centralWidget);
        QWidget::setTabOrder(line_username, line_password);
        QWidget::setTabOrder(line_password, button_login);

        retranslateUi(DBMS_QtClass);

        QMetaObject::connectSlotsByName(DBMS_QtClass);
    } // setupUi

    void retranslateUi(QMainWindow *DBMS_QtClass)
    {
        DBMS_QtClass->setWindowTitle(QApplication::translate("DBMS_QtClass", "DBMS_Qt", nullptr));
        label->setText(QApplication::translate("DBMS_QtClass", "\347\224\250\346\210\267\345\220\215\357\274\232", nullptr));
        line_username->setPlaceholderText(QApplication::translate("DBMS_QtClass", "UserName", nullptr));
        label_2->setText(QApplication::translate("DBMS_QtClass", "\345\257\206  \347\240\201\357\274\232", nullptr));
        line_password->setText(QString());
        line_password->setPlaceholderText(QApplication::translate("DBMS_QtClass", "PassWord", nullptr));
        button_login->setText(QApplication::translate("DBMS_QtClass", "Login", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DBMS_QtClass: public Ui_DBMS_QtClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DBMS_QT_H
