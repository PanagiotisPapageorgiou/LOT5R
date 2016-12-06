#include <iostream>
#include <string.h>
#include "Card.hpp"
#include "Holding.hpp"

using namespace std;

//-----Constructor-Destructor----------
Holding::Holding(string _name,int _type)
	: BlackCard(_name,_type)
{
	chainBonus = 0;
	subHolding = NULL;
	upperHolding = NULL;
	switch (type) {
    	case(PLAIN)        :   cost = 2;  harvestValue = 2;
    	case(MINE)         :   cost = 5;  harvestValue = 3;
    	case(GOLD_MINE)    :   cost = 7;  harvestValue = 5;
    	case(CRYSTAL_MINE) :   cost = 12; harvestValue = 6;
    	case(FARMS)        :   cost = 3;  harvestValue = 4;
		case(SOLO)         :   cost = 2;  harvestValue = 2;
    	case(STRONGHOLD)   :   cost = 0;  harvestValue = 5;
    }
}

Holding::~Holding()
{
	cout << name << " - was just destroyed" << endl;
}

//-----Accessors-----------------------

int Holding::get_harvestValue()
{
	return harvestValue;
}

int Holding::get_chainBonus()
{
	return chainBonus;
}

Holding* Holding::get_subHolding()
{
	return subHolding;
}

Holding* Holding::get_upperHolding()
{
	return upperHolding;
}

int Holding::getType()
{
	return HOLDING;
}
//-----Mutators------------------------

void Holding::set_harvestValue(int& harvestV)
{
	harvestValue = harvestV;
}

void Holding::set_chainBonus(int& chainB)
{
	chainBonus = chainB;
}

void Holding::set_subHolding(Holding* subH)
{
	subHolding = subH;
}
void Holding::set_upperHolding(Holding* upperH)
{
	upperHolding = upperH;
}

void Holding::print()
{
	cout << "\n" << name << "\nCost			: " << cost << "\nHarvestValue	: " << harvestValue << endl;
}

/////////////////////////////////////////////////////////////////////////
//-----Constructor-Destructor-----------

Stronghold::Stronghold(string _name,int _type) : Holding(_name,_type)
{
	isRevealed = true;
	cout << "\nPlayer: " << _name << " has entered the Gameboard!" << endl;
	//cout << "Set honour of player : " << endl;
	//cin >> honour;
	honour = 10;
	cout << "Player: " << _name << " has " << honour << " honour points" << endl;
	//cout << "Set initialDefence of his Stronghold : " << endl;
	//cin >> initialDefence;
	initialDefence = 2;
	cout << "Player: " << _name << " has " << initialDefence << " initialDefence\n" << endl;
	if (name == "nazi") {
		cout << "FUCK NAZI!!!!!!!\nFUCK FASIST!!!\nΦΑΣΙΣΤΕΣ ΚΟΥΦΑΛΕΣ ΕΡΧΟΝΤΑΙ ΚΡΕΜΑΛΕΣ!!" << endl;
		honour = 1;
		initialDefence = -10;
	}
}

Stronghold::~Stronghold()
{
	//cout << "A Stronghold leaved the game" << endl;
}

//-----Accessors------------------------

int Stronghold::get_honour()
{
	return honour;
}

int Stronghold::get_initialDefence()
{
	return initialDefence;
}

//-----Mutators-------------------------

void Stronghold::set_honour(int& _honour)
{
	honour = _honour;
}

void Stronghold::set_initialDefence(int& _initialDefence)
{
	initialDefence = _initialDefence;
}

void Stronghold::print()
{
//einai gia diagrafh???
}

void Holding::print_type()
{
		switch(type) {
    		case(PLAIN) :
                cout << "PLAIN";
                break;
    		case(MINE) :
                cout << "MINE";
                break;
    		case(GOLD_MINE) :
                cout << "GOLD_MINE";
                break;
    		case(CRYSTAL_MINE) :
                cout << "CRYSTAL_MINE";
                break;
    		case(FARMS) :
                cout << "FARMS";
                break;
			case(SOLO)         :
                cout << "SOLO";
                break;
    		case(STRONGHOLD)   :
                cout << "STRONGHOLD";
                break;
    	}
}
void Holding::print_harvestValue()
{
	cout << harvestValue;
}
void Holding::print_NamesubHolding()
{
	subHolding->print_name();
}
void Holding::print_NameupperHolding()
{
	upperHolding->print_name();
}
void Holding::print_Chainbonus()
{
	cout << chainBonus;
}
