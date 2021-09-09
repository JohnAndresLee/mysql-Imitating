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

void updatetable(string tablename, string a0, string b0,string constrain,string a11,string a12,string a21,string a22, string equal1, string equal2)
{
    string downname = tablename;
    vector<string> title;
    unordered_map<string, vector<string>> m;
    int primary_p = tableread(downname, m, title);
    if (m.size() == 0)
    {
        cout << "error!"<<endl;
        return;
    }
    unordered_map<string, vector<string>>::iterator iter = m.begin();
    int n = 0;
 //   string a0, b0;//要修改的那个表达式
    int pos = -2;

        for (int i = 0; i < title.size(); ++i)
        {
            if (title[i]==a0) //存在
            {
                pos = i;
                break;
            }
        }

    if (pos == -2)
    {
        cout << "Error!：不存在符合要求的修改字段！"<<endl;
        return;
    }
    else
    {
        int n =0;

        if (a11 == "")
        {
            if (pos == primary_p)
            {
                if (m.size() == 1)
                {
                    vector<string> hh = m.begin()->second;
                    m.erase(m.begin());
                    m.insert(pair<string, vector<string>>(b0, hh));
                    tablewrite(tablename, m, primary_p);
                    return;
                }
                else
                {
                    cout << "Error：无法对非唯一主键执行此操作！"<<endl;
                    return;
                }
            }
            else
            {
                unordered_map<string, vector<string>>::iterator iter = m.begin();
                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp -= 1;
                for (; iter != m.end(); ++iter)
                    iter->second[temp] = b0;
                tablewrite(tablename, m, primary_p);
                cout << "ok"<<endl;
                return;
            }
            return;
        }
        else if (a21 == "")
            n = 1;
        else if (constrain == "AND")
            n = 2;
        else if (constrain == "OR")
            n = 3;

        switch (n)
        {
        case(1):
        {
            int pos1 = -2;
    //        string a11, a12;
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
            
            bool flag = false;
            if (pos1 == -2)
            {
                cout << "Error!：不存在符合要求的字段！"<<endl;//不存在该字段
                return;
            }
            else if (pos1 == primary_p)
            {
                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp = temp - 1;

                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=")
                        kfc = iter->first == a12;
                    else if (equal1 == "<>")
                        kfc = iter->first != a12;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos ==primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                continue;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！" << endl;
                                return;
                            }
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                            continue;
                        }
                    }
                    iter++;
                }    
                if (flag)
                    {
                        tablewrite(tablename, m, primary_p);
                        cout << "ok"<<endl;
                        return;
                    }
                    else
                    {
                        cout << "Error!：不存在符合要求的字段！"<<endl;
                        return;
                    }
            }
            else
            {
                if (pos1 > primary_p&&primary_p!=-1)
                    pos1 -= 1;

                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp = temp - 1;

                bool flag = false;
                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=")
                        kfc = iter->second[pos1] == a12;
                    else if (equal1 == "<>")
                        kfc = iter->second[pos1] != a12;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos ==primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                continue;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！"<<endl;
                                return;
                            }
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                            continue;
                        }
                    } 
                    iter++;
                } 
                if (flag)
                    {
                        tablewrite(tablename, m, primary_p);
                        cout << "ok"<<endl;
                        return;
                    }
                    else
                    {
                        cout << "Error!：不存在符合要求的字段！" << endl;
                        return;
                    }
            }
        }
        case(2)://and
        {
            int pos1 = -2, pos2 = -2;
   //         string a11, a12, a21, a22;
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
                cout << "Error!：不存在需要修改的字段"<<endl;//不存在该字段
                return;
            }
            else if (pos1 == primary_p)
            {
                if (pos2 > primary_p && primary_p != -1)
                    pos2 -= 1;

                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp = temp - 1;

                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "="&&equal2=="=")
                        kfc = iter->first == a12 && iter->second[pos2] == a22;
                    else if (equal1 == "<>"&&equal2=="=")
                        kfc = iter->first != a12 && iter->second[pos2] == a22;
                    else if (equal1 == "=" && equal2 == "<>")
                        kfc = iter->first == a12 && iter->second[pos2] != a22;
                    else if (equal1 == "<>" && equal2 == "<>")
                        kfc = iter->first != a12 && iter->second[pos2] != a22;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos == primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                break;
                            }
                            {
                                cout << "Error:Update failed!主键重复！" << endl;
                                return;
                            }
                            //修改主键
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                        }
                    }
                    else
                        iter++;
                }
                if (flag)
                {
                    tablewrite(tablename, m, primary_p);
                    cout << "ok"<<endl;
                }
                else
                    cout << "Error!：不存在符合要求的字段!"<<endl;
                return;
            }
            else if (pos2 == primary_p)
            {
                if (pos1 > primary_p && primary_p != -1)
                    pos1 -= 1;

                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp = temp - 1;

                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=" && equal2 == "=")
                        kfc = iter->first == a22 && iter->second[pos1] == a12;
                    else if (equal1 == "<>" && equal2 == "=")
                        kfc = iter->first == a22 && iter->second[pos1] != a12;
                    else if (equal1 == "=" && equal2 == "<>")
                        kfc = iter->first != a22 && iter->second[pos1] == a12;
                    else if (equal1 == "<>" && equal2 == "<>")
                        kfc = iter->first != a22 && iter->second[pos1] != a12;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos == primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                break;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！" << endl;
                                return;
                            }
                            //修改主键
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                        }
                    }
                    else
                        iter++;
                }
                if (flag)
                {
                    tablewrite(tablename, m, primary_p);
                    cout << "ok"<<endl;
                }
                else
                    cout << "Error!：不存在符合要求的字段！"<<endl;//不存在要删除的B值
                return;
            }
            else
            {
                int temp = pos;
                if (pos > primary_p&&primary_p!=-1)
                    temp = temp - 1;

                if (pos1 > primary_p && primary_p != -1)
                    pos1 -= 1;
                if (pos2 > primary_p && primary_p != -1)
                    pos2 -= 1;

                bool flag = false;
                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=" && equal2 == "=")
                        kfc = iter->second[pos1] == a12 && iter->second[pos2] == a22;
                    else if (equal1 == "<>" && equal2 == "=")
                        kfc = iter->second[pos1] != a12 && iter->second[pos2] == a22;
                    else if (equal1 == "=" && equal2 == "<>")
                        kfc = iter->second[pos1] == a12 && iter->second[pos2] != a22;
                    else if (equal1 == "<>" && equal2 == "<>")
                        kfc = iter->second[pos1] != a12 && iter->second[pos2] != a22;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos ==primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                break;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！" << endl;
                                return;
                            }
                            //修改主键
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                        }
                    }
                    else
                        iter++;
                }
                if (flag)
                {
                    tablewrite(tablename, m, primary_p);
                    cout << "ok"<<endl;
                }
                else
                    cout << "Error!：不存在符合要求的字段!"<<endl;//不存在要删除的B值
                return;
            }
        }
        case(3)://or
        {
            int pos1 = -2, pos2 = -2;
 //           string a11="id PRIMARY_KEY", a12="9", a21="birth_place", a22="江苏";
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
                cout << "Error!：不存在需要修改的字段"<<endl;//不存在该字段
                return;
            }
            else if (pos1 == primary_p)
            {
                if (pos2 > primary_p && primary_p != -1)
                    pos2 -= 1;
                
                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp -= 1;

                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=" && equal2 == "=")
                        kfc = iter->first == a12 || iter->second[pos2] == a22;
                    else if (equal1 == "<>" && equal2 == "=")
                        kfc = iter->first != a12 || iter->second[pos2] == a22;
                    else if (equal1 == "=" && equal2 == "<>")
                        kfc = iter->first == a12 || iter->second[pos2] != a22;
                    else if (equal1 == "<>" && equal2 == "<>")
                        kfc = iter->first != a12 || iter->second[pos2] != a22;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos == primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                break;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！"<<endl;
                                return;
                            }
                            //修改主键
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                        }
                    }
                    else
                        iter++;
                }
                if (flag)
                {
                    tablewrite(tablename, m, primary_p);
                    cout << "ok"<<endl;
                }
                else
                    cout << "Error!：不存在符合要求的字段！"<<endl;//不存在要修改的B值
                return;
            }
            else if (pos2 == primary_p)
            {
                if (pos1 > primary_p && primary_p != -1)
                    pos1 -= 1;

                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp -= 1;

                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=" && equal2 == "=")
                        kfc = iter->first == a22 || iter->second[pos1] == a12;
                    else if (equal1 == "<>" && equal2 == "=")
                        kfc = iter->first == a22 || iter->second[pos1] != a12;
                    else if (equal1 == "=" && equal2 == "<>")
                        kfc = iter->first != a22 || iter->second[pos1] == a12;
                    else if (equal1 == "<>" && equal2 == "<>")
                        kfc = iter->first != a22 || iter->second[pos1] != a12;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos == primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                break;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！"<<endl;
                                return;
                            }
                            //修改主键
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                        }
                    }
                    else
                        iter++;
                }
                if (flag)
                {
                    tablewrite(tablename, m, primary_p);
                    cout << "ok"<<endl;
                }
                else
                    cout << "Error!：不存在符合要求的字段！"<<endl;//不存在要删除的B值
                return;
            }
            else
            {
                if (pos1 > primary_p && primary_p != -1)
                    pos1 -= 1;

                if (pos2 > primary_p && primary_p != -1)
                    pos2 -= 1;

                int temp = pos;
                if (pos > primary_p && primary_p != -1)
                    temp -= 1;

                bool flag = false;
                for (; iter != m.end();)
                {
                    bool kfc = false;
                    if (equal1 == "=" && equal2 == "=")
                        kfc = iter->second[pos1] == a12 || iter->second[pos2] == a22;
                    else if (equal1 == "<>" && equal2 == "=")
                        kfc = iter->second[pos1] != a12 || iter->second[pos2] == a22;
                    else if (equal1 == "=" && equal2 == "<>")
                        kfc = iter->second[pos1] == a12 || iter->second[pos2] != a22;
                    else if (equal1 == "<>" && equal2 == "<>")
                        kfc = iter->second[pos1] != a12 || iter->second[pos2] != a22;

                    if (kfc)
                    {
                        flag = true;//true表示存在该关键字和字段
                        if (pos == primary_p)
                        {
                            vector<string> temp;
                            temp = iter->second;
                            auto insertjudge = m.insert(pair<string, vector<string>>(b0, temp));
                            if (insertjudge.second)
                            {
                                m.erase(iter++);
                                break;
                            }
                            else
                            {
                                cout << "Error:Update failed!主键重复！"<<endl;
                                return;
                            }
                            //修改主键
                        }
                        else
                        {
                            iter->second[temp] = b0;
                            iter++;
                        }
                    }
                    else
                        iter++;
                }
                if (flag)
                {
                    tablewrite(tablename, m, primary_p);
                    cout << "ok"<<endl;
                }
                else
                    cout << "Error!：不存在符合要求的字段！"<<endl;//不存在要删除的B值
                return;
            }
        }
        default:
            break;
        }
    }
    return;
}