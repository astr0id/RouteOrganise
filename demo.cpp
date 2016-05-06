#include <iostream>
#include <string.h>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>

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

void load(FILE *);
void output(string);

void Dijkstra();

int main()
{
	//system("clear");
	FILE * fptr;
	string str;
	fptr= fopen ("./tb.txt","r");
	load(fptr);
	Dijkstra();


	fclose (fptr);

	return 0;
}


const string citylist[]= {"A","B","C","D","E","F","G","H","I","J"};
void Dijkstra()
{
	set<string> S;//set of visted node
	set<string> City(citylist,citylist+sizeof(citylist)/sizeof(*citylist));//set of unvisted nodes
	map<string,int> V;//result matrix
	map<string,int> ST;//record the start time
	//map<string,map<string,int>>matrix;//w[][] ?? i don't know should i use it ?????AHHHHHHHHHHHHHHHHHHHHHHHHHHHHHHH FUUUUUUUUUUUUUUCK
	map<string,string>prev;//record previous node
	set<string>::iterator it;//set S or City 's iterator
	map<string,int>::iterator mapit;//map V 's iterator
	string minC;
	int min=999;//intialize min to INFINITY

	for (it=City.begin(); it!=City.end(); it++) //initialize
	{
		V.insert(pair<string,int>(*it,1000));//set every node to start node 's distance is INFINITY
		ST[*it]=999;//initialize all node's start time to INFINITY
	}
	mapit=V.find("A");//A can be replaced as the start city
	if(mapit!=V.end())mapit->second=0;//Set A to A 's distance to ZERO
	S.insert("A");//Put A into the set of visted
	City.erase("A");//Erase A from the set of unvisted
	ST["A"]=0;//set start point's start time to STARTTIME
	//0 is the default start time
	int round=1;
	while (!City.empty())
	{
		//Extract Min
		//
		//Step 1:
		//	intialize map V : for each node in S act as the start point, reach the direct nodes and update map V with the shortest time
		//					  (in the initialize step, there's only a start node in S)
		//Step 2:
		//	Update map V:	1.for each node in City , we find the closet node  (let's call it )C to any node in set S,
		//					then add it to set S and remove it from set City
		//					(Through Step 1, we can find out the closest node to the set S)
		//					2.for each node can be reached from node C , if the distance can be reduced by bypass node C
		//					so update the distance with d[C]+d[C][v]
		//

		//----ROUTECOUNT----
		// The number of paths between different pairs of CITYS like A->B A->C D->F

		//----rNUMBER----
		// The number of WAYS you can travel along A PATH like A ---5---> B



		//INTIALIZING LOOOOOOP
		//UPDATING ALL ADJACANT

		for(int i=0; i<routecount; i++)
		{

			if(S.count(Data[i].from))//All route from vertex in S
			{
				//cout<<"Starting City is"<<Data[i].from<<endl;
				for(int j=0; j<Data[i].rNumber; j++) //for every route start from node Data[i]
				{
					//update map V
					//ESTABILISH  A  LEGAL ROUTE
					if(!S.count(Data[i].dest))
					{
						if(Data[i].TB[j].arrival<ST[Data[i].dest] && Data[i].TB[j].start >= ST[Data[i].from] )//the shortest available route
						{
							ST[Data[i].dest]=Data[i].TB[j].arrival;
							prev[Data[i].dest]=Data[i].from;
							V[Data[i].dest]=ST[Data[i].dest]-ST[Data[i].from]+V[prev[Data[i].dest]];//distance + prev point's distance
							//finish updating a route
							//travel time = ST[dest]-ST[from];
							//Total time => while tracing back from the dest and cumulate each part's travel time
							cout<<"UPDATE Route from "<<Data[i].from<<" to "<<Data[i].dest<<endl;
							cout<<"Start at "<<Data[i].TB[j].start<<" Arive at "<<Data[i].TB[j].arrival<<endl;
							cout<<"Distance is "<<V[Data[i].dest]<<endl;
						}
					}

				}
			}
		}

		cout<<"Update Round "<<round++<<" Ends"<<endl;
		cout<<endl<<endl<<endl;

		//finish updating node's data
		//------------------------------
		//start selecting and add new node to set S
		//find the node which is the closest to the root
		mapit=V.begin();
		for(; mapit!=V.end(); mapit++)
		{
			
			if(!S.count(mapit->first))//find a node which isn't belongs to set S
			{
				if(V[mapit->first]<min)
				{
					minC=mapit->first;
					min=V[mapit->first];
				}
			}
		}

		min=999;
		
		if(City.count(minC))
		{
			it=City.find(minC);
			S.insert(*it);
			City.erase(*it);
		}
		else
		{
			it=City.find("J");
			S.insert(*it);
			City.erase(*it);
		}
		

		cout<<"City include "<<endl;
		for (it=City.begin(); it!=City.end(); it++) //initialize
		{
			cout<<*it<<" ";//set every node to start node 's distance is INFINITY
		}
		cout<<endl;


	}
	
	system("CLS");
	mapit=V.begin();
	for(; mapit!=V.end(); mapit++)
	{
		cout<<mapit->first<<" is "<<mapit->second<<endl;
	}
	
}

void load(FILE * fptr)
{
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
	}
}
