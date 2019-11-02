#pragma once
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class DVD
{
private:
	string name;
	string genre;
	bool rent;
public:
	DVD();
	DVD(string str1, string str2);

	void setDVD(string str1, string str2 = "");
	bool IsRented();
	void Print();
	void Rent();
	void Return();

	bool operator<(DVD& dvd);
	bool operator>(DVD& dvd);
	bool operator==(DVD& dvd);
	
	string getName() { return name; }
	string getGenre() { return genre; }
};