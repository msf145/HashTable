/*******************************************************************************
* Pair.h
*
* author: Rikk Anderson
* date created: 11/05/2017
* last updated: 11/05/2017
*
* This class defines the key:value pair object used in a hash table
*
*******************************************************************************/
#ifndef PAIR_H
#define PAIR_H

#include <string>   // support for strings

struct Pair {
  // the data of a Pair object is the combined key:value pair
  std::string key;   // the key
  int value;    // the value associated with the key
  int status;   // marks if the node has valid data (1), empty (0), or lazy deleted invalid data (-1)
    
  Pair();
};

// small exception to the two file rule when it comes to C++ classes and structs
// all methods defined within the *.h file of a C++ class or struct must be defined
// as inline to avoid linker errors.  However, the keyword "inline" is only a 
// suggestion to the compiler and therefore, the compiler can choose to ignore this 
// keyword.  This means that inline may not work on all compilers.  I'm using inline
// here because only the HashTable.h file will #include this *.h file, meaning there
// is minimal chance of linker errors.  
inline Pair::Pair() {
  this->key = "\0";
  this->value = 0;
  this->status = 0;
}

#endif

