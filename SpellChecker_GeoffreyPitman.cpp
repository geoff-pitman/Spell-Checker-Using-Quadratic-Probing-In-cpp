// Author: Geoffrey Pitman
// Course: CSC402 - 010 - Data Structures 2
// Intructor: Dr. Zhang
// Due: 10/24/2016
// Project: 3
// File: SpellChecker_GeoffreyPitman.cpp
// Purpose:  To demonstrate the use of hash-table data structure by;
//           1. creating a hashtable from a dictionary of words
//           2. outputing the table intialization stats
//			 3. spell checking user entered word
//           4. offering suggestions for misspelled words
#include <iostream>
#include "QuadraticProbing_GeoffreyPitman.h"
#include <fstream>
using namespace std;

int main( )
{
	HashTable<string> HT;
	double n = 0;

	ifstream inf;
    vector<string> list;
	string temp;
	inf.open("words.dat");
	
	for (int idx = 0; inf >> temp; idx++)
	{
		HT.insert(temp);
		list.push_back(temp);
		n++;
	}
	inf.close();
	 
	cout << endl;
	HT.printLoadFactor(n);
	HT.printCollisions();
	cout << "Done!" << endl << endl;
	
	while (true)
	{
		string choice = "";
		cout << "Enter a word for spell checking (enter done to exit):   ";
		cin >> choice;
		if (choice == "done")
			return 0;
		else if (HT.contains(choice))
			cout << "Correct!" << endl;
		else
		{
			vector<string> possible, wrong, missing;
			string build = "";
			
			//extra///////////////////////////////////////////
			for (int idx = 0; idx < choice.length(); idx++)
			{
				for (int ii = 0; ii < choice.length(); ii++ )
				{
					if(ii != idx )
						build += choice[ii];
				}
				if(HT.contains(build) )
				{
					bool check = true;
					for (int ii = 0; ii < possible.size(); ii++)
					{
						if (build == possible[ii])
							check = false;
					}
					if (check)
						possible.push_back(build);
				}
				build = "";
			}	
			///////////////////////////////////////////////////////
			
			//wrong //////////////////////////////////////////////
			for (int idx = 0; idx < choice.length(); idx++)
			{
				build = choice;
				for(int ii = 0; ii < 26; ii++)
				{
					build[idx] = 'a'+ii;
					wrong.push_back(build);
				}
				
			}
			for (int idx = 0; idx < wrong.size(); idx++)
			{
			    if(HT.contains(wrong[idx]) )
				{
					bool check = true;
					for (int ii = 0; ii < possible.size(); ii++)
					{
						if (wrong[idx] == possible[ii])
							check = false;
					}
					if (check)
						possible.push_back(wrong[idx]);
				}
			}
			//////////////////////////////////////////////////////////
			

			//missing//////////////////////////////////////////////////
			for (int idx = 0; idx <= choice.length(); idx++)
			{
				int count = 0;
				build = 'a' + choice;
				for (int ii = 0; ii < choice.length(); ii++)
				{
					if (ii == count)
					{
						ii--;
						count++;
					}
					else if (ii != idx)
						build[ii] = choice[ii];
				}
				for(int ii = 0; ii < 26; ii++)
				{
					build[idx] = 'a'+ii;
					missing.push_back(build);
				}

			}
			for (int idx = 0; idx < missing.size(); idx++)
			{
			    if(HT.contains(missing[idx]))
				{
					bool check = true;
					for (int ii = 0; ii < possible.size(); ii++)
					{
						if (missing[idx] == possible[ii])
							check = false;
					}
					if (check)
						possible.push_back(missing[idx]);
				}
			}
		
			/////////////////////////////////////////////////////////////////

			cout << "Wrong! Possible corrections:   ";
			for (int iii = 0; iii < possible.size(); iii++)
			{
				cout << possible[iii];
				
				if (iii != possible.size()-1)
					cout << " , ";
					
			}
			cout << endl;
		}	
		
	}

    return 0;
}