#include <iostream>
#include <string.h>

#include "demo.h"

using namespace std;

int main()
{
	system("reset");
	FILE * fptr;
	string str;
	fptr= fopen ("./tb.txt","r");
	load(fptr);
	TimeBased();


	fclose (fptr);

	return 0;
}
