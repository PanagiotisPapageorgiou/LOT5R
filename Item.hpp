class Item:public GreenCard{
	protected:
		int durability;
	public:
//-----Constructor-Destructor--------
		Item(std::string,int);
		~Item();
//-----Accessors----------------------
		int get_durability();
		int getType();
//-----Mutators-----------------------
		void damageItem();
//-----Print Functions----------------
		void print();
		void print_durability();
};
