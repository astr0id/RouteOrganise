
#ifndef DATASTRUCT_H
#define DATASTRUCT_H

using namespace std;

struct timetable
{
	int start;
	int arrival;
	int cost;
	string kind;
	string name;
};

typedef struct
{
	string from;
	string dest;
	int rNumber;//Records the number of routes between two citys
	timetable TB[30];
} DATA;

typedef struct 
{
	string start;
	string dest;
	timetable TB;
}RouteData;

const string citylist[]= {"A","B","C","D","E","F","G","H","I","J"};


#endif
