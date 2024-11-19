/******************************************************************************
Fall 2024 Programming Foundations I
Author: Alex Plunk
Date: November 15, 2024
Purpose: main function and compiling the program
*******************************************************************************/

#include "Trainer.h"


//wild Pokemon (read in from a file) list size
const int WILD_POKEMON_LIST_SIZE = 25;

//error checking for input of y or n
char charInputCheck()
{
	char input;
		cout << ">> "; cin >> input;
		while(input != 'y' && input != 'n')
		{
			   cout << "Please enter either 'y' or 'n'.\n>> ";
			   cin >> input;
		}
	return input;
}


//given - generate both a wild Pokemon and an item
void generateEncounter(string pokeList[], string &encounteredPokemon, string &pickedUpItem)
{
	srand(time(NULL));
	int randomNum = rand() % WILD_POKEMON_LIST_SIZE;
	encounteredPokemon = pokeList[randomNum];
	
	randomNum = rand() % Trainer::INVENTORY_MAX;
	switch(randomNum)
	{
		case 0: 
			pickedUpItem = "Poke Ball";
			break;
		case 1: 
			pickedUpItem = "Ultra Ball";
			break;
		case 2: 
			pickedUpItem = "Revive";
			break;
		default: 
			pickedUpItem = "Poke Ball";
	}
}
void readFile(string pokeList[], const string filename)
{
	string Pokemon;
	int index = 0;
	//step 1
	ifstream din;
	//step 2 
	din.open("PokemonList.txt");
	//step 3 
	if(din.fail())
    {
        cout << filename << " opening failed.\n";
    } 
	else
	//step 4 
	while(din >> Pokemon)
		{
			pokeList[index] = Pokemon;
			index++;
		}
	cout << "Opening file success!\n";
	//step 5
	din.close();
}


int main() 
{
	string wildPokemon = "";
	string item = "";
	bool stillPlaying = true;
	char input = 'a';
	int choice = 0;
	int itemIndex = 0;
	string currPokemon = "";
	string pokemonList[WILD_POKEMON_LIST_SIZE];

	

	//uncomment each of the tests as you finish writing the code in Trainer.cpp
	cout << "Testing readFile()...\n" << endl;
	readFile(pokemonList, "PokemonList.txt");

	cout << "Testing default constructor..." << endl;
	Trainer player;
	player.printStats();

	cout << "Testing parameterized constructor..." << endl;
	Trainer misty("Misty", "Psyduck");
	misty.printStats();

	cout << "Testing copy constructor..." << endl;
	Trainer misty2(misty);
	misty2.printStats();

	cout << "Testing setName()..." << endl;
	player.setName("Ash");
	player.printStats();

	cout << "Testing addPokemon()..." << endl;
	player.addPokemon("Pikachu");
	player.printStats();

	cout << "Testing addItem()..." << endl;
	player.addItem(Trainer::POKE_BALL);
	player.addItem(Trainer::ULTRA_BALL);
	player.addItem(Trainer::REVIVE);
	player.printStats();

	cout << "Testing generateEncounter()..." << endl;
	generateEncounter(pokemonList, wildPokemon, item);
	cout << "wildPokemon: " << wildPokemon << endl;
	cout << "item: " << item << endl;
	cout << endl;

	cout << "Testing generateEncounter()..." << endl;
	// generateEncounter(pokemonList, wildPokemon, item);
	// cout << "wildPokemon: " << wildPokemon << endl;
	// cout << "item: " << item << endl;
	// cout << endl;

	cout << "Game loop starting..." << endl;
	while(stillPlaying)
	{
		//generate an encounter to get the random item and the wild Pokemon
		generateEncounter(pokemonList, wildPokemon, item);
		
		
		
		//fulfill item encounter
		cout << "You found a(n) " << item << ", do you want to keep it? y/n\n";
		if(charInputCheck() == 'y')
			{
				if(item == "Revive")
					player.addItem(Trainer::REVIVE);
				else if(item == "Poke Ball")
					player.addItem(Trainer::POKE_BALL);
				else if(item == "Ultra Ball")
					player.addItem(Trainer::ULTRA_BALL);
			}
		else
			cout << "You put the " << item << " back.\n";
			



		//print stats
		player.printStats();
		

		//generate steps
		int numSteps = rand() % 10 + 1;
		for (int i = 1; i <= numSteps; i++)
		{ 
			if(numSteps == 1)
				cout << "You've taken 1 step.\n";
			else
				cout << "You've taken " << i << " steps." << endl;
		}

		//fulfill Pokemon encounter
		int ballChoice;
		char catchChoice;
		int win;
		int index = 0;
		int pokemonChoice;
		char reviveChoice; 
		cout << "You've encountered a(n) " << wildPokemon << ", would you like to fight it? y/n\n";
	if(charInputCheck() == 'y')
		{
				cout << "Which Pokemon do you want to use?\n";
        	for (int i = 0; i < player.getNumPokemon(); i++) 
				{
            		cout << i + 1 << ") " << player.getPokemon(i) << endl;
				}
			cin >> pokemonChoice; 
			while(pokemonChoice <= 0 && pokemonChoice > player.getNumPokemon())
				{
					cout << "Invalid input, please choose from the list\n";
					cin >> pokemonChoice;
				}
			currPokemon = player.getPokemon(pokemonChoice - 1);	//had to decrement cuz if i didnt it would return empty in the cout below
			
			win = rand() % 2;
				if(win == 0)
					{
						cout << "Uh-oh! " << currPokemon << " fainted and the " << wildPokemon << " escaped!\n";
							if(player.getItemAmount(Trainer::REVIVE) > 0)
								{
									cout << "Would you like to use a Revive? y/n\n";
									cin >> reviveChoice;
									reviveChoice = toupper(reviveChoice);
									while(reviveChoice != 'N' && reviveChoice != 'Y')
									{
										cout << "Please choose a valid input. y/n >>";
										cin >> reviveChoice;
										reviveChoice = toupper(reviveChoice); 
									}
									if (reviveChoice = 'Y')
										{
											player.useItem(Trainer::REVIVE);
											cout << currPokemon << " was healed! You have " << player.getItemAmount(Trainer::REVIVE) << " Revive(s) left.\n";
										}
									else
										{
											cout << currPokemon << " was sent to Professor Oak!\n";
											player.removePokemon(pokemonChoice);
										}

								}
							else
								{
									player.removePokemon(pokemonChoice);
									cout << "You don't have any Revives to use. " << currPokemon << " was sent to Professor Oak!\n";
								}

					}
				else //win == 1
				{
					cout << "You and " << currPokemon << " win! Do you want to catch the " << wildPokemon << "? y/n\n";
					cin >> catchChoice;
					catchChoice = toupper(catchChoice);

					//error checking for answer
					while(catchChoice != 'Y' && catchChoice != 'N')
						{
							cout << "Enter a valid input. y/n";
							cin >> catchChoice;
							catchChoice = toupper(catchChoice);
						}
					// if(player.hasPokemonSpace());
					// 	if(player.getItemAmount(Trainer::POKE_BALL) == 0 && player.getItemAmount(Trainer::ULTRA_BALL) == 0)
					// 		cout << "You don't have any poke balls to use.\n";

					//checking if the player has space in their inventory
					if(!player.hasPokemonSpace())
						cout << "You don't have any more room for more Pokemon!\n";
					if(player.hasPokemonSpace())
							if(player.getItemAmount(Trainer::POKE_BALL) == 0 && player.getItemAmount(Trainer::ULTRA_BALL) == 0)
								cout << "You don't have any poke balls to use.\n";
				//if catchChoice is Y then keep the encounter going
				if(catchChoice == 'Y')
						{	
									cout << "What ball do you want to use? enter 1 or 2.\n";
									cout << "1) Poke Ball (" << player.getItemAmount(Trainer::POKE_BALL) << " remaining)\n";
									cout << "2) Ultra Ball (" << player.getItemAmount(Trainer::ULTRA_BALL) << " remaining)\n";
									cout << ">>";
									cin >> ballChoice;
									while(ballChoice != 1 && ballChoice != 2)
										{
											cout << "Please enter a valid number.\n"; 
											cout << ">>";
											cin >> ballChoice; 
										}
									while(ballChoice == 1 && player.getItemAmount(Trainer::POKE_BALL) == 0)
									{
										cout << "You dont have any poke balls to use. enter another option.\n";
										cout << ">>";
										cin >> ballChoice;
									}
									while(ballChoice == 2 && player.getItemAmount(Trainer::ULTRA_BALL) == 0)
									{
										cout << "You dont have any ultra balls to use. enter another option.\n";
										cout << ">>";
										cin >> ballChoice;
									}
									if(ballChoice == 1 && player.getItemAmount(Trainer::POKE_BALL) > 0)
										{
											player.useItem(Trainer::POKE_BALL);
											player.addPokemon(wildPokemon);
											cout << "You caught " << wildPokemon << endl;
										}
										
									else if(ballChoice == 1 && player.getItemAmount(Trainer::ULTRA_BALL) > 0)
											{
												player.useItem(Trainer::ULTRA_BALL);
												player.addPokemon(wildPokemon);
												cout << "You caught " << wildPokemon << endl;
											}
										
						}
				else
					cout << "You leave the " << wildPokemon << " at peace and run away.\n";
					
				}	



		}
	else
		cout << "You disengage, the " << wildPokemon << " escaped!\n";
		
			
			
	
		
		
		

		//check if user can still play, and then if they want to still play
		// if the user has no pokemon, they can't keep playing
		if(player.getNumPokemon() <= 0)
			{		
				cout << "You don't have any more pokemon to play with.\n";
				stillPlaying = false;
			}
		else
			{
		
		
		//else, see if the user wants to keep playing
		
		
			//note that these 4 lines will likely be inside of an if/else block that is detailed 
			//at the end of "2. Description" in the homework
			cout << "Do you want to keep playing?" << endl;
			input = charInputCheck();

			if (input == 'n')
				stillPlaying = false;
			}
		
	}

	//create a unique filename with number of seconds passed since Jan 1, 1970 so multiple
	//runs of the program will save to different files
	string outputFilename = "player-";
	outputFilename.append(std::to_string(time(0)));
	outputFilename.append(".txt");

	//save to file
	player.writeFile(outputFilename);

	
	

	cout << "Your player information has been saved to " << outputFilename << ". Until next time!\n";
	return 0;
}
