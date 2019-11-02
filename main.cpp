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

void readMember(); // member 파일로 부터 유저 Data를 member 리스트에 저장
void readEvent(); //eventData 파일로부터 이벤트 정보를 받아서 event 큐에 저장
void readDVD(); //dvdData 파일로부터 DVD 정보를 받아서 DVD 트리에 저장
void mainMenu(); // 메인 메뉴 출력
void printErrorMessage(); // 잘못된 명령어 입력시 오류 메세지 출력
void managerMenu(); // 관리자 메뉴 출력
void memberMenu(string& ID); // 회원 메뉴 출력
void nonMemberMenu(); // 비회원 메뉴 출력
void managerFunction(); // 관리자 기능 함수
void register_Member(); // 회원가입 함수
void searchDVD(); // DVD 검색 함수
void searchMember(string& ID, int& count); // 회원 검색 함수
void login(); // 회원 로그인 함수
void couponMenu(string& ID); // 쿠폰 개수 출력 메뉴
void eventMenu(); // 이벤트 관리 메뉴
void AddEvent(); // 이벤트 추가 함수
void PrintEvent(); // 현재 이벤트 출력 함수
void PrintTodayEvent(); // 오늘의 이벤트 출력

manager khu; // 관리자 객체 khu 선언
SortedType<Student> member; // 멤버 리스트 선언
QueType<Event> event; // 이벤트 큐 선언
TreeType tree; // DVD 트리 선언

int main()
{
	readMember();
	readEvent();
	readDVD();

	int user; // 사용자로부터 수행할 명령을 받아 저장

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
	fin.open("member.txt"); // member 파일 open

	if (!fin)
	{
		cerr << "파일 오픈에 실패하였습니다. 관리자에게 문의바랍니다." << endl;
		exit(100);
	}
	
	stringstream ss; // 읽어들인 한줄을 각각의 변수에 저장하기 위한 string stream
	string line; // 한줄씩 읽어들일 변수
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
	fin.open("eventData.txt"); // eventData 파일 open

	if (!fin)
	{
		cerr << "파일 오픈에 실패하였습니다. 관리자에게 문의바랍니다." << endl;
		exit(100);
	}

	stringstream ss; // 읽어들인 한줄을 각각의 변수에 저장하기 위한 string stream
	string line; // 한줄씩 읽어들일 변수
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
	fin.open("dvdData.txt"); // dvdData 파일 open

	if (!fin)
	{
		cerr << "파일 오픈에 실패하였습니다. 관리자에게 문의바랍니다." << endl;
		exit(100);
	}

	stringstream ss; // 읽어들인 한줄을 각각의 변수에 저장하기 위한 string stream
	string line; // 한줄씩 읽어들일 변수
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
	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+-------------------------------------------------+" << endl;
	cout << "|  <사용자 권한을 선택하세요>                     |" << endl;
	cout << "|  1. 관리자                                      |" << endl;
	cout << "|  2. 회원                                        |" << endl;
	cout << "|  3. 비회원                                      |" << endl;
	cout << "|  0. 종료                                        |" << endl;
	cout << "+-------------------------------------------------+" << endl;
	cout << "-> ";
}

void printErrorMessage()
{
	cout << "잘못된 명령어를 입력하셨습니다. 처음으로 돌아갑니다." << endl << endl << endl;
}

void managerMenu()
{
	system("cls");

	string ID; // ID를 입력받을 변수
	string PW; // 비밀번호를 입력받을 변수
	int count = 0; // 입력 횟수를 카운트 할 변수
	bool complete = false; // 로그인 성공 여부를 확인할 변수

	while (count < 5)
	{
		cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
		cout << "+-------------------------------------------------------------------+" << endl;
		cout << "|  <관리자>                                                         |" << endl;
		cout << "| * ID 또는 PW 입력이 5회 이상 잘못될 경우 처음으로 돌아갑니다.     |" << endl;
		cout << "| * 이전 화면으로 돌아가려면 ID에 0을 입력하세요.                   |" << endl;
		cout << "+-------------------------------------------------------------------+" << endl;
		cout << "ID와 PW를 입력해주세요" << endl;
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
			cout << ++count << "회 잘못 입력하셨습니다." << endl << endl;
		}
	}

	if (complete)
		managerFunction();
}

void memberMenu(string& ID)
{
	system("cls");
	int user;

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <회원>                                                  |" << endl;
	cout << "| * 아래 기능 중 원하는 기능을 선택해주세요.              |" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "실행하실 기능을 입력해주세요" << endl;
	cout << "1. DVD 검색" << endl;
	cout << "2. DVD 반납" << endl;
	cout << "3. 쿠폰 개수 조회" << endl;
	cout << "0. 초기화면" << endl;
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

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <비회원>                                                |" << endl;
	cout << "| * 회원가입 또는 뒤로가기 중 원하는 기능을 선택하세요    |" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "실행하실 기능을 입력해주세요" << endl;
	cout << "1. 회원가입" << endl;
	cout << "0. 뒤로가기" << endl;
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
		cerr << "파일 오픈에 실패하였습니다. 관리자에게 문의바랍니다." << endl;
		exit(100);
	}

	string user_ID;
	string user_PW;
	bool found = false;

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <회원가입>                                              |" << endl;
	cout << "| * ID는 자신의 학번을 입력해주세요.                      |" << endl;
	cout << "| * PW는 영문, 숫자를 혼용하여 입력해주세요.              |" << endl;
	cout << "+---------------------------------------------------------+" << endl;

	cout << "ID를 입력하세요 : ";
	cin >> user_ID;

	member.RetrieveItem(user_ID, found);
	if (found)
	{
		cout << "이미 존재하는 ID입니다. 관리자에게 문의해주세요" << endl;
		fout.close();
		return;
	}

	cout << "PW를 입력하세요 : ";
	cin >> user_PW;

	fout << user_ID << "\t" << user_PW << "\t" << 0 << endl;
	member.InsertItem(Student(user_ID, user_PW));
	cout << "회원가입에 성공하였습니다!!" << endl << endl;

	fout.close();
}

void managerFunction()
{
	system("cls");

	int user; // 사용자 명령어 입력 변수

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <관리자>                                                         |" << endl;
	cout << "| * 원하는 기능을 선택해주세요.                                     |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "실행하실 기능을 입력해주세요" << endl;
	cout << "1. 회원 출력" << endl;
	cout << "2. 이벤트 관리" << endl;
	cout << "0. 초기화면" << endl;
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

	int user; // 사용자 명령어 입력 변수

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <이벤트 관리>                                                    |" << endl;
	cout << "| * 원하는 기능을 선택해주세요.                                     |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "실행하실 기능을 입력해주세요" << endl;
	cout << "1. 이벤트 추가" << endl;
	cout << "2. 이벤트 출력" << endl;
	cout << "0. 초기화면" << endl;
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

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <로그인>                                                |" << endl;
	cout << "| * ID와 PW를 입력해주세요.                               |" << endl;
	cout << "+---------------------------------------------------------+" << endl;

	while (count < 3)
	{
		cout << "ID를 입력하세요 : ";
		cin >> user_ID;
		cout << "PW를 입력하세요 : ";
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
			cout << "일치하는 회원 정보가 존재하지 않습니다." << 3 - (++count) << "회 남았습니다." << endl << endl;
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

	string user; // 사용자에게 입력 받을 제목을 담을 변수
	bool found; // 검색 성공 여뷰
	DVD temp;

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <DVD 검색>                                                       |" << endl;
	cout << "| * 찾고자 하는 DVD의 제목을 입력해주세요                           |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "-> ";
	cin.ignore();
	getline(cin, user);

	temp.setDVD(user);

	tree.RetrieveItem(temp, found);

	if (!found)
	{
		system("cls");
		cout << "찾고자 하는 DVD가 존재하지 않습니다." << endl << endl;
	}
	else
	{
		temp.Print();
		cout << endl;

		if (!temp.IsRented())
		{
			int command;

			cout << "이 DVD를 대여하시겠습니까?( Yes : 1, No : 0)" << endl;
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

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+---------------------------------------------------------+" << endl;
	cout << "| <쿠폰 개수 조회>                                        |" << endl;
	cout << "| * 쿠폰 개수는 DVD 1회 대여마다 증가합니다.              |" << endl;
	cout << "| * 쿠폰은 이벤트 참가에 사용될 수 있습니다.              |" << endl;
	cout << "+---------------------------------------------------------+" << endl;

	searchMember(ID, count);
	cout << "회원님의 현재 쿠폰 개수는 " << count << "개 입니다." << endl << endl;
}

void AddEvent()
{
	system("cls");

	string name, contents; // 사용자 입력 변수
	ofstream fout("eventData.txt", ios::app);
	if (!fout)
	{
		cerr << "파일 오픈에 실패하였습니다. 관리자에게 문의바랍니다." << endl;
		exit(100);
	}

	cout << "### 경희대학교 중앙도서관 음향자료실 대여시스템 ###" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "|  <이벤트 추가>                                                    |" << endl;
	cout << "| * 추가하고자 하는 이벤트의 제목, 내용을 입력해주세요.             |" << endl;
	cout << "+-------------------------------------------------------------------+" << endl;
	cout << "이벤트의 제목을 입력해주세요" << endl;
	cout << "-> ";
	cin.ignore();
	getline(cin, name);
	cout << "이벤트의 내용을 입력해주세요" << endl;
	cout << "-> ";
	getline(cin, contents);
	
	event.Enqueue(Event(name, contents));
	fout << name << "\t" << contents << "\t" << 0 << endl;

	system("cls");
	cout << "등록이 완료되었습니다." << endl << endl;

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

		cout << ++index << "번째 이벤트 <" << temp2.getName() << ">" << endl;
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
		cout << "현재 진행중인 이벤트가 없습니다." << endl << endl;
		return;
	}

	static Event temp;
	event.Dequeue(temp);

	cout << "오늘의 이벤트는 <" << temp.getName() << "> 입니다." << endl;
	cout << "-> " << temp.getContents() << endl << endl;
	cout << "현재 참여한 사람은 " << temp.getCount() << "명 입니다." << endl << endl;

	event.Enqueue(temp);
}