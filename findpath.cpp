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

void findpath(string start,string destiny,int moneylimit,int timelimit,int curcost,int curtime,int starttime)
{
	//cout<<"Break 1"<<start<<starttime<<endl;
	//if it's out of bound,then don't travel any further
	if(curcost >= moneylimit && start != destiny)
		return ;
	if(curtime >= timelimit && start != destiny)
		return ;

	if(start==destiny)
	{
		if(curcost > moneylimit || curtime > timelimit)return;
		cout<<CityStack.top()<<"————";
		CityStack.pop();
		return ;
	}
	//deep-priority traverse
	for(int i=1; i<=routecount; i++)
	{

	//cout<<"Break 2"<<start<<starttime<<endl;
		if(Data[i].from == start)//All route from vertex in S
		{

	//cout<<"Break 3"<<start<<starttime<<endl;
			CityStack.push(Data[i].from);
			cout<<"test"<<CityStack.top()<<" ";
			for(int j=0; j<=Data[i].rNumber; j++)
			{
				int est;
				est=Data[i].TB[j].arrival-starttime;
				if(Data[i].TB[j].start < starttime)est+=24;
				findpath(Data[i].dest,destiny,moneylimit,timelimit,curcost+Data[i].TB[j].cost,curtime+est,Data[i].TB[j].arrival);

			}
			cout<<CityStack.top()<<" ";
			CityStack.pop();
		}
	}
	return ;
}