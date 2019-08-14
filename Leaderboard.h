#pragma once

#include <list>
#include <string>

//запись в таблице рекордов
struct RecordEl
{
	std::string name;
	int scores;

	RecordEl(std::string name, int scores)
	{
		this->name = name;
		this->scores = scores;
	}
};

class Leaderboard
{
public:
	Leaderboard(const char *filename);
	~Leaderboard();

	std::list<RecordEl> leaderBoardData;	

	void show();							
	void add(int scores, std::string name);	

private:
	const char *filename;	

	void saveFile();	
};

