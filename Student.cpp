#include "Student.h"

Student::Student()
{
	ID = "0";
	PW = "0";
}

Student::Student(string id, string pw)
{
	ID = id;
	PW = pw;
	stamp_num = 0;
}

Student::Student(string id, string pw, int stampNum)
{
	ID = id;
	PW = pw;
	stamp_num = stampNum;
}

bool Student::operator<(Student& another)
{
	return (ID.compare(another.getID()) < 0);
}

bool Student::operator>(Student& another)
{
	return (ID.compare(another.getID()) > 0);
}

bool Student::operator==(Student& another)
{
	return (ID.compare(another.getID()) < 0 == 0);
}

string Student::getID() const
{
	return ID;
}

string Student::getPW() const
{
	return PW;
}

int Student::getNum() const
{
	return stamp_num;
}

void Student::Print() const
{
	cout << setw(20) << setfill(' ') << ID << setw(20) << setfill(' ') << PW << setw(20) << setfill(' ') << stamp_num << endl;
}