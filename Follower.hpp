class Follower:public GreenCard{
	public:
//----Constructor-Destructor--------
		Follower(std::string,int);
		~Follower();
//----Print Functions---------------
		void print();
//----Accessors---------------------
		int getType();
};
