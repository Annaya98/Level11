#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fileutil.h"
// ===== ARRAYS OF ARRAYS ======

// DIRECTIONS
// Choose whether you are doing the 2D array or
// the array of arrays.
// For the 2D array,
//    implement loadFile2D, substringSearch2D, and free2D.
// For the array of arrays,
//    implement loadFileAA, substringSearchAA, and freeAA.


// Load the text file from the given filename.
// Return a pointer to the array of strings.
// Sets the value of size to be the number of valid
// entries in the array (not the total array length).

//CAPACITY value between 10-100
#define CAPACITY 70


char **loadFileAA(char *filename, int *size) {
    // <-- THIS ONEEEEE!!
    //Open the file for reading.
    FILE *in = fopen(filename, "r");
    if (!in) {
        perror("Can't open file");
        exit(1);
    }
    //Make the initial allocation of CAPACITY strings:
    //char ** arr = malloc(CAPACITY * sizeof(char *)).
    char **arr = malloc(CAPACITY * sizeof(char *));

    //Set the SIZE to 0
    *size = 0;
    //initialize other var
    int capacity = CAPACITY;
    char buffer[1000];

    //Start looping through the file
    //Use fgets to read the line into a buffer string
    while (fgets(buffer, 1000, in) != NULL) {
        //while fgets is not equal to end of file

        //Check if the array needs extending. If so, increase the CAPACITY, then use realloc to extend.
        if (*size >= capacity) {
            //capacity reached?
            capacity *= 2; // then extend the capaccity x2
            arr = realloc(arr, capacity * sizeof(char *)); // extends array to new capacity
        }
        //Trim off the newline character.
        int length = strlen(buffer);
        buffer[length - 1] = '\0';

        //Use strlen to determine the length of the buffer, then use malloc to a string of this
        //length, plus 1 for the null character.
        length = strlen(buffer);
        arr[*size] = malloc((length + 1) * sizeof(char));

        //Copy the buffer into the array at index SIZE using strcpy.
        strcpy(arr[*size], buffer);

        //Increment the SIZE.
        (*size)++;
    }
    //close when end of file is reached
    fclose(in);
    //return pointer to arr
    return arr;
}


//=======================================================
char (*loadFile2D(char *filename, int *size))[COLS] {
    FILE *in = fopen(filename, "r");
    if (!in) {
        perror("Can't open file");
        exit(1);
    }

    // TODO
    // Allocate memory for an 2D array, using COLS as the width.
    // Read the file line by line into a buffer.
    // Trim newline.
    // Expand array if necessary (realloc).
    // Copy each line from the buffer into the array (use strcpy).
    // Close the file.

    // The size should be the number of entries in the array.
    *size = 0;

    // Return pointer to the array.
    return NULL;
}

// Search the array for the target string.
// Return the found string or NULL if not found.

//=======================================================
char *substringSearchAA(char *target, char **lines, int size) //This is now a LinearSearch
{
    //Search the given array for a target string. Both a pointer to the array-of-strings and its size (the number of valid entries) must be passed in.
    //Use strcmp to locate the line that contains the target string. Returns the found string, or NULL if not found. If there is more than one matching string, return the first one found.

    //linear search:
    for (int i = 0; i < size; i++) {
        // loop through all strings
        //use strcmp to locate the line that contains the target string
        //EX:
        //if (*aa == *bb) { // if they are equal return 0
        //    return 0;
        if (strcmp(lines[i], target) == 0) {
            //used strcmp as discussed in the video to compare each hash exactly
            return lines[i]; //return string
        }
    } //didnt find target?
    return NULL; //return NULL
}

//=======================================================
char *substringSearch2D(char *target, char (*lines)[COLS], int size) //IGNORE
{
    return NULL;
}

//=======================================================
// Free the memory used by the array
void freeAA(char **arr, int size) // <----
{
    // Free the memory used by the array
    for (int i = 0; i < size; i++) {
        //for loop to free up each string to prevent memory leaks
        free(arr[i]);
    }
    free(arr);
}

void free2D(char (*arr)[COLS]) //IGNORE
{
}
