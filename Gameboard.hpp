#include "Player.hpp"
#include "PlayerComm.hpp"

class Gameboard{
	Player* player;
    DeckBuilder* Deck;
	//Bale na krataei oria kartwn
	public:
		Gameboard();
		~Gameboard();
        void attack(PlayerComm &);
        void defend(PlayerComm &);
		void initialiseGameboard(int);
		void gameplay(PlayerComm &,int);
		void startingPhase();
		void equipPhase();
		void economyPhase();
		void endPhase();
		bool checkWinningCondition();
		void Consequences(std::list<Personality*>& List,Player*,int);
		void printGameStatistics();

};
