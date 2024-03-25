/**
 * Sorting Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef SORT_C
#define SORT_C
#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include "../include/functions.h"

extern char sortChoice;
extern int quantities[MAX_CATEGORIES];
extern char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
extern int numCategories;

/**
 * Function to get sorting method
 * @return int
*/
void getSortMethod() {
    // sorting method
    printf("%s", INPUT_SORT);
    scanf(" %c", &sortChoice);
    switch (sortChoice) {
        case 'a':
            sortByCatName(quantities, categories, numCategories);
            break;
        case 'b':
            sortByBarLength(quantities, categories, numCategories);
            break;
    }
}

/**
 * Function to sort the chart by bar length
 * @param int quantities[]
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int numCategories
 * @return void
*/
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories) {
    for (int i = 0; i < numCategories - 1; i++) {
        for (int j = 0; j < numCategories - i - 1; j++) {
            if (quantities[j] > quantities[j + 1]) {
                int temp_quantity = quantities[j];
                quantities[j] = quantities[j + 1];
                quantities[j + 1] = temp_quantity;

                char temp_categories[MAX_NAME_LEN + 1];
                strcpy(temp_categories, categories[j]);
                strcpy(categories[j], categories[j + 1]);
                strcpy(categories[j + 1], temp_categories);
            }
        }
    }
}

/**
 * Function to sort the chart by category name
 * @param int quantities[]
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int numCategories
 * @return void
*/
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories) {
    for (int i = 0; i < numCategories - 1; i++) {
        for (int j = 0; j < numCategories - i - 1; j++) {
            if (strcmp(categories[j], categories[j + 1]) > 0) {
                int temp_quantity = quantities[j];
                quantities[j] = quantities[j + 1];
                quantities[j + 1] = temp_quantity;

                char temp_categories[MAX_NAME_LEN + 1];
                strcpy(temp_categories, categories[j]);
                strcpy(categories[j], categories[j + 1]);
                strcpy(categories[j + 1], temp_categories);
            }
        }
    }
}

#endif