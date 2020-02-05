#include<iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <cstring>
#include <chrono>
#include <vector>
#define HAVE_STRUCT_TIMESPEC
#include<pthread.h>
#include "md5.h"

using namespace std;
#define NUM_THREADS 20 //Define number of threads/workers

bool cracked = 0; //Flag for checking cracked condition
const string knownHashValue = "60d28e7d879c0dc48b9a593468cf11e5";  // MD5("Lion") = 60d28e7d879c0dc48b9a593468cf11e5
void CrackPass(vector<char> characterSet, string, const int, const int);
void *ThreadWorkers(void *);

class MyThreadClass
{
	public:
		int characterSet_len;//length of character set
		int pass_len;//Length of password to be checked, determined by the resource capabilities of the machine
		int t_start;//Starting index
		int t_end;//Ending Index
		vector<char>str;//Character Set containing all possible characters that can appear in a password
};
//Define a struct consisting of the above variables

int main()
{
	int characterSet_len = 95;//Consists of ASCII values from 32 to 127 (A-Z,a-z,0-9,Special Characters)
	vector<char> characterSet(characterSet_len);
	int pass_length = 8;//Max length of password that can be checked depending on the current resources
	
	for (char i = 0; i < characterSet_len; i++)
	{
		characterSet[(int)i] = i + 32;//Generate an array of ASCII values
		
	}
	
	pthread_t t[NUM_THREADS];// Declare number of threads to be spawned
	
	int chunkPerThread = characterSet_len / NUM_THREADS; //Divide the characterset into number of threads - DECOMPOSITION
	
	//cout << "Number of threads used to crack the password: " << NUM_THREADS<<endl;
	std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();//Start Recording time

	for (int i = 0; i < NUM_THREADS; i++)
	{
		
		class MyThreadClass *t_data = new class MyThreadClass;
		
		t_data->str = characterSet;
		t_data->characterSet_len = characterSet_len;
		t_data->pass_len = pass_length;
		t_data->t_start = chunkPerThread * i;//set start index per thread
		t_data->t_end = (i == NUM_THREADS - 1) ? characterSet_len : chunkPerThread * (i + 1);//set end index per thread
		
		pthread_create(&t[i], NULL, ThreadWorkers, (void *)t_data);//ASSIGNMENT - Spawn Threads
	}
	
	for (int i = 0; i < NUM_THREADS; i++)
	{
		pthread_join(t[i], NULL);//Join Threads
	}
	
	std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();//Stop Recording time
	cout << "Password found in " << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count() << "ms\n";
	
	return 0;
}

void *ThreadWorkers(void *args)
{
	class MyThreadClass *t_data = ( class MyThreadClass*)args;//Extract thread info from arguments
	int start = t_data->t_start; //Start index
	int end = t_data->t_end; // End Index
	
	for (int k = 1; k < t_data->pass_len; k++)//For every possible password length
	{
		for (int i = start; i < end; i++)//for every character assigned to the thread from the character set
		{
			string s(1,t_data->str[i]);//pick one starting character from the character set
			
			CrackPass(t_data->str,s, t_data->characterSet_len, k); //Try to find all combinations and check hash. Stop wehn found else return.
		}
	}
	return NULL;
}

void CrackPass(vector<char> characterSet,  string prefix, const int n, const int k)
{
	if (cracked)//Check if password is cracked then STOP
	{
		return;
	}
	
	else
	{
		if (prefix.length() < k)
		{
			for (int i = 0; i < n; i++)
			{
				CrackPass(characterSet, prefix + characterSet[i], n, k);// generate combinations recursively for each password length, k
				
			}
		}
		
		else if (prefix.length() == k)//check all combinations
		{	
			if ((md5(prefix)== knownHashValue))
			{
				cout << "Cracked Password: " << prefix << endl;
				cracked = 1;//Set flag to 1
				return;
			}
		}
		
		else
		{
			cout << "Not Crackable due to hardware limitations" << endl;
			return;
		}
	}
}