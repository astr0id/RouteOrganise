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


void Passenger::TimeBased(string start_city, string end_city)
{
	map<string, int> FinalRecord, TempFinalRecord;
	map<int, string> NewRecord;
	map<string, string> tempPath, Path;
	map<string, int>Index0;
	map<string, int>Index1;
	set<string> S;//set of visted node
	set<string> City(citylist, citylist + sizeof(citylist) / sizeof(*citylist));//set of unvisted nodes
	map<string, int> V;//result matrix
	map<string, int> ST;//record the start time
	map<string, int> RM;
	map<string, string>prev;//record previous node
	set<string>::iterator it;//set S or City 's iterator
	map<string, int>::iterator mapit;//map V 's iterator
	string minC;
	int min = 999;//intialize min to INFINITY

	for (it = City.begin(); it != City.end(); it++) //initialize
	{
		V.insert(pair<string, int>(*it, 1000));//set every node to start node 's distance is INFINITY
		ST[*it] = 999;//initialize all node's start time to INFINITY
		RM[*it] = 0;
	}
	mapit = V.find(start_city);//A can be replaced as the start city
	if (mapit != V.end())mapit->second = 0;//Set A to A 's distance to ZERO
	S.insert(start_city);//Put A into the set of visted
	City.erase(start_city);//Erase A from the set of unvisted
	ST[start_city] = starttime;//set start point's start time to STARTTIME
							   //0 is the default start time
	int round = 1;
	while (!City.empty())
	{

		//----ROUTECOUNT----
		// The number of paths between different pairs of CITYS like A->B A->C D->F

		//----rNUMBER----
		// The number of WAYS you can travel along A PATH like A ---5---> B

		//INTIALIZING LOOOOOOP
		//UPDATING ALL ADJACANT

		for (int i = 1; i <= routecount; i++)
		{

			if (S.count(Data[i].from))//All route from vertex in S
			{
				//cout<<"Starting City is"<<Data[i].from<<endl;
				for (int j = 0; j<Data[i].rNumber; j++) //for every route start from node Data[i]
				{
					//update map V
					//ESTABILISH  A  LEGAL ROUTE
					if (!S.count(Data[i].dest))
					{
						int est;
						est = Data[i].TB[j].arrival - ST[Data[i].from];
						if (Data[i].TB[j].start>Data[i].TB[j].arrival || Data[i].TB[j].start < ST[Data[i].from])est += 24;
						//if(est<OT[Data[i].dest])//the shortest available route
						if (est + V[Data[i].from] < V[Data[i].dest])
						{
							RM[Data[i].dest] = Data[i].TB[j].cost + RM[prev[Data[i].dest]];
							//OT[Data[i].dest] =  est;
							ST[Data[i].dest] = Data[i].TB[j].arrival;
							prev[Data[i].dest] = Data[i].from;
							Path[Data[i].dest] = Data[i].TB[j].name;
							Index0[Data[i].TB[j].name] = i;
							Index1[Data[i].TB[j].name] = j;
							V[Data[i].dest] = est + V[prev[Data[i].dest]];//distance + prev point's distance
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
		mapit = V.begin();
		for (; mapit != V.end(); mapit++)
		{

			if (!S.count(mapit->first))//find a node which isn't belongs to set S
			{
				if (V[mapit->first]<min)
				{
					minC = mapit->first;
					min = V[mapit->first];
				}
			}
		}

		min = 999;

		if (City.count(minC))
		{
			it = City.find(minC);
			S.insert(*it);
			City.erase(*it);
		}
		else
		{
			it = City.begin();
			S.insert(*it);
			City.erase(*it);
		}


	}

	string temp;
	temp = end_city;
	int j = 1;
	while (temp != start_city)
	{
		//cout<<temp<<"<-";
		temp = prev[temp];
		j++;
	}

	temp = end_city;
	while (temp != start_city)
	{
		FinalRecord[temp] = j--;
		temp = prev[temp];
	}

	cout << "FINAL TIME " << V[end_city] << endl;
	totaltime = V[end_city];
	//totalmoney = RM[];

	int RecNum = 0;
	TBlock TBtemp;
	for (int i = 0; i<13; i++)
	{
		if (FinalRecord[citylist[i]] != 0)
		{
			NewRecord[FinalRecord[citylist[i]]] = citylist[i];
			RecNum++;
		}
	}
	for (int i = 1; i <= RecNum; i++)
	{
		TBtemp.start = NewRecord[i];
		TBtemp.dest = NewRecord[i + 1];;
		TBtemp.from = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].start;
		TBtemp.arrival = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].arrival;
		TBtemp.cost = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].cost;
		TBtemp.id = Path[NewRecord[i + 1]];
		TBtemp.kind = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].kind;
		RouteStack.push(TBtemp);
	}

}

void Passenger::MoneyBased(string city_start, string city_end)
{
	map<int, string> NewRecord;
	map<string, int> FinalRecord;
	map<string, string> Path;
	map<string, int>Index0;
	map<string, int>Index1;
	int totaltime = 0, num = 1;
	set<string> S;
	set<string> City(citylist, citylist + sizeof(citylist) / sizeof(*citylist));//set of unvisted nodes
	map<string, int> V;
	map<string, int> ST;
	map<string, int>OT;
	map<string, int> RM;
	map<string, string>prev;
	set<string>::iterator it;
	map<string, int>::iterator mapit;
	string minC;
	int min = 32766;
	for (it = City.begin(); it != City.end(); it++)
	{
		V.insert(pair<string, int>(*it, 32767));
		RM[*it] = min;
		OT[*it] = 999;
		ST[*it] = 999;
	}
	mapit = V.find(city_start);
	if (mapit != V.end())mapit->second = 0;
	S.insert(city_start);
	City.erase(city_start);
	ST[city_start] = starttime;
	RM[city_start] = 0;
	while (!City.empty())
	{
		for (int i = 1; i <= routecount; i++)
		{

			if (S.count(Data[i].from))
			{
				for (int j = 0; j<Data[i].rNumber; j++)
				{
					if (!S.count(Data[i].dest))
					{
						int est;
						est = Data[i].TB[j].arrival - ST[Data[i].from];
						if (Data[i].TB[j].start>Data[i].TB[j].arrival || Data[i].TB[j].start < ST[Data[i].from])est += 24;
						prev[Data[i].dest] = Data[i].from;
						if (Data[i].TB[j].cost + V[prev[Data[i].dest]]<V[Data[i].dest] || (Data[i].TB[j].cost + V[prev[Data[i].dest]] == V[Data[i].dest]) && (est + OT[prev[Data[i].dest]] < OT[Data[i].dest]))
						{

							ST[Data[i].dest] = Data[i].TB[j].arrival;
							prev[Data[i].dest] = Data[i].from;
							Path[Data[i].dest] = Data[i].TB[j].name;
							Index0[Data[i].TB[j].name] = i;
							Index1[Data[i].TB[j].name] = j;
							V[Data[i].dest] = Data[i].TB[j].cost + V[prev[Data[i].dest]];
							OT[Data[i].dest] = est + OT[prev[Data[i].dest]];
						}

					}
				}
			}
		}
		mapit = V.begin();
		for (; mapit != V.end(); mapit++)
		{

			if (!S.count(mapit->first))//find a node which isn't belongs to set S
			{
				if (V[mapit->first]<min)
				{
					minC = mapit->first;
					min = V[mapit->first];
				}
			}
		}
		min = 32766;
		if (City.count(minC))
		{
			it = City.find(minC);
			S.insert(*it);
			City.erase(*it);
		}
		else
		{
			it = City.begin();
			S.insert(*it);
			City.erase(*it);
		}
	}
	string temp;
	temp = city_end;
	//cout<<"the route is : ";
	while (temp != city_start)
	{
		//cout<<temp<<"<-";
		temp = prev[temp];
		num++;
	}
	int j = num;
	temp = city_end;
	while (temp != city_start)
	{
		FinalRecord[temp] = j--;
		temp = prev[temp];
	}
	//cout<<city_start<<endl<<"total time is : "<<V[city_end]<<endl;
	totalmoney += V[city_end];

	int RecNum = 0;
	TBlock TBtemp;
	for (int i = 0; i<13; i++)
	{
		if (FinalRecord[citylist[i]] != 0)
		{
			NewRecord[FinalRecord[citylist[i]]] = citylist[i];
			RecNum++;
		}
	}
	for (int i = 1; i <= RecNum; i++)
	{
		TBtemp.start = NewRecord[i];
		TBtemp.dest = NewRecord[i + 1];;
		TBtemp.from = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].start;
		TBtemp.arrival = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].arrival;
		TBtemp.cost = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].cost;
		TBtemp.id = Path[NewRecord[i + 1]];
		TBtemp.kind = Data[Index0[Path[NewRecord[i + 1]]]].TB[Index1[Path[NewRecord[i + 1]]]].kind;
		RouteStack.push(TBtemp);
	}

}


extern DATA Data[1000];
extern int routecount;


bool Paseenger::stackcheck()
{
    stack<string> temp;
    bool flag=true;
    while(!CityStack.empty())
    {
        temp.push(CityStack.top());
        CityStack.pop();
    }
    while(!temp.empty())
    {
        if(inRoute.find(temp.top())!=inRoute.end())
            flag=true;
        else
            flag=false;

        CityStack.push(temp.top());
        temp.pop();
    }

    return flag;
}

void Passenger::findpath(string start,string destiny,int moneylimit,int timelimit,int curcost,int curtime,int starttime)
{
    //cout<<"start"<<start<<"     timelimit"<<timelimit<<endl;
    TBlock temp;
    //set<string>::iterator sit;
    //if it's out of bound,then don't travel any further
    if(curcost >= moneylimit && start != destiny)
        return ;
    if(curtime >= timelimit && start != destiny)
        return ;

    if(start==destiny)
    {
        //if(!stackcheck())return;
        if(curcost > moneylimit || curtime > timelimit)return;
        if(curcost < mincost)
        {
            mincost=curcost;
            //printstack(TStack);
            TData=TStack;
        }
        RDnum++;
        return ;
    }
    //deep-priority traverse
    pastcity.erase(start);
    for(int i=1; i<=routecount; i++)
    {
        if(Data[i].from == start && ( pastcity.find(Data[i].dest)!=pastcity.end() ) )//Don't go back
        {
            CityStack.push(Data[i].from);
            temp.start=Data[i].from;
            temp.dest=Data[i].dest;
            for(int j=0; j<=Data[i].rNumber; j++)
            {
                temp.from=Data[i].TB[j].start;
                temp.arrival=Data[i].TB[j].arrival;
                temp.id=Data[i].TB[j].name;
                temp.kind=Data[i].TB[j].kind;
                temp.cost=Data[i].TB[j].cost;
                int est;
                est=Data[i].TB[j].arrival-starttime;
                if(Data[i].TB[j].start < starttime || Data[i].TB[j].start > Data[i].TB[j].arrival)est+=24;

                TStack.push(temp);
                findpath(Data[i].dest,destiny,moneylimit,timelimit,curcost+Data[i].TB[j].cost,curtime+est,Data[i].TB[j].arrival);
                TStack.pop();
            }
            CityStack.pop();
        }
    }
    pastcity.insert(start);
    return ;
}
