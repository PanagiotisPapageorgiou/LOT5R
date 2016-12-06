#include <string>
#include <list>

enum Personalities { ATTACKER=1, DEFENDER, SHOGUN, CHANCELLOR, CHAMPION};
enum Holdings { PLAIN=1, MINE, GOLD_MINE, CRYSTAL_MINE, FARMS, SOLO, STRONGHOLD};
enum Followers { FOOTSOLDIER, ARCHER, SIEGER, CAVALRY, NAVAL, BUSHIDO};
enum Items { KATANA, SPEAR, BOW, NINJATO, WAKIZASHI};
enum TypeOfCard {PERSONALITY = 1,HOLDING,FOLLOWER,ITEM};

class Card{
	protected:
		std::string name;
		int cost;
		int type;
		bool isTapped;
	public:
//--------Constructor - Destructor-----
		Card(std::string,int);
		virtual ~Card();
//--------Accessors--------------------
		std::string get_name();
		int get_cost();
		bool get_isTapped();
		int get_type();
		int get_category();
		virtual int getType();
//--------Mutators-------------
		void set_name(std::string);
		void set_cost(int&);
		void set_isTapped(bool);
//--------Print functions------
		void print_name();
		void print_cost();
		void print_isTapped();
		virtual void print_type();
		virtual void print();
};

class GreenCard:public Card{
	protected:
		int attackBonus;
		int defenceBonus;
		int minimumHonour;
		std::string cardText;
		int effectCost;
		int effectBonus;
		bool bought;
	public:
//----Constructor-Destructor-------
		GreenCard(std::string,int);
		virtual ~GreenCard(); //den eimai sigouros gia virtual
//----Accessors--------------------
		int get_attackBonus();
		int get_defenceBonus();
		int get_minimumHonour();
		int get_effectCost();
		int get_effectBonus();
		std::string get_cardText();
		bool get_bought();
//----Mutators---------------------
		void set_attackBonus(int&);
		void set_defenceBonus(int&);
		void set_minimumHonour(int&);
		void set_effectCost(int&);
		void set_effectBonus(int&);
		void set_bought(bool);
//----Print functions-------------
		void print_attackBonus();
		void print_defenceBonus();
		void print_minimumHonour();
		void print_effectCost();
		void print_effectBonus();
		void print_bought();
};

class BlackCard:public Card{
	protected:
		bool isRevealed;
	public:
//-----Constructor-Destructor---------
		BlackCard(std::string,int);
		virtual ~BlackCard(); //den eimai sigouros gia virtual
//-----Accessors----------------------
		bool get_Revealed();
//-----Mutators-----------------------
		void set_Revealed(bool);
//-----Prints-------------------------
};

		

