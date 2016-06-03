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
#include <time.h>
#include "Datastruct.h"

using namespace std;

extern std::stack<TBlock> TData;
extern PassengerData PData;
std::stack<TBlock> TTemp,ReData;

void reverse()
{
	while(!TData.empty())
	{
		TTemp.push(TData.top());
		ReData.push(TData.top());
		TData.pop();
	}
	while(!TTemp.empty())
	{
		TData.push(TTemp.top());
		TTemp.pop();
	}
}

void go()
{

	int day = 0,hour = 0,time = 0,seq=2;
	int totaltime=0,totalmoney=0;
	bool flag=true;
	TBlock topelem;
	reverse();
	PData.currentCity = ReData.top().start;
	PData.nextCity = ReData.top().dest;
	PData.timeleft=ReData.top().from - hour;
	PData.isTravel =false;
	topelem=ReData.top();
	ReData.pop();
	//cout<<"RecNUM is "<<RecNum<<endl;
	while(flag)
	{

		if(!PData.isTravel)
		{

			if(hour != topelem.from)
			{
				PData.isTravel=false;
			}
			else
			{
				PData.isTravel=true;
			}
		}

		if(PData.isTravel)
		{
			PData.timeleft = topelem.arrival - hour;
		}
		else
		{
			PData.timeleft = topelem.from - hour;
		}

		if(PData.timeleft == 0)
		{
			if(PData.isTravel)
			{
				if(!ReData.empty())
				{
					
					totalmoney+=topelem.cost;
					topelem=ReData.top();
					ReData.pop();
					PData.isTravel=false;
					PData.currentCity=topelem.start;
					PData.nextCity=topelem.dest;
					
					if(hour == topelem.from)PData.isTravel=true;
				}
				else
				{
					cout<<"---------------------------------------"<<endl;
					cout<<"Arrive Final Station "<<PData.currentCity<<endl;
					cout<<"Total Time Consumption:"<<day*24+hour<<" hour"<<endl;
					cout<<"Total Money Consumption:"<<totalmoney<<endl;
					cout<<"---------------------------------------"<<endl;
					return;
					flag=false;
				}
			}
			else
			{
				PData.isTravel = true;
				PData.timeleft = topelem.arrival - hour;
			}
		}

		cout<<"---------------------------------------"<<endl;
		cout <<"DAY : "<<day<<" Hour : "<<hour<<endl;
		if(PData.isTravel)
		{
			cout<<"Traveling!"<<endl;
			//cout<<"Depart from:"<<PData.currentCity<<endl;
			cout<<"Left "<<PData.timeleft<<" to go!"<<endl;
			cout << "Arrive At " << topelem.dest
				<< "  at" << topelem.arrival << endl;
		
		}
		else
		{
			cout<<"Waiting!"<<endl;
			cout <<"Current City : "<<PData.currentCity<<endl;
			cout<< "Wait for : "<<topelem.kind << endl;
			cout << "Number is :" << topelem.id << endl;
			cout << "start at:" << topelem.from << endl;
		
		}
		cout<<"---------------------------------------"<<endl;


		//if(ReData.empty())return;
		time++;
		hour++;
		if(hour>=24)
		{
			day++;
			hour=0;
		}
		Sleep(10);
	}
}