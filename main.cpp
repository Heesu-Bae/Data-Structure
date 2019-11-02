#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>
#include <sstream>
#include "manager.h"
#include "sorted.h"
#include "Student.h"
#include "QueType.h"
#include "Event.h"
#include "TreeType.h"
using namespace std;

void readMember(); // member ���Ϸ� ���� ���� Data�� member ����Ʈ�� ����
void readEvent(); //eventData ���Ϸκ��� �̺�Ʈ ������ �޾Ƽ� event ť�� ����
void readDVD(); //dvdData ���Ϸκ��� DVD ������ �޾Ƽ� DVD Ʈ���� ����
void mainMenu(); // ���� �޴� ���
void printErrorMessage(); // �߸��� ��ɾ� �Է½� ���� �޼��� ���
void managerMenu(); // ������ �޴� ���
void memberMenu(string& ID); // ȸ�� �޴� ���
void nonMemberMenu(); // ��ȸ�� �޴� ���
void managerFunction(); // ������ ��� �Լ�
void register_Member(); // ȸ������ �Լ�
void searchDVD(); // DVD �˻� �Լ�
void searchMember(string& ID, int& count); // ȸ�� �˻� �Լ�
void login(); // ȸ�� �α��� �Լ�
void couponMenu(string& ID); // ���� ���� ��� �޴�
void eventMenu(); // �̺�Ʈ ���� �޴�
void AddEvent(); // �̺�Ʈ �߰� �Լ�
void PrintEvent(); // ���� �̺�Ʈ ��� �Լ�
void PrintTodayEvent(); // ������ �̺�Ʈ ���

manager khu; // ������ ��ü khu ����
SortedType<Student> member; // ��� ����Ʈ ����
QueType<Event> event; // �̺�Ʈ ť ����
TreeType tree; // DVD Ʈ�� ����

int main()
{
	readMember();
	readEvent();
	readDVD();

	int user; // ����ڷκ��� ������ ����� �޾� ����

	while (1)
	{
		PrintTodayEvent();
		mainMenu();	
		cin >> user;

		switch (user)
		{
		case 1:
			managerMenu();
			break;
		case 2:
			login();
			break;
		case 3:
			nonMemberMenu();
			break;
		case 0:
			return 0;
		default:
			printErrorMessage();
			break;
		}
	}

	return 0;
}

void readMember()
{
	ifstream fin;
	fin.open("member.txt"); // member ���� open

	if (!fin)
	{
		cerr << "���� ���¿� �����Ͽ����ϴ�. �����ڿ��� ���ǹٶ��ϴ�." << endl;
		exit(100);
	}
	
	stringstream ss; // �о���� ������ ������ ������ �����ϱ� ���� string stream
	string line; // ���پ� �о���� ����
	string ID, PW;
	int stamp_num;

	while(getline(fin, line))
	{
		ss << line;
		ss >> ID >> PW >> stamp_num;
		ss.clear();
		member.InsertItem(Student(ID, PW, stamp_num));
	}

	fin.close();
}

void readEvent()
{
	ifstream fin;
	fin.open("eventData.txt"); // eventData ���� open

	if (!fin)
	{
		cerr << "���� ���¿� �����Ͽ����ϴ�. �����ڿ��� ���ǹٶ��ϴ�." << endl;
		exit(100);
	}

	stringstream ss; // �о���� ������ ������ ������ �����ϱ� ���� string stream
	string line; // ���پ� �о���� ����
	string name, contents;
	int count;

	while (getline(fin, line))
	{
		ss << line;
		getline(ss, name, '\t');
		getline(ss, contents, '\t');
		ss >> count;
		
		ss.clear();
		event.Enqueue(Event(name, contents, count));
	}

	fin.close();
}

void readDVD()
{
	ifstream fin;
	fin.open("dvdData.txt"); // dvdData ���� open

	if (!fin)
	{
		cerr << "���� ���¿� �����Ͽ����ϴ�. �����ڿ��� ���ǹٶ��ϴ�." << endl;
		exit(100);
	}

	stringstream ss; // �о���� ������ ������ ������ �����ϱ� ���� string stream
	string line; // ���پ� �о���� ����
	string name, genre;
	int count;

	while (getline(fin, line))
	{
		ss << line;
		getline(ss, name, '\t');
		getline(ss, genre, '\t');

		ss.clear();
		tree.InsertItem(DVD(name, genre));

	}

	fin.close();
}

void mainMenu()
{
	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+-------------------------------------------------+" << endl;
	cout << "|  <����� ������ �����ϼ���>                     |" << endl;
	cout << "|  1. ������                                      |" << endl;
	cout << "|  2. ȸ��                                        |" << endl;
	cout << "|  3. ��ȸ��                                      |" << endl;
	cout << "|  0. ����                                        |" << endl;
	cout << "+-------------------------------------------------+" << endl;
	cout << "-> ";
}

void printErrorMessage()
{
	cout << "�߸��� ��ɾ �Է��ϼ̽��ϴ�. ó������ ���ư��ϴ�." << endl << endl << endl;
}

void managerMenu()
{
	system("cls");

	string ID; // ID�� �Է¹��� ����
	string PW; // ��й�ȣ�� �Է¹��� ����
	int count = 0; // �Է� Ƚ���� ī��Ʈ �� ����
	bool complete = false; // �α��� ���� ���θ� Ȯ���� ����

	while (count < 5)
	{
		cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
		cout << "+-------------------------------------------------------------------+" << endl;
		cout << "|  <������>                                                         |" << endl;
		cout << "| * ID �Ǵ� PW �Է��� 5ȸ �̻� �߸��� ��� ó������ ���ư��ϴ�.     |" << endl;
		cout << "| * ���� ȭ������ ���ư����� ID�� 0�� �Է��ϼ���.                   |" << endl;
		cout << "+-------------------------------------------------------------------+" << endl;
		cout << "ID�� PW�� �Է����ּ���" << endl;
		cout << "ID : ";
		cin >> ID;

		if (ID == "0")
			break;

		cout << "PW : ";
		cin >> PW;

		if (ID == khu.getID() && PW == khu.getPW())
		{
			complete = true;
			break;
		}
		else
		{
			system("cls");
			cout << ++count << "ȸ �߸� �Է��ϼ̽��ϴ�." << endl << endl;
		}
	}

	if (complete)
		managerFunction();
}

void memberMenu(string& ID)
{
	system("cls");
	int user;

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <ȸ��>                                                  |" << endl;
	cout << "| * �Ʒ� ��� �� ���ϴ� ����� �������ּ���.              |" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "�����Ͻ� ����� �Է����ּ���" << endl;
	cout << "1. DVD �˻�" << endl;
	cout << "2. DVD �ݳ�" << endl;
	cout << "3. ���� ���� ��ȸ" << endl;
	cout << "0. �ʱ�ȭ��" << endl;
	cout << "-> ";
	cin >> user;

	switch (user)
	{
	case 1:
		searchDVD();
		break;
	case 2:

	case 3:
		couponMenu(ID);
		break;
	case 0:
		system("cls");
		break;
	default:
		printErrorMessage();
		break;
	}
}

void nonMemberMenu()
{
	system("cls");
	int user;

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <��ȸ��>                                                |" << endl;
	cout << "| * ȸ������ �Ǵ� �ڷΰ��� �� ���ϴ� ����� �����ϼ���    |" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "�����Ͻ� ����� �Է����ּ���" << endl;
	cout << "1. ȸ������" << endl;
	cout << "0. �ڷΰ���" << endl;
	cout << "-> ";
	cin >> user;

	switch (user)
	{
	case 1:
		register_Member();
		break;
	case 0:
		system("cls");
		break;
	default:
		printErrorMessage();
		break;
	}
}

void register_Member()
{
	system("cls");

	ofstream fout("member.txt", ios::app);
	if (!fout)
	{
		cerr << "���� ���¿� �����Ͽ����ϴ�. �����ڿ��� ���ǹٶ��ϴ�." << endl;
		exit(100);
	}

	string user_ID;
	string user_PW;
	bool found = false;

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <ȸ������>                                              |" << endl;
	cout << "| * ID�� �ڽ��� �й��� �Է����ּ���.                      |" << endl;
	cout << "| * PW�� ����, ���ڸ� ȥ���Ͽ� �Է����ּ���.              |" << endl;
	cout << "+---------------------------------------------------------+" << endl;

	cout << "ID�� �Է��ϼ��� : ";
	cin >> user_ID;

	member.RetrieveItem(user_ID, found);
	if (found)
	{
		cout << "�̹� �����ϴ� ID�Դϴ�. �����ڿ��� �������ּ���" << endl;
		fout.close();
		return;
	}

	cout << "PW�� �Է��ϼ��� : ";
	cin >> user_PW;

	fout << user_ID << "\t" << user_PW << "\t" << 0 << endl;
	member.InsertItem(Student(user_ID, user_PW));
	cout << "ȸ�����Կ� �����Ͽ����ϴ�!!" << endl << endl;

	fout.close();
}

void managerFunction()
{
	system("cls");

	int user; // ����� ��ɾ� �Է� ����

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <������>                                                         |" << endl;
	cout << "| * ���ϴ� ����� �������ּ���.                                     |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "�����Ͻ� ����� �Է����ּ���" << endl;
	cout << "1. ȸ�� ���" << endl;
	cout << "2. �̺�Ʈ ����" << endl;
	cout << "0. �ʱ�ȭ��" << endl;
	cout << "-> ";
	cin >> user;

	switch (user)
	{
	case 1:
		member.Print();
		break;
	case 2:
		eventMenu();
		break;
	case 0:
		break;
	default:
		printErrorMessage();
		break;
	}
}

void eventMenu()
{
	system("cls");

	int user; // ����� ��ɾ� �Է� ����

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <�̺�Ʈ ����>                                                    |" << endl;
	cout << "| * ���ϴ� ����� �������ּ���.                                     |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "�����Ͻ� ����� �Է����ּ���" << endl;
	cout << "1. �̺�Ʈ �߰�" << endl;
	cout << "2. �̺�Ʈ ���" << endl;
	cout << "0. �ʱ�ȭ��" << endl;
	cout << "-> ";
	cin >> user;

	switch (user)
	{
	case 1:
		AddEvent();
		break;
	case 2:
		PrintEvent();
		break;
	case 0:
		system("cls");
		break;
	default:
		printErrorMessage();
		break;
	}
}

void login()
{
	system("cls");

	string user_ID;
	string user_PW;
	bool complete = false;
	Student temp;
	int count = 0;

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <�α���>                                                |" << endl;
	cout << "| * ID�� PW�� �Է����ּ���.                               |" << endl;
	cout << "+---------------------------------------------------------+" << endl;

	while (count < 3)
	{
		cout << "ID�� �Է��ϼ��� : ";
		cin >> user_ID;
		cout << "PW�� �Է��ϼ��� : ";
		cin >> user_PW;

		member.ResetList();

		for (int i = 0; i < member.getLen(); i++)
		{
			member.GetNextItem(temp);

			if (user_ID == temp.getID() && user_PW == temp.getPW())
			{
				complete = true;
				break;
			}
		}

		if (complete)
			break;
		else
		{
			cout << "��ġ�ϴ� ȸ�� ������ �������� �ʽ��ϴ�." << 3 - (++count) << "ȸ ���ҽ��ϴ�." << endl << endl;
		}
	}

	if (count == 3)
		return;
	else
		memberMenu(user_ID);
}

void searchDVD()
{
	system("cls");

	string user; // ����ڿ��� �Է� ���� ������ ���� ����
	bool found; // �˻� ���� ����
	DVD temp;

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <DVD �˻�>                                                       |" << endl;
	cout << "| * ã���� �ϴ� DVD�� ������ �Է����ּ���                           |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "-> ";
	cin.ignore();
	getline(cin, user);

	temp.setDVD(user);

	tree.RetrieveItem(temp, found);

	if (!found)
	{
		system("cls");
		cout << "ã���� �ϴ� DVD�� �������� �ʽ��ϴ�." << endl << endl;
	}
	else
	{
		temp.Print();
		cout << endl;

		if (!temp.IsRented())
		{
			int command;

			cout << "�� DVD�� �뿩�Ͻðڽ��ϱ�?( Yes : 1, No : 0)" << endl;
			cout << "->";
			cin >> command;

			switch (command)
			{
			case 1:
				temp.Rent();
			case 0:
				break;
			default:
				printErrorMessage();
				break;
			}
		}
	}
}

void searchMember(string& ID, int& count)
{
	Student temp;

	member.ResetList();

	for (int i = 0; i < member.getLen(); i++)
	{
		member.GetNextItem(temp);

		if (temp.getID() == ID)
		{
			count = temp.getNum();
			break;
		}
	}
}

void couponMenu(string& ID)
{
	system("cls");
	int user;
	int count;

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <���� ���� ��ȸ>                                        |" << endl;
	cout << "| * ���� ������ DVD 1ȸ �뿩���� �����մϴ�.              |" << endl;
	cout << "| * ������ �̺�Ʈ ������ ���� �� �ֽ��ϴ�.              |" << endl;
	cout << "+---------------------------------------------------------+" << endl;

	searchMember(ID, count);
	cout << "ȸ������ ���� ���� ������ " << count << "�� �Դϴ�." << endl << endl;
}

void AddEvent()
{
	system("cls");

	string name, contents; // ����� �Է� ����
	ofstream fout("eventData.txt", ios::app);
	if (!fout)
	{
		cerr << "���� ���¿� �����Ͽ����ϴ�. �����ڿ��� ���ǹٶ��ϴ�." << endl;
		exit(100);
	}

	cout << "### ������б� �߾ӵ����� �����ڷ�� �뿩�ý��� ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <�̺�Ʈ �߰�>                                                    |" << endl;
	cout << "| * �߰��ϰ��� �ϴ� �̺�Ʈ�� ����, ������ �Է����ּ���.             |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "�̺�Ʈ�� ������ �Է����ּ���" << endl;
	cout << "-> ";
	cin.ignore();
	getline(cin, name);
	cout << "�̺�Ʈ�� ������ �Է����ּ���" << endl;
	cout << "-> ";
	getline(cin, contents);
	
	event.Enqueue(Event(name, contents));
	fout << name << "\t" << contents << "\t" << 0 << endl;

	system("cls");
	cout << "����� �Ϸ�Ǿ����ϴ�." << endl << endl;

	fout.close();
}

void PrintEvent()
{
	QueType<Event> temp;
	Event temp2;
	int index = 0;

	system("cls");
	while (!event.IsEmpty())
	{
		event.Dequeue(temp2);
		temp.Enqueue(temp2);

		cout << ++index << "��° �̺�Ʈ <" << temp2.getName() << ">" << endl;
	}
	cout << endl;

	while (!temp.IsEmpty())
	{
		temp.Dequeue(temp2);
		event.Enqueue(temp2);
	}
}

void PrintTodayEvent()
{
	if (event.IsEmpty())
	{
		cout << "���� �������� �̺�Ʈ�� �����ϴ�." << endl << endl;
		return;
	}

	static Event temp;
	event.Dequeue(temp);

	cout << "������ �̺�Ʈ�� <" << temp.getName() << "> �Դϴ�." << endl;
	cout << "-> " << temp.getContents() << endl << endl;
	cout << "���� ������ ����� " << temp.getCount() << "�� �Դϴ�." << endl << endl;

	event.Enqueue(temp);
}