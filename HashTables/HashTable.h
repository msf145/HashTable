#pragma once
/*******************************************************************************
* HashTable.h
*
* author: Michael Fournier
* date created: 11/5/2017
* last updated: 11/7/2017
*
* This file contains the member function prototypes of the HashTable class.
  This hash table is constructed using vectors and provides linear probing and quadratic probing
  collision resolution. The table is resizable. 
*
*******************************************************************************/


#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <iostream>
#include <string>
#include <vector>
#include "Pair.h"


using namespace std;

class HashTable 
{
	private:
		
		vector<Pair> htable; // The vector class holds multiple Pair objects.
		
		int num_cells; // Tracks the number of cells present in the table

		int max_probes; // Defines the maximum number of probes allowed for search/addition

		char col_res_type; // Defines type of collision resolution, 'q' = quadratic probing; 'l' = linear probing 

		int c1; // User-defined constant for quadratic probing

		int c2; // User-defined constant for quadratic probing

		int hash_fn(string inputString); // Function that returns the base index of where a key should be inserted 

		int lin_probe(string linInputString); // Utilizes the linear probing formula to resolve collisions 

		int quad_probe(string quadInputString); // Utilizes the quadratic probing formula to resolve collisions

		int find_cell(string findString); // Searches for a specific string by using the designated collision resolution type

	public:

		HashTable(int tableSize, char probingType, int maxProbes, int c1, int c2); // Initializes the hash table 

		~HashTable(); // Clears the hash table and sets all member variables to zero

		bool add_key(string key, int value); // Attempts to add a key - value pair to the hash table, uses collision resolution

		bool remove_key(string remStrValue); // Enables a previously added element to be overwritten by another

		void erase_table(); // Sets all the values of every pair in a vector to zero

		bool resize_table(int newSize); // Attempts to insert 

		bool value(string strValue, int& tableValue); // Sets a passed in variable's value equal to a hashtable string's value

		void print_table(); // Test function that prints the entire table, displays key,value,status

		int test_lin_probe(string key, int i); // Used to test lin_probe

		int test_quad_probe(string key, int i); // Used to test quad_probe

		int get_index(string key); // Returns the hashtable index of a key










};

#endif