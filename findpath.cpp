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
int mincost = 9999;
stack<string> CityStack;
std::stack<TBlock> TData;
std::stack<TBlock> TStack;
set<string> pastcity(citylist,citylist + sizeof(citylist)/sizeof(*citylist));
int RDnum;

void printstack(stack<TBlock> printee)
{

	stack<TBlock> temp;
	while(!printee.empty())
	{
		temp.push(printee.top());
		printee.pop();
	}
	cout<<"Route NO."<<RDnum<<endl;
	while(!temp.empty())
	{
		cout<<"Start @"<<temp.top().from<<" Depart From:"<<temp.top().start<<endl<<
		"Take "<<temp.top().kind<<" ID:"<<temp.top().id<<" Cost :$"<<temp.top().cost<<endl<<
		"Arrive At "<<temp.top().dest<<" at "<<temp.top().arrival<<endl<<endl;
		printee.push(temp.top());
		temp.pop();
	}
}


void findpath(string start,string destiny,int moneylimit,int timelimit,int curcost,int curtime,int starttime)
{
	TBlock temp;
	//set<string>::iterator sit;
	//if it's out of bound,then don't travel any further
	if(curcost >= moneylimit && start != destiny)
		return ;
	if(curtime >= timelimit && start != destiny)
		return ;

	if(start==destiny)
	{
		if(curcost > moneylimit || curtime > timelimit)return;
		if(curcost < mincost)
		{
			mincost=curcost;
			//printstack(TStack);
			TData=TStack;
		}
		RDnum++;
		return ;
	}
	//deep-priority traverse
	pastcity.erase(start);
	for(int i=1; i<=routecount; i++)
	{
		if(Data[i].from == start && ( pastcity.find(Data[i].dest)!=pastcity.end() ) )//Don't go back
		{
			CityStack.push(Data[i].from);
			temp.start=Data[i].from;
			temp.dest=Data[i].dest;
			for(int j=0; j<=Data[i].rNumber; j++)
			{
				temp.from=Data[i].TB[j].start;
				temp.arrival=Data[i].TB[j].arrival;
				temp.id=Data[i].TB[j].name;
				temp.kind=Data[i].TB[j].kind;
				temp.cost=Data[i].TB[j].cost;
				int est;
				est=Data[i].TB[j].arrival-starttime;
				if(Data[i].TB[j].start < starttime || Data[i].TB[j].start > Data[i].TB[j].arrival)est+=24;

				TStack.push(temp);
				findpath(Data[i].dest,destiny,moneylimit,timelimit,curcost+Data[i].TB[j].cost,curtime+est,Data[i].TB[j].arrival);
				TStack.pop();
			}
			CityStack.pop();
		}
	}
	pastcity.insert(start);
	return ;
}