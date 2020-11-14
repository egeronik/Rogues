#include <iostream>
#include <string>
#include <map>
#include <random>
#include <string>
#include <vector>


#ifndef GENERATION_H
#define GENERATION_H

int randRange(int min, int max) {
	return rand() % (max - min) + min;
}


class leaf {
	
public :
	int minLeafSize = 10;
	int minRoomSize = 5;
	leaf *leftChild;
	leaf *rightChild;


	int height, width;
	int x, roomX, pointX;
	int y, roomY, pointY;
	int sizeX, sizeY;
	leaf(int X, int Y, int HEIGHT, int WIDTH) {
		x = X;
		y = Y;
		height = HEIGHT;
		width = WIDTH;
	}
	void split() {
		bool splitH = false;
		if (height > width ) {
			splitH = true;
		}
		else if (width > height ) {
			splitH = false;
		}
		else {
			if (rand() % 2 == 0) splitH = true;
		}
		if (splitH&&height < (minLeafSize * 2 + 1)) splitH = false;


		if (splitH) {
			int newSplit = rand() % (height-2*minLeafSize)+minLeafSize;
			//newSplit = height / 2;
			leftChild = new leaf(x,y,newSplit,width);
			rightChild = new leaf(x+newSplit,y,height-newSplit,width);
		}
		else {
			int newSplit = rand() % (width-2*minLeafSize)+minLeafSize;
			//newSplit = width / 2;
			leftChild = new leaf(x, y, height , newSplit);
			rightChild = new leaf(x , y + newSplit , height, width - newSplit);
		}
	}
	void generateRoom() {
		sizeX = randRange(minRoomSize, height-2);
		sizeY = randRange(minRoomSize, width-2);
		roomX = randRange(x + 1, x + height - sizeX - 1);
		roomY = randRange(y + 1, y + width - sizeY - 1);

	}
	void generatePoint() {
		pointX = randRange(roomX+1, (roomX + sizeX)-1);
		pointY = randRange(roomY+1, (roomY + sizeY)-1);
	}
};


int deb = 1;

void generateInterracts(leaf *r, int n , std::vector<std::vector<std::string> > &gameMap) {
	if (n == 0) return;
	int x = randRange(r->roomX + 1, (r->roomX + r->sizeX) - 1);
	int y = randRange(r->roomY + 1, (r->roomY + r->sizeY) - 1);
	if (gameMap[x][y] != gameFloor) generateInterracts(r, n, gameMap);
	else {
		gameMap[x][y] = gameInterract;
		generateInterracts(r, n - 1, gameMap);
	}
	

}


bool generateRooms(leaf *&Leaf, std::vector<std::vector<std::string> > &gameMap) {
	if (Leaf->height>(Leaf->minLeafSize*2+1)|| Leaf->width >( Leaf->minLeafSize * 2 + 1 )) {
		
		Leaf->split();
		bool needToConnect = true;
		if (generateRooms(Leaf->leftChild, gameMap)) {
			Leaf->leftChild->generatePoint();
			//gameMap[Leaf->leftChild->pointX][Leaf->leftChild->pointY] = "4";
			
		}
		else needToConnect = false;
		if (generateRooms(Leaf->rightChild, gameMap)) {
			Leaf->rightChild->generatePoint();
			//gameMap[Leaf->rightChild->pointX][Leaf->rightChild->pointY] = "4";
			
		}
		else needToConnect = false;
		
		needToConnect = true;
		if (needToConnect) {
			
			int startX, startY, endX, endY ,vert;
			startX = Leaf->rightChild->pointX > Leaf->leftChild->pointX ? Leaf->leftChild->pointX : Leaf->rightChild->pointX;
			endX = Leaf->rightChild->pointX < Leaf->leftChild->pointX ? Leaf->leftChild->pointX : Leaf->rightChild->pointX;
			startY = Leaf->rightChild->pointY > Leaf->leftChild->pointY ? Leaf->leftChild->pointY : Leaf->rightChild->pointY;
			endY = Leaf->rightChild->pointY < Leaf->leftChild->pointY ? Leaf->leftChild->pointY : Leaf->rightChild->pointY;
			if (Leaf->rightChild->pointX > Leaf->leftChild->pointX) {
				
				
				if (Leaf->leftChild->pointY > Leaf->rightChild->pointY) {
					vert = -1;
				}
				else vert = 1;
			}
			else {
				
				
				if (Leaf->leftChild->pointY > Leaf->rightChild->pointY) {
					vert = 1;
				}
				else vert = -1;
			}
			



			//cout << startX << ' ' << endX << ' ' << startY << ' ' << endY;
			//system("pause");
			vector<pair<int, int>> road;
			for (int i = startX; i < endX; i++) 
				if (gameMap[i][startY] == gameWater) {
					gameMap[i][startY] = gameFloor;
					pair<int, int> tmp;
					tmp.first = i;
					tmp.second = startY;
					road.push_back(tmp);
				}

			if(vert>0)
				for (int j = startY; j < endY; j++) {
					if (gameMap[endX][j] == gameWater) {
						gameMap[endX][j] = gameFloor;
						pair<int, int> tmp;
						tmp.first = endX;
						tmp.second = j;
						road.push_back(tmp);
					}
				}
			else 
				for (int j = endY; j > startY; j--) {
					if (gameMap[startX][j] == gameWater) {
						gameMap[startX][j] = gameFloor;
						pair<int, int> tmp;
						tmp.first = startX;
						tmp.second =  j;
						road.push_back(tmp);
					}
				}
			int t = randRange(0, road.size());
			Leaf->pointX = road[t].first;
			Leaf->pointY = road[t].second;

			
		}
		
		return false;
	}
	else {
		Leaf->generateRoom();

		for (int i = Leaf->roomX; i < Leaf->roomX + Leaf->sizeX; ++i) {
			for (int j = Leaf->roomY; j < Leaf->roomY + Leaf->sizeY; ++j) {
				gameMap[i][j] = gameFloor;
			}
		}
		generateInterracts(Leaf, interractsNumber, gameMap);
		
		deb++;
		if (deb > 14) deb = 1;
		return true;
	}
}


#endif