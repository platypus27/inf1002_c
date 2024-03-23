/**
 * Function Menu
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef MENU_C
#define MENU_C
#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include "../include/functions.h"

/**
 * Function to edit values of the chart
 * @param int *numCategories
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int quantities[]
 * @return void
*/
void editmenu(int *numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]) {
    chartValues(*numCategories, categories, quantities);
    int index, userChoice;
    char userInput[MAX_NAME_LEN + 1];

    printf("%s",EDIT_VALUES);
    scanf(" %d", &userChoice);

    chartValues(*numCategories, categories, quantities);
    switch (userChoice) {
        case 1:
            changeCatName(index, numCategories, userInput);
            break;
        case 2:
            changeCatQuant(index, numCategories, userInput);
            break;
        case 3:
            addCategory(index, numCategories, userInput);
            break;
        case 4:
            deleteCategory(index, numCategories, userInput);
            break;
        case 5:
            break;
        default:
            printf("%s",INVALID_INPUT);
    }
}

#endif