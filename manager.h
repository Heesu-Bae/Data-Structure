#pragma once
#include <iostream>
#include <string>
using namespace std;

class manager
{
private:
	const string m_ID;
	const string m_PW;
public:
	manager();

	string getID() { return m_ID; }
	string getPW() { return m_PW; }
};