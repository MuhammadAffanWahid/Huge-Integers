#include "BSCS_19039_HugeRealIntegers.h"
#include<string.h>
using namespace std;


                                                                                                                                      //    Trim
BSCS_19039_HugeRealIntegers BSCS_19039_HugeRealIntegers:: Trim()
{
	int len = 0,Dlen=0;
	BSCS_19039_HugeRealIntegers Dummy;
	 len = CalculateZeros(*this);
	 Dlen = CalculateDecimalZeros(*this);

	 if (Size - Dlen-1 == PointIndex)
		Dlen++;
	if (Size - len != 0)
	{
		Dummy.PointIndex = PointIndex-len;
		Dummy.Sign = Sign;
		Dummy.Size = this->Size - len-Dlen;
		Dummy.Ds = new int[Dummy.Size];      // Removing Left and Right Zeros and also Removing Point if all decimal values are zero.
		for (int i = 0; i < Dummy.Size; i++)
		{
			Dummy.Ds[i] = Ds[i + Dlen];
		}
	}
	//else
	//{
	//	Dummy.Size = this->Size;
	//	Dummy.Ds = new int[Dummy.Size];
	//	for (int i = 0; i < Dummy.Size; i++)
	//	{
	//		Dummy.Ds[i] = Ds[i];
	//	}
	//	/*Dummy.Size = 1;
	//	Dummy.Ds = new int[Dummy.Size];
	//	Dummy.Ds[0] =0;*/
	//}
	* this = Dummy;
	return Dummy;
}
                                                                                                                                      //    Load
void BSCS_19039_HugeRealIntegers::Load(ifstream& Rdr)
{
	string s;
	Rdr >> Sign;
	Rdr >> s;
	Size = s.length();
	Ds = new int[Size];
	int j = 0;

	for (int i = 0; i < Size; i++)
	{
		
		if (((int)s[i]-48) == -2)
		{
			PointIndex = i;
			//j++;
		}
		/*	else*/
		{
			int k = ((int)s[i] - 48);
			Ds[Size - j - i - 1] = k;
		}
	}
	//if (j == 0)
	//{
	//	PointIndex = Size;
	//}
	*this = (*this).Trim();
}
                                                                                                                                      //    <<
ostream& operator<<(ostream&, const BSCS_19039_HugeRealIntegers& H)
{
	cout << H.PointIndex+1<<endl<<endl;
	cout << H.Sign;
	for (int i = 0; i < H.Size; i++)
	{
		if (H.Ds[H.Size - i - 1] == -2)
			cout << ".";
		else
		{
			cout << H.Ds[H.Size - i - 1];
			/*if (H.Size - i - 1 == H.PointIndex)
				cout << ".";*/
		}
    }
	
	return cout;
}
                                                                                                                                      //    >>
ifstream& operator>>(ifstream& Rdr, BSCS_19039_HugeRealIntegers& H)
{
	H.Load(Rdr);
	return Rdr;
}
                                                                                                                                      //    +

                                                                                                                                      

/*





void operator=(const BSCS_19039_HugeRealIntegers& H2)
{
	Sign = H2.Sign;
	Size = H2.Size;
	Ds = new int[Size];
	for (int i = 0; i < H2.Size; i++)
	{
		Ds[i] = H2.Ds[i];
	}
}



bool operator==(const BSCS_19039_HugeRealIntegers& H2)
{
	if (Size != H2.Size)
		return 0;
	if (Sign != H2.Sign)
		return 0;
	for (int i = 0; i < Size; i++)
	{
		if (Ds[i] != H2.Ds[i])
			return 0;
	}
	return 1;
}



*/