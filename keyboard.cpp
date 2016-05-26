#include <iostream>

#include "keyboard.h"
#include "moneybased.h"
#include "timebased.h"

using namespace std;

void keyboard()
{
	string start, end, via[50];
	string temp;
	string path[50];
	int city_via = 0, totaltime = 0, num = 1, time = 0, day = 0, totalmoney = 0, starttime = 0;
	cout << "where to start ?" << endl;
	cin >> start;
	cout << "where to go ?" << endl;
	cin >> end;
	cout << "when to go ?" << endl;
	cin >> starttime;
	cout << "how many country do you want to pass through?" << endl;
	cin >> city_via;
	if (city_via)
	{
		cout << "where to pass through?" << endl;
		for (int i = 1; i <= city_via; i++)
		{
			cin >> via[i];
			cout << " ";
		}
	}
	int choice;
	cout<<"Fast or Cheap"<<endl;
	cin>>choice;
	time = starttime;
	via[0] = start;
	via[city_via + 1] = end;
	cout << "the route is : ";
	for (int i = 0; i < city_via + 1; i++)
	{
		if (i)cout << "->";
		if(choice)
			TimeBased(via[i], via[i + 1], time, totaltime,totalmoney, path, num);
		else
			MoneyBased(via[i], via[i + 1], time, totaltime, totalmoney, path, num);
		for (int j = 1; j <= num; j++)
		{
			if (i&&j == 1)continue;
			cout << path[j];
			if (j != num)
				cout << "->";
		}
		time += totaltime;
		totaltime = 0;
		num = 1;
	}
	cout << endl << "total time is : " << time - starttime << endl;
	cout << "total money is:" << totalmoney<<endl;
}