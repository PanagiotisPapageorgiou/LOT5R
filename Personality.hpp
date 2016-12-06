#include "Card.hpp"
#include "Item.hpp"
#include "Follower.hpp"

class Personality:public BlackCard{
	protected:
		int attack;
		int defence;
		int honour;
		bool isDead;
		int itemlimit;
		int followerlimit;
  		std::list <Item*> ItemList;
  		std::list <Follower*> FollowerList;

	public:
//-----Constructor-Destructor---------
		Personality(std::string,int);
		~Personality();
//-----Accessors----------------------
		int get_attack();
		int get_defence();
		int get_honour();
		bool get_isDead();
		int getType();
		int getFLSize();
		int getILSize();
		void sacrificeThisFollower(std::list<Follower*>::iterator);
		void getFirstFollower(std::list<Follower*>::iterator);
		//int getThisFollowerAttack(std::list<Follower*>::iterator);
		void performSeppuku();
		int getTheFollowerAttack(std::list<Follower*>::iterator);
//-----Mutators-----------------------
		void set_attack(int&);
		void set_defence(int&);
		void set_honour(int&);
		void set_isDead(bool&);
		int equipItem(Item*);
        int equipFollower(Follower*);
        int disarmFollower(Follower*);
        int disarmItem(Item*);
        int IncreaseStats();
        int	DecreaseStats();
		void reduceItemsDurability();
		void reduceHonour();
//-----Print Functions-----------------
		void print();
		void printFollowers();
		void printItems();
		void print_type();
		void print_attack();
		void print_defence();
		void print_honour();
		void print_isDead();
		void print_itemlimit();
		void print_followerlimit();
		void print_Honour();
		void print_numberOfFollowers();
		void print_numberOfItems();
};
