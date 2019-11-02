#pragma once
#include <iostream>
#include <string>
using namespace std;

#define MAX_COUNT 10

class Event
{
private:
	string name;
	string contents;
	int count;

public:
	Event();
	Event(string str1, string str2,  int n = 0);

	void setName(string str);
	void setContents(string str);
	string getName();
	string getContents();
	int getCount();
	bool IsFull();

	void Print() const;
};