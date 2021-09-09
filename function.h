#pragma once
#include<string>
#include<vector>
using namespace std;

bool deletefunc(vector<string> title, unordered_map<string, vector<string>>& m, int primary_p, string constrain, string a11, string a12, string a21, string a22,string equal1, string equal2);

void deletetable(string tablename, string constrain, string a11, string a12, string a21, string a22,string equal1,string equal2);

void selecttable(bool distinct, string value, string tablename, string constrain,string a11, string a12, string a21, string a22,string equal1,string equal2);

void updatetable(string tablename, string a0, string b0, string constrain, string a11, string a12, string a21, string a22,string equal1,string equal2);

void alter(string tablename, string func, string value);

void alterex1(string tablename,string value);

void alterex2(string tablename);

void renametable(string tablename, string newtablename);
