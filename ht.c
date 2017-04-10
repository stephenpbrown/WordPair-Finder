// Steve Brown
// CS360
// Assignment 1
// Due 2/1/16


#include "ht.h"


// Makes a new hash table
Ht *htNew()
{
	Ht *newTable;
	int size = 5; // Initial size of hash table	

	newTable = malloc(sizeof(Ht)); // Allocate space for structure
	newTable->table = calloc(size, sizeof(linkedlist *)); // Allocate space for hash table

	newTable->size = size; // Set the table's size
	newTable->count = 0; // Initialize number of inserts to zero

	return newTable;
}


// Search function
void *htSearch(Ht *table, char *wordPair)
{
	int index = hash(wordPair)%table->size; // Find the hash key for the word pair

	linkedlist *pair = table->table[index]; // Points pair to the bucket in the hash table

	while(pair != NULL) // Loops through the linked list
	{
		if(strcmp(wordPair, pair->wordpairs) == 0) // If it finds the word pair, then returns the occurence
			return pair->occurence;
		pair = pair->next; // Increments to the next pointer
	}

	return NULL; // If word pair isn't found, returns NULL
}


// Inserts into the linked lists in the hash table
int htInsert(Ht *table, char *wordPair, void *occurence)
{
	table->count++;

	int index = hash(wordPair)%table->size; // Makes index equal to the hashed value for the string

	linkedlist *ptr = malloc(sizeof(linkedlist)); // Makes a pointer to a new structure
	
	ptr->wordpairs = wordPair;
	ptr->occurence = occurence; // Points to the inputted occurence
	ptr->next = table->table[index]; // Points next to where the bucket is pointing
	table->table[index] = ptr; // Points the bucket to the new structure

	if((table->count)/(table->size) >= 3) // Checks on when to grow
		table = growHt(table, (table->size*7)); // Grows the hash table

	return 0;
}


// Function that deletes
void htDelete(Ht *table, void(*delfunc)(char *wordPair, void *occurence))
{
	if(table == NULL) return;

	linkedlist *LLptr = NULL;
	linkedlist *temp = NULL;

	for(int i = 0; i < table->size; i++) // Free memory for every string in the table
	{
		LLptr = table->table[i]; // List points to the ith element of the table
		while(LLptr != NULL)
		{
			temp = LLptr; // Sets temp to what LLptr is pointing to
			LLptr = LLptr->next; // Sets LLptr to the next structure
			delfunc(temp->wordpairs, temp->occurence); // Sends the word pairs and occurences to be freed
			free(temp); // Frees the structure
		}
	}
	free(table->table); // Frees the table
	free(table); // Frees the table pointer
}


// Deletes the hash table and frees its memory
void freeLL(char *wordPair, void *occurence)
{
	free(wordPair);
	free(occurence);
}


// Grow function that increases the size of the hash table
Ht *growHt(Ht *table, int newSize)
{
	linkedlist *LLptr, *nextptr; // Pointer variables
	Ht *newHt = (Ht *) malloc(sizeof(Ht)); // Mallocs space for a new hash table pointer
	int index = 0;

	newHt->table = calloc(newSize, sizeof(linkedlist *)); // Creates a new hash table with the new size

	for(int i = 0; i < table->size; i++) // Loops through the previous table buckets
	{
		LLptr = table->table[i]; // Points LLptr to the structure table is pointing to
		while(LLptr != NULL)
		{
			nextptr = LLptr->next; // Saves the next structure pointer
			index = hash(LLptr->wordpairs)%newSize; // Rehashes the word pair with new size
			LLptr->next = newHt->table[index]; // Points next in the structure back to the structure the bucket is pointing to
			newHt->table[index] = LLptr; // Points the bucket in the new table to the structure	
			LLptr = nextptr; // Makes LLptr point to the next structure saved with nextptr
		}
	}

	free(table->table); // Frees the previous table

	table->table = newHt->table; // points previous table to new table
	table->size = newSize; // Updates the size in the hash table function

	free(newHt); // Frees the new hash table pointer

	return table;
}


// A function to apply the user's function
void htApply(Ht *table, void(*func)(char *wordpairs, void *occurence))
{
	for(int i = 0; i < table->size; i++)
	{
		linkedlist *ptr = table->table[i]; // Points to the buckets of the table
		while(ptr) // While the pointer isn't NULL
		{
			func(ptr->wordpairs, ptr->occurence); // Recursively passes to a passed in function
			ptr = ptr->next; // Increments to the next pointer
		}
	}
}


// Compare the structures for qsort
int cmpfunc(const void *a_, const void *b_)
{
	const linkedlist *a = (const linkedlist *) a_; // Creates a linkedlist pointer for a
	const linkedlist *b = (const linkedlist *) b_; // Creates a linkedlist pointer for b

	if(*((int*)(a->occurence)) > *((int*)(b->occurence))) return 1; // If a < b return positive
	else if(*((int*)(a->occurence)) < *((int*)(b->occurence))) return -1; // If a < b return negative
	else return 0; // If a == b return 0
}


// Makes array of structures to sort
void makeArray(char *wordPair, void *occurence)
{
	Array[ind].wordpairs = wordPair; // Makes member wordpairs of the array equal to wordPair
	Array[ind].occurence = occurence; // Makes member occurence of the array equal to occurence
	ind++; // Increments the index
}


// Gets called with htApply to print out the word pairs and their occurences
void print(char *wordPair, void *occurence)
{
	int *ptr = (int *) occurence; // Gets the occurence as an int
	printf("%s %i\n", wordPair, *ptr); // Prints out the word pair and its occurence
}


// Creates a hash key based on the word pair
int hash(char *wordPair)
{
	int hashKey = 0;
	 
	for(int i = 0; i < strlen(wordPair); i++)
	{
		hashKey += wordPair[i]; // http://stackoverflow.com/questions/7666509/hash-function-for-string
		hashKey += (hashKey << 10); // Shift left 10 bits
		hashKey += (hashKey >> 6); // Shift right 6 bits
	}
	
	hashKey += (hashKey << 3); // Shift left 3 bits
	hashKey += (hashKey >> 11); // Shift right 11 bits
	hashKey += (hashKey << 15); // Shift left 15 bits

	return(abs(hashKey));
}


