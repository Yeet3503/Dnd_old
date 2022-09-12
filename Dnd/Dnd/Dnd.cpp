// Dnd.cpp : This file contains the 'main' function. Program execution begins and ends there.


#include <iostream>
#include <algorithm>
#include <cctype>
#include <string>
#include <map>
#include <vector>
#include <stdio.h>
#include <stdlib.h>     
#include <time.h>       

#include "fighterMain.h"
#include "warlockMain.h"

using namespace std;

static string GlobalProfs[18] = { "Athletics","Acrobatics","Sleight of Hand","Stealth","Arcana","History","Investigation","Nature","Religion","Animal Handling","Insight","Medicine","Perception","Survival","Deception","Intimidation","Performance","Persuasion" };

// num D dtype + mod , adv: 1, none: 0, disadv: -1
vector<vector<int>> roll(int num, int dtype, int mod, int advnum)
{
	vector<vector<int>> retval(2,vector<int>());
	int total1 = 0;
	int total2 = 0;
	switch(advnum)
	{
	case 0:
		for (int n = 0; n < num; n++)
		{
			int roll = rand() % dtype;
			total1 += roll;
			retval[0].push_back(roll);
		}
		total1 += mod;
		retval[0].insert(retval[0].begin(), total1);
		break;
	case 1:
		for (int n = 0; n < num; n++)
		{
			int roll = rand() % dtype;
			retval[0].push_back(roll);
			total1 += roll;
		}
		for (int n = 0; n < num; n++)
		{
			int roll = rand() % dtype;
			retval[1].push_back(roll);
			total2 += roll;
		}
		total1 += mod;
		total2 += mod;
		retval[0].insert(retval[0].begin(), total1);
		retval[1].insert(retval[1].begin(), total2);
		//max(total1, total2);
		if (total1 < total2)
		{
			iter_swap(retval.begin(), retval.begin() + 1);
		}
		break;
	case -1:
		for (int n = 0; n < num; n++)
		{
			int roll = rand() % dtype + mod;
			retval[0].push_back(roll);
			total1 += roll;
		}
		for (int n = 0; n < num; n++)
		{
			int roll = rand() % dtype;
			retval[1].push_back(roll);
			total2 += roll;
		}
		total1 += mod;
		total2 += mod;
		retval[0].insert(retval[0].begin(), total1);
		retval[1].insert(retval[1].begin(), total2);
		if (total1 > total2)
		{
			iter_swap(retval.begin(), retval.begin() + 1);
		}
	}
	return retval;
}

class Character
{
public:
	string Name;
	int totallevels = 1;
	vector<vector<string>>classLevels;

	vector<string> allfeats;

	// str, dex, con, int, wis, cha
	int Stats[6];

	// current health, max health
	int Health[2] = {0,0};

	// action, bonus action, reaction
	bool Actions[3] = { true,true,true };

	// prof bonus
	int prof = 2;

	//                0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
	//				  Str  Dex  -    -    Int  -    -    -    -    Wis  -    -    -    -    Cha  -    -    -
	//				  Athl Acro Slei Stea Arca Hist Inve Natu Reli Anim Insi Medi Perc Surv Dece Inti Perf Pers
	int profs[18] = { 0,   1,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	
	vector<int> CalcMods(int stat[])
	{
		// str, dex, con, int, wis, cha
		vector<int> mods = { 0, 0, 0, 0, 0, 0 };
		//int *ip = mods;
		for (int i = 0; i <	6; i++)
		{
			mods[i] = floor((stat[i] - 10)/2);
			//mods[i] = ip[i];
		}
		return mods;
	}

	void InitClass(vector<string> input, int ClassID)
	{
		// set class name & level
		classLevels.push_back(vector<string>{"1", input[0], input[1]});
		//classLevels[ClassID][0] = 1;        //level
		//classLevels[ClassID][1] = input[0]; //hitdice
		//classLevels[ClassID][2] = input[1]; //name
		//health
		int hd = stoi(input[1]);
		Health[0] = hd + CalcMods(Stats)[2];
		Health[1] = hd + CalcMods(Stats)[2];
		vector<string> skls = { "Athl", "Acro", "Slei", "Stea", "Arca", "Hist", "Inve", "Natu", "Reli", "Anim", "Insi", "Medi", "Perc", "Surv", "Dece", "Inti", "Perf", "Pers" };
		for (int i = 2; i < input.size(); i++)
		{
			if (input[i].substr(0, 3) == "skl")
			{
				profs[find(skls.begin(), skls.end(), input[i].substr(3, 4)) - skls.begin()] = 1;
			}
			else if (input[i].substr(0, 3) == "exp")
			{
				profs[find(skls.begin(), skls.end(), input[i].substr(3, 4)) - skls.begin()] = 2;
			}
			else if (input[i].substr(0, 3) == input[0].substr(0,3))
			{
				// class feat
				allfeats.push_back(input[i]);
			}
		}
	}

	void LevelUp(string cl, int times)
	{
		//lowercase
		transform(cl.begin(), cl.end(), cl.begin(), [](unsigned char c) { return tolower(c); });
		int clnum;
		//get class index
		for (int i = 0; i < classLevels.size(); i++)
		{
			if (cl == classLevels[i][1])
			{
				clnum = i;
				break;
			}
		}
		//actually add levels
		classLevels[clnum][0] = to_string(stoi(classLevels[clnum][0]) + times);
		//health / feats
		for (int i = 0; i < times; i++)
		{
			//todo: spell slots*/spells, WIP : features
			
			int hd = stoi(classLevels[clnum][2]);
			//health up
			Health[0] += (hd / 2) + 1 + CalcMods(Stats)[2];
			Health[1] += (hd / 2) + 1 + CalcMods(Stats)[2];
		}
		//prof bonus
		totallevels = 0;
		for (int j = 0; j < classLevels.size(); j++)
		{
			totallevels += stoi(classLevels[j][0]);
		}
		prof = floor((totallevels - 1) / 4) + 2;
		//feats - remember to add classes to maps
		string classname = classLevels[clnum][1];
		vector<string> feats;
		//gettin feats
		if (classname == "fighter") { feats = fighterMain::LVLUP(stoi(classLevels[clnum][0]) - times, times); }
		if (classname == "warlock") { feats = warlockMain::LVLUP(stoi(classLevels[clnum][0]) - times, times); }

		for (int i = 0; i < feats.size(); i++)
		{
			allfeats.push_back(feats[i]);
		}
		
	}

	void PrintSkills()
	{
		system("cls");
		for (int i = 0; i < *(&profs + 1) - profs; i++)
		{
			int currentmod = profs[i] * prof;
			//print prof name
			string tempname = GlobalProfs[i];
			for (int j = GlobalProfs[i].length(); j < 15; j++)
			{
				tempname += " ";
			}
			std::cout << tempname;

			if (profs[i] == 0)
			{
				std::cout << " [ ] ";
			}
			else if (profs[i] == 1)
			{
				std::cout << " [P] ";
			}
			else if (profs[i] == 2)
			{
				std::cout << " [E] ";
			}

			if (i == 0)
			{
				//athletics - Str
				currentmod += CalcMods(Stats)[0];
			}
			else if (i < 4)
			{
				//Acrobatics-Stealth - Dex
				currentmod += CalcMods(Stats)[1];
			}
			else if (i < 9)
			{
				//Arcana-Religion - Int
				currentmod += CalcMods(Stats)[3];
			}
			else if (i < 14)
			{
				//Animal-Survival - Wis
				currentmod += CalcMods(Stats)[4];
			}
			else
			{
				//Deception-Persuasion - Cha
				currentmod += CalcMods(Stats)[5];
			}
			std::cout << "+" << currentmod << "\n";
		}
	}

	void PrintStats()
	{
		system("cls");
		std::cout << "Name: " << Name << "\n";
		std::cout << "Level: " << totallevels << "\n";
		std::cout << "Health: " << Health[0] << "/" << Health[1] << "\n";
		vector<int> mods = CalcMods(Stats);

		for (int i = 0; i < *(&Stats + 1) - Stats; i++)
		{
			string StatNames[6] = { "str: ","dex: ","con: ","int: ","wis: ","cha: " };
			mods[i] = mods[i];
			std::cout << StatNames[i] + to_string(Stats[i]) << " +" << mods[i] <<  "\n";
		}

		//Actions
		for (int i = 0; i < 3; i++)
		{
			if (Actions[i])
			{
				switch (i)
				{
				case 0:
					std::cout << "A [o]  ";
					break;
				case 1:
					std::cout << "BA [o]  ";
					break;
				case 2:
					std::cout << "R [o]\n";
					break;
				}
			}
			else
			{
				switch (i)
				{
				case 0:
					std::cout << "A [ ]  ";
					break;
				case 1:
					std::cout << "BA [ ]  ";
					break;
				case 2:
					std::cout << "R [ ]\n";
					break;
				}
			}
		}
	}
};


int main()
{
	srand(time(NULL));
	Character uno;
	uno.Name = "test";
	for (int i = 10; i < 16; i++)
	{
		uno.Stats[i - 10] = i;
	}

	uno.InitClass(fighterMain::IN(), 0);

	uno.PrintStats();

	bool done = false;

	while (!done)
	{
		vector<vector<int>> rout;
		vector<char> command;
		char strcommandchar[100];
		cin.getline(strcommandchar, sizeof(strcommandchar));
		string strcommand = string(strcommandchar);

		/*char input[50];
		cin.getline(input, sizeof(input));

		for (int i = 0; i < sizeof(input); i++)
		{
			if (input[i] == NULL) { break; }
			command.push_back(input[i]);
			strcommand += input[i];
		}*/

		if (strcommand == "char" || strcommand == "sheet")
		{
			//character sheet
			uno.PrintStats();
		}
		else if (strcommand == "skills" || strcommand == "abilities")
		{
			//show skills and proficiencies
			uno.PrintSkills();
		}
		else if (strcommand == "levelup" || strcommand == "level")
		{
			string cmd2;
			std::cout << "Which Class: ";
			cin >> strcommand;
			std::cout << "How Many Levels: ";
			cin >> cmd2;
			uno.LevelUp(strcommand, stoi(cmd2));
			uno.PrintStats();
		}
		else if (strcommand == "feats" || strcommand == "features")
		{
			system("cls");
			for (int i = 0; i < uno.allfeats.size(); i++)
			{
				std::cout << uno.allfeats[i] << endl;
			}
		}
		else if (strcommand.substr(0, 4) == "roll")
		{
			// roll 3d6 a
			// roll 4d8+1 n
			// roll 4d20+4 d
			strcommand += '.';
			int sec = 0;
			bool mod = false;
			string bnum = "";
			vector<int> args{ 0,0,0,0 };
			for (char const &c : strcommand.substr(5,30))
			{
				switch (sec)
				{
				case 0:
					//num dice
					if (isdigit(c))
					{
						//form num
						bnum += c;
					}
					else if(c == 'd')
					{
						//next arg
						args[0] = stoi(bnum);
						sec++;
						bnum = "";
					}
					break;
				case 1:
					//dice type
					if (isdigit(c))
					{
						//form num
						bnum += c;
					}
					else if (c == ' ')
					{
						//next arg
						args[1] = stoi(bnum);
						sec += 2;
						bnum = "";
					}
					else if (c == '+')
					{
						//next arg
						args[1] = stoi(bnum);
						sec++;
						bnum = "";
					}
					else if (c == '.')
					{
						//end
						args[1] = stoi(bnum);
						sec += 3;
						bnum = "";
					}
					break;
				case 2:
					//mod
					if (isdigit(c))
					{
						//form num
						bnum += c;
					}
					else if (c == ' ')
					{
						//next arg
						args[2] = stoi(bnum);
						sec++;
						bnum = "";
					}
					else if (c == '.')
					{
						//end
						args[2] = stoi(bnum);
						sec += 3;
						bnum = "";
					}
					break;
				case 3:
					//advantage
					switch (c)
					{
					case 'a':
						//advantage
						args[3] = 1;
						break;
					case 'd':
						//disadvantage
						args[3] = -1;
						break;
					case 'n':
						//none
						args[3] = 0;
						break;
					case '.':
						//end
						break;
					default:
						//neutral
						args[3] = 0;
						break;
					}
					break;
				}
			}
			//print
			/*for (int i = 0; i < args.size(); i++)
			{
				std::cout << args[i];
			}*/
			//call func
			rout = roll(args[0],args[1],args[2],args[3]);
			//print output
			for (int i = 0; i < rout.size(); i++)
			{
				std::cout << "roll set #" << i << endl;
				for (int j = 0; j < rout[i].size(); j++)
				{
					std::cout << rout[i][j] << endl;
				}
			}
			std::cout << "rolling ";
			std::cout << args[0] << "d" << args[1] << " (" << rout[0][0] - args[2] << ") " << " + " << args[2] << " = " << rout[0][0] << endl;
		}
		else if (strcommand == "stop")
		{
			return 0;
		}
		else
		{
			uno.PrintStats();
		}
	}
	return 0;
}

/*	TODO
 *	dll modding implementation -> search mod dict for dlls, load, parse maps of funcs/triggers
 *	Help command
 *
 *
 *
 *
 */