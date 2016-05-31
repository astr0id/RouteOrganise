
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
	string currentCity;
	string nextCity;
	int timeleft;
	//int currentState;
	//1-waiting 2-traveling
	bool isTravel;
}PassengerData;

const string citylist[]= {"A","B","C","D","E","F","G","H","I","J"};


#endif
