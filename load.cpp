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
void combine()
{

	FILE * fptr;
	fptr= fopen ("./tb-car.txt","r");
	const char * sep = "-|";
	char str[100];
	char *buffer;
	int cnt=0;
	while(!feof(fptr))
	{
		routecount++;
		fscanf (fptr,"%s",str);
		buffer = strtok(str, sep);
		while(buffer)
		{
			Data[routecount].from=buffer;
			buffer = strtok(NULL, sep);
			Data[routecount].dest=buffer;
			buffer = strtok(NULL, sep);

		}
		fscanf (fptr,"%s",str);
		buffer = strtok(str, sep);
		cnt=0;
		while(buffer)
		{
			Data[routecount].TB[cnt].start=atoi(buffer);
			buffer = strtok(NULL, sep);
			Data[routecount].TB[cnt].arrival=atoi(buffer);
			buffer = strtok(NULL, sep);
			Data[routecount].TB[cnt].kind="car";
			cnt++;
		}
		Data[routecount].rNumber=cnt;
		fscanf(fptr,"%s",str);
		for(int j=0;j<Data[routecount].rNumber;j++)
		{
			Data[routecount].TB[j].cost=atoi(str);
		}
	}
	freopen ("./tb-train.txt","r",fptr);
	while(!feof(fptr))
	{
		routecount++;
		fscanf (fptr,"%s",str);
		buffer = strtok(str, sep);
		while(buffer)
		{
			Data[routecount].from=buffer;
			buffer = strtok(NULL, sep);
			Data[routecount].dest=buffer;
			buffer = strtok(NULL, sep);

		}
		fscanf (fptr,"%s",str);
		buffer = strtok(str, sep);
		cnt=0;
		while(buffer)
		{
			Data[routecount].TB[cnt].start=atoi(buffer);
			buffer = strtok(NULL, sep);
			Data[routecount].TB[cnt].arrival=atoi(buffer);
			buffer = strtok(NULL, sep);
			Data[routecount].TB[cnt].kind="train";
			cnt++;
		}
		Data[routecount].rNumber=cnt;
		fscanf(fptr,"%s",str);
		for(int j=0;j<Data[routecount].rNumber;j++)
		{
			Data[routecount].TB[j].cost=atoi(str);
		}
	}
	
	fptr= fopen ("./tb-plane.txt","r");
	while(!feof(fptr))
	{
		routecount++;
		fscanf (fptr,"%s",str);
		buffer = strtok(str, sep);
		while(buffer)
		{
			Data[routecount].from=buffer;
			buffer = strtok(NULL, sep);
			Data[routecount].dest=buffer;
			buffer = strtok(NULL, sep);

		}
		fscanf (fptr,"%s",str);
		buffer = strtok(str, sep);
		cnt=0;
		while(buffer)
		{
			Data[routecount].TB[cnt].start=atoi(buffer);
			buffer = strtok(NULL, sep);
			Data[routecount].TB[cnt].arrival=atoi(buffer);
			buffer = strtok(NULL, sep);
			Data[routecount].TB[cnt].kind="plane";
			cnt++;
		}
		Data[routecount].rNumber=cnt;
		fscanf(fptr,"%s",str);
		for(int j=0;j<Data[routecount].rNumber;j++)
		{
			Data[routecount].TB[j].cost=atoi(str);
		}
	}
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


//Change the old form Timetable into new DB-like Timetable
void generate()
{
	FILE * fptr;
	fptr = fopen("./TBs.txt","w");
	fprintf(fptr, "Route Name\tStart City\tEnd City\tStart Time\tArrive Time\tCost\tTransportation\n" );
	map<string,string> tag;
	tag.insert(pair<string,string>("train","T"));
	tag.insert(pair<string,string>("car","C"));
	tag.insert(pair<string,string>("plane","P"));
	string name,sufix;int ran;char tmp[4];
	for(int i=1;i<=routecount;i++)
	{
		for(int j=0;j<=Data[i].rNumber;j++)
		{
			ran=(random(9000)+1000);
			sprintf(tmp, "%d", ran);
			sufix = tmp;
			name=tag[Data[i].TB[j].kind];
			name=name+sufix;

			

			fprintf(fptr, "%s\t\t%s\t\t%s\t\t%d\t\t%d\t\t%d\t\t%s\n",
				name.c_str(),
				Data[i].from.c_str(),Data[i].dest.c_str(),Data[i].TB[j].start,
				Data[i].TB[j].arrival,Data[i].TB[j].cost,Data[i].TB[j].kind.c_str());
		}
	}
	fclose(fptr);
}

void oldload()
{

	FILE * fptr;
	fptr= fopen ("./nTB.txt","r");
	const char * sep = "\n\t";
	char str[200];
	char *buffer;
	fgets(str,sizeof(str),fptr);
	string S,E,pS,pE;
	pS="ERROR";pE="ERROR";
	routecount=0;
	while(fgets(str,sizeof(str),fptr))
	{
		buffer = strtok(str, sep);S=buffer;
		buffer = strtok(NULL, sep);E=buffer;
		//cout<<"past city A is "<<pS<<" past city B is "<<pE<<endl;

		//cout<<"  S:"<<S<<"  E:"<<E<<endl;
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