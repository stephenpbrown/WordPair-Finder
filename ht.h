// Steve Brown
// CS360
// Assignment 1
// Due 2/1/16


#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h>
#include <string.h>
#include <math.h>


// Linked list structure
typedef struct _linkedlist
{
   char *wordpairs; // Word pair
   void *occurence; // occurences of word pairs 
   struct _linkedlist *next; // Linked list pointer
} linkedlist;

// Hash table
typedef struct _Ht
{
   int count; // Number of inserts
   int size; // Size of the table
   linkedlist **table; // Hash table
} Ht;

	Ht *htNew(); // Initializes a hash table
	void *htSearch(Ht *table, char *wordpairs); // Searches for word pairs in the hash table structures
	int htInsert(Ht *table, char *wordPairs, void *occurence); // Inserts word pairs into the structures
	void htDelete(Ht *table, void(*delfunc)(char *wordPair, void *occurence)); // Frees the structures
	void freeLL(char *wordPair, void *occurence); // Frees the word pairs and occurences
	void htApply(Ht *table, void(*func)(char *wordpairs, void *occurence)); // Used for making an array of structures to be sorted
  
	int hash(char *wordpair); // Creates a hash key based off the word pair
 	Ht *growHt(Ht *table, int newSize); // Creates a bigger hash table and copies over pointers to structures
	int cmpfunc(const void *wordPair,const void *occurence); // Compares structures for qsort
	void makeArray(char *wordPair, void *occurence); // Makes an array of structures to be sorted
	void print(char *wordPair, void *occurence); // Prints out unsorted word pairs and occurences


	extern int ind; // Index counter for Array
	extern linkedlist *Array; // Array to be used to store and sort word pairs
