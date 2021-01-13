//
//  main.cpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//
#include "MainPro.hpp"
#include "Table.hpp"
#include "Select.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#include <cstdio>
using namespace std;
string login_username="";

void init()
{
    FILE *fp = fopen("user.db","rt");
    if(fp == NULL)
    {
        //string screate="create table user.db (username char(20), password char(20))";//string screate
        string screate = "create table user.db (username varchar(20), password varchar(20), authorization integer)";//string screate
        char sc[100];//buffer for convert string to char
        strcpy(sc,screate.c_str());//convert string to char
        SQL *sql_sc = new SQL(sc);
        createTable(sql_sc);
        
        string sinsert = "insert into user.db values (\"root\",\"root\",1)";
        char si[100];
        strcpy(si,sinsert.c_str());
        SQL *sql_si = new SQL(si);
        insertRecord(sql_si);
        
        
    }
    else
        fclose(fp);
    fp=fopen("__Table__.db","rt");
    if(fp==NULL){
        string screate="create table __Table__.db(table varchar(20))";
        char sc[100];
        strcpy(sc,screate.c_str());
        SQL *sql_sc=new SQL(sc);
        createTable(sql_sc);
    }else{
        fclose(fp);
    }
}

int login()
{
    
    while (1)
    {
        string username, password;
        printf("Please input your username:");
        cin >> username;
        printf("Please input your password:");
        cin >> password;
        string Verify = "select username, password from user.db where username=\"" + username + "\" and password=\"" + password + "\"";
        char sv[100];
        strcpy(sv,Verify.c_str());
        SQL *sql_verify = new SQL(sv);
        Table *t = doselect(sql_verify,1);
        if(t->rnum == 0)
        {
            printf("Login Failed!\n");
        }
        else
        {
            getchar();
            login_username = username;
            return 1;
        }
    }
}



int main()
{
//    cout<<__DATE__<<" "<<__TIME__<<endl;
    init();
    freopen("test.txt","r",stdin);
//    while(login()==0);//直到用户名和密码匹配为止
    char s[100];
    while(true)
    {
        gets(s);
        SQL *sql=new SQL(s);
        //此处不能用switch-case,因为switch不支持string类型的匹配
        if(sql->Get(0) == "create" && sql->Get(1) == "table")
            createTable(sql);
        else if(sql->Get(0) == "drop" && sql->Get(1) == "table")
            dropTable(sql);
        else if(sql->Get(0) == "alter" && sql->Get(1) == "table")
            alterTable(sql);
        else if(sql->Get(0) == "insert" && sql->Get(1) == "into")
            insertRecord(sql);
        else if(sql->Get(0) == "delete")
            deleteRecord(sql);
        else if(sql->Get(0) == "update")
            updateRecord(sql);
        else if(sql->Get(0) == "select")
            select(sql);
        else if(sql->Get(0) == "grant")
            grant(sql);
        else if(sql->Get(0) == "revoke")
            revoke(sql);
        else if(sql->Get(0) == "create" && sql->Get(1) == "index")
            createindex(sql);
        else if(sql->Get(0) == "drop" && sql->Get(1) == "index")
            dropindex(sql);
        else if(sql->Get(0) == "create" && sql->Get(1) == "view")
            createview(sql);
        else if(sql->Get(0) == "drop" && sql->Get(1) == "view")
            dropview(sql);
        else if(sql->Get(0) == "create" && sql->Get(1) == "user")
            createuser(sql);
        else if(sql->Get(0) == "drop" && sql->Get(1) == "user")
            dropuser(sql);
        else if(sql->Get(0) == "show" && sql->Get(1) == "user")
            showuser();
        else if(sql->Get(0) == "show" && sql->Get(1) == "table")
            showTable();
        else if(sql->Get(0)=="-" && sql->Get(1)=="-")
            continue;
        else if(sql->Get(0)=="exit"){
            cout<<"Bye~"<<endl;
            break;
        }
        else cout<<"Bad command!"<<endl;
    }
    fclose(stdin);
    return 0;
}
//
