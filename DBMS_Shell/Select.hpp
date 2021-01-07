//
//  Select.hpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#ifndef Select_hpp
#define Select_hpp

#include <stdio.h>
#include "Table.hpp"
#include "SQLPro.hpp"

void extend(Table* );
Table* distinct(Table*);
Table* ty(Table*,vector<string> stype);//投影
Table* choose(Table*,string,string,string,string);
Table* join(Table*,Table*);//笛卡尔积
Table* jiao(Table*,Table*);
Table* unio(Table*,Table*);
bool type_check(string *s,string type);
Table* doselect(SQL *sql,int i);

#endif /* Select_hpp */

