#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <deque>
#include <stack>

#include "keyboard.h"
#include "moneybased.h"
#include "timebased.h"
#include "Datastruct.h"
#include "findpath.h"
#include "LTLM.h"

using namespace std;

void TMBkeyboard(int);
void LTkeyboard();

extern DATA Data[1000];
extern int routecount;
map<string, int> FinalRecord, TempFinalRecord;
map<string, string> tempPath, Path;
map<string, int>Index0;
map<string, int>Index1;

int step=2;

void FPkb()
{
	string start, end;
	int starttime,tlimit,mlimit;
	cout << "where to start ?" << endl;
	cin >> start;
	cout << "where to go ?" << endl;
	cin >> end;
	cout << "when to go ?" << endl;
	cin >> starttime;
	cout << "what time you have" << endl;
	cin >> tlimit;
	cout<< "how much money you have"<<endl;
	cin >> mlimit;
	findpath(start,end,mlimit,tlimit,0,0,starttime);
}

void keyboard()
{
	int strategy;
	cout<<"Which Strategy you want?"<<endl<<
	"1:Least Money Strategy"<<endl<<
	"2:Least Time Strategy"<<endl<<
	"3:Limit Time Least Money Strategy"<<endl;
	cin>>strategy;
	switch(strategy)
	{
		case 1:
			TMBkeyboard(0);
			break;
		case 2:
			TMBkeyboard(1);
			break;
		case 3:
			//LTkeyboard();
			FPkb();
			break;
	}
}

void TMBkeyboard(int choice)
{
	for (int i = 1; i <= routecount; i++)
	{
		for (int j = 0; j < Data[i].rNumber; j++)
		{
			Index0.insert(pair<string, int>(Data[i].TB[j].name, 0));
			Index1.insert(pair<string, int>(Data[i].TB[j].name, 0));
		}
	}
	set<string> City(citylist, citylist + sizeof(citylist) / sizeof(*citylist));
	set<string>::iterator it;
	for (it = City.begin(); it != City.end(); it++)
	{
		Path.insert(pair<string, string>(*it, ""));
		FinalRecord.insert(pair<string, int>(*it, 0));
	}
	string start, end, via[50];
	string temp;

	int city_via = 0, totaltime = 0, num = 1, time = 0, totalmoney = 0, starttime = 0, count = 0;//day
	cout << "where to start ?" << endl;
	cin >> start;
	cout << "where to go ?" << endl;
	cin >> end;
	cout << "when to go ?" << endl;
	cin >> starttime;
	cout << "how many country do you want to pass through?" << endl;
	cin >> city_via;
	if (city_via)
	{
		cout << "where to pass through?" << endl;
		for (int i = 1; i <= city_via; i++)
		{
			cin >> via[i];
			cout << " ";
		}
	}
	time = starttime;
	via[0] = start;
	via[city_via + 1] = end;
	for (int i = 0; i < city_via + 1; i++)
	{
		FinalRecord[via[i]] = 1;
		if(!choice)
			MoneyBased(via[i], via[i + 1], time, totalmoney);
		else
			TimeBased(via[i], via[i + 1], time, totalmoney);

		for (count = 0, it = City.begin(); it != City.end(); it++)
		{
			if (FinalRecord.find(*it)->second)count++;
		}
		for (int i = step; i <= count; i++)
		{
			for (it = City.begin(); it != City.end(); it++)
			{
				if (FinalRecord.find(*it)->second == i)
				{
					cout << "from :" << Data[Index0[Path[*it]]].from << endl << "Take :" << Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].kind << endl;
					cout << "number is :" << Path[*it] << endl << "Arrive At " << Data[Index0[Path[*it]]].dest << "  at" << Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].arrival << endl;
					if (i == count)
					{
						if (Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].start < time)totaltime += Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].arrival - time + 24;
						else totaltime += Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].arrival - time;
					}
				}
			}
		}
		step+=count;
		step++;
		/*
		for (it = City.begin(); it != City.end(); it++)
			FinalRecord[*it] = 0;
		*/
		time = (totaltime + starttime) % 24;
	}
	cout << endl << "total time is : " << totaltime << endl;
	cout << endl;
	cout << "total money is:" << totalmoney<<endl;
}

void LTkeyboard()
{
	int MinMoney = 0;
	for (int i = 1; i <= routecount; i++)
	{
		for (int j = 0; j < Data[i].rNumber; j++)
		{
			Index0.insert(pair<string, int>(Data[i].TB[j].name, 0));
			Index1.insert(pair<string, int>(Data[i].TB[j].name, 0));
		}
	}
	set<string> City(citylist, citylist + sizeof(citylist) / sizeof(*citylist));
	set<string>::iterator it;
	for (it = City.begin(); it != City.end(); it++)
	{
		tempPath.insert(pair<string, string>(*it, ""));
		Path.insert(pair<string, string>(*it, ""));
		FinalRecord.insert(pair<string, int>(*it, 0));
		TempFinalRecord.insert(pair<string, int>(*it, 0));
	}
	MinMoney = 32767;
	string start, end, via[50];
	string temp;
	string path[50];
	int city_via = 0, totaltime = 0, num = 1, money = 0, time = 0, starttime = 0, limittedtime = 30;//day 
	int count;
	cout << "where to start ?" << endl;
	cin >> start;
	cout << "where to go ?" << endl;
	cin >> end;
	cout << "when to go ?" << endl;
	cin >> starttime;
	cout << "how many country do you want to pass through?" << endl;
	cin >> city_via;
	if (city_via)
	{
		cout << "where to pass through?" << endl;
		for (int i = 1; i <= city_via; i++)
		{
			cin >> via[i];
			cout << " ";
		}
	}


	time = starttime;
	via[0] = start;
	via[city_via + 1] = end;
	FinalRecord.find(start)->second = 1;
	TempFinalRecord = FinalRecord;
	count = 2;
	cout << "the route is : ";
	LimittedTimeLeastMoney(totaltime, time, starttime, limittedtime, money, start, end, count, MinMoney, via);
	
	for (count = 0, it = City.begin(); it != City.end(); it++)
	{
		if (FinalRecord.find(*it)->second)count++;
	}
	if (count == 1)
	{
		system("CLS");
		cout << "The route doesn't exist." << endl;
		return;
	}
	//
	MinMoney = 0;
	for (int i = 1; i < count; i++)
	{
		for (it = City.begin(); it != City.end(); it++)
		{
			if (FinalRecord.find(*it)->second == i)
			{
				cout << "from :" << Data[Index0[Path[*it]]].from << endl << "Take :" << Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].kind << endl;
				cout << "number is :" << Path[*it] << endl << "Arrive At " << Data[Index0[Path[*it]]].dest << "  at" << Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].arrival << endl;
				if (Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].start < time)
					totaltime += Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].arrival - time + 24;
				else
					totaltime += Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].arrival - time;
				time = (starttime + totaltime) % 24;
				MinMoney += Data[Index0[Path[*it]]].TB[Index1[Path[*it]]].cost;
			}
		}
	}

	int j = 1;
	if (totaltime <= limittedtime)
	{
		for (it=City.begin(); j <= count; j++)
		{
			while (FinalRecord.find(*it)->second != j&&it != City.end())
				it++;
			if (j == count)
				cout << *it;
			else
				cout << *it << "->";
			it = City.begin();
		}
		cout << endl << "total time is : " << totaltime << endl;
		cout << endl;
		cout << "total money is:" << MinMoney<<endl;
	}
	else 
	{
		system("CLS");
		cout << "The route doesn't exist." << endl;
		return;
	}}