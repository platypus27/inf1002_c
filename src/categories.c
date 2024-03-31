/**
 * Get Categories Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef CATEGORIES_C
#define CATEGORIES_C
#include <stdio.h>
#include <stdlib.h>

#include <windows.h>
#include <mmsystem.h>

#include "../include/config.h"
#include "../include/functions.h"

extern int numCategories;
extern char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
extern int frontSpacing;
extern int quantities[MAX_CATEGORIES];

/**
 * Function to get categories
 * Gets user input for categories and quantities
 * @return int
*/
int getCategories() {
    // Loop until a valid number of categories is entered
    do {
        printf("%s",INPUT_NUMCAT);
        // Check if the input is a number and within the valid range
        if (scanf("%d", &numCategories) != 1 || numCategories < 1 || numCategories > MAX_CATEGORIES) {
            printf("%s%d.\n",INVALID_RANGE, MAX_CATEGORIES);
            // Clear the input buffer
            while (getchar() != '\n')
                ;
        }
    } while (numCategories < 1 || numCategories > MAX_CATEGORIES);

    // Loop for each category
    for (int i = 0; i < numCategories; i++)
    {
        printf("Enter category %d name: ", i + 1);
        scanf(" %[^\n]", &categories[i]);

        // Check if the category name is "snake"
        if (strcmp(categories[i], "snake") == 0) {
            char yn;
            printf("Do you want to play snake? (y/n): ");
            scanf(" %c", &yn);
            // If the user wants to play snake, call the snake function
            if (yn == 'y') {
                printf("test");
                snake();
            }
        } 
        // Check if the category name is "cat" and play a sound if it is
        else if (strcmp(categories[i], "cat") == 0) {
            PlaySound(TEXT("sound/cat-meow5.wav"), NULL, SND_FILENAME | SND_ASYNC);
        } 
        // Check if the category name is "dog" and play a sound if it is
        else if (strcmp(categories[i], "dog") == 0) {
            PlaySound(TEXT("sound/dog-bark7.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }

        frontSpacing = strlen(categories[0]);

        // Check if the category name already exists
        for (int j = 0; j < i; j++){
            if (strcmp(categories[i], categories[j]) == 0)
            {
                printf("%s",CATNAME_EXISTS);
                scanf(" %s", categories[i]);
                j = -1;
            }
        }
        // Check if the category name is too long
        checkLength(i);
    }
}

#endif