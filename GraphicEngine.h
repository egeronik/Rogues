#ifndef ENGINE_H
#define ENGINE_H
#include <Windows.h>
#include "Basics.h"
#include <string>
#include <vector>



//#include "Cell.h"

void setCur(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}



void ClearMap(std::vector<vector<string> > &a) {
	for (int x = 0; x < mapSizeX; ++x) {
		for (int y = 0; y < mapSizeY; ++y) {
			a[x][y] = gameWater;
		}
	}
}


void DrawMap(std::vector<vector<string> > a, char mapSign) {
	int color = 0;
	for (int x = 0; x < mapSizeX; ++x) {
		for (int y = 0; y < mapSizeY; ++y) {
			if (roomCheckMode) {
				
				SetConsoleTextAttribute(console, std::stoi(a[x][y]));
				if (a[x][y] == gameInterract) std::cout << interractSign;
				else
					std::cout << mapSign;
				
			}
			else {
				std::cout << gameObj[a[x][y]];
			}
				
			
		}
		std::cout <<endl;
	}
	
}

#endif