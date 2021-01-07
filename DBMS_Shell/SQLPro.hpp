//
//  SQLPro.hpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#ifndef SQLPro_hpp
#define SQLPro_hpp

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class SQL
{
    vector<string> sql;  //存输入的指令
public:
    vector<string> type;//存每一个有效词的类型
    SQL(char *s); //用于分析指令，字符串扫描
    string Get(int i); //得到第i个有效词
    int GetSize();//有效词总数
};
#endif /* SQLPro_hpp */
