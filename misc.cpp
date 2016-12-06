#include <iostream>
#include "Gameboard.hpp"

using namespace std;

void Gameboard :: gameplay(PlayerComm &pl,int turn)
{

	int flag = 1;
	int choice = 0;
	while(true){
	    if(turn == 1){
	        pl.sendMessage("Opponent starts turn");
            startingPhase();
            equipPhase();

            if(player->has_untapped_army())
            {
                cout<<"You will conduct your battle phase ? (1 yes/0 no) :";
                cin>>choice;
                if(choice == 1)
                {
                    pl.sendMessage("Attacking to the opponent");
                    attack(pl);
                }
                else{
                    pl.sendMessage("No attack today");
                }
            }
            economyPhase();
            endPhase();
            cout<<"Press -1 to terminate the program : ";
            cin>>flag;

            if(flag == -1){
                pl.sendMessage("Terminate");
                break;
            }else{
                pl.sendMessage("End of Turn");
                turn = !turn;
            }
	    }
	    else{
	    	cout<<"Waiting for the other player to finish"<<endl;
            string *message = pl.readMessage();
            if( strcmp( (*message).c_str() , "Terminate") == 0 )
                break;
            else if(strcmp((*message).c_str() , "End of Turn")==0)
                turn = !turn;
            else if(strcmp((*message).c_str() , "Attacking to the opponent")==0){
                cout<<"I am receiving attack"<<endl;
                defend(pl);
            }
            else
                cout<<*message<<endl;
	    }
	    sleep(1);
	}
}
