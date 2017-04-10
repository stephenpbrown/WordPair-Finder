// Steve Brown
// CS360
// Assignment 1
// Due 2/1/16


#include "ht.h"
#include "getWord.h"


int ind = 0; // Index counter for Array
linkedlist *Array = NULL; // Array to be used to store and sort word pairs


// Checks for the word pair and inserts it if it doesn't exist
void mainInsert(Ht *table, char *wordPair)
{
	int *occurence = (int *) htSearch(table, wordPair); // Casts the value htSearch returns to an int

	if(occurence == NULL) // If occurence is null then the word pair isn't in the table
	{	
		occurence = (int *) malloc(sizeof(int)); // Allocates heap memory for an int
		(*occurence) = 1; // Set occurence to 1
	
		if(htInsert(table, wordPair, occurence) != 0) // Sends table, word pair and occurence to htInsert
			printf("A problem occured while inserting\n"); // Error checking
	}
	else 
	{
		(*occurence)++; // If the word pair is in the table, then just increment the occurence
		free(wordPair); // Frees the wordPair that didn't get inserted
	}
}


// This is the main function
int main(int argc, char **argv)
{	
	if(argc < 2) // Makes sure there are at least two arguments
	{
		fprintf(stderr, "Invalid input.\n\nUse form: ./wordpairs <-count> filename1 <filename2> ... <filenameN>\n\nWhere -count is the number of word pairs and filename is a directory to a text file.\n");
		return 1;
	}

	Ht *hashTable = htNew(); // Makes an initial hash table
	int i = 0, count = 0, j = 1;
	char *curWord, *nextWord, *wordPair; // Variables for storing words and the word pair

	if(sscanf(argv[1], "%i", &count) == 1)  // Checks for a negative number to know if to include a count
	{
		if(count > 0) // Makes sure to not try to print 0 word pairs
		{
			fprintf(stderr, "Invalid input.\n\nUse form: ./wordpairs <-count> filename1 <filename2> ... <filenameN>\n\nWhere -count is the number of word pairs and filename is a directory to a text file.\n");
			return 1;
		}
		if(count == 0)
		{
			fprintf(stderr, "Can't print 0 word pairs.\n");
			return 1;
		}
		count *= (-1);
		j = 2; // Starts parsing out files starting on the third string
	}

	for(i = j; i < argc; i++) // Loops through all the text files and stores them
	{
		if(isdigit(*argv[i])) // Checks if the input string is a number instead of directory


		{
			fprintf(stderr, "Invalid input.\n\nUse form: ./wordpairs <-count> filename1 <filename2> ... <filenameN>\n\nWhere -count is the number of word pairs and filename is a directory to a text file.\n");
			return 1;
		}

		FILE *fp;
		if((fp = fopen(argv[i], "r")) == NULL) // Opens the file in the specified directory
		{


			//fprintf(stderr, "Invalid directory inputted. Unable to open specified file.\n");

			break;
			//return 1; 
		}
	
		// Gets the first two words in the file.
		curWord = getNextWord(fp); // Points curWord to the first word
		nextWord = getNextWord(fp); // Points nextWord to the second word

		// Checks to make sure the text file has two or more words
		if(curWord == NULL || nextWord == NULL)
		{
 		   fprintf(stderr, "Invalid file contents\n"); // Change later
		   return 1;
		}

  		// Makes word pair and sends to mainInsert
		wordPair = (char *) malloc(strlen(curWord) + strlen(nextWord) + 2); // Allocate exact space for wordpair

		strcpy(wordPair, curWord); // Copies over the value of curWord to wordPair
		strcat(wordPair, " "); // Concatenates a space onto the end of wordPair
		strcat(wordPair, nextWord); // Concatinates nextWord onto the end of wordPair

		mainInsert(hashTable, wordPair); // Pass to mainInsert to search for and insert word pair

		free(curWord); // Frees the value curWord is pointing to
		curWord = nextWord; // Points curWord to nextWord

		// Loops through, makes wordpair, and sends to mainInsert
		while((nextWord = getNextWord(fp)) != NULL)
		{
			wordPair = (char *) malloc(strlen(curWord) + strlen(nextWord) + 2); // Allocate exact space for wordpair

			strcpy(wordPair, curWord); // Copies over the value of curWord to wordPair
			strcat(wordPair, " "); // Concatenates a space onto the end of wordPair
			strcat(wordPair, nextWord); // Concatinates nextWord onto the end of wordPair

			mainInsert(hashTable, wordPair); // Pass to mainInsert to search for and insert word pair
			free(curWord); // Frees the value curWord is pointing to
			curWord = nextWord; // Points curWord to nextWord
		}
		fclose(fp); // Closes the file
		free(curWord); // Frees the remaining memory of curWord
	}
	Array = malloc(sizeof(linkedlist)*hashTable->count); // Make an array to store structures

	htApply(hashTable, makeArray); // Makes an array of structures to sort

	qsort(Array, hashTable->count, sizeof(linkedlist), cmpfunc); // Quick sorts the array

	// Prints out if the count is greater than the number of word pairs
	if(count > hashTable->count)
	{
		for(int i = (hashTable->count-1); i >= 0; i--)
			printf("%10d %s\n", *(int *) Array[i].occurence, (char *) Array[i].wordpairs);
	}
	// Prints all word pairs if no count is specified
	else if(count != 0)
		for(int i = (hashTable->count-1); i >= (hashTable->count-count); i--)
			printf("%10d %s\n", *(int *) Array[i].occurence, (char *) Array[i].wordpairs);
	// Prints the number of word pairs that count specified
	else
		for(int i = (hashTable->count-1); i >= 0; i--)
			printf("%10d %s\n", *(int *) Array[i].occurence, (char *) Array[i].wordpairs);

	free(Array); // Frees the Array
	
	htDelete(hashTable, freeLL); // Deletes the hash table and linked structures

	return 0;
}
