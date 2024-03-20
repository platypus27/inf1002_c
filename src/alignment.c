/**
 * Alignment Functions
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#define ALIGNMENT_C
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/config.h"
#include "functions.h"

/**
 * Function to generate whitespace
 * @param int numSpaces
 * @return char *
*/
char *genWhitespace(int numSpaces) {
    char *spaces = malloc(numSpaces + 1); // Allocate memory for the spaces and the null terminator
    if (spaces != NULL) {
        memset(spaces, ' ', numSpaces); // Fill the memory with spaces
        spaces[numSpaces] = '\0';       // Add the null terminator
    }
    return spaces;
}

/**
 * Function to align the title of the chart in the center
 * @param char *title
 * @param int maxQuantity
 * @return char *
*/
char *alignCenter(char *title, int maxQuantity) {
    int spacing = (maxQuantity - strlen(title)) / 2;
    char *alignedTitle = malloc(strlen(title) + spacing + 1);
    for (int count = 0; count < spacing; count++) {
        alignedTitle[count] = ' ';
    }

    strcpy(alignedTitle + spacing, title);
    return alignedTitle;
}

/**
 * Function to get the multiplier for the x-axis
 * @param int n
 * @return int
*/
int multiplier(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    if (pow(10, count - 2) < 1) {
        return 1;
    }
    else {
        return pow(10, count - 2);
    }
}
