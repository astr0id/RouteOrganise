#include <iostream>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>


#include "load.h"
#include "Datastruct.h"
using namespace std;

DATA Data[1000];
int routecount;
void load()
{

	FILE * fptr;
	fptr= fopen ("./tb.txt","r");
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

void newload()
{

	FILE * fptr;
	fptr= fopen ("./nTB.txt","r");
	const char * sep = "\t";
	char str[200];
	char *buffer;
	fgets(str,sizeof(str),fptr);
	string S,E,pS,pE;
	pS="ERROR";pE="ERROR";

	while(fgets(str,sizeof(str),fptr))
	{
		buffer = strtok(str, sep);S=buffer;
		buffer = strtok(NULL, sep);E=buffer;
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
	//cout<<"Total "<<routecount<<endl;
	printf("Start City\tEnd City\tStart Time\tArrive Time\tCost\n" );
	for(int i=1;i<=routecount;i++)
	{
		for(int j=0;j<=Data[i].rNumber;j++)
		{
			printf("%s\t\t%s\t\t%d\t\t%d\t\t%d\t%s",
				Data[i].from.c_str(),Data[i].dest.c_str(),Data[i].TB[j].start,Data[i].TB[j].arrival,
				Data[i].TB[j].cost,Data[i].TB[j].kind.c_str());
		}
	}
}


//Change the old form Timetable into new DB-like Timetable
void generate()
{
	FILE * fptr;
	fptr = fopen("./nTB.txt","w");
	fprintf(fptr, "Start City\tEnd City\tStart Time\tArrive Time\tCost\tTransportation\n" );
	for(int i=0;i<routecount;i++)
	{
		for(int j=0;j<Data[i].rNumber;j++)
		{
			fprintf(fptr, "%s\t\t%s\t\t%d\t\t%d\t\t%d\t\t%s\n",
				Data[i].from.c_str(),Data[i].dest.c_str(),Data[i].TB[j].start,Data[i].TB[j].arrival,Data[i].TB[j].cost,Data[i].TB[j].kind.c_str());
		}
	}
	fclose(fptr);
}