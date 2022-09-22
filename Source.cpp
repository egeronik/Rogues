#include <iostream>
#include <conio.h>
#include <windows.h>
#include "GraphicEngine.h"
#include "DungeonGeneration.h"
#include "Interractions.h"
using namespace std;



void cursorOff() {
	CONSOLE_CURSOR_INFO curs = { 0 };
	curs.dwSize = sizeof(curs);
	curs.bVisible = false;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &curs);
}


char getInput(){
	return _getch();
}

struct characterState
{
	int x;
	int y;
	int health;
	int armor;
	int deamage;
};

characterState player;


void generateMap(vector<vector<string> > &a) {
	for (int x = 0; x < mapSizeX; ++x) {
		vector<string> tmp;
		tmp.clear();
		for (int y = 0; y < mapSizeY; ++y) {
			tmp.push_back("0");
		}
		a.push_back(tmp);
	}
}

vector<vector<string> > gameMap;

leaf *Root = new leaf(0, 0, mapSizeX, mapSizeY);


bool canMove(char input, std::vector<vector<string>> &map) {
	switch (input)
	{
	case 'w':
		if (map[player.x - 1][player.y] != gameWater) {
			map[player.x][player.y] = gameFloor;
			SetConsoleTextAttribute(console, stoi(gameFloor));
			setCur(player.y, player.x);
			cout << 0;
			player.x -= 1;
			return true;
		}
		else return false;
	case 'a':
		if (map[player.x][player.y - 1] != gameWater) {
			map[player.x][player.y] = gameFloor;
			SetConsoleTextAttribute(console, stoi(gameFloor));
			setCur(player.y, player.x);
			cout << 0;
			player.y -= 1;
			return true;
		}
		else return false;
	case 's':
		if (map[player.x + 1][player.y] != gameWater) {
			map[player.x][player.y] = gameFloor;
			SetConsoleTextAttribute(console, stoi(gameFloor));
			setCur(player.y, player.x);
			cout << 0;
			player.x += 1;
			return true;
		}
		else return false;
	case 'd':
		if (map[player.x][player.y + 1] != gameWater) {
			map[player.x][player.y] = gameFloor;
			SetConsoleTextAttribute(console, stoi(gameFloor));
			setCur(player.y, player.x);
			cout << 0;
			player.y += 1;
			return true;
		}
		else return false;
	default:
		return false;
	}
}

void triggerAction(int x, int y , char mapSign) {
	if (gameMap[x][y] == gameInterract) {
		system("cls");
		//
		DrawMap(gameMap,mapSign);
	}
}



COORD getFreeSpot(vector<vector<string>> gameMap) {
	int x = rand() % mapSizeX;
	int y = rand() % mapSizeY;

	if (gameMap[x][y] == gameFloor) {
		COORD tmp;
		tmp.X = x;
		tmp.Y = y;
		return tmp;
		
	}
	else {
		return getFreeSpot(gameMap);
	}
}


//void generateGameObjects(int chestNumber, int monsterNumber)//Доделай тута


void goToNextLvl(char &mapSign) {
	ClearMap(gameMap);
	generateRooms(Root, gameMap);
	mapSign++;
	COORD tmpPlayer = getFreeSpot(gameMap);
	player.x = tmpPlayer.X;
	player.y = tmpPlayer.Y;
	gameMap[player.x][player.y] = gamePlayer;

}


int main() {
	init();
	cursorOff();
	player.armor = 0;
	player.deamage = 1;
	player.health = 10;
	char mapSign = '0';
	generateMap(gameMap);	
	goToNextLvl(mapSign);
	char input;
	mapSign = '0';
	intChest();
	

	
	DrawMap(gameMap, mapSign);
	while (1) {
		
		
		input = getInput();
		
		
		if (canMove(input, gameMap)) {
			triggerAction(player.x, player.y,mapSign);
		}
		gameMap[player.x][player.y] = gamePlayer;
		setCur(player.y, player.x);
		SetConsoleTextAttribute(console, stoi(gamePlayer));
		cout << 'a';
		setCur(0, 0);
		//system("cls");
		//DrawMap(gameMap, mapSign);
		//ClearMap(gameMap);
		//generateRooms(Root, gameMap);
		
		
		
		
	}
	
}