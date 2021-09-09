#pragma once
#include<string>
#include<vector>
#include<map>
#include<unordered_map>
using namespace std;

int splitStringToVect(const string& srcStr, vector<string>& destVect, const string& strFlag);

void tablewrite(string& filename, unordered_map<string, vector<string>> m, int n);

int tableread(string& filename, unordered_map<string, vector<string>>& m,vector<string>& vec);

void tablecreate(string str,string value);

int showtables();

void insert(string tablename, string value);

void droptable(string tablename);

void tabledisplay(vector<string> vec,unordered_map<string, vector<string>> m,bool flag,int pos);

