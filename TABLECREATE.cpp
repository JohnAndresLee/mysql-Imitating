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

using namespace std;

int splitStringToVect(const string& srcStr, vector<string>& destVect, const string& strFlag);
void tabledisplay(vector<string> vec,unordered_map<string, vector<string>> m,bool flag,int pos);

void tabletitle(vector<string> title, string origin, string pv, int primarykey_p);//修改tablelist,table1

int tableread(string& filename,unordered_map<string, vector<string>>& m,vector<string>& vec)
{
    string origin = filename;
    filename = filename.append("1.txt");
    ifstream myfile1(filename);
    if (!myfile1)
    {
        cout << "Open Failed!"<<endl;
        return -2;
    }
    string str;
    int position=-1;

    getline(myfile1, str);
    splitStringToVect(str, vec, ",");
    string::size_type idx;
    string temp;
    for (int i = 0; i < vec.size(); ++i)
    {
        string target = " PRIMARY_KEY";
        idx = vec[i].find(target);
        int pos = vec[i].find(target);
        if (idx != string::npos) //存在
        {
            position = i;
            temp= vec[i];
            int n = target.size();
            if (n != -1)
            {
                vec[i] = vec[i].erase(pos, n);
                break;
            }
            break;
        }
    }
    myfile1.close();


    origin=origin.append(".txt");
    ifstream file(origin);
    if (!file.is_open())
    {
        cout << "Open Failed!";
        return -2;
    }    
    string str2;
    int num = 0;
    while (getline(file, str2))
    {
        if (str2 == "1")
            break;
        else
        {
            vector<string> vec1;
            splitStringToVect(str2, vec1, ",");
            if (position != -1)
            {
                temp = vec1[position];
                vec1.erase(vec1.begin() + position);
                m.insert(pair<string, vector<string>>(temp, vec1));
            }
            else
            {
                string str = "NULL";
                m.insert(pair<string, vector<string>>(str.append(to_string(num)), vec1));
            }
            num++;
        }
    }
    file.close();

    return position;
}

void tablewrite(string& filename, unordered_map<string, vector<string>> m,int n)
{

    filename = filename.append(".txt");
    ofstream myfile(filename);
    if (!myfile.is_open())
    {
        cout << "Open Failed!";
        return;
    }
    if (m.size() == 0)
        myfile << "1";
    unordered_map<string, vector<string>>::iterator iter;
    for (iter = m.begin(); iter != m.end(); iter++)
    {
        if (n == -1)//没有设置主键
        {
            for (int i = 0; i < iter->second.size(); ++i)
            {
                if (i ==iter->second.size() - 1)
                    myfile << iter->second[i];
                else
                    myfile << iter->second[i] << ",";
            }
        }
        else if (n == iter->second.size())
        {
            for (int i = 0; i < iter->second.size(); ++i)
                myfile << iter->second[i] << ",";
            myfile << iter->first;
        }
        else
        {
            for (int i = 0; i < iter->second.size(); ++i)
            {
                if (i == n)
                    myfile << iter->first << ",";
                if (i ==iter->second.size() - 1)
                    myfile << iter->second[i];               
                else
                    myfile << iter->second[i] << ",";
            }
        }
        myfile<< endl;
    }
    return;
}

int splitStringToVect(const string& srcStr, vector<string>& destVect, const string& strFlag)
{
    int pos = srcStr.find(strFlag, 0);
    int startPos = 0;
    int splitN = pos;
    string lineText(strFlag);
    while (pos > -1)
    {
        lineText = srcStr.substr(startPos, splitN);
        startPos = pos + 1;
        pos = srcStr.find(strFlag, pos + 1);
        splitN = pos - startPos;
        destVect.push_back(lineText);
    }

    lineText = srcStr.substr(startPos, srcStr.length() - startPos);
    destVect.push_back(lineText);

    return destVect.size();
}

void tablecreate(string str,string value)
{ 
        ofstream outfile("tablelist.txt", ofstream::app);
        if (!outfile)
        {
            outfile << str << "(" << value << ")" << endl;
            outfile.close();
        }
        else
        {
            fstream myfile; //判断该表是不是已经被创建过
            myfile.open("tablelist.txt");

            string temp;
            if (!myfile)
            {
                cout << "Open Failed!" << endl;
                return;
            }
            while (getline(myfile, temp))
            {
                if (temp.find(str) != string::npos)
                {
                    cout << "Error!:表名不可重复" << endl;//表名重复的报错
                    return;
                }
            }
            myfile.close();

            outfile << str << "(" << value << ")" << endl;
            outfile.close();
        }


        string tablename = str;
        str=str.append("1");//创建 
    string sub_key =value;    
    vector<string> vec;
    splitStringToVect(sub_key, vec, ",");    

    int n =-1;//记录主键的位置,-1为初始位置
    string PRIMARY_KEY="NULL";
    string::size_type idx;
    for (int i = 0; i < vec.size(); ++i)
    {
        idx = vec[i].find("PRIMARY_KEY");
        if (idx != string::npos) //存在
        {
            n = i;
            PRIMARY_KEY = vec[i];
            vec.erase(vec.begin() + i);
            break;
        }
    }

    cout<< "ok"<<endl;

    unordered_map<string, vector<string>> m;
    m.insert(pair<string, vector<string>>(PRIMARY_KEY,vec));
    tablewrite(str, m,n);

    ofstream file(tablename.append(".txt"));
    file << "1";
    file.close();
    return;
}

int showtables()
{
    int num = 0;
    ifstream myfile("tablelist.txt");
    vector<string> vec;
    string temp;
    if (myfile.is_open())
    {
        while (getline(myfile, temp))
        {
            vec.push_back(temp);
            num++;
        }
        cout << num << " table(s):" << endl;
        if (num != 0)
        {
            vector<string>::iterator ite = vec.begin();
            for (; ite != vec.end(); ite++)
                cout << *ite << endl;
        }
        myfile.close();
    }
    else
        cout << num << " table(s):" << endl;
    return num;
}

void droptable(string tablename)
{
    string origin = tablename;

    string dou = tablename;

    tablename = tablename.append(".txt");
    dou = dou.append("1.txt");
    if (remove(tablename.c_str()) == 0)
    {
        remove(dou.c_str());

        ifstream myfile("tablelist.txt");
        vector<string> vec;
        string temp;
        if (myfile.is_open())
        {
            while (getline(myfile, temp))
            {
                if (temp.find(origin)== string::npos)
                    vec.push_back(temp);
            }
            myfile.close();
            ofstream outfile("tablelist.txt");
            for (int i = 0; i < vec.size(); ++i)
                outfile << vec[i]<<endl;
            outfile.close();
        }
        cout << "Delete Successfully！" << endl;
    }
    else
        cout << "Delete Failed!" << endl;
    return;
}

void insert(string tablename, string value)//记住考虑0的情况!!!!
{
    vector<string> title;
    string origin = tablename;
    unordered_map<string, vector<string>> m;
    int primarykey_p = tableread(tablename, m,title);

        int n = title.size();
        vector<string> vec;//新插入的值
        int nvalue = splitStringToVect(value, vec, ",");
        string pkey = "NULL";
       

        if (n == nvalue)
        {
            if (primarykey_p == -2)
            {
                cout << "Error：不存在该表！" << endl;
                return;
            }
            if (primarykey_p != -1)
            {
                pkey = vec[primarykey_p];
                vec.erase(vec.begin() + primarykey_p);
            }
            else
            {
                pkey = pkey.append(to_string(m.size()));
            }


            bool is = m.insert(pair<string, vector<string>>(pkey, vec)).second;
            if (!is)
            {
                cout << "Error：重复的主键值！" << endl;
                return;
            }
            if (primarykey_p == -1)
                tabledisplay(title, m, false, primarykey_p);
            else
                tabledisplay(title, m, true, primarykey_p);

            tablewrite(origin, m, primarykey_p);

            cout << "ok" << endl;
        }
        else
        {
            cout << "Error：字段数不匹配！" << endl;//属性值数量不对的报错
        }
    return;
}


// <summary>
// 可行的解决方案：
// 用unordered_map存储读入的数据（输出时怎么办？？顺序不对了）
// 不用unordered_map对重复主键判断失去了敏感度。
// 记录主键位置，unordered_map再通过主键位置的记录按序输出。（涉及到两个空格的问题）---文件存储中 用,隔开
// 有主键时根据主键位置确定一个数字，无主键时默认为-1
// 
// </summary>


void tabledisplay(vector<string> vec,unordered_map<string,vector<string>> m,bool flag,int pos)
{   
    unordered_map<string, vector<string>>::iterator iter=m.begin();
    int num = m.begin()->second.size();
    if (flag)
    {
        num += 1;
        flag = true;
    }
    if (num!= 0)
    {
        for(int i=0;i<num-1;++i)
            cout << "+--------------------";
        cout << "+--------------------+" << endl;

        if (flag)
        {
            cout << "|" << left << setw(20) << vec[pos] << "|";
            vec.erase(vec.begin()+pos); 
            for (int i = 0; i < vec.size(); ++i)
                cout << left << setw(20) <<vec[i] << "|";
            cout << endl;
        }
        else
        {
            cout << "|";
            for(int i=0;i<vec.size();++i)
                cout<<left << setw(20) <<vec[i]<< "|";
            cout << endl;
        }

        for (int i = 0; i < num - 1; ++i)
            cout << "+--------------------";
        cout << "+--------------------+" << endl;

        for (iter = m.begin(); iter != m.end(); iter++)
        {
            string str = iter->first;
            if (flag == false)
            {
                for (int i = 0; i < iter->second.size(); ++i)
                    cout << "|" << left << setw(20) << iter->second[i];
                cout << "|" << endl;
            }
            else
            {
                cout << "|" << left << setw(20) << str << "|";
                for (int i = 0; i < iter->second.size(); ++i)
                    cout << left << setw(20) << iter->second[i] << "|";
                cout << endl;
            }
            for (int i = 0; i < num-1; ++i)
                cout<< "+--------------------";
            cout << "+--------------------+" << endl;
        }
    }
    return;
}
 
void alter(string tablename,string func,string value)
{
    vector<string> title;
    string origin = tablename;
    unordered_map<string, vector<string>> m;
    int primarykey_p = tableread(tablename, m, title);//没有主键返回值为-1

    if (primarykey_p == -2)
    {
        cout << "Error：不存在该表！"<<endl;
        return;
    }

    int pos = -2;

    string pv;
    if (primarykey_p != -1)
        pv = title[primarykey_p];

    //如果已有该字段
    for (int i = 0; i < title.size(); ++i)
    {
        if (value == title[i])
        {
            pos = i;
            break;
        }
    }

    if (func == "ADD")
    {
        if (pos != -2)
        {
            cout << "该字段已在表中！"<<endl;
            return;
        }
        else
        {
            title.push_back(value);
            unordered_map<string, vector<string>>::iterator iter = m.begin();
            for (; iter != m.end(); ++iter)
                iter->second.push_back("");
            string originan = origin;
            tablewrite(origin, m, primarykey_p);

            tabletitle(title, originan,pv,primarykey_p);
            cout << "ok" << endl;
            return;
        }
        return;
    }
    else if (func == "DROP")
    {
        if (pos == -2)
        {
            cout << "Error!：不存在该字段！" << endl;
            return;
        }

        int temp = pos;
        title.erase(title.begin() + temp);
        string tt = origin;
        if (pos == primarykey_p)//如果删除的是主键
        {
            tablewrite(tt, m, -1);
            tabletitle(title, origin, "", -1);
            cout << "ok" << endl;
            return;
        }
        else
        {
            int i = primarykey_p;
            if (primarykey_p > pos)
                i -= 1;
            if (pos > primarykey_p&&primarykey_p!=-1)
                temp -= 1;
            unordered_map<string, vector<string>>::iterator iter = m.begin();
            for (; iter != m.end(); ++iter)
                iter->second.erase(iter->second.begin() + temp);
            tablewrite(tt, m, i);
            tabletitle(title, origin,pv,i);
            cout << "ok" << endl;
            return;
        }
    }
    return;
}

void alterex1(string tablename, string value)
{
    vector<string> title;
    string origin = tablename;
    unordered_map<string, vector<string>> m;
    int primarykey_p = tableread(tablename, m, title);//没有主键返回值为-1

    if (primarykey_p == -2)
    {
        cout << "Error：不存在该表！" << endl;
        return;
    }

    int pos = -2;
    for (int i = 0; i < title.size(); ++i)
    {
        if (value == title[i])
        {
            pos = i;
            break;
        }
    }

    if (primarykey_p!= -1)
    {
        cout << "Error：该表已存在主键" << title[primarykey_p] << "!" << endl;
        return;
    }
    else
    {
        title[pos] = value.append(" PRIMARY_KEY");
        unordered_map<string, vector<string>>::iterator iter1 = m.begin();
        bool flag = true;
        for (; iter1 != m.end(); ++iter1)
        {
            unordered_map<string, vector<string>>::iterator iter2 = m.begin();
            for (; iter2 != m.end(); ++iter2)
            {
                if (iter1 != iter2 && iter2->second[pos] == iter1->second[pos])
                {
                    flag = false;
                    break;
                }
            }
        }
        if (flag)
        {
            string originan = origin;
            tabletitle(title, originan,"", primarykey_p);
            cout << "ok" << endl;
        }
        else
        {
            cout << "Error！：该字段不能设置为主键！" << endl;
            return;
        }
        return;
    }
}

void alterex2(string tablename)
{
    vector<string> title;
    string origin = tablename;
    unordered_map<string, vector<string>> m;
    int primarykey_p = tableread(tablename, m, title);//没有主键返回值为-1

    if (primarykey_p == -2)
    {
        cout << "Error：不存在该表！" << endl;
        return;
    }

    if (primarykey_p == -1)
    {
        cout << "Error：该表不存在主键!" << endl;
        return;
    }
    else
    {
        string originan = origin;
        tabletitle(title, originan, "",-1);
        cout << "ok" << endl;
    }
    return;
}


void renametable(string tablename,string newtablename)
{
    int len = tablename.length();
    string originold = tablename;
    string originnew = newtablename;
    string o = tablename,n=newtablename;
    string oldname1=tablename.append(".txt"), newname1=newtablename.append(".txt");
    string oldname2 = o.append("1.txt"), newname2 = n.append("1.txt");
    if (!rename(oldname1.c_str(), newname1.c_str()))
    {
        rename(oldname2.c_str(), newname2.c_str());
        ifstream file2("tablelist.txt");
        if (file2)
        {
            string temp;
            vector<string> vec;
            while (getline(file2, temp))
            {
                vec.push_back(temp);
            }
            file2.close();

            ofstream file3("tablelist.txt");
            if (file3)
            {
                for (int i = 0; i < vec.size(); ++i)
                {
                    if (vec[i].find(originold)==0)
                    {
                        string hh = vec[i].substr(len);
                        hh = originnew + hh;
                        file3 << hh << endl;
                    }
                    else
                         file3 << vec[i] << endl;
                }
            }
            file3.close();

        }
        cout << "rename successfully!" << std::endl;
        return;
    }
    else
    {
        cout << "rename error!" << std::endl;
        return;
    }
    return;
}

void tabletitle(vector<string> title,string origin,string pv,int primarykey_p)//修改tablelist,table1
{
    string oo = origin;
    ofstream file1(origin.append("1.txt"));
    if (file1)
    {
        for (int i = 0; i < title.size(); ++i)
        {
            if (primarykey_p != -1 && title[i] == pv)
            {
                if (i != title.size() - 1)
                    file1 << pv.append(" PRIMARY_KEY") << ",";
                else if (i == title.size() - 1)
                    file1 << pv.append(" PRIMARY_KEY") << endl;
            }
            else
            {
                if (i != title.size() - 1)
                    file1 <<title[i] << ",";
                else if (i == title.size() - 1)
                    file1 <<title[i] << endl;
            }
        }
    }
    file1.close();

    ifstream file2("tablelist.txt");
    if (file2)
    {
        string temp;
        vector<string> vec;
        while (getline(file2, temp))
        {
            if (temp.find(oo)== string::npos)
                vec.push_back(temp);
        }
        string newstr=oo.append("(");
        for (int i = 0; i < title.size(); ++i)
        {
            if (primarykey_p != -1 && title[i] == pv)
            {
                if (i != title.size() - 1)
                {
                    newstr.append(title[i]);
                    newstr.append(",");
                }
                else if (i == title.size() - 1)
                {
                    newstr.append(title[i]);
                    newstr.append(")\n");
                }
            }
            else
            {
                if (i != title.size() - 1)
                {
                    newstr.append(title[i]);
                    newstr.append(",");
                }
                else if (i == title.size() - 1)
                {
                    newstr.append(title[i]);
                    newstr.append(")");
                }
            }
        }
        vec.push_back(newstr);
        file2.close();

        ofstream file3("tablelist.txt");
        if (file3)
        {
            for (int i = 0; i < vec.size(); ++i)
                file3 << vec[i] << endl;
        }
        file3.close();
        
    }
    return;
}