// Fundamentals of Computing
// Lab8 
// Amir Tomashpayev

// main part of the program

// P.S. I asked grad TA Jacob for an extension, because I was at Yale for hackathon over the weekend last week. 
// He granted me the extension for this lab.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "cwfunc.h"

int main(int argc, char *argv[]) {
    char puzzle[SIZE][SIZE];
    char solution[SIZE][SIZE];
    Word words[MAXW];
    int wordCount = 0;


    initBoard(puzzle, '#');
    initBoard(solution, '.');

    if (argc == 1) {
        interactiveMode(puzzle, solution, words, &wordCount);
    }
    else if (argc == 2) {
        FILE *in = fopen(argv[1], "r");
        if (!in) {printf("Error: cannot open", argv[1]); return 1;}
        batchMode(puzzle, solution, words, &wordCount, in, stdout);
        fclose(in);
    }
    else if (argc == 3) {
        FILE *in = fopen(argv[1], "r");
        FILE *out = fopen(argv[2], "w");
        if (!in) {printf("Error: cannot open", argv[1]); return 1;}
        if (!out) {printf("Error: cannot open", argv[2]); return 1;
        batchMode(puzzle, solution, words, &wordCount, in, out);
        fclose(in);
        fclose(out);
    }
    else {
        printf("Error: too many command line arguments today\n");
        return 1; 
    }

    return 0;

    }
}

