#include "DBMS_Qt.h"
#include "MainPro.hpp"
#include "Table.hpp"
#include "Select.hpp"
#include <iostream>

#include <string>
#include <vector>
#include <QString>
int login_used_by_qt(string username, string password)
{
    if (username.length() == 0 || password.length() == 0)
    {
        printf("Can't fit with empty input\n");
        return 0;
    }
    string Verify = "select username, password from user.db where username=\"" + username + "\" and password=\"" + password + "\"";
    char sv[100];
    strcpy(sv, Verify.c_str());
    SQL* sql_verify = new SQL(sv);
    Table* t = doselect(sql_verify, 1);
    if (t->rnum == 0)
    {
        printf("Login_Failed!\n");
        return 0;
    }
    else
    {
        printf("Login_Successs!\n");
        return 1;
    }

}
using namespace std;
DBMS_Qt::DBMS_Qt(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    //connect(谁，发出了什么信号，谁，执行什么操作)；
    connect(this->ui.button_login, SIGNAL(clicked(bool)), this, SLOT(qt_login()));
}


void DBMS_Qt::qt_login()
{
    QString qt_name = this->ui.line_username->text();
    QString qt_password = this->ui.line_password->text();
    string name = qt_name.toStdString();
    string password = qt_password.toStdString();
    if (login_used_by_qt(name, password))
    {
        this->hide();
        p_toidx->show();
    }



}