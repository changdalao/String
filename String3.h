#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class String {
private:
	char* _str;
public:
	int& GetRefCount()//获取前四个字节的数字
	{
		return (*((int*)(_str - 4)));
	}
	String(const char* str = "")
		:_str(new char[strlen(str) + 5])
	{
		_str += 4;//从地址开始的后四个字节开始操作字符串，前四个字节预留为引用计数
		strcpy(_str, str);
		GetRefCount() = 1;
	}
	String(const String& s)
		:_str(s._str)
	{
		++GetRefCount();
	}
	~String()
	{
		if (GetRefCount() == 0)
		{
			delete[] _str;
		}
	}
	const char* c_str()
	{
		return _str;
	}
	String& operator=(const String& s);
	void CopyOnWrite();
	char& operator[](size_t pos);
};
void String::CopyOnWrite()
{
	if (GetRefCount() > 1)
	{
		char* newstr = new char[strlen(_str) + 5];
		--GetRefCount();
		strcpy(newstr + 4, _str);
		_str = newstr + 4;
		GetRefCount() = 1;
	}
}
char& String::operator[](size_t pos)
{
	CopyOnWrite();
	return _str[pos];
}
String& String::operator=(const String& s)
{
	if (_str != s._str)
	{
		--GetRefCount();
		if (GetRefCount() == 0)
		{
			delete[] (_str-4);
		}
		_str = s._str;
		GetRefCount()++;
	}
	return *this;
}
void Test3()
{
	String s1("hello word");
	cout << s1.c_str() << endl;
	String s2(s1);
	String s3("change word");
	s3 = s1;
	cout << s3.c_str() << endl;
	s1[3] = 'x';
	cout << s1.c_str() << endl;
}
