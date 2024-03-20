/**
 * Get Categories Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#define CATEGORIES_C
#include <stdio.h>
#include "../include/config.h"
#include "functions.h"

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
    do {
        printf("%s",INPUT_NUMCAT);
        if (scanf("%d", &numCategories) != 1 || numCategories < 1 || numCategories > MAX_CATEGORIES) {
            printf("%s ", INVALID_RANGE " %d.\n", MAX_CATEGORIES);
            // Clear the input buffer
            while (getchar() != '\n')
                ;
        }
    } while (numCategories < 1 || numCategories > MAX_CATEGORIES);
    for (int i = 0; i < numCategories; i++)
    {
        printf("Enter category %d name: ", i + 1);
        scanf("%s", categories[i]);
        frontSpacing = strlen(categories[0]);
        for (int j = 0; j < i; j++){
            if (strcmp(categories[i], categories[j]) == 0)
            {
                printf("%s",CATNAME_EXISTS);
                scanf(" %s", categories[i]);
                j = -1;
            }
        }
        // check if category name is too long
        if (strlen(categories[i]) > MAX_NAME_LEN) { 
            printf("%s",CATNAME_LONG);
            scanf("%s", categories[i]);
        }
        do {
            printf("Enter quantity for %s: ", categories[i]);
            if (scanf("%d", &quantities[i]) != 1 || quantities[i] <= 0){
                printf(INVALID_NEGATIVE);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
            }
        } while (quantities[i] <= 0);
    }
}