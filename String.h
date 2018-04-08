#include<iostream>
#include<string.h>
using namespace std;

class String {
public:
	String(const char* str);
	String(const String& s);
	~String();
	String& operator=(const String& s);
	void Swap(const String& s);
	void Expand(size_t n);
	void PushBack(const char ch);
	void PushBack(const char* str);
	void Insert(size_t pos, char ch);
	void Insert(size_t pos, const char* str);
	void Erase(size_t pos, size_t n );
	size_t Find(char ch);
	size_t Find(const char* str);
	void operator+(const char ch);
	void operator+(const char* str);
	bool operator>(const String& s);
	bool operator<(const String& s);
	bool operator>=(const String& s);
	bool operator<=(const String& s);
	const char* c_str()
	{
		cout << "size:" << _size << " capacity:" << _capacity << endl;
		return _str;
	}
private:
	char* _str;
	size_t _size;
	size_t _capacity;
};
void String::Expand(size_t n)
{
	if (n > _capacity)
	{
		char* tmp = new char[n + 1];
		strcpy(tmp, _str);
		delete[] _str;
		_str = tmp;
		_capacity = n;
	}
}

void String::Swap(const String& s)
{
	String tmp(s._str);
	swap(_str, tmp._str);
	swap(_size, tmp._size);
	swap(_capacity, tmp._capacity);
}

String::String(const char* str = "")
{
	_size = _capacity = strlen(str);
	_str = new char[_capacity + 1];
	strcpy(_str, str);
}

String::String(const String& s)
{
	//String newstr(s._str);
	Swap(s);
}

String::~String()
{
	_size = _capacity = 0;
	delete[] _str;
}

String& String::operator=(const String& s)
{
	if (s._str != _str)
		Swap(s);
	return *this;
}

void String::PushBack(const char ch = '\0')
{
	if (_size >= _capacity)
		Expand(_capacity*2);
	_str[_size++] = ch;
	_str[_size] = '\0';
}

void String::PushBack(const char* str = "")
{
	if (_size + strlen(str) >= _capacity )
	{
		Expand((_capacity + strlen(str))*2);
	}
	strcpy(_str + _size, str);
	_size += strlen(str);
}

void String::operator+(const char ch)
{
	PushBack(ch);
}

void String::operator+(const char* str)
{
	PushBack(str);
}

bool String::operator>(const String& s)
{
	if (strcmp(_str, s._str) == 0)
		return false;
	else if (strcmp(_str, s._str) < 0)
		return false;
	else
		return true;
}

bool String::operator<(const String& s)
{
	if (strcmp(_str, s._str) == 0)
		return false;
	else if (strcmp(_str, s._str) > 0)
		return false;
	else
		return true;
}

bool String::operator>=(const String& s)
{
	return !(_str < s._str);
}

bool String::operator<=(const String& s)
{
	return !(_str > s._str);
}

void String::Insert(size_t pos, char ch)
{
	if (_size >= _capacity)
		Expand(_capacity * 2);
	for (int i = _size; i >=(int)pos; i--)//切记强转为int，否则死循环
	{
		_str[i + 1] = _str[i];
	}
	_str[pos] = ch;
	_str[++_size] = '\0';
}

void String::Insert(size_t pos, const char* str)
{
	if (_size + strlen(str) >= _capacity)
		Expand(_capacity + _size + strlen(str));
	size_t size = _size;
	size_t len = strlen(str);
	while (pos != size)
	{
		_str[size + strlen(str)] = _str[size];
		size--;
	}
	_str[size + strlen(str)] = _str[size];
	while (*str)					
		_str[size++] = *str++;
	_size +=len;
}

void String::Erase(size_t pos, size_t n )
{
	size_t size = pos;
	while (_str[size + n])//将pos后的位置每次向前移动n个位置
	{
		_str[size] = _str[size + n];
		size++;
	}
	_str[size] = '\0';//元素已经移动到适当位置，将后面的元素置为0，同时size--，达到删除目的
	_size -= n;
}

size_t String::Find(char ch)
{
	int count = 0;
	for (int i = 0; i <= _size; i++)
	{
		if (_str[i] == ch)
			count++;
	}
	return count;
}

size_t String::Find(const char* str)
{
	int count = 0;
	for (int i = 0; i <= _size; i++)
	{
		const char* cur = str;
		int j = i;//找到相同的字符时，开始遍历字符串查询，查询完毕后，下标置为开始，为下次做准备
		while (*cur)
		{
			if (_str[j] == *cur)
			{
				cur++;
				j++;
			}
			else
				break;
		}
		if (*cur == '\0')
			count++;
	}
	return count;
}


void Test()
{
	String s1("Hello");
	cout << "s1: " << s1.c_str() << endl; 
	String s2(s1);
	cout << "s2: " << s2.c_str() << endl;
	String s3("word");
	cout << "s3: " << s3.c_str() << endl;
	s2 = s3;
	cout << "s2: " << s2.c_str() << endl;
	s3.PushBack('!');
	cout << s3.c_str() << endl;
	s1.PushBack(" word");
	cout << s1.c_str() << endl;
	s1.PushBack(" Y!");
	cout << s1.c_str() << endl;
	String s4(s2);
	s2 + '!';
	cout << "s2: " << s2.c_str() << endl;
	String s5("Hello");
	cout << "s5: " << s5.c_str() << endl;
	s5 + " word";
	cout << "s5: " << s5.c_str() << endl;
	String s6("Hello");
	cout << "s6: " << s6.c_str() << endl;
	s6.Insert(0, '%');
	cout << "s6: " << s6.c_str() << endl;
	String s7("11223344");
	cout << "s7: " << s7.c_str() << endl;
	s7.Insert(3, "aaabbaacc");
	cout << "s7: " << s7.c_str()<<endl;
	s7.Erase(0,3);
	cout << "s7: " << s7.c_str() << endl;
	cout << "查找统计某一个字母a出现的次数>" << s7.Find('a') << endl;
	cout << "查找字符串“aa”出现次数" << s7.Find("aa") << endl;
}
