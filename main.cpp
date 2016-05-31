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

#include "load.h"
#include "keyboard.h"
#include "findpath.h"
#include "Datastruct.h"
using namespace std;

PassengerData PData;


extern DATA Data[1000];
extern int routecount;
extern map<string, int> FinalRecord;
extern map<string, string> Path;
extern map<string, int> Index0;
extern map<string, int> Index1;

static map<string,int>::iterator it;

map<int,string> NewRecord;
int RecNum;
void trans()
{
	for(int i=0;i<10;i++)
	{
		//cout<<citylist[i]<<" : "<<FinalRecord[citylist[i]]<<endl;
		if(FinalRecord[citylist[i]] != 0)
		{
			NewRecord[FinalRecord[citylist[i]]]=citylist[i];
			RecNum++;
		}
		//cout<<FinalRecord[citylist[i]]<<"--"<<NewRecord[FinalRecord[citylist[i]]]<<endl;
	}
}

int main()
{
	int day = 0,hour = 0,time = 0,seq=2;
	bool flag=true,setoff=true;
	newload();
	keyboard();
	trans();
	PData.currentCity = NewRecord[1];
	PData.nextCity = NewRecord[2];
	PData.timeleft=Data[Index0[Path[PData.nextCity]]].TB[Index1[Path[PData.nextCity]]].start - hour;
	PData.isTravel =false;
	//cout<<"RecNUM is "<<RecNum<<endl;
	while(hour<=5)
	{

		if(!PData.isTravel)
		{

			if(hour != Data[Index0[Path[PData.nextCity]]].TB[Index1[Path[PData.nextCity]]].start)
			{
				PData.isTravel=false;
			}
			else
			{
				seq++;
				PData.currentCity = PData.nextCity;
				PData.nextCity = NewRecord[seq];
				PData.isTravel=true;
				setoff=true;
			}
		}
		if(PData.isTravel)
		{
			setoff=false;
			PData.timeleft=Data[Index0[Path[PData.currentCity]]].TB[Index1[Path[PData.currentCity]]].arrival - hour;
		}
		if(PData.timeleft == 0)
		{
			if(seq == RecNum)
			{
				flag=false;
			}
			else
			{
				if(!setoff)
				{
					seq++;
					PData.currentCity = PData.nextCity;
					PData.nextCity = NewRecord[seq];

					PData.isTravel=false;
					setoff=true;
				}
				if(hour != Data[Index0[Path[PData.nextCity]]].TB[Index1[Path[PData.nextCity]]].start)
				{
					PData.isTravel=false;
				}
				else
				{
					seq++;
					PData.currentCity = PData.nextCity;
					PData.nextCity = NewRecord[seq];
					PData.isTravel=true;
					setoff=true;
				}

			}
		}
		cout<<"---------------------------------------"<<endl;
		cout <<"DAY : "<<day<<" Hour : "<<hour<<endl;
		if(PData.isTravel)
		{
			cout<<"Traveling!"<<endl;
			//cout<<"Depart from:"<<PData.currentCity<<endl;
			cout<<"Left "<<PData.timeleft<<" to go!"<<endl;
			cout<< "Arrive At " << Data[Index0[Path[PData.currentCity]]].dest 
		     	<< "  at" << Data[Index0[Path[PData.currentCity]]].TB[Index1[Path[PData.currentCity]]].arrival << endl;
		
		}
		else
		{
			cout<<"Waiting!"<<endl;
			cout <<"Current City : "<<PData.currentCity<<endl;
			cout<< "Wait for : "<<Data[Index0[Path[PData.currentCity]]].TB[Index1[Path[PData.currentCity]]].kind << endl;
			cout << "Number is :" << Path[PData.currentCity] << endl;
			cout<<"start at："<<Data[Index0[Path[PData.currentCity]]].TB[Index1[Path[PData.currentCity]]].start<<endl;
		
		}
		cout<<"---------------------------------------"<<endl;



		time++;
		hour++;
		if(hour>=24)
		{
			day++;
			hour=0;
		}
	}
	return 0;
}
