#pragma once
#include <string>
#include <iostream>
#include <iomanip>
using namespace std;

class Student // 학생 정보를 담을 클래스
{
private:
	string ID; // 학생 ID
	string PW; // 학생 PW
	int stamp_num; // 쿠폰의 스탬프 개수

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