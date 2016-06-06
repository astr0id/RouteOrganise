#include <iostream>
#include <string.h>
#include <cstdio>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include <cstdlib>

#include "load.h"
#include "Datastruct.h"
using namespace std;

#define random(x) (rand() % x)

DATA Data[1000];
std::stack<TBlock> TData;
int routecount;

void newload()
{

	FILE * fptr;
	fptr= fopen ("./TBs.txt","r");
	const char * sep = "\n\t";
	char str[200];
	char *buffer;
	fgets(str,sizeof(str),fptr);
	string S,E,pS,pE,N;
	pS="ERROR";pE="ERROR";
	routecount=0;
	while(fgets(str,sizeof(str),fptr))
	{
		buffer = strtok(str,sep);N=buffer;
		buffer = strtok(NULL, sep);S=buffer;
		buffer = strtok(NULL, sep);E=buffer;
		//cout<<"N:"<<N<<"  S:"<<S<<"  E:"<<E<<endl;
		//cout<<"past city A is "<<pS<<" past city B is "<<pE<<endl;

		//cout<<"curr city A is "<<S<<" curr city B is "<<E<<endl<<endl;
		if(pS==S && pE==E)
		{
			Data[routecount].rNumber++;
		}
		else
		{
			pS=S;pE=E;
			routecount++;
			Data[routecount].rNumber=0;
		}	
		Data[routecount].TB[Data[routecount].rNumber].name=N;
		Data[routecount].from=S;
		Data[routecount].dest=E;
		buffer = strtok(NULL, sep);
		Data[routecount].TB[Data[routecount].rNumber].start=atoi(buffer);
		buffer = strtok(NULL, sep);
		Data[routecount].TB[Data[routecount].rNumber].arrival=atoi(buffer);
		buffer = strtok(NULL, sep);
		Data[routecount].TB[Data[routecount].rNumber].cost=atoi(buffer);
		buffer = strtok(NULL, sep);
		Data[routecount].TB[Data[routecount].rNumber].kind=buffer;

	}
	cout<<routecount<<endl;
	fclose (fptr);
}


void print()
{
	int cnnt=0;
	//cout<<"Total "<<routecount<<endl;
	printf("Route Name\tStart City\tEnd City\tStart Time\tArrive Time\tCost\t\tKind\n" );
	for(int i=1;i<=routecount;i++)
	{
		cout<<"-----------------------------"<<endl;
		cout<<"Route count :"<<i<<endl;
		for(int j=0;j<=Data[i].rNumber;j++)
		{
			cout<<"-----------"<<endl;
			cout<<"rNumber : "<<j<<endl;
			cnnt++;
			printf("%s\t\t%s\t\t%s\t\t%d\t\t%d\t\t%d\t\t%s\n",Data[i].TB[j].name.c_str(),
				Data[i].from.c_str(),Data[i].dest.c_str(),Data[i].TB[j].start,Data[i].TB[j].arrival,
				Data[i].TB[j].cost,Data[i].TB[j].kind.c_str());
		}
	}
	cout<<"Total num : "<<cnnt<<endl;
}

void printstack(stack<TBlock> printee)
{

	stack<TBlock> temp;
	while (!printee.empty())
	{
		temp.push(printee.top());
		printee.pop();
	}
	//cout<<"Route NO."<<RDnum<<endl;
	while (!temp.empty())
	{
		cout << "Start @" << temp.top().from << " Depart From:" << temp.top().start << endl <<
			"Take " << temp.top().kind << " ID:" << temp.top().id << " Cost :$" << temp.top().cost << endl <<
			"Arrive At " << temp.top().dest << " at " << temp.top().arrival << endl << endl;
		printee.push(temp.top());
		temp.pop();
	}
}