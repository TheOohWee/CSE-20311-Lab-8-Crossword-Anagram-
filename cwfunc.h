#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// 1. defining macros 
#define SIZE 15
#define MAXW 20
#define MAXC 15

// 4. typedef struct for words
typedef struct {
    char word[MAXC]; // readwords
    int length; // readwords
    int placed;
    int row;
    int col;
    int direction; // let's say 0 = across and 1 is down
} Word;


// 2. showing function prototypes
void initBoard(char [][SIZE], char); // done
void printBoard(char [][SIZE], FILE*); // done

// 3. modes function prototypess
void interactiveMode(char [][SIZE], char [][SIZE], Word [], int*);
void batchMode(char [][SIZE], char [][SIZE], Word[], int*, FILE*, FILE* );


// 5. functions for the backend of the program
void toUpper(char []); // done
void readWords(FILE*, Word[], int*); // done
void placeFirstWord(char [][SIZE], Word*); //dojne
int  canPlace(char [][SIZE], char *, int, int, int, int); // done
void placeWord(char [][SIZE], Word*); // done 
int findPlacement(char [][SIZE], Word*); // done
void buildPuzzle(char [][SIZE], char [][SIZE]); // done
void scrambleWord(char*, char*); // done 
void printClues(FILE*, Word [], int); // done 
int isValid(char []); // done
void sortWords(Word [], int); // done
int compareWords(const void*, const void*); // done

#endif
