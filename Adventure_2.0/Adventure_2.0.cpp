#include <iostream>
#include <string>
#include <cstdlib>
#include <algorithm>
#include <ctime>

using namespace std;

// Global Variables

const int max_health = 30;
int health = max_health;		// The Player's total amount of health
int totalGold = 0;			// Total gold collected
int totalEncounters = 0;		// Total enemies encounters
int goldMultiplier = 1;		// Gold bonus multiplier

// Fuctions

void Story();
bool AskYesNo(string question);
int RollDie(int sides = 6);
void Ending();
void Adventure();

//	Story

void Story() {

	cout << "-------------------------------------------------------------------------\n";		// Story information pop up.
	cout << "|Welcome to Adventure 2.0!                                              |\n";
	cout << "|In this game you will encounter battles, find gold, and test your luck.|\n";
	cout << "|Your starting health is " << health << ". Good luck!                                 |\n";
	cout << "-------------------------------------------------------------------------\n";

}

//	AskYesNo

bool AskYesNo(string question) {		// Question Prompt for certain scenarios (Y/N)

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
	totalEncounters++;

	cout << "\n-------------------------------------\n";		// Enemy VS Player Information
	cout << "Enemy attacks with " << attack << " power. \n";
	cout << "You block with " << block << " power.\n";
	cout << "-------------------------------------\n";

	if (block < attack) {
		int damage = attack - block;
		health -= damage;
		cout << "\nDuring the fight you took " << damage << " damage!\n";
		cout << "\nYour health is now: " << health << "\n";
		cout << "\nTotal gold: " << totalGold << "\n";
		if (health <= 0) {
			cout << "/n You sadly succumbed to your wounds and died.\n";
			Ending();
				exit(0);
		}

	} 	else {
		int blockReward = RollDie(15);		// Reward for blocking the attack

		int finalGold = blockReward * goldMultiplier;
		cout << "\nYou successfuly block the attack! You earn " << blockReward << " gold.\n";

		if (goldMultiplier > 1) {
			cout << "\nYour ancient relic glows, increasing your gold to " << finalGold << " gold!\n";
			cout << "\nThe relic turns to dust...\n";
		}
		
		totalGold += finalGold;
		cout << "Total gold: " << totalGold << "\n";

		goldMultiplier = 1;
	}

	if (AskYesNo("\nWould you like to spend gold to restore some health? [20 gold = 10 health] ")) {	//  This prompts the ability to rest and regain health with the cost of gold. 
																											// This makes it so player can continue the adventure 
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
			cout << "You now have a total of " << totalGold << " gold\n";
		}
		else {
			cout << "\nYou don't have enough gold to rest right now!\n";
		}
	}

	// Random Event

	if (AskYesNo("\nYou find something glittering on the ground, do you want to check it out?")) {		// Does player want to start a random event 
		int eventRoll = RollDie(10);

		if (eventRoll <= 5) {

			totalGold += gold;
			cout << "\nYou found " << gold << " gold! You now have a total of " << totalGold << " gold!\n\n";	// Regular Gold Event

		}
		else if (eventRoll <= 7) {
			int healAmount = RollDie(10) + 5;
			if (health == max_health) {
				cout << "\n You found a health potion!\n";		// Potion on event drop, lets player know if they are at full health
				cout << "\nBut... You are already at full health.\n";
			} else {
				health = min(health + healAmount, max_health);
				cout << "\nYou found a health potion and healed " << healAmount << " health! Current health : " << health << " / " << max_health << "\n";	// Added an option to heal for free through RNG
			}
		}
		else if (eventRoll <= 9) {
			int trapDamage = RollDie(5) + 2;
			health -= trapDamage;
			cout << "\nOn no! It was a trap! You took " << trapDamage << " damage! Current health : " << health << " / " << max_health << "\n";		// Added an option to lose health through event
		}
		else {
			cout << "\nYou found an ancient relic! It increases your winnings from battle by x2!\n";	// Added an option to increase gold output
			goldMultiplier = 2;
		}

	}
	else {
		cout << "you decided to ignore it and move on.../n";	// Option for the player to ignore the event.
	}

}

//	Ending

void Ending() {

	if (health <= 0) {				// If player reaches 0 health, Defeat ending will play
		cout << "You have fallen in battle... \n";
		cout << "Despite your efforts, the adventure ends here.\n";

	} else {						// If health is above 0 health, player gets regular ending
		cout << "\nYou decided to end your adventure. \n";
		cout << "You return home with " << totalGold << " gold!\n";
	}

	if (totalGold > 100) {			// If player manages to get 100 Gold  during their Adventure, this prompt will run.
		cout << "\nthat's impressive! Congratulations on reaching pass 100 gold!\n";
	}


	cout << "\n----------------[FINAL STATS]-----------------\n";		// Final Stats for the game
	cout << "Final Health: " << health << " / " << max_health << " \n";
	cout << "Total Gold Collected: " << totalGold << "\n";
	cout << "Total Encounters Survived: " << totalEncounters << "\n";
	cout << "----------------------------------------------\n";
	cout << "\nThanks for playing!\n";
}

//	Main

int main() {
	srand(time(0));

	Story();

	if (!AskYesNo("\nAre you ready to begin your adventure?")) {			// Asks player if they are ready to start the game
		cout << "Take your time. When you're ready, restart the game.\n";		// if player says no, it will prompt them to take their time and end game.
		return 0;
	}

	while (health > 0) {
		
		Adventure();

		if (health <= 0) {
			cout << "\n You've run out of health!\n";
			break;

		}
		cout << "\n----------[PLAYER STATS]----------\n";
		cout << "|Health: " << health << " / " << max_health << " | Gold: " << totalGold << "\t | \n";
		cout << "----------------------------------\n";
		if (!AskYesNo("Do you want to continue your adventure?" )) {
			break;
		}
	}

	Ending();

	return 0;
}