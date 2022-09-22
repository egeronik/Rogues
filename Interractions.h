#include <iostream>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include "GraphicEngine.h"
using namespace std;

#pragma once

struct item{
	string rarity = "common";
	string name = "";
	string discription = "";
	int dmg=0, arm=0, hp=0;
	
};

//item getItem() {
//	ifstream itemData)
//}



bool fTof() {
	int r = rand() % 2;
	if (r == 1) return true;
	else return false;
}


bool dialogYN(int row) {
	char input;
	bool ans = true;
	cout << "YES<<      NO  \n";
	while (1) {
		input = _getch();
		setCur(0, row);
		switch (input)
		{
		case 'a':
			cout << "YES<<      NO  \n";
			ans = true;
			break;
		case 'd':
			cout << "YES        NO<<\n";
			ans = false;
			break;
		case 13:
			return ans;
		default:
			break;
		}
	}
}




void intExit() {
	cout << "CONGRATULATIONS YOU FOUND AN EXIT!!!!!!!!!!!!\n";
	system("pause");
}





void intChest() {
	cout << "CONGRATULATIONS YOU FOUND AN CHEST!!!!!!!!!!!!\n";
	if (dialogYN(1)) {
		system("cls");
		cout << "You openning the chest....";
		_getch();
		if (fTof()) {
			cout << "Congratulations you found a item";

		}
	}

}
