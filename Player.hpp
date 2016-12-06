#include <list>
//#include "Personality.hpp"
//#include "Holding.hpp"
#include "DeckBuilder.hpp"

class Player {
		std:: list<GreenCard*>* FateDeck;
		std:: list<BlackCard*>* DynastyDeck;
		std:: list<GreenCard*>*  hand;
		std:: list<BlackCard*>*  provinces;
		std:: list<Personality*>*  army;
		std:: list<Holding*>*  holdings;
		Stronghold* Stats;
		int provincesLeft,turn_money;
		TypeConverter Converter;
	public:
		Player(std::list<GreenCard*>* , std::list<BlackCard*>*);
		~Player();
//-------------------------------------------------------------------------//
//------------------------startingPhase-----------------------------------//
//-----------------------------------------------------------------------//
        void initialize_money();
		void untapEverything();
		void drawFateCard();
		void drawDynastyCard();
		void revealProvinces();
		void printHand();
		void printProvinces();
		void printArmy();
		void printHoldings();
//-------------------------------------------------------------------------//
//------------------------equipPhase--------------------------------------//
//-----------------------------------------------------------------------//
		void need_more_Money(int );
		void equipPersonalities();
		void AttachItem(int);
		bool Buy_Item_Follower(std::list<Personality*>::iterator, std::list<GreenCard*>::iterator);
//-------------------------------------------------------------------------//
//------------------------battlePhase-------------------------------------//
//-----------------------------------------------------------------------//
		void FIGHT(std::list<Personality*>& , int );
		int targetProvince(int& );
		void destroyBattleParticipants(std::list<Personality*>&);
		void RetireSoldier(Personality* );
		void IncreaseTheirStats(std::list<Personality*>&);
		void DecreaseTheirStats(std::list<Personality*>&);
//-------------------------------------------------------------------------//
//------------------------economyPhase------------------------------------//
//-----------------------------------------------------------------------//
		Holding* LookforUpperHolding(int );
		Holding* LookforSubHolding(int );
		void Chain_Mines();
		void set_chainBonuses();
		void BuyProvince();
		int availableProvinces();
//-------------------------------------------------------------------------//
//------------------------finalPhase--------------------------------------//
//-----------------------------------------------------------------------//
		void discardSurplusFateCards(int&);
		int handsize();
//-------------------------------------------------------------------------//
//--------------------------------Other-----------------------------------//
//-----------------------------------------------------------------------//
        char take_answer();
        int choosePersonality();
        int chooseHolding();
        int chooseHand();
        int chooseProvince(int);
		void lostOneProvince();
		Stronghold* get_Stats();
		int hand_minimum_Cost();
		int provinces_minimum_Cost();
		void  harvestStrongHold();
		bool affordBuyCard(int ,bool );
		bool has_untapped_army();
		bool has_untapped_holdings();
		bool has_tapped_army();
		int Total_BattleStats(list<Personality*>& ,int );
		std::list<BlackCard*>::iterator get_firstProvince();
		void get_FirstSoldier(std::list<Personality*>::iterator);		//xreiazetai?
		int getArmySize();	//xreiazetai?
		void eraseFromArmy(std::list<Personality*>::iterator);
		std::list<Personality*>::iterator goAfterTheLastSoldier(); //xreiazetai?
		void destroyProvince(std::list<BlackCard*>::iterator );
		int numberofprovince();
		bool has_army();
		bool has_hand();
		bool has_Revealed_provinces();
		void print();
    	void printBattleList(list<Personality*> battlelist);
};

int lengthOfInt(int);
