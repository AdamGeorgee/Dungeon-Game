#include "game.h"
#include <iostream>
#include <cstdlib>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Character::SetHealth(int h) {
    Health = h;
}

void Character::SetPower(int p) {
    Power = p;
}

int Character::GetHealth() const{
    return Health;
}

int Character::GetPower() const{
    return Power;
}

Party::Party() {
    run = false;
    currSize = 5;
    Team = new Character[5];
    Treasure = 0;
    srand(time(0));
    for (int i = 0; i < 5; i++) {
        int x = (rand() % 21) + 80;
        int y = (rand() % 7) + 4;
        Team[i].SetHealth(x);
        Team[i].SetPower(y);
    }
}

Party::Party(const Party& p) {
    currSize = p.currSize;
    Team = new Character[currSize];
    Treasure = p.Treasure;
    for (int i = 0; i < currSize; i++) {
        Team[i].SetHealth(p.Team[i].GetHealth());
        Team[i].SetPower(p.Team[i].GetPower());
    }
}

void Party::operator=(const Party& p) {
    currSize = p.currSize;
    Team = new Character[currSize];
    Treasure = p.Treasure;
    for (int i = 0; i < currSize; i++) {
        Team[i].SetHealth(p.Team[i].GetHealth());
        Team[i].SetPower(p.Team[i].GetPower());
    }
}

Party::~Party() {
    delete [] Team;
}

ostream& operator<<(ostream& output, const Party& p) {
    for (int i = 0; i < p.currSize; i++) {
        output << "Character " << i << ".) Health: " << p.Team[i].GetHealth() << " Power: " << p.Team[i].GetPower() << endl;
    }
    return output;
}

int Party::GetTreasure() const {
    return Treasure;
}

void Party::SetTreasure(int t) {
    Treasure = t;
}

void Party::AddTreasure() {
	srand(time(0));
	int treasure = (rand() % 10) + 1;
	Treasure += treasure;
}

void Monster::SetHealth(int h) {
    Health = h;
}

void Monster::SetPower(int p) {
    Power = p;
}

int Monster::GetHealth() const{
    return Health;
}

int Monster::GetPower() const{
    return Power;
}

MonsterParty::MonsterParty() {
    srand(time(0));
    currSize = (rand() % 5) + 1;
    MonsterTeam = new Monster[currSize];
    Reward = (rand() % 10) + 1;

    for (int i = 0; i < currSize; i++) {
        int x = (rand() % 21) + 15;
        int y = (rand() % 6) + 1;
        MonsterTeam[i].SetHealth(x);
        MonsterTeam[i].SetPower(y);
    }
}

MonsterParty::MonsterParty(const MonsterParty& mp) {
    currSize = mp.currSize;
    MonsterTeam = new Monster[currSize];
    Reward = mp.Reward;
    for (int i = 0; i < currSize; i++) {
        MonsterTeam[i].SetHealth(mp.MonsterTeam[i].GetHealth());
        MonsterTeam[i].SetPower(mp.MonsterTeam[i].GetPower());
    }
}

void MonsterParty::operator=(const MonsterParty& mp) {
    currSize = mp.currSize;
    MonsterTeam = new Monster[currSize];
    Reward = mp.Reward;
    for (int i = 0; i < currSize; i++) {
        MonsterTeam[i].SetHealth(mp.MonsterTeam[i].GetHealth());
        MonsterTeam[i].SetPower(mp.MonsterTeam[i].GetPower());
    }
}

MonsterParty::~MonsterParty() {
    delete [] MonsterTeam;
}

ostream& operator<<(ostream& output, const MonsterParty& mp) {
    for (int i = 0; i < mp.currSize; i++) {
        output << "Monster " << i << ".) Health: " << mp.MonsterTeam[i].GetHealth() << " Power: " << mp.MonsterTeam[i].GetPower() << endl;
    }
    return output;
}

void MonsterParty::RemoveMonster() {
    for (int i = 0; i < currSize; i++) {
        if (MonsterTeam[i].GetHealth() <= 0) {
            for (int j = i; j < currSize; j++) {
                MonsterTeam[j].SetHealth(MonsterTeam[j+1].GetHealth());
                MonsterTeam[j].SetPower(MonsterTeam[j+1].GetPower());
            }
            currSize--;
        }
    }
}

void Party::RemoveCharacter() {
    for (int i = 0; i < currSize; i++) {
        if (Team[i].GetHealth() <= 0) {
            for (int j = i; j < currSize; j++) {
                Team[j].SetHealth(Team[j+1].GetHealth());
                Team[j].SetPower(Team[j+1].GetPower());
            }
            currSize--;
        }
    }
}

void Party::Combat(MonsterParty mp) {
    srand(time(0));
    bool loop = true;
    do {
    for (int i = 0; i < currSize; i++) {
        int target;
        cout << "Which monster would you like character " << i << " to attack?" << endl;
        cin >> target;
        int hitChance = (rand() % 20) + 1;
        if (hitChance == 1 || hitChance == 2 || hitChance == 3) {
            cout << "Attack missed!" << endl;
        }
        else {
            cout << "Attack hit!" << endl;
            int newMonHealth = mp.MonsterTeam[target].GetHealth() - Team[i].GetPower();
            mp.MonsterTeam[target].SetHealth(newMonHealth);
            mp.RemoveMonster();
        }
    }
    for (int i = 0; i < mp.currSize; i++) {
        int hitChance2 = (rand() & 2) + 1;
        if (hitChance2 == 1) {
            int target2 = (rand() % currSize-1) + 1;
            cout << "Monster " << i << " attacked character " << target2 << "!" << endl;
            int newCharHealth = Team[target2].GetHealth() - mp.MonsterTeam[i].GetPower();
            Team[target2].SetHealth(newCharHealth);
            RemoveCharacter();
        }
        else {
            cout << "Monster " << i << " missed!" << endl;
        }
    }
    cout << endl;
    cout << "Monster's Party: " << endl;
    cout << mp << endl;
    cout << "Your Party: " << endl;
    for (int i = 0; i < currSize; i++) {
    cout << "Character " << i << ".) Health: " << Team[i].GetHealth() << " Power: " << Team[i].GetPower() << endl;
    }
    if (CheckCharacters() == 1) {
        loop = false;
    }
    if (mp.CheckMonsters() == 1) {
        Treasure += mp.Reward;
        loop = false;
    }
    } while (loop);
}

void Party::Run(MonsterParty mp) {
    srand(time(0));
    int chance;
    switch (mp.currSize) {
        case 5:
            chance = (rand() % 10) + 1;
            if (chance == 1) {
                cout << "Got away safely." << endl;
                run = true;
            }
            else {
                cout << "Couldn't get away!" << endl;
                Combat(mp);
            }
            break;
        case 4:
            chance = (rand() % 5) + 1;
            if (chance == 1) {
                cout << "Got away safely." << endl;
                run = true;
            }
            else {
                cout << "Couldn't get away!" << endl;
                Combat(mp);
            }
            break;
        case 3:
            chance = (rand() % 10) + 1;
            if (chance == 1 || chance == 2 || chance == 3) {
                cout << "Got away safely." << endl;
                run = true;
            }
            else {
                cout << "Couldn't get away!" << endl;
                Combat(mp);
            }
            break;
        case 2:
            chance = (rand() % 5) + 1;
            if (chance == 1 || chance == 2) {
                cout << "Got away safely." << endl;
                run = true;
            }
            else {
                cout << "Couldn't get away!" << endl;
                Combat(mp);
            }
            break;
        case 1:
            chance = (rand() % 2) + 1;
            if (chance == 1) {
                cout << "Got away safely." << endl;
                run = true;
            }
            else {
                cout << "Couldn't get away!" << endl;
                Combat(mp);
            }
            break;
    }
}

bool Party::CheckCharacters() {
    bool gameOver = false;
    if (currSize == 0) {
        gameOver = true;
    }
    return gameOver;
}

bool MonsterParty::CheckMonsters() {
    bool winBattle = false;
    if (currSize == 0) {
        winBattle = true;
    }
    return winBattle;
}