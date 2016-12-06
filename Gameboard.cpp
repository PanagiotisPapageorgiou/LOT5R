#include <iostream>
#include "Gameboard.hpp"
#include <stdlib.h>

using namespace std;

std::string itoa(int value, int base) {

/**
	 * C++ version 0.4 std::string style "itoa":
	 * Contributions from Stuart Lowe, Ray-Yuan Sheu,
	 * Rodrigo de Salvo Braz, Luc Gallant, John Maloney
	 * and Brian Hunt
*/
	
	std::string buf;
	
	// check that the base if valid
	if (base < 2 || base > 16) 
	return buf;
	enum { kMaxDigits = 35 };
	buf.reserve( kMaxDigits ); // Pre-allocate enough space.
	
	int quotient = value;
	
	// Translating number to string with base:
	do {
		buf += "0123456789abcdef"[ std::abs( quotient % base ) ];
		quotient /= base;
	} while ( quotient );

	// Append the negative sign
	if ( value < 0) buf += '-';
	
	std::reverse( buf.begin(), buf.end() );
	return buf;
}

Gameboard::Gameboard()
{
				    //TO DECKBUILDER EINAI MOUFA,DN FTIAXNEI AN PARATHRHSEIS DIAFORETIKA DECKS
					//FTIAXNEI PANTA TA IDIA DECKS KAI APLA TA DINEIS DIAFORETIKA ANAKATEMENA STON KATHENA
					//PEACE - AXRHSTO SXOLIO
					//DEN THA ORISW ENA DECKBUILDER MONO GT MOLIS GINETAI DELETE MIA KARTA APO DECKS TOU ENOS PAIKTH THA GINETAI K 						APO ALLOU

cout << "|---------------------------------------------------------------------|" << endl
<<      "|  |||         ||=======|| /////////////  ||=======                   |" << endl
<<      "|  |||         ||       ||      |||       ||                          |" << endl
<<      "|  |||         ||       ||      |||       ||______                    |" << endl
<<      "|  |||         ||       ||      |||       ========|                   |" << endl
<< 		"|  |||_______  ||_______||      |||              ||                   |" << endl
<< 		"|  |||ZZZZZZZ  ||=======||      |||       ZZZZZZZZZ                   |" << endl
<< 		"|      _______      ___   ____        ___    __________      _______  |" << endl
<< 		"|      |||ZZZZ||    |||   |||||       |||   ||/||||||||     |/||||||  |" << endl
<< 		"|      |||     ||   |||   |||||||     |||  |||      |||    |||        |" << endl
<< 		"|      |||     ||   |||   |||  |||    |||  |||             ||||____   |" << endl
<< 		"|      |||ZZZZzz    |||   |||   |||   |||  |||   |||||||    ||||||||  |" << endl
<< 		"|      |||  zzzz    |||   |||     ||| |||  |||       |||         |||  |" << endl
<< 		"|      |||    zzzz  |||   |||       |||||  |||====== |||   _____||||  |" << endl
<< 		"|      |||     zzzz |||   |||        ||||  |||======|||    ||||||||   |" << endl
<<      "|                                                                     |" << endl
<< 		"|  CREATED BY:                                                        |" << endl
<< 		"|                                                                     |" << endl
<< 		"| sdi1100150: Vasilis Samartzis  AND  sdi1100151: Panos Papageorgiou  |" << endl
<< 		"|                                                                     |" << endl
<< 		"|                      PRESS [Enter] TO PLAY                          |" << endl
<< 		"|      CLOPYRIGHT 2013     TRADEMARK KAIBA CORPORATION                |" << endl
<< 		"|_____________________________________________________________________|" << endl << endl << endl;


    cin.clear();
    cin.get();
    cin.ignore(256,'\n');

	cout << "WELCOME TO LEGEND OF THE 5 RINGS!" << endl;

	initialiseGameboard(1);

}

Gameboard::~Gameboard()
{

    delete Deck;
    delete player;

	cout << "Thank you for playing! This message will never be read\n" <<
	"thanks to SEGMENTATION FAULT!!" <<	endl;
}

void Gameboard::initialiseGameboard(int number)
{
	list<GreenCard*>* FateDeck;
	list<BlackCard*>* DynastyDeck;

	int i = 0, Honour = 0;

    Deck = new DeckBuilder();		//DHMIOURGIA DECKS GI AUTON TON PAIKTH - TA DECKS OLWN TWN PAIKTWN THA NAI IDIA
												//APLA FTIAXNW EK NEOU ME new DECKS GIA NA MIN EINAI KOINO TO DECK KAI MOLIS
												//XANEI KARTES O ENAS XANEI K O ALLOS
    FateDeck = Deck->createFateDeck();
    DynastyDeck = Deck->createDynastyDeck();
    Deck->deckShuffler(FateDeck);
    Deck->deckShuffler(DynastyDeck);

    player = new Player(FateDeck,DynastyDeck);

}

void Gameboard::startingPhase()
{
cout << "//-------------------------------------------------------------------------//\n"
<< "//------------------------startingPhase-----------------------------------//\n" <<
"//-----------------------------------------------------------------------//\n" << endl;
    player->initialize_money();
	player->untapEverything();
	player->drawFateCard();
	player->revealProvinces();
	player->printHand();
	player->harvestStrongHold();
}

void Gameboard::equipPhase()
{
cout << "//-------------------------------------------------------------------------//\n"
<< "//------------------------equipPhase--------------------------------------//\n"
<< "//-----------------------------------------------------------------------//\n" << endl;
	player->equipPersonalities();
}

void Gameboard::Consequences(list <Personality*>& List, Player* player, int damage)
{
		list <Personality*>::iterator itP;
		list <Follower*>::iterator itF;
		list <BlackCard*>::iterator itPro;
		list <Personality*>::iterator ita;
		list <Personality*>::iterator itb;

		unsigned int PersonChoice = 0,FollowerChoice = 0;
		// delete attackers personalities until damage is 0

		//player->IncreaseTheirStats(List);
		while((damage > 0) && (List.size() > 0)) {
			cout << "Select a Personality and/or Followers to sacrifice.\n(You have to sacrifice " << damage << " more points" << endl;
			player->printBattleList(List);
			cin >> PersonChoice;
			itP = List.begin();
			while((PersonChoice < 1) || (PersonChoice > List.size()))
				cin >> PersonChoice;
			advance(itP,PersonChoice - 1);
			if((*itP)->getFLSize() > 0){
				cout << "This Personality has Followers,select Followers to sacrifice first." << endl;
				(*itP)->reduceHonour();
				while((damage > 0) && ((*itP)->getFLSize() > 0)){
					cout << "Select a Follower to sacrifice." << endl;
					(*itP)->printFollowers();
					cin >> FollowerChoice;
					(*itP)->getFirstFollower(itF);
					while((FollowerChoice < 1) || (FollowerChoice > ((*itP)->getFLSize())))
						cin >> FollowerChoice;
					advance(itF,FollowerChoice - 1);
					damage = damage - (*itP)->getTheFollowerAttack(itF);
					(*itP)->sacrificeThisFollower(itF);
				}
				if(damage <= 0) break;
			}
			damage = damage - (*itP)->get_attack();

			player->RetireSoldier(*itP);
			List.erase(itP);
		}
		player->DecreaseTheirStats(List);
		if(List.size() > 0)
			for(int i = 0; i < List.size(); i++){
				itP = List.begin();
				advance(itP,i);
				(*itP)->reduceItemsDurability();
				(*itP)->reduceHonour();
				if((*itP)->get_honour() == 0){
					player->RetireSoldier(*itP);
					List.erase(itP);
					i--;
                    if(List.size() == 0) break;
				}
			}
}

void Gameboard::attack(PlayerComm &pl)
{
    list<Personality*> AttackList;
    int total_attack,enemyProvinces,target,damage,result = 1,choice;
    string message; //b is from buffer

    //while (result) {

        //Count and send Total Attack (1-2)
        player->FIGHT(AttackList,1);
        if (AttackList.size() == 0) // no untapped army
            return;
        total_attack = player->Total_BattleStats(AttackList,1);
        message = itoa (total_attack,10);
        pl.sendMessage(message.c_str());

        cout<<"Waiting for opponent to send available provinces..."<<endl; //(3)
        //Received available provinces nad choose target (4-5)
        message = *(pl.readMessage());
        enemyProvinces = atoi(message.c_str());
		cout << "Attacker -> NO.PRO : " << enemyProvinces << endl;
        target = player->chooseProvince(enemyProvinces);
		message = itoa (target,10);
        pl.sendMessage(message.c_str());

        cout<<"Waiting for opponent to send battle result..."<<endl; //(6-8)

        //Receives the results (9)
        message = (*pl.readMessage());
		cout << "Attacker -> damage(message) : " << message << endl;
        damage = atoi(message.c_str());
		cout << "Attacker -> damage : " << damage << endl;
        if (damage == 0) {
            cout << "Target successfully destroyed\nYou won the Battle" << endl;
            return;
        }
        else if (damage < total_attack) {
            cout << "You win not perfect!!!" << endl;
            Consequences(AttackList , player ,damage);
        }
        else if (damage == -1) {
            cout << "Tie!!!" << endl;
            player->destroyBattleParticipants(AttackList);
        }
        else if (damage == -2) {
            cout << "Lose everything" << endl;
            player->destroyBattleParticipants(AttackList);
        }
		//player->DecreaseTheirStats(AttackList);
        cout<<"Waiting for opponent to tell the result of BattlePhase..."<<endl; //(10)

        //Receives the results (11)
        message = *(pl.readMessage());
        result = atoi(message.c_str());
		cout << "Attacker-> result = " << result << endl;
        //if result is :0 - stop
        //else :1 can attack again (loop)

        while (AttackList.size() > 0) AttackList.pop_front();

    // if (result == 0) //Destroed province-game continues
        if (result == 2) {
            cout << "No enemy provinces left...You won!!!\nCongrats and thank you for playing" << endl;
            // code here
        }
        if(result == 1){
            cout <<"Do you want to attack again ? (1 yes/0 no) :" << endl;
            cin >> choice;
            if(choice == 1) {
                pl.sendMessage("Attacking to the opponent");
                attack(pl);
            }
            else{
                pl.sendMessage("No attack today");
                return;
            }
        }

}

void Gameboard::defend(PlayerComm &pl)
{
    list<Personality*> DefendList;
    int result = 1,total_attack,total_defense,damage,target,provinceDEF;
    list<BlackCard*>::iterator itPro;
	string message;

    cout<<"Waiting for opponent to send his total attack..."<<endl;
    message = *(pl.readMessage());
    total_attack = atoi(message.c_str());
    cout << "Defender -> total_attack : " << total_attack << endl;
    message = itoa (player->numberofprovince(),10);
    pl.sendMessage(message.c_str());

    cout<<"Waiting for opponent to send target..."<<endl; //(3)cout << "Defender -> total_attack : " << total_attack << endl;
    message = *(pl.readMessage());
    target = atoi(message.c_str());
	cout << "Defender -> target : " << target << endl;
    provinceDEF = player->targetProvince(target);

    if(player->has_untapped_army()){
        player->FIGHT(DefendList,2);
        total_defense = provinceDEF + player->Total_BattleStats(DefendList,2);
    }

    if(total_attack > total_defense){
        cout << "Attacker won the battle..." << endl;
        damage = total_attack - total_defense;
        if(damage >= provinceDEF){
            damage = 0;
            itPro = player->get_firstProvince();
            cout << "target is: " << target << endl;
            advance(itPro,target - 1);
            player->destroyProvince(itPro);
            cout << "Province : "<< target << " destroyed!" << endl;
            cout << "Target province destroyed!" << endl;
            result = 0;
        }
        player->destroyBattleParticipants(DefendList);
    }
    else if(total_attack == total_defense){
        damage = -1;
        cout << "Tie!!" << endl;
        player->destroyBattleParticipants(DefendList);
    }
    else{
        cout << "We have won the battle!! But the war is not over yet!" << endl;
        damage = -2;
        Consequences(DefendList,player,damage);
    }
	//player->DecreaseTheirStats(DefendList);
	cout << "Defender -> damage : " << damage << endl;
    message = itoa (damage,10);
	cout << "Defender -> damage(message) : " << message << endl;
    pl.sendMessage(message.c_str());

    if(!player->numberofprovince()) result = 2;
    message = itoa (result,10);
    pl.sendMessage(message.c_str());

    while(DefendList.size() > 0) DefendList.pop_front();

    if(result == 1){
        cout <<"Waiting for opponent's choice..." << endl; //(3)
        message = *(pl.readMessage());
		if( strcmp((message).c_str() , "Attacking to the opponent") == 0 )
        	result = 1;
		else return;
    }
    //result changes, it depends on attacker
    if (result == 1)
        defend(pl);
}

void Gameboard::economyPhase()//mhpws na ton onomasoume current?
{
	char answer;
	cout << "//-------------------------------------------------------------------------//\n"
	<< "//------------------------economyPhase------------------------------------//\n"
	<< "//-----------------------------------------------------------------------//\n" << endl;
	cout << "Would you like to buy any of the provinces? (Y/N)" << endl;
    answer = player->take_answer();
    if(answer == 'N') return;
    player->BuyProvince();
    player->Chain_Mines();
    player->set_chainBonuses();
}

void Gameboard::endPhase()
{
	int choice;

cout << "//-------------------------------------------------------------------------//\n"
<< "//--------------------------endPhase--------------------------------------//\n"
<< "//-----------------------------------------------------------------------//\n" << endl;

	while (player->handsize() > 6)	{
		player->printHand();
		cout << "Too many GreenCards in your hand\n " << endl;
		do {
			cout << "Choose which Card you want to discard : \n" << endl;
			cin >> choice;
		}while( (choice < 1) || (choice > player->handsize()) );
		player->discardSurplusFateCards(choice);
	}
    std::cout << "Press [ Enter ] to continue to Statistics...";
    cin.clear(); // Make sure the buffers are clear, you may want to do cin.flush() as well but I am not sure if both are needed.
    cin.get();
    cin.ignore(256,'\n');
	printGameStatistics();

}

void Gameboard::printGameStatistics()
{
	cout << "\nStatistics :\n" << endl;
	player->print();
	player->printHand();
}

bool Gameboard::checkWinningCondition()
{
	/*list<Player*>::iterator itP;
	Player* temp;
	for(int i = 0; i < ListOfPlayers.size(); i++){
		itP = ListOfPlayers.begin();
		advance(itP,i);
		if ((*itP)->numberofprovince() == 0) {
			temp = *itP;
			if (temp != NULL) {
				delete temp;
				ListOfPlayers.erase(itP);
				i--;
			}
		}
	}
	if (ListOfPlayers.size() == 1)
		return true;
	return false;*/
}



