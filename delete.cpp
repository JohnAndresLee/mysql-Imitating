#include<utility>
#include<iostream>
#include<vector>
#include<string>
#include<fstream>  
#include<unordered_map>
#include<regex>
#include<cstdio>
#include"stdio.h"
#include"io.h"
#include<iomanip>
#include"tablecreate.hpp"

using namespace std;

bool deletefunc(vector<string> title,unordered_map<string,vector<string>>& m,int primary_p,string constrain, string a11, string a12, string a21, string a22, string equal1, string equal2)
{ 
    int n = 0;
    if (a21 == "")
        n = 1;
    else if (constrain == "AND")
        n = 2;
    else if (constrain == "OR")
        n = 3;
   
    switch (n)
    {
    case(1):
    {
        int pos = -2;
        unordered_map<string, vector<string>>::iterator iter = m.begin();

        for (int i = 0; i < title.size(); ++i)
        {
            if (title[i]==a11) //存在
            {
                pos = i;
                break;
            }
        }
        bool flag = false;
        if (pos == -2)
        {
            return flag;
        }
        else if (pos == primary_p)
        {
            if (equal1 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
        else
        {
            if (primary_p < pos&&primary_p!=-1)
                pos -= 1;
            bool flag = false;
            if (equal1 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos] == a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos] != a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
    }
    case(2)://and
    {
        int pos1 = -2, pos2 = -2;
        unordered_map<string, vector<string>>::iterator iter = m.begin();

        string::size_type idx;
        for (int i = 0; i < title.size(); ++i)
        {
            idx = title[i].find(a11);
            if (idx != string::npos) //存在
            {
                pos1 = i;
                break;
            }
        }
        for (int i = 0; i < title.size(); ++i)
        {
            idx = title[i].find(a21);
            if (idx != string::npos) //存在
            {
                pos2 = i;
                break;
            }
        }

        bool flag = false;
        if (pos1 == -2 || pos2 == -2)
        {
            return flag;
        }
        else if (pos1 == primary_p)
        {
            int temp=pos2;
            if (pos2 > primary_p&&primary_p!=-1)
                temp = pos2 - 1;
            if (equal1 == "=" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a12 && iter->second[temp] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a12 && iter->second[temp] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "=" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a12 && iter->second[temp] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a12 && iter->second[temp] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }

            return flag;
        }
        else if (pos2 == primary_p)
        {
            int temp=pos1;
            if (pos1 > primary_p&&primary_p!=-1)
                temp = pos1 - 1;
            if (equal1 == "=" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a22 && iter->second[temp] == a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a22 && iter->second[temp] != a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "=" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a22 && iter->second[temp] == a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a22 && iter->second[temp] != a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
        else
        {
            if (pos1 > primary_p&&primary_p!=-1)
                pos1 -= 1;
            if (pos2 > primary_p&&primary_p!=-1)
                pos2 -= 1;

            bool flag = false;
            if (equal1 == "=" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] == a12 && iter->second[pos2] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] != a12 && iter->second[pos2] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "=" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] == a12 && iter->second[pos2] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "<>" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] != a12 && iter->second[pos2] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
    }
    case(3)://or
    {
        int pos1 = -2, pos2 = -2;
        unordered_map<string, vector<string>>::iterator iter = m.begin();

        string::size_type idx;
        for (int i = 0; i < title.size(); ++i)
        {
            idx = title[i].find(a11);
            if (idx != string::npos) //存在
            {
                pos1 = i;
                break;
            }
        }
        for (int i = 0; i < title.size(); ++i)
        {
            idx = title[i].find(a21);
            if (idx != string::npos) //存在
            {
                pos2 = i;
                break;
            }
        }

        bool flag = false;
        if (pos1 == -2 && pos2 == -2)
        {
            return flag;
        }
        else if (pos1 == primary_p)
        {
            int temp=pos2;
            if (pos2 > primary_p&&primary_p!=-1)
                temp = pos2 - 1;
            if (equal1 == "=" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a12 || iter->second[temp] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a12 || iter->second[temp] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "=" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a12 || iter->second[temp] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "<>" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a12 || iter->second[temp] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
        else if (pos2 == primary_p)
        {
            int temp=pos1;
            if (pos1 > primary_p&&primary_p!=-1)
                temp = pos1 - 1;
            if (equal1 == "=" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a22 || iter->second[temp] == a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->first == a22 || iter->second[temp] != a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "=" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a22 || iter->second[temp] == a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "<>" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->first != a22 || iter->second[temp] != a12)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
        else
        {
            if (pos1 > primary_p&&primary_p!=-1)
                pos1 -= 1;
            if (pos2 > primary_p&&primary_p!=-1)
                pos2 -= 1;

            bool flag = false;
            if (equal1 == "=" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] == a12 || iter->second[pos2] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "<>" && equal2 == "=")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] != a12 || iter->second[pos2] == a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "=" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] == a12 || iter->second[pos2] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            if (equal1 == "<>" && equal2 == "<>")
            {
                for (; iter != m.end();)
                {
                    if (iter->second[pos1] != a12 || iter->second[pos2] != a22)
                    {
                        flag = true;//true表示存在该关键字和字段
                        m.erase(iter++);
                    }
                    else
                        iter++;
                }
            }
            return flag;
        }
    }
    default:
        break;
    }
}

void deletetable(string tablename, string constrain, string a11, string a12, string a21, string a22, string equal1, string equal2)
{
    string temptable = tablename;
    string downname = tablename;
    vector<string> title;
    unordered_map<string, vector<string>> m;
    int primary_p = tableread(tablename, m, title);
    if (primary_p == -2)
    {
        cout << "Error!：不存在该表！" << endl;
        return;//不存在该表
    }
    else
    {
        unordered_map<string, vector<string>>::iterator iter;
        if (a11 == "")
        {
            m.clear();
            ofstream file(temptable.append(".txt"));
            file << "1";
            file.close();
            cout << "ok" << endl;
            return;
        }
        else
        {
            bool flag = deletefunc(title, m, primary_p, constrain, a11, a12, a21, a22, equal1, equal2);
            if (flag)
            {
                tablewrite(downname, m, primary_p);
                cout << "ok" << endl;
            }
            else
                cout << "Error!：不存在符合要求的字段！" << endl;//不存在要删除的B值
            return;
        }
    }
}