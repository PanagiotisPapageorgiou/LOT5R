#include <iostream>
#include "Player.hpp"
#include <stdlib.h>

using namespace std;


Player::Player(list<GreenCard*>* GreenDeck, list<BlackCard*>* BlackDeck)
	: FateDeck(GreenDeck) , DynastyDeck(BlackDeck)
{
	int i;
	string _name;
	cout << "What is the name of this Player?" << endl;
	cin >> _name;
	hand = new list<GreenCard*>();
	provinces = new list<BlackCard*>();
	army = new list<Personality*>();
	holdings = new list<Holding*>();
	Stats = new Stronghold(_name,STRONGHOLD);
	for (i = 0; i < 5; i++) //fuck me why??????
		this->drawFateCard();
	for (i = 0; i < 4; i++)
		this->drawDynastyCard();

	provincesLeft = 1;

}

Player::~Player()
{
	delete hand;
	delete provinces;
	delete army;
	delete holdings;
    delete Stats;
}

//-------------------------------------------------------------------------//
//------------------------startingPhase-----------------------------------//
//-----------------------------------------------------------------------//

void Player::initialize_money()
{
    turn_money = 0;
}

void Player::untapEverything()
{
	list<BlackCard*>::iterator it;
	list<Holding*>::iterator it2;
	list<Personality*>::iterator it3;

	if (provinces->size() > 0) {
		for(it = provinces->begin(); it != provinces->end(); it++)
			(*it)->set_isTapped(false);
	}
	if (holdings->size() > 0){
		for(it2 = holdings->begin(); it2 != holdings->end(); it2++)
			(*it2)->set_isTapped(false);
	}
	if (army->size() > 0) {
		for(it3 = army->begin(); it3 != army->end(); it3++)
			(*it3)->set_isTapped(false);
	}
	Stats->set_isTapped(false);
	cout << "\nEverything was untapped\n" << endl;
}

void Player::drawFateCard()
{
    if(FateDeck->size() <= 0){
        cout << "No cards left in Fate Deck!" << endl;
        return;
    }
	hand->push_back(FateDeck->back());
	FateDeck->pop_back();
}

void Player::drawDynastyCard()
{
    if(DynastyDeck->size() <= 0){
        cout << "No cards left in Dynasty Deck!" << endl;
        return;
    }
	provinces->push_back(DynastyDeck->back());
	DynastyDeck->pop_back();
}


void Player::revealProvinces()
{
	list<BlackCard*>::iterator it;

	if(provinces->size() > 0){
		for(it = provinces->begin(); it != provinces->end(); it++)
			(*it)->set_Revealed(true);
	}
}

//-------------------------------------------------------------------------//
//------------------------equipPhase--------------------------------------//
//-----------------------------------------------------------------------//

void Player::need_more_Money(int money_needed)
{
    list<Holding*> ::iterator it;
    //cout << "\nDo you want to use (untapped) Holdings to harvest money? (Y/N) (You have " << turn_money << " gold)" << endl;
        if(has_untapped_holdings() == false)
            return;
        this->printHoldings();
        cout << "Select a Holding to harvest!" << endl;
        do{
            it = holdings->begin();
            advance(it, chooseHolding() - 1);
        }while((*it)->get_isTapped() == true);
        (*it)->set_isTapped(true);
        turn_money += (*it)->get_harvestValue() + (*it)->get_chainBonus();
        if(turn_money < money_needed){
            cout << "Your money still is not enough to buy " << endl;
            affordBuyCard(money_needed,true);
            need_more_Money(money_needed);
        }
        else{
            cout << "Enough money have been gathered! (You have " << turn_money << " gold)" << endl;
        }
}

void Player::equipPersonalities()
{
	list<Personality*>::iterator it1;
	list<GreenCard*>::iterator it2;

	int Greenchoice;
	char answer;

	if(!has_army())
		 return;

	cout << "Do you want to equip your Personalities with items? (Y/N)" << endl;
	affordBuyCard(0,true);
	answer = take_answer();
	if(answer == 'N') return;
	while( (affordBuyCard(hand_minimum_Cost(),false)) && (has_hand()) ) {
	    this->printArmy();
        this->printHand();
        cout << "Select an Item or Follower to equip with : " << endl;
        affordBuyCard(0,true);
        Greenchoice = chooseHand();
        it2 = hand->begin();
		advance(it2 , Greenchoice - 1);
		if((*it2)->get_cost() <= turn_money){
		    this->AttachItem(Greenchoice);
		}
		else{
			cout << "Sorry you don't have enough money for this." << endl;
            if(affordBuyCard((*it2)->get_cost(),true) == true) {
            	cout << "\nDo you want to use (untapped) Holdings to harvest money \nin order to buy this province? (Y/N) (You have " << turn_money << " gold)" << endl;
        		answer = take_answer();
            	if (answer == 'N')
            		return;
            	this->need_more_Money((*it2)->get_cost());
            	this->AttachItem(Greenchoice);
            }
		}
		cout << "Do you want to buy another Item or Follower (Y/N)? " << endl;
        affordBuyCard(0,true);
        answer = take_answer();
        if(answer == 'N')
            return;
        continue;
    }
    if (hand->size() > 0) cout << "You can't buy anything" << endl; //Apo th while vgainei mono an den mporei na agorasei tpt, alliws kanei return
}

void Player::AttachItem(int AttachChoice)
{
    list<Personality*>::iterator itP;
    list<GreenCard*>::iterator itG;

    itG = hand->begin();
	advance(itG,AttachChoice - 1);

    int type, choice;
    char answer;
    bool bought = false;

    cout << "Select a Personality to equip (0 to EXIT)" << endl;
    this->printArmy();
    itP = army->begin();
	choice = choosePersonality();
	if (choice == 0) return; 
    advance(itP,choice - 1);
    if((*itP)->get_honour() >= (*itG)->get_minimumHonour()){
        type = (*itG)->getType();
        if(type == ITEM){
            if((*itP)->getILSize() < 4)
                bought = Buy_Item_Follower(itP , itG);
            else
                cout << "This Personality can't carry any more Items" << endl;
        }
        else if(type == FOLLOWER) {
            if((*itP)->getFLSize() < 4)
                bought = Buy_Item_Follower(itP , itG);
            else
                cout << "This Personality can't have any more Followers" << endl;
        }
    }
    else
        cout << "This Personality is not honourable enough" << endl;
    if (bought)
        return;
    cout << "Do you want to equip this follower to another Personality (Y/N)?" << endl;
    answer = take_answer();
    if(answer == 'Y')
        AttachItem(AttachChoice);
}

bool Player::Buy_Item_Follower(list<Personality*>::iterator itP, list<GreenCard*>::iterator itG)
{
    Follower* follower;
	Item* item;

    int type,cost = (*itG)->get_cost() ,effect_cost = (*itG)->get_effectCost();
    char answer;

    type = (*itG)->getType();
    turn_money -= cost;
    // answer = take_answer();
    if (affordBuyCard(effect_cost,true)) {
        cout << "Would you like to purchase the effectBonus too (Y/N)?" << endl;
        answer = take_answer();
        if(answer == 'Y') {
            if (turn_money < effect_cost)
                need_more_Money(effect_cost);
            turn_money -= effect_cost;
            (*itG)->set_bought(true);
        }
    }
    Converter.getCorrectType(*itG, &follower, &item);
    if ( type == ITEM)
        (*itP)->equipItem(item);
    else
        (*itP)->equipFollower(follower);
    if ((*itG)->get_bought() == true)
        cost += effect_cost;
    cout << "(" << cost << " removed)" <<endl;
    hand->erase(itG);
    return true; //gia ta print sthn attach
}
//-------------------------------------------------------------------------//
//------------------------battlePhase-------------------------------------//
//-----------------------------------------------------------------------//

void Player::FIGHT(list<Personality*>& Army, int situation) //situation 1 : attacker, 2 : defender
{
	list<Personality*>::iterator it;
	int choice;
	char answer;
    cout << "Select an untapped Personality to " ;
    if (situation == 1) cout <<  "attack (0 to exit)" << endl;
    else cout << "defend(0 to exit)"  << endl;
    printArmy();
    //VALE NA TYPWNEI MONO ONOMATA APO TO ARMY
    it = army->begin();
	choice = choosePersonality();
	if (choice == 0) return;
    advance(it,choice - 1);
    if ((*it) -> get_isTapped() == true)
        cout << "This personality is tapped!" << endl;
    else {
        cout << "Ready to fight for you sir!!" << endl;
        (*it)->set_isTapped(true); //tap card
        Army.push_front(*it);
    }
	cout << "Do you want to "  ;
    if (situation == 1) cout <<  "attack" ;
    else cout << "defend";
    cout << " with other personalities (Y/N)?" << endl;
    answer = take_answer();
    if ( answer == 'Y' )
        FIGHT(Army, situation);
}

void Player::DecreaseTheirStats(list<Personality*>& Army)
{
	list<Personality*>::iterator it;

	if(!Army.size()) return;
	for(it = Army.begin(); it != Army.end(); it++)
		if(((*it)->getILSize() > 0) || (((*it)->getFLSize() > 0)))
            (*it)->DecreaseStats();
}

void Player::IncreaseTheirStats(list<Personality*>& Army)
{
	list<Personality*>::iterator it;

	if(!Army.size()) return;
	for(it = Army.begin(); it != Army.end(); it++)
		if(((*it)->getILSize() > 0) || (((*it)->getFLSize() > 0)))
            (*it)->IncreaseStats();
}

int Player::targetProvince(int & choice)
{
	list <BlackCard*>::iterator itpro;
    int defence = 0,type;
	Personality* soldier;
	Holding* holding;

    itpro = provinces->begin();
	advance(itpro,choice - 1);
	type = (*itpro)->getType();
	if ( type == HOLDING ) defence = Stats->get_initialDefence();
	else {
		Converter.getCorrectType(*itpro,&soldier,&holding);
		defence = Stats->get_initialDefence(); // we add stronghold defence to personality
		defence += (soldier) -> get_defence();
	}
	cout << "Province defence : " << defence << endl;
	return defence;
}

void Player::destroyBattleParticipants(list <Personality*>& listA)
{
	Personality* soldier;
	list <Personality*>::iterator itP;

	while(listA.size() > 0){
        soldier = listA.front();
		listA.pop_front();
		RetireSoldier(soldier);
	}
}

void Player::RetireSoldier(Personality* soldier)
{
    list <Personality*>::iterator itP;
    for (itP = army->begin(); itP != army->end(); itP++) {
        if ((*itP) == soldier){
            army->erase(itP);
            soldier->performSeppuku();
	    break; //Kane seg gt meta dn uparxei o itP kai kanei ++
        }
    }
}

//-------------------------------------------------------------------------//
//------------------------economyPhase------------------------------------//
//-----------------------------------------------------------------------//

void Player::Chain_Mines()
{
	list<Holding*>::iterator itH;
	Holding* holtptr;

	int type,k;
	//find randomly the first holding
	k = rand() % 2;
	if ( k == 0 ) holdings->reverse();

	for (itH = holdings->begin(); itH != holdings->end(); itH++) {
		type = (*itH)->get_category();
		if (type < MINE || type > CRYSTAL_MINE) continue;
		if ((*itH)->get_upperHolding() == NULL) {
		    //cout << "I am "; (*itH)->print_type(); cout << " - ";
		    //cout << "Attempting to connect with Upper Mine" << endl;
			holtptr = LookforUpperHolding(type);
			//DES THN PERIPTWSH MINE->GOLDMINE KAI GOLDINE
			if (holtptr != NULL) {
			    //cout << "Upper mine Found" << endl;
				(*itH)->set_upperHolding(holtptr);
				holtptr->set_subHolding(*itH);
				}
		}
		if ((*itH)->get_subHolding() == NULL) {
		    //cout << "I am "; (*itH)->print_type(); cout << " - ";
		    //cout << "Attempting to connect with Sub Mine" << endl;
			holtptr = LookforSubHolding(type);
			if (holtptr != NULL) {
			    //cout << "Sub mine Found" << endl;
				(*itH)->set_subHolding(holtptr);
				holtptr->set_upperHolding(*itH);
				}
		}
	}
}

void Player::set_chainBonuses()
{
	list<Holding*>::iterator itH;
	Holding* temp;
	Holding* temp2;
	int type,bonus,countChain = 0;

	for (itH = holdings->begin(); itH != holdings->end(); itH++) {
	    countChain = 0;
		type = (*itH)->get_category();
		if (type < MINE || type > CRYSTAL_MINE) continue;
		temp = (*itH);
		while ((type == MINE) && (temp->get_chainBonus() == 0) && (temp->get_upperHolding() != NULL)) {
			countChain++;
			if (countChain == 2) { //FULL CHAIN
				bonus = 2;
				(*itH)->set_chainBonus(bonus); //MINE
				bonus = 2 * (temp->get_harvestValue());
				temp->set_chainBonus(bonus); //GOLD-MINE
				temp2 = temp->get_upperHolding();
				bonus = 3 * (temp2->get_harvestValue());
				temp2->set_chainBonus(bonus); //CRYSTAL_MINE
				cout << "MINE-GOLDMINE-CRYSTALMINE created! Mine has ChainBonus: " << (*itH)->get_chainBonus() << "\nGold Mine has ChainBonus: " << temp->get_chainBonus()
				<< "\nCrystal Mine has ChainBonus: " << temp2->get_chainBonus() << endl;
				break;
			}
			temp = temp->get_upperHolding();
			if (temp->get_upperHolding() == NULL) { // MNE-GOLDMINE
				bonus = 2;
				(*itH)->set_chainBonus(bonus); //MINE
				temp = (*itH)->get_upperHolding();
				bonus = 4;
				temp->set_chainBonus(bonus); //GOLD_MINE
				cout << "MINE-GOLDMINE created! Mine has ChainBonus: " << (*itH)->get_chainBonus() << "\nGold Mine has ChainBonus: " << temp->get_chainBonus() << endl;
				break;
			}
		}
		if ((type == GOLD_MINE) && ((*itH)->get_chainBonus() == 0) && ((*itH)->get_upperHolding() != NULL) && ((*itH)->get_subHolding() == NULL)) {
			temp = (*itH)->get_upperHolding();
			bonus = 5;
			(*itH)->set_chainBonus(bonus); //GOLD_MINE
			bonus = temp->get_harvestValue();
			temp->set_chainBonus(bonus); //CRYSTAL-MINE
			cout << "GOLDMINE-CRYSTALMINE created! Gold Mine has ChainBonus: " << (*itH)->get_chainBonus() << "\nCrystal Mine has ChainBonus: " << temp->get_chainBonus() << endl;

		}
	}
}

Holding* Player::LookforUpperHolding(int type)
{
	if (type < MINE || type >= CRYSTAL_MINE)
		return NULL;

	list<Holding*>::iterator itH;

	for (itH = holdings->begin(); itH != holdings->end(); itH++)
		if (((*itH)->get_category() == type + 1) && ((*itH)->get_subHolding() == NULL))
			return (*itH);
	return NULL;
}

Holding* Player::LookforSubHolding(int type)
{
	if (type <= MINE || type > CRYSTAL_MINE)
		return NULL;

	list<Holding*>::iterator itH;

	for (itH = holdings->begin(); itH != holdings->end(); itH++)
		if (((*itH)->get_category() == type - 1) && ((*itH)->get_upperHolding() == NULL))
			return (*itH);
	return NULL;
}

int Player::availableProvinces()
{
	list<BlackCard*>::iterator itPro;

	int reveiledCards = 0;;
	for(itPro = provinces->begin(); itPro != provinces->end(); itPro++){
		if((*itPro)->get_Revealed() == true)
			reveiledCards++;
	}
	return reveiledCards;
}

void Player::BuyProvince()
{
	list<BlackCard*>::iterator itPro;
	Holding* tempH;
	Personality* tempP;

	int money_needed,type;
	char answer;

    if (!has_Revealed_provinces())
        return;
    if (affordBuyCard(provinces_minimum_Cost(),false) == false) {//if cant buy the chipest province break;
        cout << "No gold to buy any of the provinces!" << endl;
        return;
    }
    printProvinces();
    cout << "Select a province to buy" << endl;
	itPro = provinces->begin();
	advance(itPro , chooseProvince(availableProvinces()) - 1);
	money_needed = (*itPro)->get_cost();  //cost of desired province
	if (affordBuyCard(money_needed,false) == false) //if total untapped provinces can provide the money
		cout << "Can't purchase this , not enough money" << endl;
	else {
        if (turn_money >= money_needed) {
        	cout << "Purchase completed successfully! (" << money_needed << " removed)" <<endl;
        	turn_money -= money_needed;
        	type = (*itPro)->getType();
       	 	Converter.getCorrectType(*itPro, &tempP, &tempH);
       	 	if ( type == HOLDING ) {
        		tempH->set_Revealed(true);
        		tempH->set_isTapped(true);
        		holdings->push_back(tempH);
        	}
       		else if (type == PERSONALITY){
        		tempP->set_Revealed(true); // otan ta agorazeis den ta kanei print meta
        		army->push_back(tempP);
       		}
       		provinces->erase(itPro); //erase it from provinces
        	drawDynastyCard();
    	}
    	else {
    		cout << "\nDo you want to use (untapped) Holdings to harvest money \nin order to buy this province? (Y/N) (You have " << turn_money << " gold)" << endl;
        	answer = take_answer();
            if (answer == 'Y')
            	need_more_Money(money_needed); //LEW NA TO KANOUME AN DEN MPOREI NA KANEI UNTAP
        }
    }
	drawFateCard();
    cout << "\nWould you like to purchase any of the other provinces? (Y/N) " << endl;
    affordBuyCard(0,true);
    answer = take_answer();
    if(answer == 'Y')
        BuyProvince();
	return ;
}

//-------------------------------------------------------------------------//
//--------------------------endPhase--------------------------------------//
//-----------------------------------------------------------------------//

void Player::discardSurplusFateCards(int& choice)
{
	list <GreenCard*>:: iterator itH;
	itH = hand->begin();
	advance(itH , choice - 1);
	delete *itH;
	hand->erase(itH);
}

int Player::handsize()
{
	return hand->size();
}

//-------------------------------------------------------------------------//
//--------------------------------Other-----------------------------------//
//-----------------------------------------------------------------------//

char Player::take_answer()
{
    char answer;
    do{
        cin >> answer;
    }while((answer != 'Y') && (answer != 'N'));
    //cout << "answer : " << answer << endl;
    return answer;
}

int Player::choosePersonality()
{
    int choice;
    do {
        cin >> choice;
    }while ((choice != 0) && (choice < 1) || (choice > army->size()));
    return choice;
}

int Player::chooseHolding()
{
    int choice;
    do {
        cin >> choice;
    }while ((choice < 1) || (choice > holdings->size()));
    return choice;
}

int Player::chooseHand()
{
    int choice;
    do {
        cin >> choice;
    }while ((choice < 1) || (choice > hand->size()));
    return choice;
}

int Player::chooseProvince(int size)
{
    int choice;
    cout << "Choose province (1-" << size << "). " << endl;
    do {
        cin >> choice;
    }while ((choice < 1) || (choice > size));
    return choice;
}

void Player::lostOneProvince()
{
	provincesLeft--;
}

Stronghold* Player::get_Stats()
{
	return Stats;
}

int Player::provinces_minimum_Cost()
{
	list<BlackCard*>::iterator itPro;

	int minimumCost;
	itPro = provinces->begin();
	minimumCost = (*itPro)->get_cost();
	for(itPro = provinces->begin(); itPro != provinces->end(); itPro++){
	    if ((*itPro)->get_Revealed() == true)
            if( (*itPro)->get_cost()  < minimumCost)
                minimumCost = (*itPro)->get_cost();
	}
	//cout << "--------- " << minimumCost << " ------------" << endl;
	return minimumCost;
}

int Player::hand_minimum_Cost()
{
	list<GreenCard*>::iterator itH;

	int minimumCost;
	minimumCost = (*(hand->begin()))->get_cost();
	for(itH = hand->begin(); itH != hand->end(); itH++){
		if( (*itH)->get_cost()  < minimumCost)
			minimumCost = (*itH)->get_cost();
	}
	//cout << "--------- " << minimumCost << " ------------" << endl;
	return minimumCost;
}

void Player::harvestStrongHold()
{
	if (Stats->get_isTapped() == false) //gia pan endexomeno
		Stats->set_isTapped(true);
	turn_money = Stats->get_harvestValue();
}

bool Player::affordBuyCard(int money_needed , bool print) //if total money is more than money needed return true;
{
	list<Holding*>::iterator itH;
	int total_money,harvest_money;
	total_money = turn_money;
	for ( itH = holdings->begin(); itH != holdings->end(); itH++ )
		if ((*itH)->get_isTapped() == false)
			total_money += (*itH)->get_harvestValue() + (*itH)->get_chainBonus();
    if (print == true) {
        harvest_money = total_money - turn_money;
        if (money_needed != 0)
            cout << "Money needed : " << money_needed << " | ";
        cout << "Gold you have : " << turn_money << " | Max gold you can harvest : " << harvest_money << endl;
    }
    if (money_needed > total_money)
        return false;
	return true;
}

bool Player::has_untapped_army() //return true if he has at least one personality unttaped
{
	list<Personality*>::iterator it1;
	if (!army->size())
        cout << "No army at all" << endl;
	for(it1 = army->begin(); it1 != army->end(); it1++)
		if((*it1)->get_isTapped() == false) return true;
	cout << "No untapped personality" << endl;
	return false;
}

bool Player::has_untapped_holdings() //return true if he has at least one holding unttaped
{
	list<Holding*>::iterator it1;
	for(it1 = holdings->begin(); it1 != holdings->end(); it1++)
		if((*it1)->get_isTapped() == false) return true;
	cout << "No untapped Holding to withdraw money" << endl;
	return false;
}

bool Player::has_tapped_army() //return true if he has at least one personality unttaped
{
	list<Personality*>::iterator it1;
	for(it1 = army->begin(); it1 != army->end(); it1++)
		if((*it1)->get_isTapped() == false) return true;
	cout << "No tapped personality" << endl;
	return false;
}

int Player::Total_BattleStats(list<Personality*>& Army, int condition) //1 : attack , 2 : defend
{
    list<Personality*>::iterator itP;
    int total = 0;
	IncreaseTheirStats(Army);
    for(itP = Army.begin(); itP != Army.end(); itP++)
        if (condition)
            total += (*itP)->get_attack();
        else
            total += (*itP)->get_defence();
    return total;
}

list<BlackCard*>::iterator Player::get_firstProvince()
{
	return provinces->begin();
}

void Player::get_FirstSoldier(list<Personality*>::iterator itP){
	itP = army->begin();
}

int Player::getArmySize()
{
	return army->size();
}

void Player::destroyProvince(list<BlackCard*>::iterator itPro)
{
	cout << "Goodbye Province" << endl;
	provinces->erase(itPro);
	delete (*itPro);
	this->lostOneProvince();
}

int Player::numberofprovince() //mhpws na thn vgaloume
{
	return provincesLeft;
}

bool Player::has_army()
{
	if (!army->size()) {
        cout << "Player has no army" << endl;
        return false;
	}
	return true;
}

bool Player::has_hand()
{
	if (!hand->size()) {
        cout << "Player has no hand Cards" << endl;
        return false;
	}
	return true;
}

bool Player::has_Revealed_provinces()
{
    list<BlackCard*>::iterator itPro;
	for(itPro = provinces->begin(); itPro != provinces->end(); itPro++)
		if((*itPro)->get_Revealed() == true) return true;
	cout << "No provinces left to buy" << endl;
	return false;
}

void Player::print()
{
	cout << Stats->get_name() << endl;
	printProvinces();
	printArmy();
	printHoldings();
}
