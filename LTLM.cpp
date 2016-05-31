#include <iostream>
#include <string>
#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <map>
#include <fstream>
#include "Datastruct.h"
#include "LTLM.h"


extern DATA Data[1000];
extern int routecount;
extern map<string, int> FinalRecord, TempFinalRecord;
extern map<string, string> Path, tempPath;
extern map<string, int>Index0;
extern map<string, int>Index1;

int temptime;

void LimittedTimeLeastMoney(int TotalTime, int Cur_time, int starttime, int LimittedTime, int &Money, string City_start, string City_end, int count, int &MinMoney, string via[]){
	int moneytemp , totaltimetemp ,  tempcount = count;
	int num = 0, k = 0;
	set<string> City(citylist, citylist + sizeof(citylist) / sizeof(*citylist));
	map<string, int>::iterator mapit;
	set<string>::iterator it, tempit;
	it = City.begin();
	if (TotalTime > LimittedTime);
	else if (City_start == City_end)//µΩ¥Ô÷’µ„
	{
		if (((Money == MinMoney) && (TotalTime < temptime)) || Money < MinMoney)
		{
			k = 0;
			for (; via[k] != ""; k++)
			{
				if (TempFinalRecord.find(via[k])->second)num++;
			}
			if (num == k)
			{
				Path = tempPath;
				FinalRecord = TempFinalRecord;
				MinMoney = Money;
				temptime = TotalTime;
			}
		}		
	}
	else
	{
		while (it != City.end())
		{
			mapit = TempFinalRecord.find(*it);
			if (!mapit->second)
			{
				TempFinalRecord.find(*it)->second = count++;
				for (int i = 1; i <= routecount; i++)
				{
					if (Data[i].from == City_start&&Data[i].dest == *it)
					{
						for (int j = 0; j < Data[i].rNumber; j++)
						{
								moneytemp = Money;
								totaltimetemp = TotalTime;
								Money += Data[i].TB[j].cost;
								if (Data[i].TB[j].start < Cur_time)
									TotalTime += Data[i].TB[j].arrival - Cur_time + 24;
								else
									TotalTime += Data[i].TB[j].arrival - Cur_time;
								Cur_time = (starttime + TotalTime) % 24;
								tempPath[Data[i].from] = Data[i].TB[j].name;
								Index0[Data[i].TB[j].name] = i;
								Index1[Data[i].TB[j].name] = j;
								LimittedTimeLeastMoney(TotalTime, Cur_time, starttime, LimittedTime, Money, *it, City_end, count, MinMoney,via);
								tempPath[Data[i].from] = "";
								Index0[Data[i].TB[j].name] = i;
								Index1[Data[i].TB[j].name] = j;
								Money = moneytemp;
								TotalTime = totaltimetemp;
								Cur_time = (starttime + TotalTime) % 24;
								
							//}
							
						}
						
					}	
					
				}
				count = tempcount;
				TempFinalRecord.find(*it)->second = 0;
			}
			it++;
		}

	}
}