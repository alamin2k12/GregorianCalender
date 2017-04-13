#include <iostream>
#include <iomanip>
#include <cmath>
#include <windows.h>
#include <cstdlib>


using namespace std;

void clrscr();
void gotoxy(int,int);

class calender
{
public:
	calender(int d,int m,int y);
	void printcalender();

private:
	bool isleapyear(); // returns true if year is leap
	int checkday(int); // checks legality of date
	int whatdayisfirstofmonth(); // returns 0 to 6 sunday to saturday
	int howmanydays(); // returns days in month
	int day;
	int month;
	int year;
};
calender::calender(int d,int m,int y)
{

	if (y<1582)
	{
		cout<<"Setting to 2001."<<endl;
		year=2001; // invalid year so set to 2001
	}
	else
	{
		year=y;
	}
	if ((m>=1) && (m<=12))
	{
		month=m;
	}
	else
	{
		cout<<endl<<"The month "<<m<<" is invalid. Setting to month 1"<<endl;
		month=1;
	}
	day=checkday(d); // validate the day
}
bool calender::isleapyear()
{
	if ((year%400==0) || ((year %4==0) && (year%100 !=0)))
	{
		return true; // its a leap year
	}

	else
	{
		return false; // its not a leap year
	}
}
int calender::checkday(int testday)
{

	if ((testday>0) && (testday<= howmanydays()))
	{
		return testday; // day is valid for month
	}
	cout<<endl<<"Invalid day entered "<<testday<<"/"<<month<<"/"<<year
		<<". Setting to the first of the month."<<endl;
	return 1; // for invalid month set 1
};
int calender::howmanydays()
{
	if((month==2)&& isleapyear())
	{
		return 29; // feb has 29 days in a leap year
	}

	 const int daysinmonth[12]={31,28,31,30,31,30,31,31,30,31,30,31};
	return daysinmonth[month-1];
}
int calender::whatdayisfirstofmonth()
{
	int c=year/100; //  of centuries
	int d=year%100; //  of years through century
	int m=(month+10)%12; //  of month march is 1,feb is 12
	int k=1; // set the day part to 1 so we get back the day for first of month
	if ((month==1)||(month==2))// treat jan and feb as if they were in previous year
	{
		if (d==0) // if d is 0 then to go back a year d becomes 99 and c become c-1
		{
			d=99;
			c-=1;
		}
		else
		{
		d-=1; // jan and feb are treated as previous year
		}
	}
	 float g=(k + (floor(((13*m)-1)/5)) + d + (floor(d/4)) + (floor(c/4)) - (2*c));//Zellar's Algorithms form wiki

	 int f=static_cast<int>(g)%7;
	 if (f<0)
	 {
		 f+=7;
	 }
	 return f; // returns 0 to 6 corresponding to sunday to saturday
}
void calender::printcalender()
{
	clrscr();
	cout<<"Date entered was :- "<<day<<"/"<<month<<"/"<<year<<"/"<<endl;
	cout<<endl<<setw(8)<<"SUNDAY"<<setw(8)<<"MONDAY"<<setw(9)<<"TUESDAY"<<setw(11)<<"WEDNESDAY"<<setw(10)
		<<"THURSDAY"<<setw(8)<<"FRIDAY"<<setw(10)<<"SATURDAY"<<endl;
	int startday=whatdayisfirstofmonth();
	int endday=howmanydays();
	for (int i=0;i<startday;i++)
	{
		if (i==0)
		{
			gotoxy(4,4);
			cout<<"-";
		}
		if (i==1)
		{
			gotoxy(12,4);
			cout<<"-";
		}
		if (i==2)
		{
			gotoxy(21,4);
			cout<<"-";
		}
		if (i==3)
		{
			gotoxy(31,4);
			cout<<"-";
		}
		if (i==4)
		{
			gotoxy(42,4);
			cout<<"-";
		}
		if (i==5)
		{
			gotoxy(50,4);
			cout<<"-";
		}
	}


	int rows=4;
	int count=1;
	for(int j=startday;j<(startday+endday);j++)
		{
		if(j%7==0)
		{
			rows+=2;
			gotoxy(4,rows);
		}
		if(j%7==1) gotoxy(12,rows);
		if(j%7==2) gotoxy(21,rows);
		if(j%7==3) gotoxy(31,rows);
		if(j%7==4) gotoxy(42,rows);
		if(j%7==5) gotoxy(50,rows);
		if(j%7==6) gotoxy(60,rows);
		if(count==day) // set to bright red if count is the day entered
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED);
		}
		else
		{
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
		}
		cout<<count;
		count ++;
	} // end  loop
	cout<<endl<<endl<<endl;
}
void clrscr()
{
  COORD coordScreen = { 0, 0 };
  DWORD cCharsWritten;
   CONSOLE_SCREEN_BUFFER_INFO csbi;
   DWORD dwConSize;
  HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
   FillConsoleOutputCharacter(hConsole, TEXT(' '), dwConSize, coordScreen, &cCharsWritten);
   GetConsoleScreenBufferInfo(hConsole, &csbi);
   FillConsoleOutputAttribute(hConsole, csbi.wAttributes, dwConSize, coordScreen, &cCharsWritten);
   SetConsoleCursorPosition(hConsole, coordScreen);
}

void gotoxy(int x, int y)//cursor position function
{
    COORD point;
    point.X = x; point.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),point);
}
int main()
{

	while (1)
	{
	clrscr();
	SetConsoleTitle(" Calender");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),FOREGROUND_INTENSITY|FOREGROUND_RED|FOREGROUND_BLUE|FOREGROUND_GREEN);
	cout<<endl;
		cout<<"      Enter  day month and full year";
		cout<<endl<<endl;

	int d,m,y;
	cin >> d;
	cin >> m;
	cin >> y;
	char c;

	calender date(d,m,y); // object of a calender class
	date.printcalender(); // print the calender
	cout<<"If you want to see another calender please press (Y/N) ";
	char input[5];

	cin.get(c);
	cin.getline(input,4);
	if ((input[0]=='N') || (input[0]=='n'))
	{
		break;
	}
	}

	return 0;
}
