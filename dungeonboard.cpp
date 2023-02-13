#include "game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

DungeonBoard::DungeonBoard(int _size):maxTreasures(_size/2),maxMobs(_size) {
	
	size = _size;
	//allocate a new board
	boardState = new char*[size];
	for(int i = 0; i < size; i++) {
		boardState[i] = new char[size];
		for(int j = 0; j < size; j++) {
			if(i == 0 || i == size-1) {
				boardState[i][j]= '-';
				continue;
			} else if (j == 0 || j == size-1) {
				boardState[i][j] = '|';
				continue;
			}
			boardState[i][j] = ' ';
		}
	}
	
	//set the entrance
	setupEntrance();
	//set the treasures
	setupTreasure();
	//set the mobs
	setupMobs();

	tr = false;
	mon = false;
}

DungeonBoard::~DungeonBoard() {
	for(int i = 0; i < size; i++) {
		delete [] boardState[i];
	}
	delete [] boardState;
	
	for(int i = 0; i < numMobs; i++) {
		delete [] mobs[i];
	}
	delete [] mobs;
	
	for(int i = 0; i < numTreasures; i++) {
		delete [] treasures[i];
	}
	delete [] treasures;
}

ostream& operator<<(ostream& s, const DungeonBoard& db) {
	for(int i = 0; i < db.size; i++) {
		for(int j = 0; j < db.size; j++) {
			s << db.boardState[i][j] << "\t";
		}
		s << endl<<endl;
	}
	
	return s;
}

void DungeonBoard::setupEntrance() {
	//find the entry
	srand(time(0));
	//pick a number 0-3 to figure out what wall the entrance will be on
	int wall = rand()%4;
	//pick a number 1-8 to figure out what position on that wall the entrance will be at (this keeps the door from being in a corner)
	int pos = rand()%(size-2) + 1;
	switch(wall) {
		case 0:
			boardState[pos][0] = 'X';
			break;
		case 1:
			boardState[0][pos] = 'X';
			break;
		case 2:
			boardState[pos][size-1] = 'X';
			break;
		case 3:
			boardState[size-1][pos] = 'X';
			break;
	}
}

void DungeonBoard::setupTreasure() {
	numTreasures = rand() % maxTreasures + 1;
	treasures = new int*[numTreasures];
	for(int i = 0; i < numTreasures; i++) {
		//get row
		int row = rand()%(size-2) + 1;
		//get column
		int column = rand()%(size-2) + 1;
		//place treasures
		boardState[row][column] = 'T';

		treasures[i] = new int[2];
		treasures[i][0] = row;
		treasures[i][1] = column;
	}
}

void DungeonBoard::setupMobs() {
	numMobs = rand() % maxMobs + 1;
	mobs = new int*[numMobs];
	for(int i = 0; i < numMobs; i++) {
		//get row
		int row = rand()%(size-2) + 1;
		//get column
		int column = rand()%(size-2) + 1;
		//place treasures
		boardState[row][column] = 'M';
		mobs[i] = new int[2];
		mobs[i][0] = row;
		mobs[i][1] = column;
	}
}

void DungeonBoard::Move(char d) {
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (boardState[i][j] == 'X') {
				if (d == 'a' || d == 'A') {
					if (j-1 < 0) {
						cout << "Cannot move there. Please try again." << endl;
					}
					else {
					if (boardState[i][j-1] == 'T') {
						tr = true;
					}
					if (boardState[i][j-1] == 'M') {
						mon = true;
					}
					boardState[i][j] = ' ';
					boardState[i][j-1] = 'X';
					if (i == 0 || i == 9) {
						boardState[i][j] = '-';
					}
					else if (j == 0 || j == 9) {
						boardState[i][j] = '|';
					}
					break;
					}
				}
				else if (d == 's' || d == 'S') {
					if (i+1 > 9) {
						cout << "Cannot move there. Please try again." << endl;
					}
					else {
					if (boardState[i+1][j] == 'T') {
						tr = true;
					}
					if (boardState[i+1][j] == 'M') {
						mon = true;
					}
					boardState[i][j] = ' ';
					boardState[i+1][j] = 'X';
					if (i == 0 || i == 9) {
						boardState[i][j] = '-';
					}
					else if (j == 0 || j == 9) {
						boardState[i][j] = '|';
					}
					return;
					}
				}
				else if (d == 'd' || d == 'D') {
					if (j+1 > 9) {
						cout << "Cannot move there. Please try again." << endl;
					}
					else {
					if (boardState[i][j+1] == 'T') {
						tr = true;
					}
					if (boardState[i][j+1] == 'M') {
						mon = true;
					}
					boardState[i][j] = ' ';
					boardState[i][j+1] = 'X';
					if (i == 0 || i == 9) {
						boardState[i][j] = '-';
					}
					else if (j == 0 || j == 9) {
						boardState[i][j] = '|';
					}
					break;
					}
				}
				else if (d == 'w' || d == 'W') {
					if (i-1 < 0) {
						cout << "Cannot move there. Please try again." << endl;
					}
					else {
					if (boardState[i-1][j] == 'T') {
						tr = true;
					}
					if (boardState[i-1][j] == 'M') {
						mon = true;
					}
                    boardState[i][j] = ' ';
                    boardState[i-1][j] = 'X';
					if (i == 0 || i == 9) {
						boardState[i][j] = '-';
					}
					else if (j == 0 || j == 9) {
						boardState[i][j] = '|';
					}
					break;
					}
                }
				else {
					cout << "Invalid input. Please try again." << endl;
				}
            }
        }
    }
}

void DungeonBoard::AddM() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (boardState[i][j] == ' ') {
				boardState[i][j] = 'M';
				return;
			}
		}
	}
}

bool DungeonBoard::CheckBoard() {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			if (boardState[i][j] == 'T' || boardState[i][j] == 'M') {
				return false;
			}
		}
	}
	return true;
}