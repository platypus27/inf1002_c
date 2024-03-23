/**
 * Main program of Bar Chart Generator for INF1002 C Project
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

/**
 * Include statements
 * To note is the inclusion of header files
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "include/config.h"
#include "include/functions.h"

char title[MAX_TITLE_LEN + 1];
char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
int quantities[MAX_CATEGORIES];
char xAxisLabel[MAX_NAME_LEN + 1];
char sortChoice;
int choice, userChoice, numCategories, frontSpacing, scaleofXaxis;

/**
 * Function to get user choice
 * Mainly used to remove repeated printf and scanf
 * @return int
*/
int getChoice() {
    int choice;
    printf(MAIN_PRINT);
    scanf(" %d", &choice);
    return choice;
}

/**
 * Function to get main user inputs
 * To be run at start of program
 * Gets user input for categories, quantities, x-axis label and sorting method
 * @return int
*/
int inputs() {
    
    // get categories
    getCategories();

    // x-axis label
    printf("%s", INPUT_LABELX);
    scanf(" %s", xAxisLabel); // Space to consume newline

    // get sorting method
    getSortMethod();
}

/**
 * Main function
 * @return int
*/
int main() {
    // get title of bar chart
    printf("%s",INPUT_TITLE);
    scanf(" %[^\n]", &title);

    title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
    
    // get all basic inputs
    inputs();

    // display graph
    displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);

    // get choice after generating first chart
    choice = getChoice();
    while (choice >= 1 && choice <= 6) {
        switch (choice) {
            // display chart
            case 1:
                displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
                break;
            // edit values in chart
            case 2:
                editmenu(&numCategories, categories, quantities);
                break;
            // generate new chart
            case 3:
                main();
                break;
            // export chart to file
            case 4:
                exportChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
                break;
            // export dataset to file
            case 5:
                exportData(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
                break;
            case 6:
                importData();
                break;
        }
        choice = getChoice();
    }
    return 0;
}