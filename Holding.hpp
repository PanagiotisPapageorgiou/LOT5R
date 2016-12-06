class Holding:public BlackCard{
	protected:
		int harvestValue;
		int chainBonus;
		Holding* subHolding;
		Holding* upperHolding;
	public:
//-----Constructor-Destructor----------
		Holding(std::string,int);
		~Holding();
//-----Accessors-----------------------
		int get_harvestValue();
		int get_chainBonus();
		Holding* get_subHolding();
		Holding* get_upperHolding();
		int getType();
//-----Mutators------------------------
		void set_harvestValue(int&);
		virtual void set_chainBonus(int&);
		void set_subHolding(Holding*);
		void set_upperHolding(Holding*);
//-----Print Functions-----------------
		void print();
		void print_type();
		void print_harvestValue();
		void print_NamesubHolding();
		void print_NameupperHolding();
		void print_Chainbonus();
};

class Stronghold:public Holding{
	protected:
		int honour;
		int initialDefence;
	public:
//-----Constructor-Destructor-----------
		Stronghold(std::string,int);
		~Stronghold();
//-----Accessors------------------------
		int get_honour();
		int get_initialDefence();
//-----Mutators-------------------------
		void set_honour(int&);
		void set_initialDefence(int&);
//-----Print Functions------------------
		void print();
};
