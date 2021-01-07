//
//  MainPro.hpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#ifndef MainPro_hpp
#define MainPro_hpp

#include <stdio.h>
#include "Table.hpp"

void showTable();
void createTable(SQL* sql);
void dropTable(SQL* sql);
void alterTable(SQL* sql);
void insertRecord(SQL* sql);
void deleteRecord(SQL* sql);
void updateRecord(SQL* sql);
void select(SQL* sql);
void createindex(SQL* sql);
void dropindex(SQL* sql);
void createview(SQL* sql);
void dropview(SQL* sql);
void createuser(SQL* sql);
void dropuser(SQL *sql);
void grant(SQL* sql);
void revoke(SQL* sql);
void showuser();
bool hasfile(string name);
#endif /* MainPro_hpp */
