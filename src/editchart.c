/**
 * Edit Chart Values Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef EDITCHART_C
#define EDITCHART_C
#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include "../include/functions.h"

extern char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
extern int quantities[MAX_CATEGORIES];
extern char title[MAX_TITLE_LEN + 1];
extern char xAxisLabel[MAX_NAME_LEN + 1];
extern int scaleofXaxis;
extern int numCategories;
extern char sortChoice;

/**
 * Function to change category name
 * Called in editValues function below
 * case 1
 * @param int index
 * @param int *numCategories
 * @return void
*/
void changeCatName(int index, int *numCategories) {
    // Create a buffer to hold the new category name
    char inputName[MAX_NAME_LEN + 1];

    // Get the actual index of the category
    index = getCatIndex(index, numCategories);

    // Prompt the user to enter a new name for the category
    printf("%s",ENTER_CATNAME);
    scanf("%s", inputName);

    // Loop through all the categories
    for (int j = 0; j < *numCategories; j++) {
        // If the new name matches an existing category name, prompt the user to enter a different name
        if (strcmp(inputName, categories[j]) == 0) {
            printf("%s",CATNAME_EXISTS);
            scanf("%s", inputName);
            j = -1;
        }
    }

    // If the new name is too long, prompt the user to enter a shorter name
    if (strlen(categories[index]) > MAX_NAME_LEN) {
        printf("%s",CATNAME_LONG);
        scanf("%s", inputName);
    }

    // Copy the new name into the category array at the specified index
    strcpy(categories[index - 1], inputName);
}

/**
 * Function to change category quantity
 * Called in editValues function below
 * case 2
 * @param int index
 * @param int *numCategories
 * @return void
*/
void changeCatQuant(int index, int *numCategories){
    index = getCatIndex(index, numCategories);

    do {
        printf("%s",ENTER_CATQUANTITY);
        if (scanf("%d", &quantities[index - 1]) != 1 || quantities[index - 1] <= 0) {
            printf("%s",INVALID_NEGATIVE);
            // Clear input buffer
            while (getchar() != '\n')
                ;
            continue; // Continue to prompt for new input
        }
        // Check if the new input is a positive integer
        if (quantities[index - 1] <= 0) {
            printf("%s",INVALID_NEGATIVE);
            continue; // Continue to prompt for new input
        }
        // Break the loop if input is valid
        break;
    } while (1);
}

/**
 * Function to add category
 * Called in editValues function below
 * case 3
 * @param int index
 * @param int *numCategories
 * @return void
*/
void addCategory(int index, int *numCategories){
    char inputName[MAX_NAME_LEN + 1];
    if (*numCategories != MAX_CATEGORIES) {
        printf("\n%s",ENTER_CATNAME);
        scanf("%s", inputName);

        for (int j = 0; j < *numCategories; j++) {
            if (strcmp(inputName, categories[j]) == 0) {
                printf("%s",CATNAME_EXISTS);
                scanf("%s", inputName);
                j = -1;
            }
        }

        // check if category name is too long
        if (strlen(inputName) > MAX_NAME_LEN) {
            printf("%s",CATNAME_LONG);
            scanf("%s", inputName);
        }
        strcpy(categories[*numCategories], inputName);

        do {
            printf("%s",ENTER_CATQUANTITY);
            if (scanf("%d", &quantities[*numCategories]) != 1 || quantities[*numCategories] <= 0) {
                printf("%s",INVALID_NEGATIVE);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                continue; // Continue to prompt for new input
            }
            // Check if the new input is a positive integer
            if (quantities[*numCategories] <= 0) {
                printf("%s",INVALID_NEGATIVE);
                continue; // Continue to prompt for new input
            }
            // Break the loop if input is valid
            break;
        } while (1);
        (*numCategories)++;
        displayChart(title, categories, quantities, *numCategories, xAxisLabel);
    }
    else {
        printf("%s",INVLAID_MAX);
    }
}

/**
 * Function to remove category
 * Called in editValues function below
 * case 4
 * @param int index
 * @param int *numCategories
 * @return void
*/
void deleteCategory(int index, int *numCategories){
    do {
        printf("%s",ENTER_CATREMOVE);
        scanf("%d", &index);
        if (index <= 0 || index > *numCategories) {
            printf("%s\n",INVALID_INPUT);
            // Clear input buffer
            while (getchar() != '\n')
                ;
            continue; // Continue to prompt for new input
        }
        break;
    } while (1);
    (*numCategories)--;
    for (int count = index - 1; count < *numCategories; count++) {
        quantities[count] = quantities[count + 1];
        strcpy(categories[count], categories[count + 1]);
    }
    displayChart(title, categories, quantities, *numCategories, xAxisLabel);
}

/**
 * Function to edit chart title
 * @param char *title
 * @return void
*/
void editTitle(char *title) {
    printf("%s",INPUT_TITLE);
    // enter new title
    scanf("%s", title);
    // display chart
    displayChart(title, categories, quantities, numCategories, xAxisLabel);
}

/**
 * Function to edit x-axis label
 * @param char *xAxisLabel
 * @return void
*/
void editXLabel(char *xAxisLabel) {
    printf("%s",INPUT_LABELX);
    // enter new x-axis label
    scanf("%s", xAxisLabel);
    // display chart
    displayChart(title, categories, quantities, numCategories, xAxisLabel);
}

/**
 * Function to get category index
 * Called in changeCatName, changeCatQuant, addCategory, deleteCategory functions above
 * @param int index
 * @param int *numCategories
 * @return void
*/
int getCatIndex(int index, int *numCategories) {
    do {
        printf("%s",ENTER_CATINDEX);
        scanf("%d", &index);
        if (index <= 0 || index > *numCategories) {
            printf("%s",INVALID_INPUT);
            // Clear input buffer
            while (getchar() != '\n')
                ;
            continue; // Continue to prompt for new input
        }
        break;
    } while (1);
}

#endif