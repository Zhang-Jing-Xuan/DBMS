//
//  Index.cpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#include "Index.hpp"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cstring>
#define MAXSIZE 1024
using namespace std;

bool cmp(struct index a,struct index b)//排序的依据
{
    return strcmp(a.name,b.name)<0;
}

void makeindex(string input_file,string output_file,string name)
{
    FILE *in = fopen(input_file.c_str(),"r"), *out = fopen(output_file.c_str(),"w");
    int col,row;
    int i,j;
    int type=-1;//第几个类型
    long address;
    char buffer[128];
    struct index index_out[MAXSIZE];
    
    fscanf(in,"%d",&col);
    for(i=0;i<col*2;i++)
    {
        fscanf(in,"%s",buffer);
        if(buffer == name)
        {
            type = i/2;
        }
    }
    fscanf(in,"%d",&row);
    for(i=0;i<row;i++)
    {
        address = ftell(in);
        for(j=0;j<col;j++)
        {
            
            fscanf(in,"%s",buffer);
            if(j == type)
            {
                strcpy(index_out[i].name,buffer);//将buffer存入index_out中
                index_out[i].add = address;//将偏移量存入
            }
        }
    }
    sort(index_out,index_out+row,cmp);//排序
    fprintf(out,"%d\n",row);
//    int cnt=1;
    for(i=0;i<row;i++)
    {
        fprintf(out,"%s ",index_out[i].name);
        fprintf(out,"%zu\n",index_out[i].add);
//        cout<<cnt<<":"<<endl;
//        cout<<index_out[i].name<<" "<<index_out[i].add<<endl;
//        cnt++;
    }
    fclose(in);
    fclose(out);
    printf("Create index successfully!\n");
}

size_t search(string file_name,string find)//二分查找值
{
    //    const int MAXSIZE=1024;
    const char * name = find.c_str();
    int i,left,right,mid;
    int row;
    char buffer[MAXSIZE][128];
    size_t i_offset[MAXSIZE];
    FILE *index_file = fopen(file_name.c_str(),"r");
    
    fscanf(index_file,"%d",&row);
    for(i=0; i<row; i++)
    {
        fscanf(index_file,"%s %zd",buffer[i],&i_offset[i]);
    }
    left = 0;right = row-1;
    while(left <= right)//二分搜索
    {
        mid = (left+right)/2;
        if(strcmp(name,buffer[mid]) == 0)
        {
            fclose(index_file);
            return i_offset[mid];
        }
        else if(strcmp(name,buffer[mid]) > 0)
            left = mid+1;
        else right = mid-1;
        
    }
    fclose(index_file);
    return -1;
}

void indexSelect(string table_file,string index_file,string name)
{
    size_t address = search(index_file,name);
    FILE * table = fopen(table_file.c_str(),"r");
    int i,col;
    char buffer[128];
    /*    if(size_t == -1)
     {
     cout<<"Error:The value "<<name<<" isn't found"<<endl;
     return 0;
     }*/
    
    fscanf(table,"%d",&col);
    for(i=0; i<col*2;i++)
    {
        fscanf(table,"%s",buffer);
        if(i%2 == 0)
            cout<<buffer<<" ";
    }
    cout<<endl;
    //    fseek(table,-ftell(table),SEEK_SET);
    
    fseek(table,address,SEEK_SET);//以SEEK_SET为基准，偏移address个位置
    
    //    fscanf(table_file,"%s",buffer);
    //    while()
    //    {
    
    //    }
    
    for(i = 0; i< col; i++)
    {
        fscanf(table,"%s",buffer);
        printf("%s ",buffer);
    }
    cout<<endl;
    fclose(table);
}

/*int main()
 {
 indexSelect("s","s_age","18");
 indexSelect("s","s_age","19");
 indexSelect("s","s_age","20");
 indexSelect("s","s_age","21");
 indexSelect("s","s_age","22");
 indexSelect("s","s_age","23");
 return 0;
 }*/
