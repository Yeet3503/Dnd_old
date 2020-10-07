// Dnd.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

using namespace std;

static string GlobalProfs[18] = { "Athletics","Acrobatics","Sleight of Hand","Stealth","Arcana","History","Investigation","Nature","Religion","Animal Handling","Insight","Medicine","Perception","Survival","Deception","Intimidation","Performance","Persuasion" };

class Class
{
public:
	int HitDice = 10;
	int Level = 10;
	string fname = "Null";


	void GetFeatures()
	{
		system("cls");
		ifstream file;
		string line;
		vector< string > lines;
		file.open(fname);
		while (getline(file, line))
		{
			lines.push_back(line);
		}
		for (int i = 0; i < lines.size(); i++)
		{
			cout << lines[i] << "\n";
		}
	}
};

class Character
{
public:
	string Name;
	Class Cl;
	// str, dex, con, int, wis, cha
	int Stats[6];

	// current health, max health
	int Health[2] = {Cl.HitDice,Cl.HitDice};

	// action, bonus action, reaction
	bool Actions[3] = { true,true,true };

	// prof bonus
	int prof = 2;

	//                0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
	//				  Athl Acro Slei Stea Arca Hist Inve Natu Reli Anim Insi Medi Perc Surv Dece Inti Perf Pers
	int profs[18] = { 0,   1,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	
	int * CalcMods(int stat[])
	{
		// str, dex, con, int, wis, cha
		static int mods[6] = { 0, 0, 0, 0, 0, 0 };
		int *ip = mods;
		for (int i = 0; i <	6; i++)
		{
			ip[i] = floor((stat[i] - 10)/2);
			mods[i] = ip[i];
		}
		return mods;
	}

	void LevelUp(int times)
	{
		for (int i = 0; i < times; i++)
		{
			//todo: health up, prof bonus, spell slots*/spells, features
			Cl.Level++;
			//health up
			Health[0] += Cl.HitDice / 2 + 1;
			Health[1] += Cl.HitDice / 2 + 1;

			//prof bonus
			prof = floor((Cl.Level - 1) / 4) + 2;
		}
	}

	void PrintSkills()
	{
		system("cls");
		for (int i = 0; i < *(&profs + 1) - profs; i++)
		{
			//print prof name
			cout << GlobalProfs[i] << ": ";
			if (profs[i] == 0)
			{
				cout << "[ ]\n";
			}
			else if (profs[i] == 1)
			{
				cout << "[P]\n";
			}
			else if (profs[i] == 2)
			{
				cout << "[E]\n";
			}
		}
	}

	void PrintStats()
	{
		system("cls");
		cout << "Name: " << Name << "\n";
		cout << "Level: " << Cl.Level << "\n";
		cout << "Health: " << Health[0] << "/" << Health[1] << "\n";
		int *mods = CalcMods(Stats);

		for (int i = 0; i < *(&Stats + 1) - Stats; i++)
		{
			string StatNames[6] = { "str: ","dex: ","con: ","int: ","wis: ","cha: " };
			mods[i] = mods[i];
			cout << StatNames[i] + to_string(Stats[i]) << " +" << mods[i] <<  "\n";
		}

		//Actions
		for (int i = 0; i < 3; i++)
		{
			if (Actions[i])
			{
				switch (i)
				{
				case 0:
					cout << "A [o]  ";
					break;
				case 1:
					cout << "BA [o]  ";
					break;
				case 2:
					cout << "R [o]\n";
					break;
				}
			}
			else
			{
				switch (i)
				{
				case 0:
					cout << "A [ ]  ";
					break;
				case 1:
					cout << "BA [ ]  ";
					break;
				case 2:
					cout << "R [ ]\n";
					break;
				}
			}
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

	bool done = false;

	while (!done)
	{
		string command = "none";

		cin >> command;

		if (command == "char" || command == "sheet")
		{
			//character sheet
			uno.PrintStats();
		}
		else if (command == "skills" || command == "abilities")
		{
			//show skills and proficiencies
			uno.PrintSkills();
		}
		else if (command == "levelup" || command == "level")
		{
			cout << "# of times: ";
			cin >> command;
			uno.LevelUp(stoi(command));
		}
		else if (command == "feats" || command == "features")
		{
			uno.Cl.fname = "figher.txt";
			uno.Cl.GetFeatures();
		}
		else
		{
			uno.PrintStats();
		}
	}
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
