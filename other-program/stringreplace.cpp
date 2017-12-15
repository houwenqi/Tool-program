#include <iostream>
#include <string>

using namespace std;

int main()
{
	string a = "123%40qq.com";/////指定串，可根据要求替换
	string b = "%40";////要查找的串，可根据要求替换
	string c = "@";

	int pos;
	pos = a.find(b);////查找指定的串

	while (pos != -1)
	{
		a.replace(pos,b.length(),c);////用新的串替换掉指定的串
		pos = a.find(b);//////继续查找指定的串，直到所有的都找到为止
	}

	cout << a << endl;

	return 0;
} 