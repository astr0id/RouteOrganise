#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <stack>
using namespace std;
#ifndef DATASTRUCT_H
#define DATASTRUCT_H

struct timetable
{
	int start;
	int arrival;
	int cost;
	string kind;
	string name;
};

typedef struct
{
	string from;
	string dest;
	int rNumber;//Records the number of routes between two citys
	timetable TB[30];
} DATA;

typedef struct 
{
	string currentCity;
	string nextCity;
	int timeleft;
	bool isTravel;
}PassengerData;

typedef struct 
{
	string start;
	string dest;
	int from;
	int arrival;
	int cost;
	string id;
	string kind;
}TBlock;

const string citylist[] = { "A","B","C","D","E","F","G","H","I","J","K","L","M" };

class Passenger
{
public:
	void initialiaze()
	{
		/*
		startcity = qstart.toStdString();
		endcity = qend.toStdString();
		starttime = qstarttime;
		vianum = qcityvia;
		if (vianum)
		{
			for (int i = 1; i <= vianum; i++)
			{
				vianum[i] = qvia[i];
			}
		}
		routestrategy = qchoice;
		*/
		cout << "where to start ?" << endl;
		cin >> startcity;
		cout << "where to go ?" << endl;
		cin >> endcity;
		cout << "when to go ?" << endl;
		cin >> starttime;
		cout << "How many city to pass" << endl;
		cin >> vianum;
		for (int i = 1; i <= vianum; i++)
		{
			cout << "No." << i << " city to pass" << endl;
			cin >> viacity[i];
		}
		viacity[0] = startcity;
		viacity[vianum+1] = endcity;
		cout << "Which Strategy you want?" << endl
			 << "1:Least Money Strategy" << endl 
			 <<	"2:Least Time Strategy" << endl 
			 <<	"3:Limit Time Least Money Strategy" << endl;
		cin>> routestrategy;
		if (routestrategy == 3)
		{
			cout << "What's your time limit" << endl;
			cin >> timellimit;
		}
		for (int i = 0; i < 13; i++)pastcity.insert(citylist[i]);
		cout << "break" << endl;
		for (int i = 0; i <= vianum + 1; i++)inRoute.insert(viacity[i]);
		//timellimit = 30;
		this->control();
	}

	stack<TBlock> getRoute()
	{
		return RouteStack;
	}
		
		
private:
	string startcity, endcity, viacity[10];
	int starttime,vianum,routestrategy,totalmoney,totaltime;
	stack<TBlock> RouteStack;
	PassengerData myData;
	int timellimit;

	

	int mincost = 9999;
	stack<string> CityStack;
	stack<TBlock> TStack;
	set<string> pastcity;
	int RDnum; 
	set<string> inRoute;

	void control()
	{
		if (routestrategy != 3)
		{
			for (int i = 0; i <= vianum; i++)
			{
				if (routestrategy == 1)
					this->MoneyBased(viacity[i], viacity[i + 1]);
				else
				{
					this->TimeBased(viacity[i], viacity[i + 1]);
				}
					
			}
		}
		else
		{
			findpath(startcity,endcity,999999,timellimit,0,0,starttime);
		}
	}
	void TimeBased(string,string);
	void MoneyBased(string, string);
	void findpath(string, string, int, int, int, int, int);
	bool stackcheck();
};


#endif