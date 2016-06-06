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
extern set<string> pastcity;
extern std::stack<TBlock> TData;

int RecNum;

int main()
{
	int day = 0,hour = 0,time = 0,seq=2;
	bool flag=true,setoff=true;
	newload();
	class Passenger DGM;
	DGM.initialiaze();
	TData=DGM.getRoute();
	//keyboard();
	printstack(TData);
	//cout<<"min cost "<<mincost<<endl;
	//go();
	//print();
	system("pause");
	return 0;
}
