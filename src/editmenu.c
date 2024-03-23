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

extern char title[MAX_TITLE_LEN + 1];
extern char xAxisLabel[MAX_NAME_LEN + 1];
extern char sortChoice;

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
        // change category name
        case 1:
            changeCatName(index, numCategories);
            break;
        // change category quantity
        case 2:
            changeCatQuant(index, numCategories);
            break;
        // add new category
        case 3:
            addCategory(index, numCategories);
            break;
        // remove category
        case 4:
            deleteCategory(index, numCategories);
            break;
        // change title
        case 5:
            editTitle(title);
            break;
        // change x-axis label
        case 6:
            editXLabel(xAxisLabel);
            break;
        // change sort method
        case 7:
            getSortMethod();
            displayChart(title, categories, quantities, *numCategories, xAxisLabel);
            break;
        // back
        case 8:
            break;
        default:
            printf("%s",INVALID_INPUT);
    }
}

#endif