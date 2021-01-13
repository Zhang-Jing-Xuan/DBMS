//
//  SQLPro.cpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#include "SQLPro.hpp"

SQL::SQL(char *s)
{
    int j,i=0;//i：起始位置，j：终止位置
    while(s[i]!='\0')
    {
        string str="sign";
        while(s[i] == ' ')//去除空格
            i++;
        j=i;
        if(s[i]=='-'&&s[i+1]=='-'){
            sql.push_back("-");
            sql.push_back("-");
            break;
        }
        if(s[i] == '<')// <> <=
        {
            if(s[i+1] == '>' || s[i+1] == '=') j++;
            j++;
        }
        else if(s[i]=='>')// >=
        {
            if(s[i+1] == '=')
                j++;
            j++;
        }
        
        if(s[i]=='(' || s[i]==')' || s[i]==',' || s[i]=='=' || s[i]=='*') //( ) , = 直接push_back
            j++;
        else if(s[i] == '\"') //双引号中间的字符串，值为字符串
        {
            i++;
            j++;
            while(s[j]!='\"')
            {
                j++;
            }
            str="string";
        }
        else if(s[i]>='0' && s[i]<='9') //数字
        {
            while((s[j]>='0' && s[j]<='9') || s[j]=='.')
            {
                j++;
            }
            str="num";
        }
        else
        {
            while((s[j] >= '0' && s[j] <= '9') || (s[j]>='A'&&s[j]<='Z') || (s[j]>='a'&&s[j]<='z') || s[j]=='#' || s[j]=='_' || s[j]=='.') //关键字和表名、变量名等非值字符串
            {
                j++;
            }
            str="var";
        }
        string ss(s+i,s+j);
        //        cout<<ss<<endl;
        sql.push_back(ss);
        type.push_back(str);
        if(str=="string")
            j++;//越过后面的"
        i=j;
    }
}



string SQL::Get(int i)
{
    if(i >= (int)sql.size())
        return  "";
    else if(i < 0)
        return sql[sql.size()-1];
    else return sql[i];
}

int SQL::GetSize()
{
    return (int)sql.size();
}
