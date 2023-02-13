#include "game.h"
#include <iostream>
#include <cstdlib>
using namespace std;

int main() {
    cout << "---------------------------" << endl;
    cout << "WELCOME TO THE DUNGEON GAME" << endl;
    cout << "---------------------------" << endl;
    bool loop = true;
	DungeonBoard db(10);
    Party p;

    do {
    cout << db << endl;
    char choice;
    cout << "Use WASD to move or click 'x' to display your party's status:" << endl;
    cin >> choice;
    if (choice == 'x' || choice == 'X') {
        cout << p << endl;
    }
    else {
        db.Move(choice);
        cout << db << endl;
        if (db.tr == 1) {
            p.AddTreasure();
            db.tr = false;
        }
        else if (db.mon == 1) {
            MonsterParty mp;
            cout << "You've encountered a party of monsters!" << endl;
            cout << "Monster's Party: " << endl;
            cout << mp << endl;
            cout << "Your Party: " << endl;
            cout << p << endl;
            string choice1;
            cout << "Would you like to attack or run?" << endl;
            cin >> choice1;
            if (choice1 == "attack") {
                p.Combat(mp);
            }
            else if (choice1 == "run") {
                p.Run(mp);
                if (p.run == 1) {
                    db.AddM();
                    p.run = false;
                }
            }
            db.mon = false;
        }
        cout << "Treasure Counter: " << p.GetTreasure() << endl;
    }
    if (p.CheckCharacters() == 1) {
        cout << "All members of your party have died." << endl;
        cout << "GAME OVER" << endl;
        loop = false;
    }
    if (db.CheckBoard() == 1) {
        cout << "Congratulations! You have cleared the dungeon." << endl;
        loop = false;
    }
    }
    while (loop);
}