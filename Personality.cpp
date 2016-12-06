#include <iostream>
#include <string.h>
#include "Personality.hpp"

using namespace std;

//-----Constructor-Destructor---------

Personality::Personality(string _name,int _type)
	: BlackCard(_name,_type)
{
    isDead = true;
	itemlimit = 4;
	followerlimit = 4;

	switch (type) {
    	case(ATTACKER)   :    cost = 5;  attack = 3;  defence = 2;   honour = 2;  break;
    	case(DEFENDER)   :    cost = 5;  attack = 2;  defence = 3;   honour = 2;  break;
    	case(SHOGUN)     :    cost = 15; attack = 10; defence = 5;   honour = 8;  break;
    	case(CHANCELLOR) :    cost = 15; attack = 5;  defence = 10;  honour = 8;  break;
    	case(CHAMPION)   :    cost = 30; attack = 20; defence = 20;  honour = 12; break;
    }
}

Personality::~Personality()
{
	cout << name << " - was just destroyed" << endl;
}

//-----Accessors----------------------

int Personality::get_attack()
{
	return attack;
}
int Personality::get_defence()
{
	return defence;
}
int Personality::get_honour()
{
	return honour;
}
bool Personality::get_isDead()
{
	return isDead;
}

int Personality::getType()
{
	return PERSONALITY;
}

//-----Mutators-----------------------

void Personality::set_attack(int& _attack)
{
	attack = _attack;
}

void Personality::set_defence(int& _defence)
{
	defence = _defence;
}

void Personality::set_honour(int& _honour)
{
	honour = _honour;
}

void Personality::set_isDead(bool& _isDead)
{
	isDead = _isDead;
}


int Personality::equipItem(Item* card)
{
	cout << "Item equipped!" << endl;
	ItemList.push_back(card);
	return 0;
}

int Personality::equipFollower(Follower* follower)
{
	cout << "Follower equipped!" << endl;
	FollowerList.push_back(follower);
	return 0;
}

int Personality::getFLSize()
{
	return FollowerList.size();
}
int Personality::getILSize()
{
	return ItemList.size();
}

int Personality::disarmItem(Item* item)
{
	list<Item*>::iterator it;

	if(ItemList.size() > 0){
		for(it = ItemList.begin(); it != ItemList.end(); it++)
			if(*it == item) {
				(*it)->print();
				it = ItemList.erase (it);
				if(*it != NULL) delete item;
				return 1;
			}
	}
}

int Personality::disarmFollower(Follower *follower)
{
	list<Follower*>::iterator it;

	if(FollowerList.size() > 0){
		for(it = FollowerList.begin(); it != FollowerList.end(); it++)
			if(*it == follower) {
				(*it)->print();
				it = FollowerList.erase (it);
				if(*it != NULL) delete follower;
				return 1;
			}
	}
}

int Personality::IncreaseStats()
{
	list<Item*> temp (ItemList);
	Item* itemtemp;
	while (!temp.empty()) {
		itemtemp = temp.front();
		attack = attack + itemtemp->get_attackBonus();
		defence = defence + itemtemp->get_defenceBonus();
		if (itemtemp->get_bought() == true) {
			attack = attack + itemtemp->get_effectBonus();
			defence = defence + itemtemp->get_effectBonus();
		}
		temp.pop_front();
  	}
	list<Follower*> temp2 (FollowerList);
	Follower* followertemp;
	while (!temp2.empty()) {
		followertemp = temp2.front();
		attack = attack + followertemp->get_attackBonus();
		defence = defence + followertemp->get_defenceBonus();
		if (followertemp->get_bought() == true) {
			attack = attack + followertemp->get_effectBonus();
			defence = defence + followertemp->get_effectBonus();
		}
		temp2.pop_front();
  	}
	cout << "\nIncrease Stats :\n" << endl;
	//this->print();
}

int Personality::DecreaseStats()
{
	list<Item*> temp (ItemList);
	Item* itemtemp;
	while (!temp.empty()) {
		itemtemp = temp.front();
		attack = attack - itemtemp->get_attackBonus();
		defence = defence - itemtemp->get_defenceBonus();
		if (itemtemp->get_bought() == true) {
			attack = attack - itemtemp->get_effectBonus();
			defence = defence - itemtemp->get_effectBonus();
		}
		temp.pop_front();
  	}
	list<Follower*> temp2 (FollowerList);
	Follower* followertemp;
	while (!temp2.empty()) {
		followertemp = temp2.front();
		attack = attack - followertemp->get_attackBonus();
		defence = defence - followertemp->get_defenceBonus();
		if (followertemp->get_bought() == true) {
			attack = attack - followertemp->get_effectBonus();
			defence = defence - followertemp->get_effectBonus();
		}
		temp2.pop_front();
  	}
	cout << "\nDecrease Stats :\n" << endl;
	//this->print();
}

void Personality::print()
{
		cout << "\n" << name << "\nCost	 : " << cost << "\nAttack	 : " << attack
		<< "\nDefense	 : " << defence << "\nHonor	 : " << honour  << "\nFollowers: "
		<< FollowerList.size() << "\nItems	 : " << endl;
		printItems();
		printFollowers();
}

void Personality::printFollowers(){

	list<Follower*>::iterator follower;

	if(!FollowerList.size()) return;
	cout << name << " has " << FollowerList.size() << " Followers : \n" << endl;
	for(follower = FollowerList.begin(); follower != FollowerList.end(); follower++)
		(*follower)->print();
}

void Personality::printItems(){

	list<Item*>::iterator item;

	if(!ItemList.size()) return;
	cout << name << " has " << ItemList.size() << " Items : \n" << endl;
	for(item = ItemList.begin(); item != ItemList.end(); item++)
		(*item)->print();
}

void Personality::getFirstFollower(list<Follower*>::iterator itF)
{
	itF = FollowerList.begin();
}

void Personality::sacrificeThisFollower(list<Follower*>::iterator itF)
{
	FollowerList.erase(itF);
}

/*int Personality::getThisFollowerAttack(list<Follower*>::iterator itF)
{
	return (*itF)->get_attackBonus();
}*/

void Personality::performSeppuku()
{
	delete this;
}
void Personality::reduceHonour()
{
	honour--;
}
void Personality::reduceItemsDurability()
{
	list<Item*>::iterator item;
	int flag = 1;

	if(ItemList.size() > 0){
		for(int i = 0; i < ItemList.size(); i++){
			item = ItemList.begin();
			advance(item,i);
			(*item)->damageItem();
			if((*item)->get_durability() == 0){
				delete (*item);
				ItemList.erase(item);
				i--;
				if(ItemList.size() == 0) break;
			}
		}
	}
}

int Personality::getTheFollowerAttack(std::list<Follower*>::iterator follower)
{
	return (*follower)->get_attackBonus();
}

void Personality::print_type(){
		switch(type) {
    		case(ATTACKER) : cout << "ATTACKER";
    		case(DEFENDER) : cout << "DEFENDER";
    		case(SHOGUN) : cout << "SHOGUN";
    		case(CHANCELLOR) : cout << "CHANCELLOR";
    		case(CHAMPION) : cout << "CHAMPION";
    	}
}

void Personality::print_attack()
{
	cout << attack;
}
void Personality::print_defence()
{
	cout << defence;
}
void Personality::print_honour(){
	cout << honour;
}
void Personality::print_isDead(){
	cout << isDead;
}
void Personality::print_itemlimit(){
	cout << itemlimit;
}
void Personality::print_followerlimit(){
	cout << followerlimit;
}
void Personality::print_Honour(){
	cout << honour;
}
void Personality::print_numberOfFollowers(){
	cout << FollowerList.size();
}
void Personality::print_numberOfItems(){
	cout << ItemList.size();
}
