#include <iostream>
#include <string.h>

#include "timebased.h"
#include "load.h"

using namespace std;

int main()
{
	
	system("reset");
	string start,end,time;
	
	cout<<"where to start ?"<<endl;
	cin>>start;
	cout<<"where to go ?"<<endl;
	cin>>end;
	cout<<"when to go ?"<<endl;
	cin>>time;
	
	
	newload();
	TimeBased(start,end,time);
	//combine();
	//generate();
	//print();


	return 0;
}
