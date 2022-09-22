

#ifndef BASICS_H
#define BASICS_H
#include <iostream>
#include <string>
#include <map>
#include <windows.h>
using namespace std;

bool roomCheckMode = true;

HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);

string wallColor = "1";
string gameFloor = "10";
string gameWater = "1";
string gamePlayer = "12";
string gameInterract = "8";
int interractsNumber = 2;

char interractSign = '?';

const int mapSize = 60, mapSizeX = 30, mapSizeY = 80;
map <string, char> gameObj;
void init() {
	gameObj["wWall"] = '|';
	gameObj["hWall"] = '-';
	gameObj["corner"] = '+';
	gameObj["chest"] = '▄';
	gameObj["character"] = '©';
	gameObj["enemy"] = '!';
	gameObj["something"] = '?';
	
}


#endif