#include <iostream>
using namespace std;

class Character {
    public:
        void SetHealth(int);
        void SetPower(int);
        int GetHealth() const;
        int GetPower() const;

    private:
        int Health;
        int Power;
};

class Monster {
    public:
        void SetHealth(int);
        void SetPower(int);
        int GetHealth() const;
        int GetPower() const;
    private:
        int Health;
        int Power;
};

class MonsterParty {
    public:
        MonsterParty();
        MonsterParty(const MonsterParty&);
        void operator=(const MonsterParty&);
        ~MonsterParty();

        friend ostream& operator<<(ostream& output, const MonsterParty& mp);
        friend class Party;
        void RemoveMonster();
        bool CheckMonsters();
    private:
        Monster* MonsterTeam;
        int currSize;
        int Reward;
};

class Party {
    public:
        Party();
        Party(const Party&);
        void operator=(const Party&);
        ~Party();

        int GetTreasure() const;
        void SetTreasure(int);

        friend ostream& operator<<(ostream& output, const Party& p);
        void AddTreasure();

        void Combat(MonsterParty);
        void Run(MonsterParty);
        void RemoveCharacter();
        bool run;
        bool CheckCharacters();
    private:
        Character* Team;
        int currSize;
        int Treasure;
};

class DungeonBoard {
    friend ostream& operator<<(ostream& s, const DungeonBoard& db);
    public:
        DungeonBoard(int _size);
        ~DungeonBoard();
        void Move(char);
        bool tr;
        bool mon;
        void AddM();
        bool CheckBoard();
    private:
        //data
        const int maxTreasures;
        int numTreasures;
        const int maxMobs;
        int numMobs;
        int size;
        char** boardState;
        int** treasures;
        int** mobs;

        //entrance
        int x_enter;
        int y_enter;

        //exit
        int x_exit;
        int y_exit;

        //functionality
        void setupEntrance();
        void setupTreasure();
        void setupMobs();
};