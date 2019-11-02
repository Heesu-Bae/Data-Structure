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
	cout << "<����> " << setw(25) << setfill(' ') << name << "              <�帣> " << setw(13) << setfill(' ')  << genre;
	
	if (!rent)
	{
		cout << "             <�뿩 ��Ȳ> �뿩 ����" << endl;
	}
	else
		cout << "             <�뿩 ��Ȳ> �뿩 �Ұ���" << endl;
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
