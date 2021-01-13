//
//  MainPro.cpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#include "MainPro.hpp"
#include "Table.hpp"
#include "Index.hpp"
#include "Select.hpp"



Table *table;

void createTable(SQL* sql)
{
    FILE *fp = fopen(sql->Get(2).c_str(),"rt");
    if(fp != NULL)
    {
        cout<<"Error:The Table '"<<sql->Get(2)<<"' already exist"<<endl;
        fclose(fp);
        return ;
    }
    else
    {
        table = new Table(sql);
        delete(table);
        if(sql->Get(2)!="__Table__.db"){
            string sinsert = "insert into __Table__.db values(\""+sql->Get(2)+"\")";
            char si[100];
            strcpy(si,sinsert.c_str());
            SQL *sql_si = new SQL(si);
            insertRecord(sql_si);
        }
    }
    
}


void dropTable(SQL* sql)
{
    if(sql->GetSize()<3)
    {
        cout<< "Syntax Error: Please input the name of the table" <<endl;
        return ;
    }
    if(hasfile(sql->Get(2)))
    {
        remove(sql->Get(2).c_str());
        if(sql->Get(1) == "table")
            cout<<"Drop table "<<sql->Get(2)<<" success!"<<endl;
        else
            cout<<"Drop view "<<sql->Get(2)<<" success!"<<endl;
        string sdele="delete from __Table__.db where table=\""+sql->Get(2)+"\"";
        char si[100];
        strcpy(si,sdele.c_str());
        SQL *sql_si = new SQL(si);
        deleteRecord(sql_si);
    }
    else return;
}

void alterTable(SQL* sql)
{
    if(hasfile(sql->Get(2)))
    {
        table = new Table(sql->Get(2));
        table->alter(sql);
        delete(table);
    }
    else return;
}

void insertRecord(SQL* sql)
{
    if(hasfile(sql->Get(2)))
    {
        table = new Table(sql->Get(2));
        table->insert(sql);
        delete(table);
    }
    else return;
}

void deleteRecord(SQL* sql)
{
    if(hasfile(sql->Get(2)))
    {
        table = new Table(sql->Get(2));
        table->delet(sql);
        delete(table);
    }
    else return ;
}

void updateRecord(SQL* sql)
{
    if(hasfile(sql->Get(1)))
    {
        table = new Table(sql->Get(1));
        table->update(sql);
        delete(table);
    }
    else return ;
}
void select(SQL* sql)
{
    /*    if(sql->GetSize() > 4 && sql->GetSize() <=6)
     {
     if(sql->GetSize() != 6 || sql->Get(4) != "on")
     {
     cout<< "Syntax Error: Please input the name of the table" <<endl;
     return ;
     }
     indexSelect(sql->Get(5),sql->Get(3),sql->Get(1));
     return ;
     }
     if(sql->GetSize()<4 && sql->Get(1) == "*")
     {
     cout<< "Syntax Error: Please input the name of the table" <<endl;
     return ;
     }
     else if(hasfile(sql->Get(3)))
     {
     table = new Table(sql->Get(3));
     table->show(sql);
     delete(table);
     }
     else return;*/
    //select 18 from s_age on s
    if(sql->GetSize() == 6 && sql->Get(4) == "on")
    {
        indexSelect(sql->Get(5),sql->Get(3),sql->Get(1));
        return ;
    }
    Table *t = doselect(sql,1);
    if(t != NULL)
    {
        
        t->show();
        delete(t);
    }
}


void createindex(SQL* sql)//create index s_age on s (age)
{
    if(sql->Get(3) != "on" || sql->Get(-1) != ")")
    {
        cout<< "Syntax Error" <<endl;
        return ;
    }
    
    if(hasfile(sql->Get(4)))
    {
        makeindex(sql->Get(4),sql->Get(2),sql->Get(6));
    }
    else return ;
    
}

void dropindex(SQL* sql)
{
    if(sql->GetSize()<3)
    {
        cout<< "Syntax Error: Please input the name of the table" <<endl;
        return ;
    }
    if(hasfile(sql->Get(2)))
    {
        remove(sql->Get(2).c_str());
        cout<<"Drop index "<<sql->Get(2)<<" success!"<<endl;
    }
    else return;
}
void createview(SQL* sql)
{
    if(sql->Get(3) != "as")
    {
        cout<< "Syntax Error" <<endl;
        return ;
    }
    Table *t = doselect(sql,5);
    if(t != NULL)
    {
        t->name = sql->Get(2);
        t->save();
        delete(t);
    }
}
void dropview(SQL* sql)
{
    dropTable(sql);
}
void createuser(SQL* sql)
{
    FILE *fp = fopen("user.db","rt");
    string sinsert = "insert into user.db values (" + sql->Get(2) + "," + sql->Get(3) + "," + "0)";
    char si[100];
    strcpy(si,sinsert.c_str());
    SQL *sql_si = new SQL(si);
    insertRecord(sql_si);
    printf("User has been created!\n");
    fclose(fp);//
}
void dropuser(SQL *sql)
{
    string sdelete = "delete from user.db where username=\"" + sql->Get(2) + "\" and password=\"" + sql->Get(3)+ "\"";
    char sd[100];
    strcpy(sd,sdelete.c_str());
    SQL *sql_sd = new SQL(sd);
    deleteRecord(sql_sd);
    printf("User has been deleted!\n");
    
}
void grant(SQL* sql)
{
    string guser = "update user.db set authorization=1 where username=" + sql->Get(1)+ " and password=" + sql->Get(2);
    char gu[100];
    strcpy(gu,guser.c_str());
    SQL *sql_gu = new SQL(gu);
    updateRecord(sql_gu);
    printf("Granted!\n");
}
void revoke(SQL* sql)
{
    string ruser = "update user.db set authorization=0 where username=" + sql->Get(1) + " and password=" + sql->Get(2);
    char ru[100];
    strcpy(ru,ruser.c_str());
    SQL *sql_ru = new SQL(ru);
    updateRecord(sql_ru);
    printf("Revoke Successfully!\n");
}
void showuser()
{
    string ruser = "select * from user.db";
    char ru[100];
    strcpy(ru,ruser.c_str());
    SQL *sql_ru = new SQL(ru);
    select(sql_ru);
}

void showTable()
{
    string ruser = "select * from __Table__.db";
    char ru[100];
    strcpy(ru,ruser.c_str());
    SQL *sql_ru = new SQL(ru);
    select(sql_ru);
}

bool hasfile(string name)
{
    FILE *fp = fopen(name.c_str(),"rt");
    if(fp == NULL)
    {
        cout<<"Error:The table "<<name<<" isn't exist"<<endl;
        return false;
    }
    //    else
    //    {
    fclose(fp);
    return true;
    //    }
}

