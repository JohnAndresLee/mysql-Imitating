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
#include"function.h"

using namespace std;

void fdistinct(unordered_map<string, vector<string>>& m, vector<string> vec);//去重的函数//主键必定为空
bool extension(unordered_map<string, vector<string>>& m, unordered_map<string, vector<string>>& newm, bool isright, int pos1, int pos2, int primary_p, int wfj1, int wfj2, string a11, string a12, string a21, string a22, vector<int> vec1, string equal1, string equal2, int oper);

void selecttable(bool distinct, string value, string tablename, string constrain,string a11, string a12, string a21, string a22,string equal1,string equal2)//分别对应A,B,C,D其中D需要二次解析
{
    vector<string> title;
    bool flag = true;
    unordered_map<string, vector<string>> m;
    int primary_p = tableread(tablename, m, title);
    int mk = -1;
    if (m.size() == 0)
    {
        cout << "Error!：无有效数据！"<<endl;
        return;
    }
    if (primary_p == -2)
    {
        cout << "Error！：不存在该表！"<<endl;//不存在该表
        return;
    }
    else if (primary_p == -1)
        flag = false;//没有主键

    
    int pos1=-2, pos2=-2;
    for (int i = 0; i < title.size(); ++i)
    {
        if (title[i] == a11) //存在
        {
            pos1 = i;
            break;
        }
    }
    for (int i = 0; i < title.size(); ++i)
    {
        if (title[i] == a21) //存在
        {
            pos2 = i;
            break;
        }
    }


        unordered_map<string, vector<string>> newm;

        vector<string> vec;
        vector<int> vec1;

        bool exist = false;
        bool key = false;

        unordered_map<string, vector<string>>::iterator iter = m.begin();

        if (value == "*")
        {
            vec = title;
            for (int i = 0; i < title.size(); ++i)
                vec1.push_back(i);

            exist = true;
            if (primary_p != -1)
                key = true;
        }
        else
        {
            splitStringToVect(value, vec, ",");

            //
            for (int j = 0; j < vec.size(); ++j)
            {
                exist = false;

                for (int i = 0; i < title.size(); ++i)
                {
                    if (title[i] == vec[j])
                    {
                        if (i == primary_p)
                        {
                            key = true;
                            mk = j;
                        }
                        vec1.push_back(i);
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                {
                    cout << "error!" << endl;//不存在字段
                    return;
                }
            }
        }

        if (a11 == "")
        {

            int num = 0;
            unordered_map<string, vector<string>>::iterator iter = m.begin();

            for (; iter != m.end(); iter++)
            {
                string key11 = "NULL";
                vector<string> newvalue;//创建一个新的map
                key11 = key11.append(to_string(num));
                for (int i = 0; i < vec1.size(); ++i)
                {
                    if (vec1[i] == primary_p)//主键
                        newvalue.push_back(iter->first);
                    else if (vec1[i] > primary_p&&primary_p!=-1)
                        newvalue.push_back(iter->second[vec1[i] - 1]);
                    else
                        newvalue.push_back(iter->second[vec1[i]]);
                }
                newm.insert(pair<string, vector<string>>(key11, newvalue));
                num++;
            }
            if (distinct)
            {
                if (key)
                {
                    tabledisplay(vec, newm, false, -1);
                    return;
                }
                else
                {
                    fdistinct(newm, vec);
                    tabledisplay(vec, newm, false, -1);
                    return;
                }
            }
            else
            {
                tabledisplay(vec, newm, false, -1);
                return;
            }

        }
        else
        {
            int oper = 0;
            if (a21 == "")
            {
                if (pos1 == -2)
                {
                    cout << "Error！：不存在符合要求的字段！" << endl;
                    return;
                }
                oper = 1;
            }
            else if (constrain == "AND")
            {
                if (pos1 == -2 || pos2 == -2)
                {
                    cout << "Error！：不存在符合要求的字段！" << endl;
                    return;
                }
                oper = 2;
            }
            else if (constrain == "OR")
            {
                if (pos1 == -2 && pos2 == -2)
                {
                    cout << "Error！：不存在符合要求的字段！" << endl;
                    return;
                }
                oper = 3;
            }

            if (oper == 1)
            {
                int num = 0;

                int wfj = pos1;
                if (primary_p != -1 && pos1 > primary_p)
                    wfj -= 1;
                unordered_map<string, vector<string>>::iterator iter = m.begin();
                bool isright=false;

                for (; iter != m.end(); iter++)
                {
                    if (equal1 == "=")
                    {
                        if ((pos1 == primary_p && iter->first == a12) || iter->second[wfj] == a12)
                        {
                            isright = true;
                            string key11 = "NULL";
                            vector<string> newvalue;//创建一个新的map
                            key11 = key11.append(to_string(num));
                            for (int i = 0; i < vec1.size(); ++i)
                            {
                                if (vec1[i] == primary_p)//主键
                                    newvalue.push_back(iter->first);
                                else if (vec1[i] > primary_p && primary_p != -1)
                                    newvalue.push_back(iter->second[vec1[i] - 1]);
                                else
                                    newvalue.push_back(iter->second[vec1[i]]);
                            }
                            newm.insert(pair<string, vector<string>>(key11, newvalue));
                            num++;
                        }
                    }
                    else if (equal1 == "<>")
                    {
                        if ((pos1 == primary_p && iter->first != a12) || iter->second[wfj] != a12)
                        {
                            isright = true;
                            string key11 = "NULL";
                            vector<string> newvalue;//创建一个新的map
                            key11 = key11.append(to_string(num));
                            for (int i = 0; i < vec1.size(); ++i)
                            {
                                if (vec1[i] == primary_p)//主键
                                    newvalue.push_back(iter->first);
                                else if (vec1[i] > primary_p && primary_p != -1)
                                    newvalue.push_back(iter->second[vec1[i] - 1]);
                                else
                                    newvalue.push_back(iter->second[vec1[i]]);
                            }
                            newm.insert(pair<string, vector<string>>(key11, newvalue));
                            num++;
                        }
                    }
                }

                if (!isright)
                {
                    cout << " Error！：不存在符合要求的字段！" << endl;
                    return;
                }
                if (distinct)
                {
                    if (key)
                    {
                        tabledisplay(vec, newm, false, -1);
                        return;
                    }
                    else
                    {
                        fdistinct(newm, vec);
                        tabledisplay(vec, newm, false, -1);
                        return;
                    }
                }
                else
                {
                    tabledisplay(vec, newm, false, -1);
                    return;
                }
            }
            else if (oper == 2)
            {
                int wfj1 = pos1;
                if (primary_p != -1 && pos1 > primary_p)
                    wfj1 -= 1;

                int wfj2 = pos2;
                if (primary_p != -1 && pos2 > primary_p)
                    wfj2 -= 1;

                bool isright = false;
               
                isright=extension(m, newm, isright, pos1, pos2, primary_p, wfj1, wfj2, a11, a12, a21, a22, vec1, equal1, equal2, oper);

                if (!isright)
                {
                    cout << " Error！：不存在符合要求的字段！" << endl;
                    return;
                }
                if (distinct)
                {
                    if (key)
                    {
                        tabledisplay(vec, newm, false, -1);
                        return;
                    }
                    else
                    {
                        fdistinct(newm, vec);
                        tabledisplay(vec, newm, false, -1);
                        return;
                    }
                }
                else
                {
                    tabledisplay(vec, newm, false, -1);
                    return;
                }
            }
            else if (oper == 3)
            {
                int wfj1 = pos1;
                if (primary_p != -1 && pos1 > primary_p)
                    wfj1 -= 1;

                int wfj2 = pos2;
                if (primary_p != -1 && pos2 > primary_p)
                    wfj2 -= 1;
                bool isright = false;
  
                isright=extension(m, newm, isright, pos1, pos2, primary_p, wfj1, wfj2, a11, a12, a21, a22, vec1,equal1,equal2,oper);

                if (!isright)
                {
                    cout << " Error！：不存在符合要求的字段！" << endl;
                    return;
                }
                if (distinct)
                {
                    if (key)
                    {
                        tabledisplay(vec, newm, false, -1);
                        return;
                    }
                    else
                    {
                        fdistinct(newm, vec);
                        tabledisplay(vec, newm, false, -1);
                        return;
                    }
                }
                else
                {
                    tabledisplay(vec, newm, false, -1);
                    return;
                }
            }
            //
            //如果主键在select中则无需去重
        }
    return;
}

void fdistinct(unordered_map<string, vector<string>>& m, vector<string> vec)//去重的函数//主键必定为空
{
    unordered_map<string, vector<string>>::iterator iter = m.begin();
    for (; iter != m.end(); ++iter)
    {
        unordered_map<string, vector<string>>::iterator iter2 = m.begin();
        for (; iter2 != m.end(); )
        {
            if (iter2 != iter && iter2->second == iter->second)
                m.erase(iter2++);
            else
                ++iter2;
        }
    }
    return;
}

bool extension(unordered_map<string, vector<string>>& m,unordered_map<string, vector<string>>& newm,bool isright,int pos1,int pos2,int primary_p,int wfj1,int wfj2,string a11,string a12,string a21,string a22, vector<int> vec1,string equal1,string equal2,int oper)
{
    int num = 0;
    unordered_map<string, vector<string>>::iterator iter = m.begin();
    bool flag = false;
    for (; iter != m.end(); iter++)
    {
        if (oper == 2)
        {
            if (equal1 == "=" && equal2 == "=")
            {
                flag = ((pos1 == primary_p && iter->first == a12) || iter->second[wfj1] == a12) && ((pos2 == primary_p && iter->first == a22) || iter->second[wfj2] == a22);
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                flag = ((pos1 == primary_p && iter->first != a12) || iter->second[wfj1] != a12) && ((pos2 == primary_p && iter->first == a22) || iter->second[wfj2] == a22);
            }
            else if (equal1 == "=" && equal2 == "<>")
            {
                flag = ((pos1 == primary_p && iter->first == a12) || iter->second[wfj1] == a12) && ((pos2 == primary_p && iter->first != a22) || iter->second[wfj2] != a22);
            }
            else if (equal1 == "<>" && equal2 == "<>")
            {
                flag = ((pos1 == primary_p && iter->first != a12) || iter->second[wfj1] != a12) && ((pos2 == primary_p && iter->first != a22) || iter->second[wfj2] != a22);
            }
        }
        else if (oper == 3)
        {
            if (equal1 == "=" && equal2 == "=")
            {
                flag = ((pos1 == primary_p && iter->first == a12) || iter->second[wfj1] == a12) || ((pos2 == primary_p && iter->first == a22) || iter->second[wfj2] == a22);
            }
            else if (equal1 == "<>" && equal2 == "=")
            {
                flag = ((pos1 == primary_p && iter->first != a12) || iter->second[wfj1] != a12) || ((pos2 == primary_p && iter->first == a22) || iter->second[wfj2] == a22);
            }
            else if (equal1 == "=" && equal2 == "<>")
            {
                flag = ((pos1 == primary_p && iter->first == a12) || iter->second[wfj1] == a12) || ((pos2 == primary_p && iter->first != a22) || iter->second[wfj2] != a22);
            }
            else if (equal1 == "<>" && equal2 == "<>")
            {
                flag = ((pos1 == primary_p && iter->first != a12) || iter->second[wfj1] != a12) || ((pos2 == primary_p && iter->first != a22) || iter->second[wfj2] != a22);
            }
        }


        if (flag)
        {
            isright = true;
            string key11 = "NULL";
            vector<string> newvalue;//创建一个新的map
            key11 = key11.append(to_string(num));
            for (int i = 0; i < vec1.size(); ++i)
            {
                if (vec1[i] == primary_p)//主键
                    newvalue.push_back(iter->first);
                else if (vec1[i] > primary_p && primary_p != -1)
                    newvalue.push_back(iter->second[vec1[i] - 1]);
                else
                    newvalue.push_back(iter->second[vec1[i]]);
            }
            newm.insert(pair<string, vector<string>>(key11, newvalue));
            num++;
        }
        flag = false;
    }
    
        return isright;
}