#pragma once

#include <QWidget>
#include "ui_qt_index.h"

class qt_index : public QWidget
{
	Q_OBJECT

public:
	qt_index(QWidget *parent = Q_NULLPTR);
	~qt_index();
private slots:
	void qt_update_ComboBox();
	
private:
	Ui::qt_index ui;
};
