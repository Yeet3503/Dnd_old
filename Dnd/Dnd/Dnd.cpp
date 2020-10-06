// Dnd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>

using namespace std;

class Class
{
public:
	int HitDice = 1;
	int Level = 1;
};


class Character
{
public:
	string Name;
	Class Cl;
	int Stats[6];

	int calcmods(int stat[6])
	{
		for (int i = 0; i < *(&stat + 1) - stat; i++)
		{
			cout << i << endl;
		}
	}

	void PrintStats()
	{
		cout << "Name: " << Name << endl;
		cout << "Level: " << Cl.Level << endl;

		for (int i = 0; i < *(&Stats + 1) - Stats; i++)
		{
			cout << Stats[i] << endl;
		}
	}
};


int main()
{
	Character uno;
	for (int i = 10; i < 16; i++)
	{
		uno.Stats[i - 10] = i;
	}
	uno.Name = "test";
	Class pog;
	uno.Cl = pog;

	uno.PrintStats();

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
