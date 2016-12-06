#include <iostream>
#include "Card.hpp"

using namespace std;

//--------Constructor - Destructor-----

Card::Card(string _name,int _type): name(_name)
{
	isTapped = false;
	cost = 0;
	type = _type;
	//cout << "A card was just created" << endl; //den eimai sigouros me to onoma an tha to vgalei
}

Card::~Card()
{
	cout << "\nA card was just destroyed" << endl;
}

//--------Accessors--------------------

string Card::get_name()
{
	return name;
}
int Card::get_cost()
{
	return cost;
}
bool Card::get_isTapped()
{
	return isTapped;
}

int Card::get_type()
{
	return type;
}

int Card::get_category()
{
	return type;
}
int Card::getType(){}

void Card::print(){}

//--------Mutators-------------

void Card::set_name(string _name)
{
	name = _name;
}
void Card::set_cost(int& _cost)
{
	cost = _cost;
}
void Card::set_isTapped(bool _isTapped)
{
	isTapped = _isTapped;
}

void Card::print_name()
{
	cout << name;
}
void Card::print_cost()
{
	cout << cost;
}
void Card::print_isTapped()
{
	cout << isTapped;
}

void Card::print_type()
{
	cout << type;
}
//----Constructor-Destructor-------

GreenCard::GreenCard(string _name,int _type)
	: Card(_name,_type)
{
	bought = false;
	//cout << "A GreenCard was just created" << endl;
}
GreenCard::~GreenCard()
{
	cout << "\nA GreenCard was just destroyed" << endl;
}

//----Accessors--------------------

int GreenCard::get_attackBonus()
{
	return attackBonus;
}
int GreenCard::get_defenceBonus()
{
	return defenceBonus;
}
int GreenCard::get_minimumHonour()
{
	return minimumHonour;
}
int GreenCard::get_effectCost()
{
	return effectCost;
}
int GreenCard::get_effectBonus()

{
	return effectBonus;
}
string GreenCard::get_cardText()
{
	return cardText;
}

bool GreenCard::get_bought(){
	return bought;
}
//----Mutators---------------------

void GreenCard::set_attackBonus(int& attackB)
{
	attackBonus =  attackB;
}
void GreenCard::set_defenceBonus(int& defenceB)
{
	defenceBonus =  defenceB;
}
void GreenCard::set_minimumHonour(int& minHonour)
{
	minimumHonour =  minHonour;
}
void GreenCard::set_effectCost(int& effectC)
{
	effectCost =  effectC;
}
void GreenCard::set_effectBonus(int& effectB)
{
	effectBonus =  effectB;
}

void GreenCard::set_bought(bool flag)
{
    if(flag == true)
        cout << "EffectBonus purchased" << endl;
	bought = flag;
}

void GreenCard::print_attackBonus(){
	cout << attackBonus;
}
void GreenCard::print_defenceBonus(){
	cout << defenceBonus;
}
void GreenCard::print_minimumHonour(){
	cout << minimumHonour;
}
void GreenCard::print_effectCost(){
	cout << effectCost;
}
void GreenCard::print_effectBonus(){
	cout << effectBonus;
}
void GreenCard::print_bought()
{
	cout << bought;
}

//-----Constructor-Destructor---------

BlackCard::BlackCard(string _name,int _type)
	: Card(_name,_type)
{
	isRevealed = false;
	//cout << "A black card was just created" << endl;
}
BlackCard::~BlackCard()
{
	//cout << "\nA black card was just destroyed" << endl;
}

//-----Accessors----------------------

bool BlackCard::get_Revealed()
{
	return isRevealed;
}

//-----Mutators-----------------------

void BlackCard::set_Revealed(bool _isRevealed)
{
	isRevealed = _isRevealed;
}

