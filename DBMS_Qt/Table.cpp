//
//  Table.cpp
//  DBMS_Shell
//
//  Created by admin on 2021/1/3.
//  Copyright © 2021年 admin. All rights reserved.
//

#include "Table.hpp"
#include <algorithm>
#include <cmath>
using namespace std;
Table::Table()
{}

Table::Table(SQL *sql)//建表
{
    /*
    int cnt=0;
    while(sql->Get(cnt)!=""){
        cout<<"第"<<cnt<<"个词是: "<<sql->Get(cnt)<<endl;
        cout<<"第"<<cnt<<"个有效词e类型是: "<<sql->type[cnt]<<endl;
        cnt++;
    }
    cout<<endl;
    */
    if(sql->Get(3)!="(" || sql->Get(-1)!=")")
    {
        cout<<"Syntax Error: In Create Table" <<endl;
        return;
    }
    
    name= sql->Get(2);
    cnum=0; //属性个数
    
    int i=4;
    
    while(1)
    {
        //create table s(s# varchar(10),sname varchar(10),age integer,sex varchar(10))
        cname.push_back(sql->Get(i++));//属性名称
        ctype.push_back(sql->Get(i++));//属性类型
        if(sql->Get(i-1) == "varchar" )
        {
            if(sql->Get(i)!="(" || sql->Get(i+2)!=")")
            {
                cout<< "Syntax Error: In Create Table" <<endl;
                return;
            }
            i=i+3;//越过（）
        }
        cnum++;
        if(sql->Get(i)==")")
            break;
        else if(sql->Get(i)!=",")
        {
            cout<< "Syntax Error: In Create Table" <<endl;
            return ;
        }
        i++;//越过,
    }
    rnum=0;
    save();
}

Table::Table(string fname)
{
    FILE *fp = fopen(fname.c_str(),"rt");
    name=fname;
    int i;
    char buffer[100];
    string buf;
    fscanf(fp,"%d",&cnum);
    for(i=0;i<cnum;i++)
    {
        fscanf(fp,"%s",buffer);
        buf = buffer;
        cname.push_back(buf);
        fscanf(fp,"%s",buffer);
        buf = buffer;
        ctype.push_back(buf);
    }
    fscanf(fp,"%d",&rnum);
    for(i=0;i<cnum*rnum;i++)
    {
        fscanf(fp,"%s",buffer);
        record.push_back(buffer);
    }
    fclose(fp);
}

void Table::insert(SQL *sql)//insert into s values("s1","wang",20,"m")
{
    if(sql->Get(4)!="(" || sql->Get(-1)!=")")
    {
        cout<<"Syntax Error: In insert record" <<endl;
        return;
    }
    int i=5,count=0;
    while(1)
    {
        //        cout<<sql->Get(i)<<endl;
        record.push_back(sql->Get(i++));
        count++;
        if(sql->Get(i) == ")")
            break;
        else if(sql->Get(i)!=",")
        {
            cout<< "Syntax Error: In insert record" <<endl;
            return;
        }
        i++; //越过,
    }
    if(count == cnum)
    {
        rnum++;
        save();
    }
    else
    {
        cout<<"Error: The number of values isn't equls to the number of attribute"<<endl;
        return;
    }
}

void Table::save()
{
    FILE *fp = fopen(name.c_str(),"wt");
    fprintf(fp,"%d \n",cnum);
    int i,j;
    for(i=0;i<cnum;i++)
    {
        fprintf(fp,"%s ",cname[i].c_str());
        fprintf(fp,"%s ",ctype[i].c_str());
    }
    fprintf(fp,"\n");
    fprintf(fp,"%d\n",rnum);
    for(i=0;i<rnum;i++)
    {
        for(j=0;j<cnum;j++)
        {
            fprintf(fp,"%s ",record[i*cnum+j].c_str());
        }
        fprintf(fp,"\n");
    }
    fclose(fp);
    if(name!="__Table__.db")
    cout<<"Save success!"<<endl;
}

void Table::alter(SQL *sql)//alter table s add a float
{
    int i,mark=-1;
    if(sql->Get(5) == "varchar")
    {
        if(sql->Get(6)!="(" || sql->Get(8)!=")")
        {
            cout<<"Syntax Error: In alter table" <<endl;
            return ;
        }
    }
    if(sql->Get(3) == "add")//添加属性
    {
        string name=sql->Get(4);
        string type=sql->Get(5);
        for(i=0;i<cnum;i++)    //属性判重
        {
            if(name==cname[i])
            {
                if(type==ctype[i])
                {
                    cout<<"The same attribute!"<<endl;
                    return ;
                }
            }
            i++;
        }
        cname.push_back(name);
        ctype.push_back(type);
        cnum++;
        for(i=0;i<rnum;i++)//为每一条记录添加属性
            record.insert(record.begin()+i*cnum+cnum-1, "NULL" );
        save();
        return ;
    }
    else if(sql->Get(3) == "drop")//删除属性
    {
        for(i=0;i<cnum;i++)
        {
            if(cname[i] == sql->Get(4) && ctype[i] == sql->Get(5))
            {
                cname.erase(cname.begin()+i);
                ctype.erase(ctype.begin()+i);
                cnum--;
                for(mark=i;mark<cnum*rnum;mark=mark+cnum)
                {
                    //    cout<<record[mark]<<endl;
                    record.erase(record.begin()+mark);
                }
                save();
                return ;
            }
        }
        cout<<"Error: The attribute isn't found"<<endl;
    }
    else
        cout<<"Syntax Error: In alter table"<<endl;
}

void Table::delet(SQL* sql)//delete from s where sex="m"
{
    int i,j=-1,mark=-1;
    for(i=0;i<cnum;i++)
    {
        if(cname[i] == sql->Get(4))
        {
            mark=i;
            break;
        }
    }
    if(mark == -1)
    {
        cout<<"Not found the attribute"<<endl;
        return ;
    }
    for(i=0;i<rnum;i++)
    {
        if(record[i*cnum+mark] == sql->Get(6) )//删除当前记录
        {
            for(j=0;j<cnum;j++)
            {
                //                cout<<record[i*cnum+j]<<endl;
                record.erase(record.begin()+i*cnum); //不需+j，因为erase后 当前指的 就是要删除的
            }
            rnum--;
            i--;
        }
    }
    if(j==-1)
    {
        cout<<"Not found the value"<<endl;
        return ;
    }
    else
    {
        if(sql->Get(2)!="__Table__.db")
        cout<<"Delete record success!"<<endl;
        save();
    }
}

void Table::update(SQL* sql)//update s set age=00 where age=22
{
    int i,j=-1,mark=-1;
    for(i=0;i<cnum;i++)
    {
        if(cname[i] == sql->Get(7))
        {
            mark=i;
            break;
        }
    }
    if(mark == -1)
    {
        cout<<"Not found the attribute"<<endl;
        return ;
    }
    for(i=0;i<rnum;i++)
    {
        if(record[i*cnum+mark] == sql->Get(9) )//修改当前记录
        {
            for(j=0;j<cnum;j++)//寻找修改位置
            {
                if(cname[j] == sql->Get(3))
                {
                    mark=j;
                    break;
                }
            }
            if(mark == -1)
            {
                cout<<"Not found the attribute"<<endl;
                return ;
            }
            record[i*cnum+j] = sql->Get(5);
            cout<<"Update success"<<endl;
            save();
        }
    }
}

void Table::drawline()
{
    int i,j;
    for(i=0;i<cnum;i++)
    {
        cout<<"+";
        for(j=0;j<length[i];j++)
        {
            cout<<"-";
        }
    }
    cout<<"+"<<endl;
    
}

void Table::drawcol(int rownum)
{
    int i,j;
    for(i=0;i<cnum;i++)
    {
        cout<<"|";
        cout<<record[rownum*cnum+i];
        for(j=0;j<length[i]-record[rownum*cnum+i].length();j++)
        {
            cout<<" ";
        }
    }
    cout<<"|"<<endl;
}

void Table::show()
{
    int i,j;
    length.clear();
    for(i=0;i<cnum;i++)
    {
        length.push_back(cname[i].length());
        for(j=0;j<rnum;j++)
        {
            if(length[i]<record[j*cnum+i].length())
                length[i]=record[j*cnum+i].length();
        }
        //length[i]+=3;
        //cout<<".,.,"<<length[i]<<endl;
    }
    drawline();
    for(i=0;i<cnum;i++)
    {
        cout<<"|";
        cout<<cname[i];
    }
    for(i=0;i<length[cnum-1]-cname[cnum-1].length();i++)
    {
        cout<<" ";
    }
    cout<<"|"<<endl;
    for(i=0;i<rnum;i++)
    {
        drawline();
        drawcol(i);
    }
    drawline();
}
