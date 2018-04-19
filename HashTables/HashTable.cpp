/*******************************************************************************
* HashTable.cpp
*
* author: Michael Fournier
* date created: 11/5/2017
* last updated: 11/14/2017
*
* This file contains the function definitions of the HashTable class
*
*******************************************************************************/

#include "HashTable.h"
#include <iostream>
#include <string>
#include <vector>
#include <cmath> // Included for exponentiation

using namespace std;


//Note that collisionI and the probing functions were added before the int parameter was added to the probing functions in the UML.
//This was stated to be fine as long as key-value pairs are placed in their proper locations.

int collisionI; // Global variable used to keep track of collisions, used in both collision resolutions and incremented if a collision occurs

//This constructor utilizes passed-in parameters to define the size of the table, type of probing, 
//max number of probes, and the quadratic probing constants
HashTable::HashTable(int tableSize, char probingType, int maxProbes, int c1Val, int c2Val)
{
	num_cells = tableSize; // Sets number of cells present to the value passed in as tableSize
	col_res_type = probingType; // Sets the collision resolution type
	max_probes = maxProbes; // Sets the max amount of probes possible to the passed in value.
	
	if (col_res_type == 'q') // If quadratic probing was chosen, the user defined constants are set
	{
		c1 = c1Val;
		c2 = c2Val;
	}
	
	else // If linear probing was chosen, the constants are set to zero (not used for linear probing)
	{
		c1 = 0;
		c2 = 0;
	}

	htable.resize(num_cells); // Table resized to match value passed in as tableSize


}

HashTable::~HashTable() // This deconstructor clears the hashtable and sets all member variables to zero.
{
	
	htable.clear();
	col_res_type = '\0';
	
	c1 = 0;
	c2 = 0;
	
	max_probes = 0;
	num_cells = 0;

}

// Basic hashing function that returns the base index where a key should be placed in a hash table
int HashTable::hash_fn(string inputString)
{

	int tableSize = htable.size(); // Sets tableSize equal to the size of the hashtable
	

int stringSum = 0; // Running Sum Variable


//The string is iterated through and each ascii value of each character in the string is added 
//to string sum, creating a single number
for (int i = 0; i<inputString.length(); i++)
	
	{

		stringSum = stringSum + int(inputString[i]);
	
	}

// The ascii sum is modded by the size of the table, resulting in
	// a potentially viable index location in the hash table
	int value = (stringSum % tableSize); 

	return value;
}

// Collision Resolving function that increments the index location by one if a collision occurs
int HashTable::lin_probe(string linInputString)
{
	string hashingString = linInputString;
	
	int tableSize = htable.size();

	int hashValue = hash_fn(hashingString); // Calls hashing function to get the base index location 

	int newPosition = (((hashValue)+collisionI) % tableSize); // Increments the base index location by one

	return newPosition;

}

// Collision Resolving function that uses a quadratic formula to change the index location
// if a collision occurs
int HashTable::quad_probe(string quadInputString) 
{

	string hashingString = quadInputString;

	int tableSize = htable.size();

	int hashValue = hash_fn(hashingString); // Calls hashing function to get the base index location 

	// Base hashing value is incremented by a quadratic formula, c1 and c2 are used in this formula
	int newPosition = ((hashValue)+(c1*(pow(collisionI,2)))+(c2*collisionI)); 
	
	newPosition = (newPosition%tableSize);
	
	return newPosition;

}

// This function attempts to add a key, value pair to the hash table.
bool HashTable::add_key(string key, int value) 
{
	
	if (col_res_type == 'l') // This statement allows for linear probing to be executed
	{
		
		//This block calls the find_cell function to check if the value that is 
		//beind added already exists, if it isn't marked for overwriting 
		//the key's value will be replaced with another integer value, but
		//the key's string will remain the same
		int searchIndex = find_cell(key);
		if (searchIndex != -1) 
		{

			htable[searchIndex].value = value;
			return true;
		}



		
		while (collisionI < max_probes)// The following statements execute until the value of max_probes has been reached
		{


			int tableLoc = lin_probe(key); // A potentially viable location is determined by linear probing

			// If a key, value pair exists and can be overwritten, it will be overwritten by the passed in key, pair values
			// If no key, value pair exists, the passed in key, pair values are placed in the location given by the lin_probe function
			// In both cases, the status is updated to 1 and the collision count is set to zero
			if (htable[tableLoc].status == 0 || htable[tableLoc].status == -1)
			{

				htable[tableLoc].key = key;
				htable[tableLoc].value = value;
				htable[tableLoc].status = 1;
				collisionI = 0;

				return true;
			}

			// A collsion occured if a status of one was encountered, the collisionI count is incremented
			else
				collisionI++;

		}
	
		//The max probes were reached, and the value could not be added
		//cout << "Unable to add element, Max Probes Exceeded" << endl; - testing Code
		return false;
	
	}


	if (col_res_type == 'q') // This statement allows for quadratic probing to be executed
	{

		//This block calls the find_cell function to check if the value that is 
		//beind added already exists, if it isn't marked for overwriting 
		//the key's value will be replaced with another integer value, but
		//the key's string will remain the same
		int searchIndex = find_cell(key);
		if (searchIndex != -1) {

			htable[searchIndex].value = value;
			return true;
		}



		while (collisionI < max_probes)// The following statements execute until the value of max_probes has been reached
		{



			int tableLoc = quad_probe(key);// A potentially viable location is determined by quadratic probing

			// If a key, value pair exists and can be overwritten, it will be overwritten by the passed in key, pair values
			// If no key, value pair exists, the passed in key, pair values are placed in the location given by the lin_probe function
			// In both cases, the status is updated to 1 and the collision count is set to zero
			if (htable[tableLoc].status == 0 || htable[tableLoc].status == -1)
			{

				htable[tableLoc].key = key;
				htable[tableLoc].value = value;
				htable[tableLoc].status = 1;
				collisionI = 0;

				return true;
			}

			// A collsion occured if a status of one was encountered, the collisionI count is incremented
			else
			collisionI++;

		}

		//The max probes were reached, and the value could not be added
		//cout << "Unable to add element, Max Probes Exceeded" << endl; - testing code
		return false;

	}

}

// find_cell uses the chosen collision resolution to find the location of a specified string
// in the hash table, uses the same collisionI variable as add_key
int HashTable::find_cell(string findString)
{
	int searchProbes = 0;// searchProbes keeps track of how many probes has occured in the process of finding the specified string.

	if (col_res_type == 'l') // Executed if linear probing is chosen
	{

		// While the maximum amount of probes is not exceeded these statements execute:
		while (searchProbes < max_probes)
		{

			int stringLocation = lin_probe(findString); // Possible string location given by lin_probe

			if (htable[stringLocation].key == findString)// If the key is found the location is returned
			{
				collisionI = 0; 
				return stringLocation;
			}

			if (htable[stringLocation].status == 0) // If an empty cell is encountered, the probing terminates and -1 is returned
			{
			//	cout << "Empty cell encountered" << endl;
				collisionI = 0;
				return -1;
			}

			//If the previous statements do not occur, a collision occured and searchProbes and collisionI are incremented
			collisionI++;
			searchProbes++;

		}

		//If max probes is exceeded, the search ends and -1 is returned.
		// cout << "Key not found, probing exceeded" << endl; - testing code 
		return -1;

	}


	if (col_res_type == 'q') // Executed if quadratic probing is chosen
	{

		// While the maximum amount of probes is not exceeded these statements execute:
		while (searchProbes < max_probes)
		{

			int stringLocation = quad_probe(findString);// Possible string location given by quad_probe

			if (htable[stringLocation].key == findString)// If the key is found the location is returned 
			{
				collisionI = 0;
				return stringLocation;
			}

			if (htable[stringLocation].status == 0)// If an empty cell is encountered, the probing terminates and -1 is returned 
			{
		//		cout << "Empty cell encountered" << endl;;
				collisionI = 0;
				return -1;
			}

			//If the previous statements do not occur, a collision occured and searchProbes and collisionI are incremented
			collisionI++;
			searchProbes++;

		}

		//If max probes is exceeded, the search ends and -1 is returned.
		//cout << "Key not found, probing exceeded" << endl; - testing Code
		return -1;

	}

}

//The status of an existing key, value pair is set to -1, this means it can be overwritten if 
//another key, value pair can be placed in its location
bool HashTable::remove_key(string remStrValue) 
{

	int stringLocation = find_cell(remStrValue); // The index of the specific string value is found by find_cell
	
	if (stringLocation != -1) // If the string value exists in the table, the status is updated to -1
	{
		htable[stringLocation].status = -1;
			return true;
	}

	else
		return false;

}

//The value function sets the value of a reference variable to the value of a key, value pair in the hash table
bool HashTable::value(string strValue, int& tableValue) 
{

	int stringLocation = find_cell(strValue); // The index of the specific string value is found by find_cell

	if (stringLocation == -1)// If the string isn't found, the reference variable is unchanged
	{
		cout << "Value not found." << endl;
		return false;
	}

	
	else
	{
		tableValue = htable[stringLocation].value;// The reference variable is set to the value of key, value pair in the table
		return true;
	}

}

//A new table is created of a specified size and an attempt to remap the key-value pairs to the new table is made
//If the remap fails, the changes are reverted
bool HashTable::resize_table(int newSize) 
{
	// A new hashtable is made and the values in the current table are stored in the new table
	//This table also serves as a backup
	vector<Pair> tableCopy;
	tableCopy.resize(num_cells);
	tableCopy = htable;

	// Information about the old table is stored if a revert is neccessary
	int tableCopySize = tableCopy.size();
	int oldNumCells = num_cells;

	//The original table is cleared and resized to the specified size
	htable.clear();
	htable.resize(newSize);
	num_cells = htable.size();


	for (int i = 0; i < tableCopySize; i++)// The original table's copy is iterated through
	{
		// If a key, value pair's status in the original table is 1 or -1, an attempt to add the pair to the cleared original
		//table is made
		if (tableCopy[i].status == 1 || tableCopy[i].status == -1)
		{
				
			// If a key addition fails, all the changes are reverted and the original table is returned to the state 
			// it existed in before resize_table was called.
			if (add_key(tableCopy[i].key, tableCopy[i].value) == false) 
			{
				htable = tableCopy;
				num_cells = oldNumCells;
				cout << "Unable to add cells; Reverting to previous table" << endl;
				return false;

			}

		}

	}

	return true;

}

// All the values in the hash table are cleared and set to zeroes.
void HashTable::erase_table() 
{
	htable.clear();
	htable.resize(num_cells);
}


// Non-required Test Functions // // // // // // // // // // // // //
int HashTable::test_lin_probe(string key, int i) 
{
	// Tests lin_probe with a given key and collision number
	collisionI = i;
	int result = lin_probe(key);
	collisionI = 0;
	return result;
}

int HashTable::test_quad_probe(string key, int i)
{
	// Tests quad_probe with a given key and collision number
	collisionI = i;
	int result = quad_probe(key);
	collisionI = 0;
	return result;
}

void HashTable::print_table()
{
	//Iterates through the hash table and prints the key, value, and status of all cells
	for (int i = 0; i < htable.size(); i++) 
	{
		cout << htable[i].key << " " << htable[i].value << " " << htable[i].status;
		cout << endl;

	}
}

// Tests find cell by returning the index of a cell
int HashTable::get_index(string key) 
{
	int index = find_cell(key);
	return index;
}

