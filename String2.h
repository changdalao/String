#include<iostream>
#include<string.h>
#include<assert.h>
using namespace std;

class String {
private:
	char* _str;
	int* _pcount;
public:
	String(const char* str = "")
		:_str(new char[strlen(str) + 1])
		, _pcount(new int(1))
	{
		strcpy(_str, str);
	}
	String(const String& s)//拷贝构造一次，加计数
		:_str(s._str)
		,_pcount(s._pcount)
	{
		(*_pcount)++;
	}
	~String()
	{
		if (--(*_pcount) == 0)
		{
			delete _pcount;
			delete[] _str;
		}
	}
	void CopyOnWrite()//当对象需要修改内容时，因为多个对象指向一个空间，为了不影响他人，拷贝，即谁写谁拷贝，同时原来的计数减1，新拷贝的赋初值1
	{
		if ((*_pcount > 1))
		{
			char* newstr = new char[strlen(_str) + 1];
			--(*_pcount);
			strcpy(newstr, _str);
			_str = newstr;
			_pcount = new int(1);
		}
	}
	String& operator=(const String& s);
	char& operator[](size_t pos);
	const char* c_str()
	{
		return _str;
	}
};
String& String::operator=(const String& s)
{
	if (_str != s._str)//判断自己给自己赋值
	{
		--(*_pcount);
		if ((*_pcount) == 0) //如果计数减到0，直接释放
		{
			delete _pcount;
			delete[] _str;
		}
		_str = s._str;
		_pcount = s._pcount;
		++(*_pcount);
	}
	return *this;
}
char& String::operator[](size_t pos)
{
	CopyOnWrite();
	return _str[pos];
}
void Test1()
{
	String s1("hello word");
	cout << s1.c_str() << endl;
	String s2(s1);
	cout << s2.c_str() << endl;
	String s3("change word");
	s3 = s1;
	s1[3] = 'x';
	cout << s1.c_str() << endl;
	cout << s2.c_str() << endl;
	cout << s3.c_str() << endl;
}
