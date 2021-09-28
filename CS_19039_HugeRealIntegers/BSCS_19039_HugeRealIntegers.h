#pragma once
#include<iostream>
#include<conio.h>
#include<fstream>
using namespace std;
class BSCS_19039_HugeRealIntegers
{
	private:
		int* Ds;
		int  PointIndex;
		int  Size;
		char Sign;
	public:
		void Load(ifstream& Rdr);
		BSCS_19039_HugeRealIntegers Trim();
		friend ostream& operator<<(ostream&, const BSCS_19039_HugeRealIntegers& H);
		friend ifstream& operator>>(ifstream& Rdr, BSCS_19039_HugeRealIntegers& H);
		
		BSCS_19039_HugeRealIntegers(ifstream& Rdr);
		BSCS_19039_HugeRealIntegers()
		{
			this->Ds = nullptr;
			/*this->Ds = new int[1];
			this->Size = 1;
			Ds[0] = 0;*/
		}
		BSCS_19039_HugeRealIntegers(int s)
		{
			Sign = '+';
			Size = s;
			Ds = new int[Size];
		}
	/*	BSCS_19039_HugeRealIntegers(int s, int n)
		{
			this->Ds = new int[s];////////////////////////////////////////////////////////////////////////////////////////////////////////////
			this->Size = s;
			Ds[0] = n;
		}*/
		BSCS_19039_HugeRealIntegers(const BSCS_19039_HugeRealIntegers& H2)
		{
			Size = H2.Size;
			Sign = H2.Sign;
			PointIndex = H2.PointIndex;
			Ds = new int[Size];
			for (int i = 0; i < Size; i++)
			{
				Ds[i] = H2.Ds[i];
			}
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		
		int CalculateZeros(BSCS_19039_HugeRealIntegers H)
		{
			int Len = 0;
			for (int i = 0; i < Size; i++)
			{
				if (this->Ds[Size - i - 1] == 0)
				{
					Len++;                           //         Counting Left Zeros
				}
				else
					break;
			}
			return Len;
		}

		int CalculateDecimalZeros(BSCS_19039_HugeRealIntegers H)
		{
			int Dlen = 0;
			for (int i = 0; i < Size; i++)
			{
				if (this->Ds[i] == 0)
				{
					Dlen++;                          //         Counting Right Zeros
				}
				else
					break;
			}
			return Dlen;
		}

		void AddZeros(BSCS_19039_HugeRealIntegers H,int Zeros)
		{
			BSCS_19039_HugeRealIntegers Dummy(Size + Zeros);
			Dummy.Sign = H.Sign;
			for (int i = 0; i < Size+Zeros; i++)
			{
				if (i > Size)
				{
					Dummy.Ds[i] = 0;
				}
				else
				{
					Dummy.Ds[i] = H.Ds[i-Zeros];
				}
			}
			H = Dummy;
			cout << H << endl;//////////////////////
		}

		void AddDecimalZeros(BSCS_19039_HugeRealIntegers H, int DZeros)
		{
			BSCS_19039_HugeRealIntegers Dummy(Size + DZeros);
			Dummy.Sign = H.Sign;
			for (int i = 0; i < Size + DZeros; i++)
			{
				if (i < DZeros)
				{
					Dummy.Ds[i] = 0;
				}
				else
				{
					Dummy.Ds[i] = H.Ds[i - DZeros];
				}
			}
			H = Dummy;
			cout << H << endl;////////////
		}

		void SynchronizePoint(BSCS_19039_HugeRealIntegers H1, BSCS_19039_HugeRealIntegers H2)
		{
			int S1 = H1.PointIndex;
			int DS1 = H1.Size- H1.PointIndex;

			int S2 = H2.PointIndex;
			int DS2 = H2.Size - H2.PointIndex;

			if (S1 > S2)
			{
				AddZeros(H2,S1-S2);
			}
			else if (S1 < S2)
				{
				   AddZeros(H1, S2 -S1);
			    }
			if (DS1 > DS2)
			{
				AddDecimalZeros(H2, DS1 - DS2);
			}
			else if (DS1 < DS2)
			{
				AddDecimalZeros(H1, DS2 - DS1);
			}
		}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		BSCS_19039_HugeRealIntegers operator+(BSCS_19039_HugeRealIntegers H2)
		{
			SynchronizePoint(*this, H2);
			
			BSCS_19039_HugeRealIntegers R;
			if (Sign == H2.Sign)
			{
				if (*this > H2)

				{
					R = this->Add(H2);
				}
				else
				{
					R = H2.Add(*this);
				}
				R.Sign = H2.Sign;
			}
			else
			{
				if (*this>H2)
				{
					R = this->subtract(H2);
					R.Sign = this->Sign;
				}
				else
				{
					R = H2.subtract(*this);
					R.Sign = H2.Sign;
				}

			}

		//	R.Sign = '-';
			return R.Trim();

		}

		//BSCS_19039_HugeRealIntegers operator-(const BSCS_19039_HugeRealIntegers& H2)const
		//{
		//	BSCS_19039_HugeRealIntegers H3 = H2;
		//	H3.Sign = !H2.Sign;
		//	return *this + H3;
		//}

		 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		 BSCS_19039_HugeRealIntegers subtract(const BSCS_19039_HugeRealIntegers& H2)const
		 {
			 BSCS_19039_HugeRealIntegers R(Size);
			 int Carry = 0;
			 for (int i = 0; i < R.Size; i++)
			 {
				 if (i != PointIndex)
				 {
					 R.Ds[i] = (((*this).Ds[i]) - H2.Ds[i] - Carry);
					 if (R.Ds[i] < 0)
					 {
						 Carry = 1;
						 R.Ds[i] += 10;
					 }
					 else
					 {
						 Carry = 0;
					 }
				 }
			 }

			 return R;
		 }

		 BSCS_19039_HugeRealIntegers Add(const BSCS_19039_HugeRealIntegers& H2)const
		 {
			 BSCS_19039_HugeRealIntegers R(Size + 1);
			 int Carry = 0;
			 for (int i = 0; i < R.Size; i++)
			 {
				 if (i != PointIndex)
				 {
					 R.Ds[i] = (((*this).Ds[i]) + H2.Ds[i] + Carry) % 10;
					 Carry   = ((*this).Ds[i] + H2.Ds[i] + Carry) / 10;
				 }
			 }

			 return R;
		 }














		 //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		bool operator!=(const BSCS_19039_HugeRealIntegers& H2)
		{
			return !(*this == H2);
		}

		bool operator<=(BSCS_19039_HugeRealIntegers H2)
		{
			return (*this < H2 || *this == H2);
		}
		
		bool operator>=(BSCS_19039_HugeRealIntegers H2)
		{
			return (*this > H2 || *this == H2);
		}


		bool operator==(const BSCS_19039_HugeRealIntegers& H2)
		{
			return ((*this) < H2 || (*this)>H2);
			return 0;
			return 1;
		}

		bool operator<(BSCS_19039_HugeRealIntegers H2)                               
		{
			return H2>(*this);
		}

	     bool operator>(const BSCS_19039_HugeRealIntegers& I2)
		{
			if (Sign == '+' && I2.Sign == '-')
				return 1;
			if (Sign == '-' && I2.Sign == '+')
				return 0;
			if (Sign == '+' && I2.Sign == '+')
			{
				if (PointIndex > I2.PointIndex)
					return 1;
				if (PointIndex < I2.PointIndex)
					return 0;

				for (int i = 0; i < Size; i++)
				{
					if (i != PointIndex)
					{
						if ((*this).Ds[Size - i - 1] > I2.Ds[Size - i - 1])
							return 1;
						if ((*this).Ds[Size - i - 1] < I2.Ds[Size - i - 1])
							return 0;
					}
				}
				return 0;
			}
			if (Sign == '-' && I2.Sign == '-')
			{
				if (PointIndex < I2.PointIndex)
					return 1;
				if (PointIndex > I2.PointIndex)
					return 0;

				for (int i = 0; i < Size; i++)
				{
					if (i != PointIndex)
					{
						if ((*this).Ds[Size - i - 1] < I2.Ds[Size - i - 1])
							return 1;
						if ((*this).Ds[Size - i - 1] > I2.Ds[Size - i - 1])
							return 0;
					}
				}
				return 0;
			}
		}
	



};

