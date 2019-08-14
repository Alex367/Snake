#include <iostream>
#include <fstream>
#include "windows.h"
#include "Game.h"
#include "Leaderboard.h"
#include "EnemySnakePart.h"
#include "Wall.h"
#include <conio.h>

int showMainMenu()
{
	int screenWidth = 120;
	int res = 0;

	std::string menuPlay = "Play game";
	std::string menuLeaderBoard = "Leaderboard scores";
	std::string menuHelp = "Help";
	std::string menuExit = "Exit";
	std::string text;
	int selected = 1;	

	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 

	do
	{
		system("CLS");
		for (int i = 0; i < 10; i++)
			std::cout << std::endl;

		
		int tab = screenWidth / 2 - menuPlay.size() / 2 - 1;
		
		if (selected == 1)
		{
			tab--;
			SetConsoleTextAttribute(hConsole, 11);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 7);
		}
		
		for (int i = 0; i < tab; i++)
			std::cout << " ";
		
		if (selected==1)
			std::cout << ">" << menuPlay << "<" << std::endl;
		else
			std::cout << menuPlay << std::endl;

		std::cout << std::endl;

		
		tab = screenWidth / 2 - menuLeaderBoard.size() / 2 - 1;
		
		if (selected == 2)
		{
			tab--;
			SetConsoleTextAttribute(hConsole, 11);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 7);
		}
		
		for (int i = 0; i <  tab; i++)
			std::cout << " ";
		
		if (selected == 2)
			std::cout << ">" << menuLeaderBoard << "<" << std::endl;
		else
			std::cout << menuLeaderBoard << std::endl;

		std::cout << std::endl;

		
		tab = screenWidth / 2 - menuHelp.size() / 2 - 1;
		
		if (selected == 3)
		{
			tab--;
			SetConsoleTextAttribute(hConsole, 11);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 7);
		}
		
		for (int i = 0; i < tab; i++)
			std::cout << " ";
		
		if (selected == 3)
			std::cout << ">" << menuHelp << "<" << std::endl;
		else
			std::cout << menuHelp << std::endl;

		std::cout << std::endl;

		
		tab = screenWidth / 2 - menuExit.size() / 2 - 1;
		
		if (selected == 4)
		{
			tab--;
			SetConsoleTextAttribute(hConsole, 11);
		}
		else
		{
			SetConsoleTextAttribute(hConsole, 7);
		}
		
		for (int i = 0; i <  tab; i++)
			std::cout << " ";
		
		if (selected == 4)
			std::cout << ">" << menuExit << "<" << std::endl;
		else
			std::cout << menuExit << std::endl;

		for (int i = 0; i < 12; i++)
			std::cout << std::endl;
		SetConsoleTextAttribute(hConsole, 8);
		std::cout << "     UP arrow and DOWN arrow to change item. Enter to choose.";
				
		unsigned char c = getch();
		if (c == 224)  
		{
			c = getch();	
			switch (c)
			{
			case 72:
				selected--;
				if (selected < 1)
					selected = 4;

				break;
			case 80:
				selected++;
				if (selected > 4) 
					selected = 1;				

				break;
			}
		}
		else if (c == 13)	
		{
			res = selected;
		}
	} while (res < 1 || res > 4);
	
	return res;
}

void playGame(Leaderboard * leaderboard)
{
	Game *game = new Game(70, 26);
	
	int scores = game->play();
	std::cout << std::endl << "Game Over!" << std::endl << "Your scores is " << scores << std::endl << "Enter your name: ";
	char name[200];
	std::cin >> name;

	leaderboard->add(scores, name);

	delete game;
}

void showHelp()
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); 
		
	system("CLS");

	SetConsoleTextAttribute(hConsole, 7);
	std::cout << "     Help";
	std::cout << std::endl << std::endl << std::endl;
	std::cout << "  This is game Snake. User play with one snake and computer ";
	std::cout << "play with other. Your mission is collect so much food as you can.";
	std::cout << std::endl << std::endl << std::endl;

	SetConsoleTextAttribute(hConsole, 10);
	std::cout << SnakePart::SYMBOL << SnakePart::SYMBOL << SnakePart::SYMBOL 
		<< " - your snake" << std::endl;
	SetConsoleTextAttribute(hConsole, 4);
	std::cout << EnemySnakePart::SYMBOL << EnemySnakePart::SYMBOL << EnemySnakePart::SYMBOL 
		<< " - computer snake" << std::endl;
	SetConsoleTextAttribute(hConsole, 6);
	std::cout << Food::SYMBOL << " - food to collect" << std::endl;
	SetConsoleTextAttribute(hConsole, 7);
	std::cout << Wall::SYMBOL << " - wall, if you'll go to this cell, game will over" << std::endl;

	unsigned char goThrough = 176;
	std::cout << goThrough << " - if you touch this cell, you will go out on opposite side of game field" << std::endl;

	std::cout << std::endl << std::endl << std::endl;
	std::cout << "Press any key to return";
	char c = getch();
}

int main()
{
	Leaderboard * leaderboard = new Leaderboard("leaderboard.txt");	
	int res = 0;

	/*
	//просмотр возможных симоволов для замены
	for (unsigned char c = 1; c < 255; c++)
		std::cout << (int)c << " - " << c << std::endl;

	char c = getch();
	*/

	do{
		res = showMainMenu();	
		switch (res)
		{
		case 1:
			playGame(leaderboard);
			break;
		case 2:
			leaderboard->show();
			break;
		case 3:
			showHelp();
			break;
		case 4:
			break;
		}
	} while (res != 4);

	delete leaderboard;

	return 0;
}