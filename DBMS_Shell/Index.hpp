//
//  Index.hpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#ifndef Index_hpp
#define Index_hpp

#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
using namespace std;

struct index
{
    char name[128];
    size_t add;
};

void makeindex(string input_file,string output_file,string name);//创建索引
size_t search(char *file_name,char *name);//二分查找定位要找到的值的位置
void indexSelect(string table_file,string index_file,string name);//索引查询

#endif /* Index_hpp */





