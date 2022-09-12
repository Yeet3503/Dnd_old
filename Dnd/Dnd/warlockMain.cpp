#include "warlockMain.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;

vector<string> warlockMain::IN()
{
	string hitdice = "8";
	string classname = "warlock";

	//static string globalprofs[18] = { "athletics","acrobatics","sleight of hand","stealth","arcana","history","investigation","nature","religion","animal handling","insight","medicine","perception","survival","deception","intimidation","performance","persuasion" };
	//                0    1    2    3    4    5    6    7    8    9    10   11   12   13   14   15   16   17
	//				  str  dex  -    -    int  -    -    -    -    wis  -    -    -    -    cha  -    -    -
	//				  athl acro slei stea arca hist inve natu reli anim insi medi perc surv dece inti perf pers
	//int statprofs[18] = { 0,   1,   2,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0 };
	//guaranteed profs
	vector<string> retval{ classname , hitdice, "armL", "weapSimp", "saveWis", "saveCha" };

	//pickable profs
	cout << "pick 2 profs from this list (seperate lines): 1-arcana, 2-deception, 3-history, 4-intimidation, 5-investigation, 6-nature, 7-religion\n";
	int in1, in2;
	cin >> in1;
	cin >> in2;
	in1--;
	in2--;
	vector<string> p = { "sklArca", "sklDece", "sklHist", "sklInti", "sklInve", "sklNatu", "sklReli" };
	retval.push_back(p[in1]);
	retval.push_back(p[in2]);

	//lvl1 bonuses
	cout << "pick an otherworldly patron: 1-the fiend, 2-defense, 3-dueling, 4-great weapon fighting, 5-protection, 6-two-weapon fighting\n";
	cin >> in1;
	in1--;
	p = { "figFstyArch", "figFstyDefe", "figFstyDuel", "figFstyGrea", "figFstyProt", "figFstyTwow" };
	retval.push_back(p[in1]);
	retval.push_back("figSeco");

	return retval;
}



vector<string> warlockMain::LVLUP(int startlvl, int numlvl)
{
	vector<string> retval;

	for (int i = startlvl; i < startlvl + numlvl; i++)
	{
		switch (startlvl)
		{
		case 2:
			//do dis
			break;
		case 3:
			//do dis
			break;
		case 4:
			//do dis
			break;
		case 5:
			//do dis
			break;
		case 6:
			//do dis
			break;
		case 7:
			//do dis
			break;
		case 8:
			//do dis
			break;
		case 9:
			//do dis
			break;
		case 10:
			//do dis
			break;
		case 11:
			//do dis
			break;
		case 12:
			//do dis
			break;
		case 13:
			//do dis
			break;
		case 14:
			//do dis
			break;
		case 15:
			//do dis
			break;
		case 16:
			//do dis
			break;
		case 17:
			//do dis
			break;
		case 18:
			//do dis
			break;
		case 19:
			//do dis
			break;
		case 20:
			//do dis
			break;
		}
	}

	//return retval;
	return retval;
}

