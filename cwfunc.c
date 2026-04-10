#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cwfunc.h"
#include <string.h>
#include <ctype.h>


// P.S. I got an extension from grad TA Jacob.

// FUNCTIONS 

// done
// 1. initializies the board
void initBoard(char board[][SIZE], char ch) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            board[r][c] = ch;
        }
    }
}

// done
// 2. prints board 
void printBoard(char board[][SIZE], FILE* out) {

    fprintf(out, "-----------------\n");
    for (int r = 0; r < SIZE; r++) {
    fprintf(out, "|");
        for (int c = 0; c < SIZE; c++) {
            fprintf(out, "%c", board[r][c]);
        } 
    fprintf(out, "|\n");
    }
    fprintf(out, "-----------------\n");
}

// done
// 3. if word is valid: < 15 characters, all letters
int isValid(char word[]) {
    int len = strlen(word);
    if (len < 2 || len > 15) return 0;
    for (int i = 0; i < len; i++) {
        if (!isalpha(word[i])) return 0;
    }
   return 1;
}


// done
// 4. turning words to uppercase
void toUpper(char word[]) {
    for (int i = 0; word[i] != '\0'; i++) {
       word[i] = toupper(word[i]);
    }
}


// 5. batch mode
void batchMode(char puzzle[][SIZE], char solution[][SIZE], Word words[], int* wordCount, FILE* in, FILE* out) {

// HERE

readWords(in, words, wordCount);
sortWords(words, *wordCount);

placeFirstWord(solution, &words[0]);

for (int i = 1; i < *wordCount; i++) {
    if (!findPlacement(solution, &words[i])) {
        fprintf(out, "Could not place '%s' - stopping placement\n", words[i].word);
        break;
}
      placeWord(solution, &words[i]);
      }
buildPuzzle(solution, puzzle);
fprintf(out, "\nSolution:\n");
printBoard(solution, out);
fprintf(out, "\nCrossword puzzle:\n");
printBoard(puzzle, out);
printClues(out, words, *wordCount);
}

// 6. interactive mode
void interactiveMode(char puzzle[][SIZE], char solution[][SIZE], Word words[], int* wordCount) {

// HERE


    printf("Enter a list of words:\n");
    readWords(stdin, words, wordCount);
    sortWords(words, *wordCount);

    placeFirstWord(solution, &words[0]);

    for (int i = 1; i < *wordCount; i++) {
        if (!findPlacement(solution, &words[i])) {
            printf("Could not place '%s' - stopping placement\n", words[i].word);
            break;
}
placeWord(solution, &words[i]);
}
buildPuzzle(solution, puzzle);
printf("\nSolution:\n");
printf("\nCrossword puzzle:\n");
printBoard(puzzle, stdout);
printClues(stdout, words, *wordCount);
}

// 7. read words (use toUpper and isValid)
void readWords(FILE* in, Word words[], int *wordCount) {
    char temp[100];
    
    while (*wordCount < MAXW && fscanf(in, "%s", temp) == 1) {
        if (temp[0] == '.' && temp[1] == '\0') break;

        if (!isValid(temp)) {
            printf("'%s' is not valid, skipping \n", temp);
            continue;
        }

        toUpper(temp);
        strcpy(words[*wordCount].word, temp); // word
        words[*wordCount].length = strlen(temp); // length
        words[*wordCount].placed = 0;
        *wordCount++;
    }
}

// don't really need it but to make code more readable
// 8. sort words by descedning word length
void sortWords(Word words[], int wordCount) {
    qsort(words, wordCount, sizeof(Word), compareWords);
}


// 9. place first word horizontally centered
void placeFirstWord(char solution[][SIZE], Word *word) {
    int row = SIZE / 2;
    int startCol = (SIZE - word->length) / 2;
    
    for (int i = 0; i < word->length; i++) {
        solution[row][startCol + i] = word->word[i];
    }   

    word->placed = 1;
    word->row = row;
    word->col = startCol;
    word->direction = 0;
}

// need to check more abd spend more time
// 10. check if can place -> the hardest function so far
int canPlace(char board[][SIZE], char *word, int row, int col, int dir, int len) {
    int intersections = 0;

    for (int i = 0; i < len; i++) {
       int r, c;

       if (dir == 1) {
           r = row + i;
           c = col;
       } else if (dir == 0) {
           r = row;
           c = col + i;
    }

       if (r < 0 || r >= SIZE || c < 0 || c >= SIZE) return 0;

       char cell = board[r][c];

       if (cell == word[i]) {
           intersections++;
       } else if (cell != '.') {
           return 0;
       } else {
           if (dir == 0) {
               if (r - 1 >= 0 && board[r - 1][c] != '.') return 0;
               if (r + 1 < SIZE && board[r + 1][c] != '.') return 0; 
                   } else {
                        if (c - 1 >= 0 && board[r][c - 1] != '.') return 0;
                        if (c + 1 < SIZE && board[r][c + 1] != '.') return 0;
                   }
                 }
            }
           
    int beforeR, beforeC;
    if (dir == 1) {
        beforeR = row - 1;
        beforeC = col;
    } else {
        beforeR = row;
        beforeC = col - 1;
    }
    if (beforeR >= 0 && beforeR < SIZE && beforeC >= 0 && beforeC < SIZE) {
        if (board[beforeR][beforeC] != '.') return 0;
    }

    int afterR, afterC;
    if (dir == 1) {
        afterR = row + len;
        afterC = col;
    } else {
        afterR = row;
        afterC = col + len;
    }
    if (afterR >= 0 && afterR < SIZE && afterC >= 0 && afterC < SIZE) {
        if (board[afterR][afterC] != '.') return 0;
    }
    
    return (intersections == 1);
}

// 11. put a word on the board
void placeWord(char board[][SIZE], Word *word) {
    for (int i = 0; i < word->length; i++) {
        int r = word->row + (word->direction == 1 ? i : 0);        int c = word->col + (word->direction == 0 ? i : 0);
        board[r][c] = word->word[i];
    }
}   

// 12. find valid intersection of words
int findPlacement(char board[][SIZE], Word *word) {
    int len = word->length; 

    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (board[r][c] == '.') continue;

            for (int i = 0; i < len; i++) {
                if (word->word[i] != board[r][c]) continue;

                int startR = r - i;
                int startC = c;
                if (startR >= 0 && startR + len <= SIZE) {
                    if (canPlace(board, word->word, startR, startC, 1, len)) {
                        word->row = startR;
                        word->col = startC;
                        word->direction = 1;
                        word->placed = 1;
                        return 1;
                }
}

                startR = r;
                startC = c - i;
                if (startC >= 0 && startC + len <= SIZE) {
                    if (canPlace(board, word->word, startR, startC, 0, len)) {
                        word->row = startR;
                        word->col = startC;
                        word->direction = 0;
                        word->placed = 1;
                        return 1;
                    }
                }
}
}
}
return 0;
}

// 13. create puzzle from solution
void buildPuzzle(char solution[][SIZE], char puzzle[][SIZE]) {
    for (int r = 0; r < SIZE; r++) {
        for (int c = 0; c < SIZE; c++) {
            if (solution[r][c] != '.') {
                puzzle[r][c] = '.';
            } else {
                puzzle[r][c] = '#';
            }
        }
    }
}



// 14. generate an anagram of the word
void scrambleWord(char *original, char *scrambled) {
    int len = strlen(original);
    strcpy(scrambled, original);

    for (int i = len - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        char temp = scrambled[i];
        scrambled[i] = scrambled[j];
        scrambled[j] = temp;
}
}

// 15. generate coordinates of the beginning of the word for clues
void printClues(FILE* out, Word words[], int wordCount) {
    char scrambled[MAXC];

    fprintf(out, "\nClues:\n\n");
    for (int i = 0; i < wordCount; i++) {
        if (!words[i].placed) continue;

        scrambleWord(words[i].word, scrambled);
        fprintf(out, "%2d, %2d, %s, %s\n", words[i].row, words[i].col, words[i].direction == 0 ? "Across" : "Down ", scrambled);
}
}

// had to watch a youtube tutorial
// 16. how to compare words before sorting
int compareWords (const void *a, const void *b) {
    Word *wordA = (Word *)a;
    Word *wordB = (Word *)b;

    return wordB->length - wordA->length; // descdending
}


