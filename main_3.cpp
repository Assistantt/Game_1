#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>

int getRandomNumber(int min, int max)
    {
        static const double fraction = 1.0 / (static_cast<double>(RAND_MAX) + 1.0);
        return static_cast<int>(rand() * fraction * (max - min + 1) + min);
    }

class Creature{
    protected:
        std::string name;
        char symbol;
        int hp;
        int attack;
        int gold;
    public:
        Creature(std::string m_name, char m_symbol, int m_hp, int m_attack, int m_gold) : name(m_name), symbol(m_symbol), hp(m_hp), attack(m_attack), gold(m_gold){

        }
        const std::string& getName(){
            return name;
        }
        char getSymbol(){
            return symbol;
        }
        int getHp(){
            return hp;
        }
        int getAttack(){
            return attack;
        }
        int getGold(){
            return gold;
        }
        void reduceHealth(int subtract_hp){
            hp -= subtract_hp;
        }
        bool isDead(){
            if(hp <= 0){
                return true;
            }
            return false;
        }
        void addGold(int add_gold){
            gold += add_gold;
        }
};

class Player : public Creature{
    protected:
        int level = 1;
    public:
        Player(std::string m_name, char m_symbol, int m_hp, int m_attack, int m_gold) : Creature(m_name, m_symbol, m_hp, m_attack, m_gold){

        }
        void levelUp(){
            level += 1;
            attack += 1;
        }
        int getLevel(){
            return level;
        }
        bool hasWon(){
            return level >= 20;
        }
};

class Monster : public Creature{
    public:
        enum Type{
            DRAGON, 
            ORC,
            SLIME,
            MAX_TYPES
        };
        struct MonsterData{
            std::string name; 
            char symbol; 
            int health; 
            int damage; 
            int gold;
        };
        static MonsterData monsterData[MAX_TYPES]; 
        Monster(Type type): Creature(monsterData[type].name, monsterData[type].symbol, monsterData[type].health, monsterData[type].damage, monsterData[type].gold){

        }
        static Monster getRandomMonster(){
            return Monster(static_cast<Type>(getRandomNumber(0, static_cast<int>(MAX_TYPES)-1)));
        }
};

Monster::MonsterData Monster::monsterData[Monster::MAX_TYPES]
        {
            { "dragon", 'D', 20, 4, 100 },
            { "orc", 'o', 4, 2, 25 },
            { "slime", 's', 1, 1, 10 }
        };

Player CreationPlayer(){
    std::cout << "Enter your name: ";
    std::string player_name;
    std::cin >> player_name;
    Player First_player(player_name, '@', 10, 1, 0);
    std::cout << "Welcome, " << First_player.getName() << std::endl;
    return First_player;
}

bool attackMonster(Monster &m, Player &FP){
    FP.reduceHealth(m.getAttack());
    std::cout << "The " << m.getName() << " hit you for " << m.getAttack() << " damage." << std::endl;
    return FP.isDead();
}

bool attackPlayer(Monster &m, Player &FP){
    m.reduceHealth(FP.getAttack());
    std::cout << "You hit the " << m.getName() << " for " << FP.getAttack() << " damage." << std::endl;
    if(m.isDead()){
        FP.addGold(m.getGold());
        FP.levelUp();
        std::cout << "You killed the " << m.getName() << "." << std::endl;
        std::cout << "You are now level " << FP.getLevel() << "." << std::endl;
        std::cout << "You found " << FP.getGold() << " gold." << std::endl;
        return 1;
    }
    return 0;
}

bool fightMonster(Monster &m, Player &FP){
    while(true){
        std::cout << "A " << m.getName() << " (" << m.getSymbol() << ") was created.\n";
        char flag;
        do{
            std::cout << "(R)un or (F)ight: ";
            std::cin >> flag;
        }while(flag != 'R' && flag != 'F');
        if(flag == 'R'){
            if(rand() % 2){
                break;
            }
            if(attackMonster(m, FP)){
                return 1;
            }
            continue;
        }
        if(attackPlayer(m, FP)){
            break;
        }
        if(attackMonster(m, FP)){
            return 1;
        }
    }
    return 0;
}

int main()
{
	srand(static_cast<unsigned int>(time(0)));
	rand();
    Player FP = CreationPlayer();
    while(true){
        Monster m = Monster::getRandomMonster();
        if(fightMonster(m, FP)){
            std::cout << "You died at level " << FP.getLevel() << " and with " << FP.getGold() << "gold.\n";
            std::cout << "Too bad you can't take it with you!" << std::endl;
            break;
        }
        if(FP.getLevel() >= 20){
            std::cout << "You win with " << FP.getGold() << "gold.\n";
            break;
        }
    }
 
	return 0;
}