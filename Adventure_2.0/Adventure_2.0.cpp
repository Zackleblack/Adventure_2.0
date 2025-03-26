#include <iostream>
#include <string>
#include <algorithm>
#include <ctime>

using namespace std;

// Global Variables	

int health = 50;
int totalTreasure = 0;

void story();
bool AskYesNo(string question);
int RollDie(int sides = 6);
void Ending();
void Adventure();

int main() {

	srand(time(0));		// Random number generator set

	story();	// Start the adventure

	while (health > 0) {
		if (!AskYesNo("Would you like to go on your journey? (y/n): ")) {
			break;
		}
	}

	Ending();	// Game is now Over
	return 0;
	
}

// Fuctions 

void story() {

	cout << " Welcome, new adventureer! You seek treasure in a land full of danger!\n";
	cout << " Your journey will be dangerous, but riches await those dare...\n";

}

bool AskYesNo(string question) {
	string input;

	cout << "\nShould we set out and look for gold?\n";
	if (input == "y") {
		return true;		// this quits the funciton
	}
	else if (input == "n") {
		return false;
	}
	else {					// else, loop again.
		cout << "Please type 'y' or 'n'.\n";
	}
}

int RollDie(int sides) {
	return (rand() % sides) + 1;
}

void Adventure() {

	int attack = RollDie(10); // Enemy Attack Strength
	int block = RollDie(10); // Player's block strength
	int treasure = RollDie(20); // Random gold amount

	cout << "An enemy attacks with strength: " << attack << "\n";
	cout << "You attempt to block with strength: " << block << "\n";

	if (block >= attack) {
		cout << "You successfully blocked the attack!\n";
			cout << "You found " << treasure << " treasure!\n";
			totalTreasure += treasure;
	}
	else {
		int damage = attack - block;
		health -= damage;
		cout << "You failed to block the attack and lost " << damage << " health!\n";
	}

	cout << "Current Health: " << health << "\n";
	cout << "Total Treasure: " << totalTreasure << "\n";
}

void Ending() {
	if (health > 0) {
		cout << " You grew too weary, and decided to go home, your Grandma was sadly still sick and wasn't able to get the medcine...\n";
		cout << "Final Stats - Health: " << health << ", Treasure: " << totalTreasure << "\n";
	}
	else {
		cout << "You have perished on your journey...\n";
		cout << "Your final gold count was: " << totalTreasure << "\n";

	}
}