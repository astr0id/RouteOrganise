#ifndef DATASTRUCT_H
#define DATASTRUCT_H


using namespace std;

struct timetable
{
	int start;
	int arrival;
	int cost;
};

typedef struct
{
	string from;
	string dest;
	int rNumber;//Records the number of routes between two citys
	timetable TB[30];
} DATA;

DATA Data[1000];

int routecount;

const string citylist[]= {"A","B","C","D","E","F","G","H","I","J"};

#endif
