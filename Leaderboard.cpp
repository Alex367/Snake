#include "Leaderboard.h"
#include <fstream>
#include <iostream>
#include <conio.h>

Leaderboard::Leaderboard(const char *filename)
{
	char buf[255];
	int score;

	this->filename = filename;

	std::ifstream fin(filename); 

	while (fin.good())
	{
		fin >> score;		  
		fin.getline(buf, 255); 

		leaderBoardData.push_back(RecordEl(buf, score));
	}

	fin.close();
}


Leaderboard::~Leaderboard()
{
}

void Leaderboard::show()
{
	system("CLS");

	std::cout << "Leaderboard" << std::endl << std::endl;

	for (auto iter = leaderBoardData.begin(); iter != leaderBoardData.end(); iter++)
		std::cout << iter->scores << " - " << iter->name << std::endl;

	if (leaderBoardData.size()==0)
		std::cout << "Leaderboard is empty" << std::endl;

	std::cout << std::endl << "Press any key to back" << std::endl;

	getch();
}

void Leaderboard::add(int scores, std::string name)
{
	bool added = false;
	for (auto iter = leaderBoardData.begin(); iter != leaderBoardData.end(); iter++)
	{
		if (scores > iter->scores)
		{
			leaderBoardData.insert(iter, RecordEl(name, scores));
			added = true;
			break;
		}
	}

	if (!added)
		leaderBoardData.push_back(RecordEl(name, scores));

	saveFile();
}

void Leaderboard::saveFile()
{
	std::ofstream fout(filename); 
	for (auto iter = leaderBoardData.begin(); iter != leaderBoardData.end(); iter++)
	{
		fout << iter->scores << " " << iter->name << std::endl;
	}
	fout.close();
}