


#include <iostream>
#include <string>
#include <vector>
#include "HashTable.h"
#include "Pair.h"

using namespace std;


//Code was tested more extensively than what is displayed here
//This is a small test 
int main() 
{
	int stopper;
	
	//Keys and values defined
	string keys[50] = { "baaaa","abaaa","aabaa","aaaba","aaaab"};
	int values[50] = { 1,2,3,4,5};




	//Quadratic probing hash table created
	HashTable ThisHash(13,'q',6,1,1);


	//Adding values to hash table
	for (int i = 0; i < 13; i++) 
	{	
		ThisHash.add_key(keys[i], values[i]);
	}

	//Lazy deleting
	ThisHash.remove_key("aaaab");

	//Updating existing key
	ThisHash.add_key("baaaa", 999);


	cout << endl;

	//Table is resized to size 127
	ThisHash.resize_table(127);

	//Table is displayed
	ThisHash.print_table();


	cout << endl;
	cin >> stopper;


}