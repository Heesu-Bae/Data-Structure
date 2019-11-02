#include "Event.h"

Event::Event()
{
	count = 0;
}

Event::Event(string str1, string str2, int n)
{
	name = str1;
	contents = str2;
	count = n;
}

void Event::setName(string str)
{
	name = str;
}

void Event::setContents(string str)
{
	contents = str;
}

string Event::getName()
{
	return name;
}

string Event::getContents()
{
	return contents;
}

int Event::getCount()
{
	return count;
}

bool Event::IsFull()
{
	return (count == MAX_COUNT);
}

void Event::Print() const
{
	cout << "���� �̺�Ʈ <" << name << ">�� ������ ���� " << count << "�� �Դϴ�." << endl;
}