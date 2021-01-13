#include "qt_index.h"
#include <QString>
#include "qt_function.h"
#include <iostream>
#include <qstandarditemmodel.h>
using namespace std;

qt_index::qt_index(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	connect(this->ui.button_select_refresh , SIGNAL(clicked(bool)), this, SLOT(qt_update_ComboBox()));  
	connect(this->ui.box_select_talbe, QOverload<const QString&>::of(&QComboBox::currentIndexChanged), //currentIndexChanged(int)选择函数 参数传递方法目前似乎只有从Qt帮助文档中所给的函数才有传递方式
		[=](const QString& text)
		{
			string std_str = text.toStdString();
			if (std_str.empty())
			{
				return NULL;
			}
			std_str = "select * from " + std_str;
			
			char ru[100];
			strcpy(ru, std_str.c_str());
			SQL* sql_ru = new SQL(ru);
			Table* temp= select(sql_ru);
			
			
			QStandardItemModel* model = new QStandardItemModel();
			if (temp == NULL)
			{
				return NULL;
			}
			model->setColumnCount(temp->cnum);
			for (int i = 0; i < temp->cnum; i++)
			{
				
				QString Qstr_temp = QString::fromStdString(temp->cname[i]);
				model->setHeaderData(i, Qt::Horizontal, Qstr_temp);
			}
			
			model->setRowCount(temp->rnum);
			
			for(int i=0;i<temp->rnum;i++)
				for (int j = 0; j < temp->cnum; j++)
				{
					int sgn_where = i * temp->cnum + j;
					QString Qstr_temp2 = QString::fromStdString(temp->record[sgn_where]);
					model->setItem(i, j, new QStandardItem(Qstr_temp2));
				}
			
			ui.tableView->setModel(model);
			ui.tableView->show();
			
		}
	);
}

qt_index::~qt_index()
{
}

void qt_index::qt_update_ComboBox()
{
	Table* temp_Table = showTable();						//调用consloe函数实现temp_Table初始化
	ui.box_select_talbe->clear();
	for (int i = 0; i < temp_Table->rnum; i++)
	{
		QString Qstr_temp= QString::fromStdString(temp_Table->record[i]);
		ui.box_select_talbe->addItem(Qstr_temp);
	}


}
