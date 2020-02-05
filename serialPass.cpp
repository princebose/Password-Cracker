
#include<iostream>
#include <chrono>
#include<vector>
#include<string>
#include "md5.h"
#define _CRT_SECURE_NO_WARNINGS
using namespace std;

const int num_char = 36;//Size of dataset
const string givenHash = "e934202c876b0eae99dc994a8d61a86e";//Password AAB




vector<string>data_set = { "A", "B" , "C", "D", "E", "F" , "G", "H", "I", "J", "K",
							"L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V",
							"W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7",
							"8", "9", "0" };//Data set to crack password alphanumeric only

int main()
{
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now(); // start timer
	for (int i = 0; i < num_char; i++) // For loop to generate combinations from the dataset and compare with md5 hash
	{
		string try1 = data_set[i];
		
		if (md5(try1) == givenHash)
		{
			cout << "match, password is: " << try1 << endl;
			break;
		}
		
		for (int j = 0; j < num_char; j++)
		{
			string try2 = try1 + data_set[j];
			
			if (md5(try2) == givenHash)
			{
				cout << "match, password is: " << try2 << endl;
				break;
			}
			for (int k = 0; k < num_char; k++)
			{
				string try3 = try2 + data_set[k];
				
				if (md5(try3) == givenHash)
				{
					cout << "match, password is: " << try3 << endl;
					break;
				}
				
				for (int l = 0; l < num_char; l++)
				{
					string try4 = try3 + data_set[l];
					
					if (md5(try4) == givenHash)
					{
						cout << "match, password is: " << try4 << endl;
						break;
					}
					
					for (int m = 0; m < num_char; m++)
					{
						string try5 = try4 + data_set[m];
						
						if (md5(try5) == givenHash)
						{
							cout << "match, password is: " << try5 << endl;
							break;
						}
						
						for (int n = 0; n < num_char; n++)
						{
							string try6 = try5 + data_set[n];
							
							if (md5(try6) == givenHash)
							{
								cout << "match, password is: " << try6 << endl;
								break;
							}
							
						}
					}
				}

			}
		}
	}



	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now(); //stop the timer and calculate  time
	cout << "Password found in "
		<< std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms"<<endl;


	return 0;
}