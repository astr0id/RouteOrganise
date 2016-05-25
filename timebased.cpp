#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include "Datastruct.h"
#include "timebased.h"
using namespace std;

extern DATA Data[1000];
extern int routecount;
void TimeBased(string city_start, string city_end, int &starttime, int &totaltime, int &totalmoney, string path[], int &num)
{
	set<string> S;//set of visted node
	set<string> City(citylist,citylist+sizeof(citylist)/sizeof(*citylist));//set of unvisted nodes
	map<string,int> V;//result matrix
	map<string,int> ST;//record the start time
	map<string,int> OT;//note that if there is an overnight wait
	map<string, int> RM;
	map<string,string>prev;//record previous node
	set<string>::iterator it;//set S or City 's iterator
	map<string,int>::iterator mapit;//map V 's iterator
	string minC;
	int min=999;//intialize min to INFINITY

	for (it=City.begin(); it!=City.end(); it++) //initialize
	{
		V.insert(pair<string,int>(*it,1000));//set every node to start node 's distance is INFINITY
		ST[*it]=999;//initialize all node's start time to INFINITY
		OT[*it]=999;//asume all node's not wait till next day
		RM[*it] = 0;
	}
	mapit=V.find(city_start);//A can be replaced as the start city
	if(mapit!=V.end())mapit->second=0;//Set A to A 's distance to ZERO
	S.insert(city_start);//Put A into the set of visted
	City.erase(city_start);//Erase A from the set of unvisted
	ST[city_start] = starttime;//set start point's start time to STARTTIME
	//0 is the default start time
	int round=1;
	while (!City.empty())
	{


		//----ROUTECOUNT----
		// The number of paths between different pairs of CITYS like A->B A->C D->F

		//----rNUMBER----
		// The number of WAYS you can travel along A PATH like A ---5---> B



		//INTIALIZING LOOOOOOP
		//UPDATING ALL ADJACANT

		for(int i=1; i<=routecount; i++)
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
						int est;
						est=Data[i].TB[j].arrival-ST[Data[i].from];
						if(Data[i].TB[j].start < ST[Data[i].from])est+=24;

						if(est<OT[Data[i].dest])//the shortest available route
						{
							RM[Data[i].dest] = Data[i].TB[j].cost;
							OT[Data[i].dest]=est;
							ST[Data[i].dest]=Data[i].TB[j].arrival;
							prev[Data[i].dest]=Data[i].from;
							V[Data[i].dest]=OT[Data[i].dest]+V[prev[Data[i].dest]];//distance + prev point's distance
							//finish updating a route
							//travel time = ST[dest]-ST[from];
							//Total time => while tracing back from the dest and cumulate each part's travel time
							//cout<<"UPDATE Route from "<<Data[i].from<<" to "<<Data[i].dest<<endl;
							//cout<<"Start at "<<Data[i].TB[j].start<<" Arive at "<<Data[i].TB[j].arrival<<endl;
							//cout<<"Distance is "<<V[Data[i].dest]<<endl;
						}
					}
				}
				
			}
		}

		//cout<<"Update Round "<<round++<<" Ends"<<endl;
		//cout<<endl<<endl<<endl;

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
			it=City.begin();
			S.insert(*it);
			City.erase(*it);
		}
		

		//cout<<"City include "<<endl;
		//for (it=City.begin(); it!=City.end(); it++) //initialize
		//{
		//	cout<<*it<<" ";//set every node to start node 's distance is INFINITY
		//}
		//cout<<endl;


	}
	
	//system("CLS");
	//mapit=V.begin();
	//for(; mapit!=V.end(); mapit++)
	//{
	//	cout<<mapit->first<<" is "<<mapit->second<<endl;
	//}
	string temp;
	temp=city_end;
	//cout<<"the route is : ";
	while(temp!=city_start)
	{
		//cout<<temp<<"<-";
		temp=prev[temp];
		num++;
	}
	int j = num;
	temp = city_end;
	while (temp != city_start)
	{
		path[j--] = temp;
		temp = prev[temp];
	}
	path[j] = city_start;
	//cout<<city_start<<endl<<"total time is : "<<V[city_end]<<endl;
	totalmoney += RM[city_end];
	totaltime += V[city_end];
}
