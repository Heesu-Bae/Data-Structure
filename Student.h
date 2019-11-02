#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Student // �л� ������ ���� Ŭ����
{
private:
	string ID; // �л� ID
	string PW; // �л� PW
	int stamp_num; // ������ ������ ����

public:
	Student();
	Student(string id, string pw);
	Student(string id, string pw, int stampNum);

	bool operator<(Student& another);
	bool operator>(Student& another);
	bool operator==(Student& another);

	string getID() const;
	string getPW() const;
	int getNum() const;

	void Print() const;
};