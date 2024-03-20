/**
 * Error handling functions
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#define ERROR_HANDLING_C
#include <stdio.h>
#include "../include/config.h"
#include "functions.h"

/**
 * Function to check if a category name already exists in the list
 * Used for form validation
 * @param char name[]
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int numCategories
 * @return int
*/
int isDuplicateName(char name[], char categories[][MAX_NAME_LEN + 1], int numCategories) {
    for (int i = 0; i < numCategories; i++) {
        if (strcmp(name, categories[i]) == 0) {
            return 1; // Name already exists
        }
    }
    return 0; // Name is unique
}
