#include <iostream>
#include <string>
#include <list>
#include <stdlib.h>
#include <time.h>
#include "Gameboard.hpp"

using namespace std;

int main(int argc, char *argv[]){


    char *host = argv[1];
    char *player = argv[5];
    int portToConnect = atoi(argv[2]);
    int portToListen = atoi(argv[3]);
    int turn = atoi(argv[4]);

    PlayerComm pl(argv[1], portToConnect, portToListen);
    pl.init(turn);

    cout<<"I am Player : "<<player<<endl;
    pl.sendMessage(player);
	string * opponent = pl.readMessage();
	cout<<"My opponent is Player : "<< *opponent <<endl;

    sleep(1);

	srand(time(NULL));
	Gameboard game;
	game.gameplay(pl,turn);

	return 0;

}
