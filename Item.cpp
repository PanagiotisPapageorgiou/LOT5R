#include <iostream>
#include <string>
#include "Card.hpp"
#include "Item.hpp"

using namespace std;

//-----Constructor-Destructor--------

Item::Item(std::string _name,int _type)
	: GreenCard(_name,_type)
{
	switch (type) {
    	case(KATANA)   : cost = 5;  attackBonus = 3; defenceBonus = 3; minimumHonour = 1; effectCost = 5; effectBonus = 6;  durability= 4;  break;
    	case(SPEAR)    : cost = 5;  attackBonus = 2; defenceBonus = 2; minimumHonour = 1; effectCost = 4; effectBonus = 6;  durability= 4;  break;
    	case(BOW)      : cost = 10; attackBonus = 4; defenceBonus = 4; minimumHonour = 2; effectCost = 4; effectBonus = 10; durability= 6;  break;
    	case(NINJATO)  : cost = 15; attackBonus = 6; defenceBonus = 6; minimumHonour = 3; effectCost = 6; effectBonus = 10; durability= 8;  break;
    	case(WAKIZASHI): cost = 20; attackBonus = 8; defenceBonus = 8; minimumHonour = 6; effectCost = 8; effectBonus = 15; durability= 10; break;
    }
}
Item::~Item()
{
	std::cout << name << " - was just destroyed" << std::endl;
}

//-----Accessors----------------------

int Item::get_durability()
{
	return durability;
}

int Item::getType()
{
	return ITEM;
}

//-----Mutators-----------------------

void Item::damageItem()
{
	durability--; //if champions who carry's the item loses the fights
}

void Item::print(){

	std::cout << "\n" << name << "\nCost		: " << cost << "\nAttack Bonus	: " << attackBonus
		<< "\nDefense Bonus	: " << defenceBonus << "\nMinimum Honor	: " << minimumHonour 
		<< "\nEffect Bonus	: " << effectCost << "\nEffect Cost	: " << effectBonus 
		<< "\nDurability	: " << durability << "\nCard Text 	: " << std::endl;
}

void Item::print_durability()
{
	cout << durability;
}
