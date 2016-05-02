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
//Psedocode
/*
function Dijkstra(G, w, s)
    for each vertex v in V[G]                        // 初始化
    previous[v] := undefined                         // 各点的已知最短路径上的前趋都未知
    d[s] := 0                                              // 因为出发点到出发点间不需移动任何距离，所以可以直接将s到s的最小距离设为0
    S := empty set
    while Q is not an empty set                      // Dijkstra演算法主體
    	u := Extract_Min(Q)
    S.append(u)
    for each edge outgoing from u as (u,v)
        if d[v] > d[u] + w(u,v)             // 拓展边（u,v）。w(u,v)为从u到v的路径长度。
            d[v] := d[u] + w(u,v)               // 更新路径长度到更小的那个和值。
        	previous[v] := u
*/
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
	}
	mapit=V.find("A");//A can be replaced as the start city
	if(mapit!=V.end())mapit->second=0;//Set A to A 's distance to ZERO
	S.insert("A");//Put A into the set of visted
	City.erase("A");//Erase A from the set of unvisted
	ST["A"]=0;//set start point's start time to STARTTIME
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

		//for each vertex in set S
		cout<<"Break AT "<<endl;
		for(int i=0; i<routecount; i++) //find next Timetable
		{

			if(S.count(Data[i].from))//All route from vertex in S
			{
				cout<<"we found "<<Data[i].from<<endl;
				int temp=999;
				for(int j=0; j<Data[i].rNumber; j++) //for every route start from node Data[i]
				{
					//update map V
					if(temp>Data[i].TB[j].arrival-Data[i].TB[j].start && Data[i].TB[j].start>ST[Data[i].from])//the shortest available route
					{
						temp=Data[i].TB[j].arrival-Data[i].TB[j].start;
						ST[Data[i].dest]=Data[i].TB[j].arrival;
						cout<<"UPDATE Route from "<<Data[i].from<<" to "<<Data[i].dest<<endl;
					}

					//Currently we don't consider overnight route
					//And select the closest node
					if(Data[i].TB[j].arrival-Data[i].TB[j].start<min && Data[i].TB[j].arrival-Data[i].TB[j].start>0 && Data[i].TB[j].start>ST[Data[i].from])
					{
						minC=Data[i].dest;//record the closest node
					}
				}
				V[Data[i].dest]+=temp;//update the map V(initialize)
			}
		}

		min=999;
		it=City.find(minC);
		S.insert(*it);
		City.erase(*it);
		//Update d[u]

		cout<<"City include "<<endl;
		for (it=City.begin(); it!=City.end(); it++) //initialize
		{
			cout<<*it<<" ";//set every node to start node 's distance is INFINITY
		}
		cout<<endl;


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
