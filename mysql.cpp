#include<iostream>
#include<regex>
#include<string>
#include<vector>
#include"tablecreate.hpp"
#include<stdio.h>
#include<stdlib.h>
#include"function.h"

using namespace std;
int main()
{
	while (true)
	{
		int n=0;
		string str;
		smatch result;
		cout << "mysql>";
	
		getline(cin, str);

		regex regtablecreate("CREATE TABLE ([\u4e00-\u9fa5a-zA-Z0-9_]+) \\(([\u4e00-\u9fa5A-Za-z0-9_\\s,]*)\\);");
		regex regtableinsert("INSERT INTO ([\u4e00-\u9fa5a-zA-Z0-9_]+) VALUES \\(([\u4e00-\u9fa5A-Za-z0-9_\\s,]*)\\);");

		regex regDelete("DELETE FROM ([\u4e00-\u9fa5A-Za-z0-9_]+)( WHERE ([\u4E00-\u9FA5A-Za-z0-9_]+)(=|<>)([\u4E00-\u9FA5A-Za-z0-9_]+)( (AND|OR) ([\u4E00-\u9FA5A-Za-z0-9_]+)(=|<>)([\u4E00-\u9FA5A-Za-z0-9_]+))?)?;");
		regex regupdate("UPDATE ([\u4e00-\u9fa5A-Za-z0-9_]+) SET ([\u4E00-\u9FA5A-Za-z0-9_]+)=([\u4E00-\u9FA5A-Za-z0-9_]+)( WHERE ([\u4E00-\u9FA5A-Za-z0-9_]+)(=|<>)([\u4E00-\u9FA5A-Za-z0-9_]+)( (AND|OR) ([\u4E00-\u9FA5A-Za-z0-9_]+)(=|<>)([\u4E00-\u9FA5A-Za-z0-9_]+))?)?;");
		regex regselect("SELECT( DISTINCT)? ([\u4e00-\u9fa5A-Za-z0-9_\\s,\\*]*) FROM ([\u4e00-\u9fa5a-zA-Z0-9_]+)( WHERE ([\u4E00-\u9FA5A-Za-z0-9_]+)(=|<>)([\u4E00-\u9FA5A-Za-z0-9_]+)( (AND|OR) ([\u4E00-\u9FA5A-Za-z0-9_]+)(=|<>)([\u4E00-\u9FA5A-Za-z0-9_]+))?)?;");

		regex regalter("ALTER TABLE ([\u4e00-\u9fa5a-zA-Z0-9_]+) (ADD|DROP) ([\u4e00-\u9fa5a-zA-Z0-9_]+);");
		regex regalterextension1("ALTER TABLE ([\u4e00-\u9fa5a-zA-Z0-9_]+) ADD PRIMARY_KEY \\(([\u4e00-\u9fa5a-zA-Z0-9_]+)\\);");
		regex regalterextension2("ALTER TABLE ([\u4e00-\u9fa5a-zA-Z0-9_]+) DROP PRIMARY_KEY;");

		regex regshowtable("SHOW TABLES;");
		regex regdroptable("DROP TABLE ([\u4e00-\u9fa5_a-zA-Z0-9_]+);");
		regex regrename("RENAME TABLE ([\u4e00-\u9fa5a-zA-Z0-9_]+) TO ([\u4e00-\u9fa5a-zA-Z0-9_]+);");

		if (regex_match(str, regtablecreate))
		{
			n = 1;
			regex_search(str, result, regtablecreate);
		}
		else if (regex_match(str, regshowtable))
		{
			n = 2;
		}
		else if (regex_match(str, regtableinsert))
		{
			n = 3;
			regex_search(str, result, regtableinsert);
		}
		else if (regex_match(str, regdroptable))
		{
			n = 4;
			regex_search(str, result, regdroptable);
		}
		else if (regex_match(str, regDelete))
		{
			n = 5;
			regex_search(str, result, regDelete);
		}
		else if (regex_match(str, regupdate))
		{
			n = 6;
			regex_search(str, result, regupdate);
		}
		else if (regex_match(str, regselect))
		{
			n = 7;
			regex_search(str, result, regselect);
		}
		else if (regex_match(str, regalterextension2))
		{
			n = 10;
			regex_search(str, result, regalterextension2);
		}
		else if (regex_match(str, regalter))
		{
			n = 8;
			regex_search(str, result, regalter);
		}
		else if (regex_match(str, regalterextension1))
		{
			n = 9;
			regex_search(str, result, regalterextension1);
		}
		else if (regex_match(str, regrename))
		{
			n = 11;
			regex_search(str, result, regrename);
		}
		else
		{
			cout << "Illegal Input!" << endl;
			continue;
		}

		switch (n)
		{
		case(1):
		{
			tablecreate(result.str(1), result.str(2));
			break;
		}
		case(2):
		{
			showtables();
			break;
		}
		case(3):
		{
			insert(result.str(1), result.str(2));
			break;
		}
		case(4):
		{
			droptable(result.str(1));
			break;
		}
		case(5):
		{
			deletetable(result.str(1), result.str(7), result.str(3), result.str(5), result.str(8), result.str(10),result.str(4),result.str(9));
			break;
		}
		case(6):
		{
			updatetable(result.str(1), result.str(2), result.str(3), result.str(9), result.str(5), result.str(7), result.str(10), result.str(12),result.str(6),result.str(11));
			break;
		}
		case(7):
		{
			string a0, b0, a11, a12, a21, a22;
			if (result.str(1) == "")
				selecttable(false, result.str(2), result.str(3), result.str(9), result.str(5), result.str(7), result.str(10), result.str(12),result.str(6),result.str(11));
			else
				selecttable(true, result.str(2), result.str(3), result.str(9), result.str(5), result.str(7), result.str(10), result.str(12), result.str(6), result.str(11));
			break;
		}
		case(8):
		{
			alter(result.str(1), result.str(2), result.str(3));
			break;
		}
		case(9):
		{
			alterex1(result.str(1),result.str(2));
			break;
		}
		case(10):
		{
			alterex2(result.str(1));
			break;
		}
		case(11):
		{
			renametable(result.str(1), result.str(2));
			break;
		}
		default:
			break;
		}
	}
	return 0;
}