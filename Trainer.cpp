/******************************************************************************
Fall 2024 Programming Foundations I
Author: Alex Plunk
Date: November 15, 2024
Purpose: Implement the Trainer class
*******************************************************************************/

#include "Trainer.h"


using namespace std;

// -------------------------------------------------
// Name: Trainer
// Parameters: none
// Returns: none
// Purpose: Constructor. Initializes member variables.
// -------------------------------------------------
Trainer::Trainer()
{
	name = "";
	numPokemon = 0;

	for (int i = 0; i < POKEMON_MAX; i++)
	{
		pokemon[i] = "Empty";
	}

	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		inventory[i] = 0;
	}
}

// -------------------------------------------------
// Name: Trainer
// Parameters: userName: pass-by-value, the name of the player
//			   starter: pass-by-value, the name of the starter pokemon
// Returns: none
// Purpose: Constructor. Initializes member variables to parameters.
// -------------------------------------------------
Trainer::Trainer(const string userName, const string starter)
{
	
	name = userName;
	for (int i = 0; i < POKEMON_MAX; i++)
	{
		pokemon[i] = "Empty";
	}

	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		inventory[i] = 0;
	}
	pokemon[0] = starter;
	numPokemon = 1;
}


// -------------------------------------------------
// Name: Trainer
// Parameters: other: pass-by-reference, Trainer, object to be copied from
// Returns: none
// Purpose: Copy constructor. Initializes member variables to other Trainer's member variables.
// -------------------------------------------------
Trainer::Trainer(const Trainer& other)
{
	name = other.name;
	numPokemon = other.numPokemon;
	for (int i = 0; i < POKEMON_MAX; i++)
	{
		pokemon[i] = other.pokemon[i];
	}

	for (int i = 0; i < INVENTORY_MAX; i++)
	{
		inventory[i] = other.inventory[i];
	}
}



// -------------------------------------------------
// Name: ~Trainer
// Parameters: none
// Returns: none
// Purpose: Destructor. Dellocates memory.
// -------------------------------------------------
Trainer::~Trainer()
{
}

// -------------------------------------------------
// Name: getName
// Parameters: none
// Returns: string, the trainer's name
// Purpose: Gets the private name variable.
// -------------------------------------------------

string Trainer::getName() const
{
	return name;
}


// -------------------------------------------------
// Name: getNumPokemon
// Parameters: none
// Returns: int, number of pokemon
// Purpose: Gets the number of Pokemon the user has.
// -------------------------------------------------

int Trainer::getNumPokemon() const
{
	return numPokemon;
}



// -------------------------------------------------
// Name: getItemAmount
// Parameters: index: pass-by-value, int
// Returns: int, number of specific item
// Purpose: Gets the amount of a given item the user has.
// -------------------------------------------------

int Trainer::getItemAmount(const int index) const
{
	return inventory[index];
}


// -------------------------------------------------
// Name: getPokemon
// Parameters: index: pass-by-value, int
// Returns: string, name of the pokemon at the index
// Purpose: Gets the name of a pokemon the player has.
// -------------------------------------------------
string Trainer::getPokemon(const int index) const
{
	return pokemon[index];
}



// -------------------------------------------------
// Name: setName
// Parameters: userName: pass-by-value, string
// Returns: none
// Purpose: Sets the name of the trainer.
// -------------------------------------------------
void Trainer::setName(const string userName)
{
	name = userName;
}


// -------------------------------------------------
// Name: useItem
// Parameters: index: pass-by-value, int
// Returns: none
// Purpose: Uses the item at the specified index.
// -------------------------------------------------

void Trainer::useItem(const int index)
{
	if(inventory[index] > 0 )
		inventory[index]--;
}

// -------------------------------------------------
// Name: removePokemon
// Parameters: index: pass-by-value, int
// Returns: none
// Purpose: Removes Pokemon at the specified index from lineup, and moves up the other pokemon so there's not an empty slot
// -------------------------------------------------
void Trainer::removePokemon(const int index)
{
	for(int index = 0; index < numPokemon-1; index++)
		pokemon[index] = pokemon[index+1];
	numPokemon--;
	pokemon[numPokemon] = "";
}

// -------------------------------------------------
// Name: printStats
// Parameters: none
// Returns: none
// Purpose: Prints the trainer's stats to the screen
// -------------------------------------------------
void Trainer::printStats() const
{
	cout << "Name: " << name << endl;
	cout << "numPokemon: " << numPokemon << endl;
	cout << "Inventory: " << endl;
	cout << "\t(" << inventory[POKE_BALL] << ") Poke Ball(s)" << endl;
	cout << "\t(" << inventory[ULTRA_BALL] << ") Ultra Ball(s)" << endl;
	cout << "\t(" << inventory[REVIVE] << ") Revives(s)" << endl;
	cout << "Pokemon: ";
	for (int i = 0; i < numPokemon; i++)
		cout << pokemon[i] << ", ";
	cout << '\n' << endl;
}

// -------------------------------------------------
// Name: writeFile
// Parameters: filename: pass-by-value, the name of the file
// Returns: none
// Purpose: Prints the trainer's stats to a file
// -------------------------------------------------
void Trainer::writeFile(const string filename)
{
	//step 1
	ofstream dout;
	//step 2 
	dout.open(filename);
	//step 3
	if(dout)
	{
		     //step 4 write data to file

		dout << "Name: " << name << endl;
	dout << "numPokemon: " << numPokemon << endl;
	dout << "Inventory: " << endl;
	dout << "\t(" << inventory[POKE_BALL] << ") Poke Ball(s)" << endl;
	dout << "\t(" << inventory[ULTRA_BALL] << ") Ultra Ball(s)" << endl;
	dout << "\t(" << inventory[REVIVE] << ") Revives(s)" << endl;
	dout << "Pokemon: ";
	for (int i = 0; i < numPokemon; i++)
		dout << pokemon[i] << ", ";
	dout << '\n' << endl; 
		// //for loop for pokemon
		// for(int i = 0; i < POKEMON_MAX; i++)
		// {
		// 	if(pokemon[i] != "empty")
		// 		{
		// 			cout << pokemon[i] << endl;
		// 		}
		// }
		// //for loop for items in inventory
		// for(int i = 0; i < INVENTORY_MAX; i++)
		// {
		// 	cout << inventory[i] << endl;
		// }
		//step 5 close the file
	}
	dout.close();


}




// -------------------------------------------------
// Name: hasPokemonSpace
// Parameters: none
// Returns: bool, whether or not the trainer has space for another pokemon
// Purpose: Returns true if the trainer has space for another pokemon. Returns false if not.
// -------------------------------------------------

bool Trainer::hasPokemonSpace() const
{
	if(numPokemon > POKEMON_MAX)
		return false; 
	else
		return true;
}


// -------------------------------------------------
// Name: addPokemon
// Parameters: pokemonName: pass-by-value, string, the name of the new pokemon
// Returns: none
// Purpose: Adds a pokemon to the trainer's pokemon inventory.
// -------------------------------------------------
void Trainer::addPokemon(const string pokemonName)
{
	int i = -1; // set it at -1 for indexing 
	numPokemon++;
	// string wildPokemon = pokemonName;
	pokemon[numPokemon + i] = pokemonName;
	
}


// -------------------------------------------------
// Name: addItem
// Parameters: index: pass-by-value, the index of the item the trainer picked up
// Returns: bool, whether or not the item could be added
// Purpose: If the trainer has space, add an item. Otherwise don't.
// -------------------------------------------------
bool Trainer::addItem(const int index)
{
	// Check if the index is allowed
    if (index < 0 || index >= INVENTORY_MAX) 
	{
        cout << "Invalid item index." << endl;
        return false;
	}
	//see if theres room for the item to be added
	else if(inventory[index] >= ITEM_MAX)
	{
		cout << "You cannot carry any more of this item.\n";
		return false;
	}

	//adding item
	inventory[index]++;
	cout << "Item added to inventory!\n";
	return true;
}


