#include "DVD.h"

DVD::DVD()
{
	name = "";
	genre = "";
	rent = false;
}

DVD::DVD(string str1, string str2)
{
	setDVD(str1, str2);
	rent = false;
}

void DVD::setDVD(string str1, string str2)
{
	name = str1;
	genre = str2;
}

void DVD::Rent()
{
	rent = true;
}

void DVD::Return()
{
	rent = false;
}

bool DVD::IsRented()
{
	return rent;
}

void DVD::Print()
{
	cout << "<제목> " << setw(25) << setfill(' ') << name << "              <장르> " << setw(13) << setfill(' ')  << genre;
	
	if (!rent)
	{
		cout << "             <대여 상황> 대여 가능" << endl;
	}
	else
		cout << "             <대여 상황> 대여 불가능" << endl;
}


bool DVD::operator<(DVD& dvd)
{
	if (name.compare(dvd.getName()) < 0)
		return true;
	else
		return false;
}

bool DVD::operator>(DVD& dvd)
{
	if (name.compare(dvd.getName()) > 0)
		return true;
	else
		return false;
}

bool DVD::operator==(DVD& dvd)
{
	if (name.compare(dvd.getName()) == 0)
		return true;
	else
		return false;
}
