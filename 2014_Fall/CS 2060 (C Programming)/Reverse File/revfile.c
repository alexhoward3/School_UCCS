/*
 * file revfile.c
 * Author: Alex Howard
 * CS 2060 - Jason Upchurch
 * 
 * This program takes a file from stdin (redirect) and either
 * reverses the words in each line [-W] or reverses each line in the
 * file (prints last line first, first line last) [-L].
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "getline.c"
#include "zdbg.c"

/*
 * usage: revfile [-WL] < file.txt>
 * -W "C Programming Sucks!" becomes: "Sucks! Programming C" (for each line)
 * -L EOF gets Beginning of file and vice versa
 * 1024 lines or less
 */
//Pneumonoultramicroscopicsilicovolcanoconiosis

/*
 * Reverse all of the lines in the file
 * Print starting at the last line up to the first.
 */
void revLines() {
    //printf("### Reversing Lines ###\n"); //Debug
    size_t lnSize = 1024;
    char *arr[1024];
    int count = 0;
    
    //Scan how many lines are in the file and put those lines into an array of strings
    while(!feof(stdin)) {
	char *line = malloc(lnSize);
	getline(&line, &lnSize, stdin); //Get each line
	arr[count] = line; //Place each line into the array
	count++; //Increment the counter
    }
    for(int i = count-1; i > 0; i--) {
	printf("%s", arr[i]);
	if(i == count-1) {
	    printf("\n"); //Creates new line for last line
	}
    }
}

/*
 * Simple swap function
 */
void swap(char *c, int i, int j) {
    char tmp = c[i];
    c[i] = c[j];
    c[j] = tmp;
}

/*
 * Reverse the string from a given point
 */
void revstr(char *str, int len) {
    for(int i = 0; i < len/2; i++) {
	swap(str, i, len-i-1); //Swap
    }
}

/*
 * Reverse all of the lines in the file.
 * Start by getting the length of the line,
 * Then reverse all of the letters in the line.
 * Reverse all of the words,
 * then reverse the last word.
 */
void revline(char *line) {
    int length = strlen(line);
    revstr(line, length); //Reverse the entire line
    int p = 0; //Keeps track of position
    for(int i = 0; i < length; i++) {
	if(line[i] == ' ') {
	    revstr(&line[p], i-p); //Reverse each word delimeted by whitespace
	    p=i+1;
	}
    }
    revstr(&line[p], length-p); //Reverse the final word.
}

/*
 * Reverse all of the words in each line.
 */
void revWords() {
    //printf("### Reversing Words ###\n"); //Debug
    size_t lnSize = 1024;
    while(!feof(stdin)) {
	char *buffer;
	buffer = malloc(lnSize);
	getline(&buffer, &lnSize, stdin); //Get the line from the file
	if(buffer[strlen(buffer)-1] == '\n') buffer[strlen(buffer)-1] = '\0'; //Null character
	revline(buffer); //Reverse the line
	printf("%s\n", buffer); //Print out the reversed line
    }
}

/*
 * This program takes a file from stdin (redirect) and either
 * reverses the words in each line [-W] or reverses each line in the
 * file (prints last line first, first line last) [-L].
 */
int main(int argc, char *argv[]) {
    if(argc != 2) {
	printf("usage: revfile [-WL] < file.txt\n"); //Error handling
	return 1;
    } else if(!(strcmp(argv[1], "-L"))) {
	revLines(); //If the option is -L, reverse the lines
    } else if(!(strcmp(argv[1], "-W"))) {
	revWords(); //If the option is -W, reverse the words
    } else if(!(strcmp(argv[1], "-X"))) {
	printZDBG();
    } else {
	printf("usage: revfile [-WL] < file.txt\n"); //Any other input, print usage
	return 1;
    }
    
    return 0; //Exit
}