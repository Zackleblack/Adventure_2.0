#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

// Global Variables

const int max_health = 50;
int health = max_health;		// The Player's total amount of health
int totalGold = 0;			// Total gold collected

// Fuctions

void Story();
bool AskYesNo(string question);
int RollDie(int sides = 6);
void Ending();
void Adventure();

//	Story

void Story() {

	cout << "-------------------------------------------------------------------------\n";
	cout << "|Welcome to Adventure 2.0!                                              |\n";
	cout << "|In this game you will encounter battles, find gold, and test your luck.|\n";
	cout << "|Your starting health is " << health << ". Good luck!                                 |\n";
	cout << "-------------------------------------------------------------------------\n";

}

//	AskYesNo

bool AskYesNo(string question) {

	char response;

	while (true) {
		cout << question << " (y/n): ";
		cin >> response;
		response = tolower(response);

		if (response == 'y') return true;
		if (response == 'n') return false;

		cout << "Invalid input. Please enter 'y' or 'n' .\n";

	}

}

//	RollDie

int RollDie(int sides) {
	
	return rand() % sides + 1;		// Randomizes the number
}

//	Adventure

void Adventure() {
	cout << "\n------------------------------------\n";
	cout << "|\tA wild enemy appears!      |\n";
	cout << "------------------------------------\n";

	int attack = RollDie(10);	// Enemy attack power
	int block = RollDie(8);		// Player's block power
	int gold = RollDie(10);		// Possible gold

	cout << "\n-------------------------------------\n";
	cout << "Enemy attacks with " << attack << " power. \n";
	cout << "You block with " << block << " power.\n";
	cout << "-------------------------------------\n";

	if (block < attack) {
		int damage = attack - block;
		health -= damage;
		cout << "\nDuring the fight you took " << damage << " damage!\n";
		cout << "Your health is now:" << health << "\n";


	} else {
		int blockReward = RollDie(15);		// Reward for blocking the attack
		totalGold += blockReward; 
		cout << "\nYou successfuly block the attack! You earn " << blockReward << " gold.\n";
		cout << "Total gold: " << totalGold << "\n";
	}

	if (AskYesNo("\nWould you like to spend gold to restore some health? [20 gold = 10 health] ")) {
		if (health == max_health) {
			cout << "\nyou have full health! there is no need to rest.\n";
		} else if (totalGold >= 20) {
			int restoreAmount = 10;		// how much health is restored
			if (health + restoreAmount > max_health) {
				restoreAmount = max_health - health;
			}
			health += restoreAmount;
			totalGold -= 20;		// Deduction Cost
			cout << "\nYou rested and restored " << restoreAmount << " health. Your health is now " << health << "!\n";
			cout << "You now have a total of " << totalGold << "gold\n";
		}
		else {
			cout << "\nYou don't have enough gold to rest right now!\n";
		}
	}

	if (AskYesNo("\nYou find something glittering on the ground, do you want to check it out?")) {		// A chance for the player to earn some extra gold (even if they lost previous fight)
		totalGold += gold;
		cout << "\nYou found " << gold << " gold! You now have a total of " << totalGold << " gold!\n\n";

	}
	else {
		cout << "you decided to ignore it and move on.../n";
	}

}

//	Ending

void Ending() {

	if (health <= 0) {
		cout << "You have fallen in battle... \n";
		cout << "Despite your efforts, the adventure ends here.\n";
	} else {
		cout << "You decided to end your adventure. \n";
		cout << "You reutrn home with " << totalGold << " gold!\n";
	}

	if (totalGold > 100) {
		cout << "\nthat's impressive! Congratulations on reaching pass 100 gold!\n";
	}


	cout << "\n----------------------------------------------\n";
	cout << "Final Health: " << health << "\n";
	cout << "Total Gold Collected: " << totalGold << "\n";
	cout << "----------------------------------------------\n";
	cout << "\nThanks for playing!\n";
}

//	Main

int main() {
	srand(time(0));

	Story();

	if (!AskYesNo("\nAre you ready to begin your adventure?")) {
		cout << "Take your time. When you're ready, restart the game.\n";
		return 0;
	}

	while (health > 0) {
		
		Adventure();

		if (health <= 0) {
			cout << "\n You've run out of health!\n";
			break;

		}
		cout << "\n----------------------------------\n";
		cout << "|\tHealth: " << health << " | Gold: " << totalGold << "\t  |\n";
		cout << "----------------------------------\n";
		if (!AskYesNo("Do you want to continue your adventure?" )) {
			break;
		}
	}

	Ending();

	return 0;
}