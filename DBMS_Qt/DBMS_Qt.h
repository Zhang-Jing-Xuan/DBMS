#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_DBMS_Qt.h"
#include "qt_index.h"




class DBMS_Qt : public QMainWindow
{
    Q_OBJECT

public:
    DBMS_Qt(QWidget *parent = Q_NULLPTR);
    qt_index* p_toidx;
private slots:
    void qt_login();
private:
    Ui::DBMS_QtClass ui;
};
