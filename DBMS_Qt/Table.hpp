//
//  Table.hpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#ifndef Table_hpp
#define Table_hpp
#include "SQLPro.hpp"
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Table
{
public:
    string name;//表名
    int cnum;//属性个数
    vector<string> cname;//属性名称
    vector<string> ctype;//属性类型
    vector<long long> length;//属性最大长度
    int rnum;//记录的个数
    vector<string> record;//所有记录
    
    Table();
    Table(SQL *sql);    //新建表时的构造函数
    Table(string fname);//读文件时的构造函数
    
    void save();
    void insert(SQL *sql);
    void alter(SQL *sql);
    void delet(SQL* sql);
    void update(SQL* sql);
    void show();
    void drawline();
    void drawcol(int i);
    
};
#endif /* Table_hpp */
