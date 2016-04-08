#include <iostream>
#include <string>
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
}DATA;

DATA Data[1000];
int routecount;

void load(FILE *);
void output(string);

void Dijkstra();

int main()
{
	system("clear");
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
void Dijkstra()
{
	set<string> Q,S;
	set<string>::iterator it;
	  

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
