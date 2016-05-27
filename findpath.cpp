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
#include "Datastruct.h"
#include "timebased.h"
using namespace std;

extern DATA Data[1000];
extern int routecount;

stack<string> CityStack;
stack<RouteData> rStack;//stack for one route, arrary for all routes, and we let the top element records the time and money consumption, And it's good for sort
int RDnum;
RouteData tempRD;
void printstack(stack<RouteData> printee)
{

	stack<RouteData> temp;
	while(!printee.empty())
	{
		temp.push(printee.top());
		printee.pop();
	}
	cout<<"Route NO."<<RDnum<<endl;
	while(!temp.empty())
	{
		cout<<"@"<<temp.top().TB.start<<" Depart From:"<<temp.top().start<<endl<<
		"Take "<<temp.top().TB.kind<<" number:"<<temp.top().TB.name<<endl<<
		"Arrive At "<<temp.top().dest<<" at "<<temp.top().TB.arrival<<endl<<endl;
		printee.push(temp.top());
		temp.pop();
	}
	//cout<<endl;
}
void printall()
{

}

void findpath(string start,string destiny,int moneylimit,int timelimit,int curcost,int curtime,int starttime)
{
	//if it's out of bound,then don't travel any further
	if(curcost >= moneylimit && start != destiny)
		return ;
	if(curtime >= timelimit && start != destiny)
		return ;

	if(start==destiny)
	{
		if(curcost > moneylimit || curtime > timelimit)return;
		
		printstack(rStack);//cout<<destiny<<endl;
		RDnum++;
		return ;
	}
	//deep-priority traverse
	for(int i=1; i<=routecount; i++)
	{
		if(Data[i].from == start)
		{
			CityStack.push(Data[i].from);
			tempRD.start=Data[i].from;
			tempRD.dest=Data[i].dest;
			memcpy(&tempRD.TB,Data[i].TB,sizeof(Data[i].TB));
			rStack.push(tempRD);
			for(int j=0; j<=Data[i].rNumber; j++)
			{
				int est;
				est=Data[i].TB[j].arrival-starttime;
				if(Data[i].TB[j].start < starttime)est+=24;
				findpath(Data[i].dest,destiny,moneylimit,timelimit,curcost+Data[i].TB[j].cost,curtime+est,Data[i].TB[j].arrival);

			}
			CityStack.pop();
			rStack.pop();
			
		}
	}
	return ;
}