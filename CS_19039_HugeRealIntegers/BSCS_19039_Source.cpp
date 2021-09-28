#include "BSCS_19039_HugeRealIntegers.h"
#include<iostream>
#include<conio.h>
#include<fstream>


using namespace std;



int main()
{
	ifstream Rdr("BSCS_19039_Text.txt");
	int NOIs;
	Rdr >> NOIs;
	BSCS_19039_HugeRealIntegers* HIs = new BSCS_19039_HugeRealIntegers[NOIs];

	for (int i = 0; i < NOIs; i++)
	{
		Rdr >> HIs[i];
	}

	for (int i = 0; i < NOIs; i++)
	{
		cout << HIs[i] << endl << endl;
	}

//	cout << HIs[1].Trim() << endl << endl;
//	cout << HIs[0]+ HIs[1] << endl << endl;
	//cout << HIs[1] << HIs[0] << endl << endl;
	//cout << HIs[0] - HIs[1] << endl << endl;
//	cout << HIs[0] * HIs[1] << endl << endl;

	return _getch();
}



