#pragma once
#include "Table.hpp"
#include "Index.hpp"
#include "Select.hpp"


Table* select(SQL* sql)
{

    if (sql->GetSize() == 6 && sql->Get(4) == "on")
    {
        indexSelect(sql->Get(5), sql->Get(3), sql->Get(1));
        return NULL;
    }
    Table* t = doselect(sql, 1);
    /* Debug用，在控制台显示SQL语句是否有效
    if (t != NULL)
    {
        t->show();
    }
    */
    return t;
    
}


Table* showTable()
{
    string ruser = "select * from __Table__.db";
    char ru[100];
    strcpy(ru, ruser.c_str());
    SQL* sql_ru = new SQL(ru);
    return select(sql_ru);
    
}
