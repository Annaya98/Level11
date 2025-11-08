#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "md5.h"

#if __has_include("fileutil.h")
#include "fileutil.h"
#endif

#define PASS_LEN 50     // Maximum length any password will be.
#define HASH_LEN 33     // Length of hash plus one for null.
#define CAPACITY 70     // for loadFileAA

//// CHALLENGE1: Sort the hashes using qsort.
// from qsort lecture video
int alphabetic(const void * a, const void *b) {
    char ** aa = (char **)a;
    char ** bb = (char **)b;
    return strcmp(*aa, *bb);
}

// TODO: Read the hashes file into an array.
//   Use either a 2D array or an array of arrays.
//   Use the loadFile function from fileutil.c
//   Uncomment the appropriate statement.

//copied from prev assignment (lv 11)
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

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        printf("Usage: %s hash_file dictionary_file\n", argv[0]);
        exit(1);
    }

//   Uncomment the appropriate statement.
  int size;
    //char (*hashes)[HASH_LEN] = loadFile(argv[1], &size);
    char **hashes = loadFileAA(argv[1], &size);

    // ==CHALLENGE1: Sort the hashes using qsort.==
    qsort(hashes, size, sizeof(char *), alphabetic);

        // TODO
        // Open the password file for reading.
        FILE *in = fopen(argv[2], "r");
        if (!in) {
            perror("Can't open file");
            exit(1);
        }
        int count = 0;
        // TODO
        // For each password, hash it, then use the array search
        // function from fileutil.h to find the hash.
        // If you find it, display the password and the hash.
        // Keep track of how many hashes were found.

        // CHALLENGE1: Use binary search instead of linear search.

        // TODO
        // When done with the file:
        //   Close the file
            fclose(in);
        //   Display the number of hashes found.
        printf("Cracked %d hashes\n", count);

        // Free up memory.
        // Free the memory used by the array(from lv 11)
        for (int i = 0; i < size; i++) {
            //for loop to free up each string to prevent memory leaks
            free(hashes[i]);
        }
        free(hashes);
}