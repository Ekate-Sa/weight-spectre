#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
using namespace std;


// vector's weight
int weight_vec(vector <bool> x)
{
	int w = 0;
	for (int i = 0; i < size(x); i++)
	{
		if (x[i] == 1) w++;
	}
	return w;
}

// XOR SUM
vector <bool> sum_xor(vector <bool> x1, vector <bool>  x2) 
{
	vector <bool> res;
	for (int i = 0; i < size(x1); i++)
	{
		res.push_back(x1[i] ^ x2[i]);
	}
	return res;
}

int main() 
{
	ifstream vec_file("vectors.txt") ;
	
	ofstream wei_file("weights.txt") ;
	wei_file.clear();
	
	
	vector <bool> vec;
	char ch;
	
	// initialisation of A	
	vector <vector <bool>> A;
	if (vec_file.is_open())
	{
		while (!vec_file.eof())
		{
			while ( ( (ch = vec_file.get()) != '\n') && (!vec_file.eof()) )
			{
				vec.push_back(ch-'0');	//add vector's element	
				
			}
			A.push_back(vec);
			vec = {};
		}
	}
	vec_file.close();				// vectors.txt no needed more
	
	// spectre vector initialization
	vector <int> spectre ; // may be N+1 weights: [0..N]

	for (int i = 0; i < (A[0].size()+1); i++)
	{
		spectre.push_back(0);
	}
	// "all zeros"
	spectre[0]=  1;

	// ALL POSSIBLE SUMMS
	vector <bool> temp_sum ;
	
	int j;
	for (int i = 1; i < pow( 2, A.size() ); i++) // SKIP "ALL ZEROS"
	{
		temp_sum = {};
		for (int k = 0; k < A[0].size(); k++)
		{
			temp_sum.push_back(0);
		}

		int number = i;
		
		j = 0;
		while (number) 
		{
			int rem = number % 2;
			
			if (rem)
			{
				temp_sum = sum_xor(temp_sum, A[j]);
			}
			j++;
			number = number / 2;
		}
		
		spectre[weight_vec(temp_sum)]++;
		
	}
	
	// print Spectre
	for (int i = 0; i < spectre.size(); i++)
	{
		wei_file << i << '\t' << spectre[i] << endl;
	}
	
	wei_file.close();
	return 0;
}

