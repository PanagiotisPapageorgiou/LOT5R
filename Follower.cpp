#include <iostream>
#include <string.h>
#include "Card.hpp"
#include "Follower.hpp"

using namespace std;

Follower::Follower(string _name,int _type)
	: GreenCard(_name,_type)
{
	switch (type) {
    	case(FOOTSOLDIER) : cost = 0; attackBonus = 2; defenceBonus = 0; minimumHonour = 1; effectCost = 1; effectBonus = 2; break;
    	case(ARCHER)      : cost = 0; attackBonus = 0; defenceBonus = 2; minimumHonour = 1; effectCost = 1; effectBonus = 2; break;
    	case(SIEGER)      : cost = 5; attackBonus = 3; defenceBonus = 3; minimumHonour = 2; effectCost = 2; effectBonus = 3; break;
    	case(CAVALRY)     : cost = 3; attackBonus = 4; defenceBonus = 2; minimumHonour = 3; effectCost = 3; effectBonus = 4; break;
    	case(NAVAL)       : cost = 3; attackBonus = 2; defenceBonus = 4; minimumHonour = 3; effectCost = 3; effectBonus = 4; break;
    	case(BUSHIDO)     : cost = 8; attackBonus = 8; defenceBonus = 8; minimumHonour = 6; effectCost = 3; effectBonus = 8; break;
    }
}
Follower::~Follower()
{
	cout << name << " - was just destroyed" << endl;
}

int Follower::getType()
{
	return FOLLOWER;
}

void Follower::print()
{
	cout << "\n" << name << "\nCost		: " << cost << "\nAttack Bonus	: " << attackBonus
		<< "\nDefense Bonus	: " << defenceBonus << "\nMinimum Honor	: " << minimumHonour 
		<< "\nEffect Bonus	: " << effectCost << "\nEffect Cost	: " << effectBonus 
		<< "\nCard Text 	: " << endl;
}
