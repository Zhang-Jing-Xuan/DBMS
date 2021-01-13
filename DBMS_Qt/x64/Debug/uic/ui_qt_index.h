/********************************************************************************
** Form generated from reading UI file 'qt_index.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QT_INDEX_H
#define UI_QT_INDEX_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_qt_index
{
public:
    QTableView *tableView;
    QComboBox *box_select_talbe;
    QPushButton *button_select_refresh;
    QWidget *layoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QPushButton *button_update_table_2;
    QPushButton *button_delete_table_2;
    QPushButton *button_create_table_2;
    QPushButton *button_insert_talbe_2;
    QPushButton *buttom_drop_table_2;

    void setupUi(QWidget *qt_index)
    {
        if (qt_index->objectName().isEmpty())
            qt_index->setObjectName(QString::fromUtf8("qt_index"));
        qt_index->resize(924, 533);
        tableView = new QTableView(qt_index);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(170, 100, 651, 281));
        tableView->setFrameShape(QFrame::StyledPanel);
        tableView->setFrameShadow(QFrame::Sunken);
        tableView->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        tableView->setShowGrid(true);
        tableView->setSortingEnabled(true);
        box_select_talbe = new QComboBox(qt_index);
        box_select_talbe->setObjectName(QString::fromUtf8("box_select_talbe"));
        box_select_talbe->setGeometry(QRect(170, 80, 181, 22));
        button_select_refresh = new QPushButton(qt_index);
        button_select_refresh->setObjectName(QString::fromUtf8("button_select_refresh"));
        button_select_refresh->setGeometry(QRect(350, 80, 61, 23));
        layoutWidget_2 = new QWidget(qt_index);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(90, 100, 77, 141));
        verticalLayout_2 = new QVBoxLayout(layoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        button_update_table_2 = new QPushButton(layoutWidget_2);
        button_update_table_2->setObjectName(QString::fromUtf8("button_update_table_2"));

        verticalLayout_2->addWidget(button_update_table_2);

        button_delete_table_2 = new QPushButton(layoutWidget_2);
        button_delete_table_2->setObjectName(QString::fromUtf8("button_delete_table_2"));

        verticalLayout_2->addWidget(button_delete_table_2);

        button_create_table_2 = new QPushButton(layoutWidget_2);
        button_create_table_2->setObjectName(QString::fromUtf8("button_create_table_2"));

        verticalLayout_2->addWidget(button_create_table_2);

        button_insert_talbe_2 = new QPushButton(layoutWidget_2);
        button_insert_talbe_2->setObjectName(QString::fromUtf8("button_insert_talbe_2"));

        verticalLayout_2->addWidget(button_insert_talbe_2);

        buttom_drop_table_2 = new QPushButton(layoutWidget_2);
        buttom_drop_table_2->setObjectName(QString::fromUtf8("buttom_drop_table_2"));

        verticalLayout_2->addWidget(buttom_drop_table_2);


        retranslateUi(qt_index);
        QObject::connect(box_select_talbe, SIGNAL(activated(QString)), box_select_talbe, SLOT(setEditText(QString)));

        QMetaObject::connectSlotsByName(qt_index);
    } // setupUi

    void retranslateUi(QWidget *qt_index)
    {
        qt_index->setWindowTitle(QApplication::translate("qt_index", "qt_index", nullptr));
        button_select_refresh->setText(QApplication::translate("qt_index", "\345\210\267\346\226\260", nullptr));
        button_update_table_2->setText(QApplication::translate("qt_index", "\346\233\264\346\224\271", nullptr));
        button_delete_table_2->setText(QApplication::translate("qt_index", "\345\210\240\351\231\244\350\256\260\345\275\225", nullptr));
        button_create_table_2->setText(QApplication::translate("qt_index", "\346\226\260\345\273\272", nullptr));
        button_insert_talbe_2->setText(QApplication::translate("qt_index", " \346\217\222\345\205\245", nullptr));
        buttom_drop_table_2->setText(QApplication::translate("qt_index", "\345\210\240\351\231\244\350\241\250", nullptr));
    } // retranslateUi

};

namespace Ui {
    class qt_index: public Ui_qt_index {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QT_INDEX_H
