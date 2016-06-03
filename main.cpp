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
#include "go.h"
using namespace std;

PassengerData PData;


extern DATA Data[1000];
extern int routecount;
extern map<string, int> FinalRecord;
extern map<string, string> Path;
extern map<string, int> Index0;
extern map<string, int> Index1;
extern set<string> pastcity;
extern int mincost;
extern std::stack<TBlock> TData;

map<int,string> NewRecord;
int RecNum;
void trans()
{
	for(int i=0;i<10;i++)
	{
		if(FinalRecord[citylist[i]] != 0)
		{
			NewRecord[FinalRecord[citylist[i]]]=citylist[i];
			RecNum++;
		}
	}
}


int main()
{
	int day = 0,hour = 0,time = 0,seq=2;
	bool flag=true,setoff=true;
	newload();
	
	keyboard();
	//printstack(TData);
	//cout<<"min cost "<<mincost<<endl;
	go();
	return 0;
}
