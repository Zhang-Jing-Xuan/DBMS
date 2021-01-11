//
//  Select.cpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#include "Select.hpp"
#include "MainPro.hpp"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<string> newatt; //属性
vector<string> sty;   //属性类型
vector<string> thebiao;//表

bool type_check(string *s,string type)//判断查询的值或者查询条件是否合法
{
//    cout<<s->substr(0,s->length())<<" "<<type<<endl;
//    for(auto i:thebiao){
//        cout<<i<<endl;
//    }
    if(type!="var") //只有当等号右面的值为变量的时候才进行判断
        return true;
    int i,j;
    for(i=0 ; (*s)[i]!='.' && i<s->length() ; i++);
    if(i < s->length())//带点的判断
    {
        string s1 = s->substr(0,i);
        for(j = 0;j < thebiao.size() ; j++)
            if(thebiao[j] == s1)
                break;
        if(j == thebiao.size())
        {
            printf("ERROR: Table '%s' doesn't exists.\n",s1.c_str());
            return false;
        }
        string s2 = s->substr(i+1,s->length());
        Table *t = new Table(s1);
        for(j = 0;j < t->cnum; j++)
            if(t->cname[j] == s2)
                break;
        if(j==t->cnum)
        {
            printf("ERROR: Unknown column '%s' in 'field list'.\n",s2.c_str());
            delete(t);
            return false;
        }
        delete(t);
    }
    else//不带点
    {
        for(j = 0;j < thebiao.size(); j++)
        {
            Table *t = new Table(thebiao[j]);
            for(i = 0;i < t->cnum; i++)
                if(t->cname[i] == (*s))
                {
                    (*s) = thebiao[j] + "." + (*s);
                    delete(t);
                    return true;
                }
            delete(t);
        }
        printf("ERROR: Unknown column '%s' in 'field list'.\n",(*s).c_str());
        return false;
    }
    return true;
}

Table* doselect(SQL *sql,int i)
{
    newatt.clear();
    sty.clear();
    thebiao.clear();
    bool dist=false;
    if(sql->Get(i)=="distinct")
    {
        dist=true;
        i++;
    }
    int j;
    
    while(1)//from 之前
    {
        string s1 = sql->Get(i);
        if(s1 == "")
        {
            printf("ERROR: Syntax error after 'select'.\n");
            return NULL;
        }
        string type = sql->type[i++];
        if(s1 != "*" && type != "var")
        {
            printf("ERROR: Unknown column '%s' in 'field list'.\n",s1.c_str());
            return NULL;
        }
        newatt.push_back(s1);
        sty.push_back(type);
        
        string s2 = sql->Get(i++);
        if(s2 == "from")
            break;
        if(s2 == "" || s2 != ",")
        {
            printf("ERROR: Syntax error after 'select'.\n");
            return NULL;
        }
    }
    
    while(1)//from之后where之前的sql语句
    {
        string s1 = sql->Get(i++);
        if(s1 == "")
        {
            printf("ERROR: Syntax error after 'from'.\n");
            return NULL;
        }
        thebiao.push_back(s1);
        if(!hasfile(s1))
            return NULL;
        
        string s2=sql->Get(i++);
        if(s2 == "" || s2 == "where")
            break;
        if(s2 != ",")
        {
            printf("ERROR: Syntax error after 'from'.\n");
            return NULL;
        }
    }
    
    for(j = 0;j < newatt.size(); j++)
        if(!type_check(&newatt[j],sty[j]))
            return NULL;
    
    Table *table1=NULL,*table = new Table(thebiao[0]);
    
    extend(table);
    for(j = 1;j < thebiao.size(); j++)    //多个表的链接
    {
        Table *table2 = new Table(thebiao[j]);
        extend(table2);
        table = join(table,table2);//笛卡尔积
    }
    //where之后
    if(sql->Get(i-1) == "where")
    {
        string rule="";
        while(1)
        {
            string left = sql->Get(i++);
            string mid = sql->Get(i++);
            string right = sql->Get(i++);
            if(left == "" || mid == "" || right == "")
            {
                printf("ERROR: syntax error after 'where'.\n");
                return NULL;
            }
            if(!type_check(&left,sql->type[i-3]) || !type_check(&right,sql->type[i-1]))
                return NULL;
            
            Table *tetable = choose(table,left,mid,right,sql->type[i-1]);//temp_table
            if(rule == "")
                table1 = tetable;
            else if(rule == "and")
                table1 = jiao(table1,tetable);
            else if(rule == "or")
                table1 = unio(table1,tetable);
            else
            {
                printf("ERROR: syntax error after 'where'.\n");
                return NULL;
            }
            
            rule = sql->Get(i++);
            if(rule == "")
            {
                delete(table);
                table=table1;
                break;
            }
        }
    }
    table = ty(table,newatt);
    
    if(dist)
        table=distinct(table);
    return table;
}

void tablecopy_attrubte(Table *t1,Table *t2)
{
    int i;
    t1->name = t2->name;
    t1->cnum = t2->cnum;
    for(i = 0; i < t1->cnum; i++)
        t1->cname.push_back(t2->cname[i]);
    for(i = 0; i<t1->cnum; i++)
        t1->ctype.push_back(t2->ctype[i]);
    t1->rnum=0;
}

bool bech(string type,string lv,string sign,string rv)
{
    char lvalue[100],rvalue[100];
    strcpy(lvalue,lv.c_str());
    strcpy(rvalue,rv.c_str());
    
    if(type == "integer")
    {
        int a = atoi(lvalue);
        int b = atoi(rvalue);
        
        if(sign == "<")
            return a < b;
        else if(sign == "<=")
            return a <= b;
        else if(sign == ">")
            return a > b;
        else if(sign == ">=")
            return a >= b;
        else if(sign == "<>")
            return a != b;
        else if(sign == "=")
            return a == b;
    }
    else if(type == "float")
    {
        float a = atof(lvalue);
        float b = atof(rvalue);
        
        if(sign == "<")
            return a < b;
        else if(sign=="<=")
            return a <= b;
        else if(sign==">")
            return a > b;
        else if(sign==">=")
            return a >= b;
        else if(sign=="<>")
            return a != b;
        else if(sign == "=")
            return a == b;
    }
    else if(type == "varchar")
    {
        if(sign == "<")
            return strcmp(lvalue,rvalue) < 0;
        else if(sign == "<=")
            return strcmp(lvalue,rvalue) <= 0;
        else if(sign == ">")
            return strcmp(lvalue,rvalue) > 0;
        else if(sign == ">=")
            return strcmp(lvalue,rvalue) >= 0;
        else if(sign == "<>")
            return strcmp(lvalue,rvalue) != 0;
        else if(sign == "=")
            return strcmp(lvalue,rvalue) == 0;
    }
    return false;
}

void extend(Table *t)
{
    for(int i = 0;i < t->cnum; i++)
        t->cname[i] = t->name + "." + t->cname[i];
}

Table* distinct(Table *t)//记录去重
{
    Table *newt = new Table();
    tablecopy_attrubte(newt,t);
    
    int i,j,k;
    for(k = 0;k < t->cnum; k++)
        newt->record.push_back(t->record[k]);
    newt->rnum = 1;
    
    for(i = 1;i < t->rnum; i++)
    {
        for(j = 0; j < i; j++)
        {
            for(k = 0; k < t->cnum; k++)
            {
                if(t->record[i*t->cnum+k] != t->record[j*t->cnum + k])
                    break;
            }
            if(k == t->cnum)
                break;
        }
        if(j == i)
        {
            for(k = 0; k < t->cnum; k++)
                newt->record.push_back(t->record[i * t->cnum + k]);
            newt->rnum++;
        }
    }
    delete(t);
    return newt;
}

Table* ty(Table *t1,vector<string> stype)//投影
{
    if(stype[0] == "*")
        return t1;
    
    int i,j,k;
    
    Table *t = new Table();
    t->name = t1->name;//表名
    t->cnum = 0;//属性个数初始化为0
    t->rnum = t1->rnum;//记录数=t1记录数
    //处理投影属性
    for(i = 0;i < stype.size(); i++)
    {
        for(j = 0;j < t1->cnum; j++)
        {
            if(t1->cname[j] == stype[i])
            {
                t->cname.push_back(t1->cname[j]);
                t->ctype.push_back(t1->ctype[j]);
                t->cnum++;
            }
        }
    }
    
    for(i = 0;i < t1->rnum; i++)
    {
        for(j = 0;j < stype.size(); j++)
        {
            for(k = 0;k < t1->cnum; k++)
            {
                if(t1->cname[k] == stype[j])
                {
                    t->record.push_back(t1->record[i * t1->cnum + k]);
                }
            }
        }
    }
    delete(t1);
    return t;
}


Table* choose(Table *t,string left,string mid,string right,string rtype)
{
    Table *newt = new Table();
    tablecopy_attrubte(newt,t);
    
    int i,j = newt->cnum,k,c;
    for(i = 0;i < newt->cnum; i++)//记住i
        if(newt->cname[i] == left)
            break;
    
    
    if(rtype == "var")
    {
        for(j = 0;j < newt->cnum; j++)//记住 j
            if(newt->cname[j] == right)
                break;
    }
    
    for(k=0;k<t->rnum;k++)
    {
        if(j<newt->cnum)
            right=t->record[k * t->cnum + j];
        
        if(bech(t->ctype[i],t->record[k * t->cnum + i],mid,right))
        {
            for(c = 0;c < t->cnum; c++)
                newt->record.push_back(t->record[k * t->cnum + c]);
            newt->rnum++;
        }
    }
    return newt;
}

Table* join(Table *b1,Table *b2)//笛卡尔积
{
    int i,j,k;
    
    Table *newb = new Table();
    newb->rnum = 0;
    
    newb->cnum = b1->cnum + b2->cnum;
    for(i = 0;i < b1->cnum; i++)
    {
        newb->cname.push_back(b1->cname[i]);
        newb->ctype.push_back(b1->ctype[i]);
    }
    for(i = 0; i < b2->cnum; i++)
    {
        newb->cname.push_back(b2->cname[i]);
        newb->ctype.push_back(b2->ctype[i]);
    }
    
    for(i = 0; i < b1->rnum; i++)
        for(j = 0; j < b2->rnum; j++)
        {
            for(k = 0; k < b1->cnum; k++)
                newb->record.push_back(b1->record[i * b1->cnum + k]);
            for(k = 0; k < b2->cnum; k++)
                newb->record.push_back(b2->record[j * b2->cnum + k]);
            newb->rnum++;
        }
    
    delete(b1);
    delete(b2);
    return newb;
}

Table* jiao(Table *t1,Table *tt)//t=t1交tt
{
    Table *t = new Table();
    tablecopy_attrubte(t,t1);
    
    int i,j,k;
    for(i = 0; i < t1->rnum; i++)
    {
        for(j = 0; j<tt->rnum; j++)
        {
            for(k = 0; k < t1->cnum; k++)
                if(t1->record[i * t1->cnum + k] != tt->record[j * tt->cnum + k])
                    break;
            
            if(k == t1->cnum)
            {
                for(k = 0;k < t1->cnum; k++)
                    t->record.push_back(t1->record[i * t1->cnum + k]);
                t->rnum++;
                break;
            }
        }
    }
    delete(t1);
    delete(tt);
    return t;
}

Table* unio(Table *t1,Table *tt)//t1:=t1并tt
{
    int i,j,k;
    for(j = 0; j < tt->rnum; j++)
    {
        for(i = 0; i < t1->rnum; i++)
        {
            for(k = 0; k < t1->cnum; k++)
                if(t1->record[i * t1->cnum+k] != tt->record[j * tt->cnum + k])
                    break;
            
            if(k == t1->cnum)
                break;
        }
        
        if(i == t1->rnum)//以tt的一条记录为值，与t1中的进行对比，如果t1中没有tt的当前记录，则插入t1中已实现合并
        {
            for(k = 0; k < t1->cnum; k++)
                t1->record.push_back(tt->record[j * tt->cnum + k]);//add into table
            t1->rnum++;
        }
    }
    delete(tt);
    return t1;
}
