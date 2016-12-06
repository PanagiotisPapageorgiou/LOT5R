#include <iostream>
#include "Player.hpp"

using namespace std;

int lengthOfInt(int i){

	int length = 1,j = 10;

	if((i >= 0) && (i < 10)) return 1;
	else
		while(i%j != i){
			j = j*10;
			length++;
		}
	return length;
}

void Player::printHand()
{
	list<GreenCard*>::iterator it;
	list<GreenCard*>::iterator stoppedit;
	list <GreenCard*>::iterator previoustopit;

	Follower* follower;
	Item* item;
	it = hand->begin();
	stoppedit = hand->end();
	stoppedit--;
	previoustopit = hand->begin();
	int i = 0,number,length,total_length = 0,stoppedat ,previoustop = 0,slength = 0;
	cout << "\n---------------------------------------------\n";
	cout << Stats->get_name() << "'s hand holds the following: " << endl;
	if (hand->size() > 0) {

		number = hand->size();

		while(i < number){
			for(int j = 0; j < 80; j++) cout << '=';

			cout << "\nName		:|";
			i = previoustop;
			it = previoustopit;
			while(i < number){
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62){
						stoppedit = it;
						stoppedat = i;
						break;
					}
					(*it)->print_name();
					cout << '|';
				(it++);
				i++;
			}
			if(i == number){
				stoppedat = number;
			 	stoppedit = hand->end();
				stoppedit--;
			}

			slength = 0;
			cout << "\nCost		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					slength = (*it)->get_cost();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					(*it)->print_cost();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nAttackBonus	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				slength = (*it)->get_attackBonus();
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				(*it)->print_attackBonus();
				for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nDefenceBonus	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					slength = (*it)->get_defenceBonus();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					(*it)->print_defenceBonus();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nMinimumHonour	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					slength = (*it)->get_minimumHonour();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					(*it)->print_minimumHonour();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nEffect Cost	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					slength = (*it)->get_effectCost();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					(*it)->print_effectCost();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nEffect Bonus	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					slength = (*it)->get_effectBonus();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					(*it)->print_effectBonus();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nDurability	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == ITEM){
					Converter.getCorrectType(*it,&follower,&item);
					slength = (item)->get_durability();
				}
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if((*it)->getType() == ITEM){
					(item)->print_durability();
				}
				if((*it)->getType() == ITEM)
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				else for(int j = 0; j < length-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
			cout << '\n';
			for(int j = 0; j < 80; j++) cout << '=';

			cout << "\n\n";
			total_length = 0;
			previoustop = stoppedat;
			previoustopit = stoppedit;
		}
	}
	else cout << "Has no Hand" << endl;
}
void Player::printProvinces()
{
	list<BlackCard*>::iterator it;
	list <BlackCard*>::iterator stoppedit;
	list <BlackCard*>::iterator previoustopit;
	Personality* soldier;
	Holding* holding;

	it = provinces->begin();
	stoppedit = provinces->end();
	stoppedit--;
	previoustopit = provinces->begin();

	int i = 0,number,length,total_length = 0,stoppedat ,previoustop = 0,slength;
	cout << "\n---------------------------------------------\n";
	//always size > 0
	cout << Stats->get_name() << "'s side holds the following provinces: " << endl;
	if (provinces->size() > 0){

		number = provinces->size();
		cout << "NO OF PROVINCES : " << number << endl;
		while(i < number){
			for(int j = 0; j < 80; j++) cout << '=';
			cout << "\nName		:|";
			i = previoustop;
			it = previoustopit;
			while(i < number){
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62){
						stoppedit = it;
						stoppedat = i;
						break;
					}
					if((*it)->get_Revealed() == true)
						(*it)->print_name();
					else
						for(int j = 0; j < length-1; j++) cout << ' ';
					cout << '|';
				(it++);
				i++;
			}
			if(i == number){
				stoppedat = number;
			 	stoppedit = provinces->end();
				stoppedit--;
			}

			slength = 0;
			cout << "\nCost		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				slength = (*it)->get_cost();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;

					if(total_length > 62) break;
					if((*it)->get_Revealed() == true)
						(*it)->print_cost();
					else
						for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';

					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nAttack		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == PERSONALITY){
					Converter.getCorrectType(*it,&soldier,&holding);
					slength = (soldier)->get_attack();
				}
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
					(soldier)->print_attack();
				else if (((*it)->get_Revealed() == false) && ((*it)->getType() == PERSONALITY))
					for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';
				if((*it)->getType() == PERSONALITY)
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				else for(int j = 0; j < length-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nDefence		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == PERSONALITY){
					Converter.getCorrectType(*it,&soldier,&holding);
					slength = (soldier)->get_defence();
				}
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(soldier)->print_defence();
					else if (((*it)->get_Revealed() == false) && ((*it)->getType() == PERSONALITY))
						for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';
					if((*it)->getType() == PERSONALITY)
						for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					else for(int j = 0; j < length-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nHonour		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;

			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY){
						Converter.getCorrectType(*it,&soldier,&holding);
						slength = (soldier)->get_honour();
					}
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(soldier)->print_Honour();
					else if (((*it)->get_Revealed() == false) && ((*it)->getType() == PERSONALITY))
						for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';
					if((*it)->getType() == PERSONALITY)
						for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					else for(int j = 0; j < length-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\n#Items		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY){
						Converter.getCorrectType(*it,&soldier,&holding);
						slength = (soldier)->getILSize();
					}
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if (((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(soldier)->print_numberOfItems();
					else if (((*it)->get_Revealed() == false) && ((*it)->getType() == PERSONALITY))
						for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';
					if((*it)->getType() == PERSONALITY)
						for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					else for(int j = 0; j < length-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\n#Followers	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY){
						Converter.getCorrectType(*it,&soldier,&holding);
						slength = (soldier)->getFLSize();
					}
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY)) (soldier)->print_numberOfFollowers();
					else if (((*it)->get_Revealed() == false) && ((*it)->getType() == PERSONALITY))
						for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';
					if((*it)->getType() == PERSONALITY)
						for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					else for(int j = 0; j < length-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nHarvest Value	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == HOLDING){
					Converter.getCorrectType(*it,&soldier,&holding);;
					slength = (holding)->get_harvestValue();
				}
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if(((*it)->get_Revealed() == true) && ((*it)->getType() == HOLDING))
					(holding)->print_harvestValue();
				else if(((*it)->get_Revealed() == false) && ((*it)->getType() == HOLDING))
					for(int j = 0; j < lengthOfInt(slength); j++) cout << ' ';
				if((*it)->getType() == HOLDING)
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				else for(int j = 0; j < length-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
			cout << '\n';
			for(int j = 0; j < 80; j++) cout << '=';

			cout << "\n\n";
			total_length = 0;
			previoustop = stoppedat;
			previoustopit = stoppedit;
		}
	}
	else cout << "Has no provinces" << endl;
}

void Player::printArmy()
{
	list<Personality*>::iterator it;
	list <Personality*>::iterator stoppedit;
	list <Personality*>::iterator previoustopit;

	it = army->begin();
	stoppedit = army->end();
	stoppedit--;
	previoustopit = army->begin();

	int i = 0,number,length,total_length = 0,stoppedat ,previoustop = 0,slength = 0;
	cout << "\n---------------------------------------------\n";
	cout << "NO OF PERSONALITIES (aka army) : " << army->size() << endl;
	cout << Stats->get_name() << " has the following Army: " << endl;
	if (army->size() > 0) {

		number = army->size();
		while(i < number){
			for(int j = 0; j < 80; j++) cout << '=';
			cout << "\nName		:|";
			i = previoustop;
			it = previoustopit;
			while(i < number){
				if((*it)->get_Revealed() == true){
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62){
						stoppedit = it;
						stoppedat = i;
						break;
					}
					(*it)->print_name();
					cout << '|';
				}
				(it++);
				i++;
			}
			if(i == number){
				stoppedat = number;
			 	stoppedit = army->end();
				stoppedit--;
			}

			slength = 0;
			cout << "\nAttack		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == PERSONALITY)
					slength = (*it)->get_attack();
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
					(*it)->print_attack();
				for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nDefence		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == PERSONALITY)
					slength = (*it)->get_defence();

					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(*it)->print_defence();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nHonour		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY)
						slength = (*it)->get_honour();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(*it)->print_Honour();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\n#Items		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY)
						slength = (*it)->getILSize();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if (((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(*it)->print_numberOfItems();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\n#Followers	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY)
						slength = (*it)->getFLSize();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY)) (*it)->print_numberOfFollowers();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nTapped    	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if((*it)->get_isTapped() == true){
					cout << "YES";
				}
				else cout << "NO ";
				for(int j = 0; j < length-4; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}

			cout << '\n';
			for(int j = 0; j < 80; j++) cout << '=';

			cout << "\n\n";
			total_length = 0;
			previoustop = stoppedat;
			previoustopit = stoppedit;
		}
	}
	else cout << "Has no Army" << endl;
}

void Player::printHoldings()
{
	list<Holding*>::iterator it;
	list <Holding*>::iterator stoppedit;
	list <Holding*>::iterator previoustopit;

	it = holdings->begin();
	stoppedit = holdings->end();
	stoppedit--;
	previoustopit = holdings->begin();

	int i = 0,number,length,total_length = 0,stoppedat,previoustop = 0,slength = 0;
	cout << "\n---------------------------------------------\n";
	cout << "NO OF HOLDINGS : " << holdings->size() << endl;
	cout << Stats->get_name() << " has the following Holdings: " << endl;
	if (holdings->size() > 0) {
		number = holdings->size();

		while(i < number){
			for(int j = 0; j < 80; j++) cout << '=';
			cout << "\nName		:|";
			i = previoustop;
			it = previoustopit;
			while(i < number){
				if((*it)->get_Revealed() == true){
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62){
						stoppedit = it;
						stoppedat = i;
						break;
					}
					(*it)->print_name();
					cout << '|';
				}
				(it++);
				i++;
			}
			if(i == number){
				stoppedat = number;
			 	stoppedit = holdings->end();
				stoppedit--;
			}

			slength = 0;
			cout << "\nHarvest Value	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				slength = (*it)->get_harvestValue();
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if(((*it)->get_Revealed() == true) && ((*it)->getType() == HOLDING))
					(*it)->print_harvestValue();
				for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
			slength = 0;
			cout << "\nChain Bonus  	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				slength = (*it)->get_chainBonus();
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if(((*it)->get_Revealed() == true) && ((*it)->getType() == HOLDING))
					(*it)->print_Chainbonus();
				for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
   			slength = 0;
			cout << "\nUpper     	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if((*it)->get_upperHolding() != NULL){
					cout << "YES";
				}
				else cout << "NO ";
				for(int j = 0; j < length-4; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
   			slength = 0;
			cout << "\nSub       	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if((*it)->get_subHolding() != NULL){
					cout << "YES";
				}
				else cout << "NO ";
				for(int j = 0; j < length-4; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
   			slength = 0;
			cout << "\nTapped    	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if((*it)->get_isTapped() == true){
					cout << "YES";
				}
				else cout << "NO ";
				for(int j = 0; j < length-4; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}
			cout << '\n';
			for(int j = 0; j < 80; j++) cout << '=';

			cout << "\n\n";
			total_length = 0;
			previoustop = stoppedat;
			previoustopit = stoppedit;
		}
	}
	else cout << "Has no holdings" << endl;
}

void Player::printBattleList(list<Personality*> battlelist)
{
	list<Personality*>::iterator it;
	list <Personality*>::iterator stoppedit;
	list <Personality*>::iterator previoustopit;

	it = battlelist.begin();
	stoppedit = battlelist.end();
	stoppedit--;
	previoustopit = battlelist.begin();

	int i = 0,number,length,total_length = 0,stoppedat ,previoustop = 0,slength = 0;
	cout << "\n---------------------------------------------\n";
	cout << "NO OF BATTLE PARTICIPANTS : " << army->size() << endl;
	cout << Stats->get_name() << " has the following Battle Participants : " << endl;
	if (battlelist.size() > 0) {

		number = battlelist.size();
		while(i < number){
			for(int j = 0; j < 80; j++) cout << '=';
			cout << "\nName		:|";
			i = previoustop;
			it = previoustopit;
			while(i < number){
				if((*it)->get_Revealed() == true){
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62){
						stoppedit = it;
						stoppedat = i;
						break;
					}
					(*it)->print_name();
					cout << '|';
				}
				(it++);
				i++;
			}
			if(i == number){
				stoppedat = number;
			 	stoppedit = battlelist.end();
				stoppedit--;
			}

			slength = 0;
			cout << "\nAttack		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == PERSONALITY)
					slength = (*it)->get_attack();
				length = (*it)->get_name().size() + 1;
				total_length = total_length + length;
				if(total_length > 62) break;
				if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
					(*it)->print_attack();
				for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
				cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nDefence		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
				if((*it)->getType() == PERSONALITY)
					slength = (*it)->get_defence();

					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(*it)->print_defence();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\nHonour		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY)
						slength = (*it)->get_honour();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(*it)->print_Honour();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\n#Items		:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY)
						slength = (*it)->getILSize();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if (((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY))
						(*it)->print_numberOfItems();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}

			slength = 0;
			cout << "\n#Followers	:|";
			total_length = 0;
			i = previoustop;
			it = previoustopit;
			while(i < stoppedat){
					if((*it)->getType() == PERSONALITY)
						slength = (*it)->getFLSize();
					length = (*it)->get_name().size() + 1;
					total_length = total_length + length;
					if(total_length > 62) break;
					if(((*it)->get_Revealed() == true) && ((*it)->getType() == PERSONALITY)) (*it)->print_numberOfFollowers();
					for(int j = 0; j < length-lengthOfInt(slength)-1; j++)	cout << ' ';
					cout << '|';
				i++;
				it++;
			}
			cout << '\n';
			for(int j = 0; j < 80; j++) cout << '=';

			cout << "\n\n";
			total_length = 0;
			previoustop = stoppedat;
			previoustopit = stoppedit;
		}
	}
	else cout << "Has no Battle Participants" << endl;
}
