/**
 * Edit Chart Values Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#define EDITCHART_C
#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include "functions.h"

extern char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
extern int quantities[MAX_CATEGORIES];


/**
 * Function to edit values of the chart
 * @param int *numCategories
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int quantities[]
 * @return void
*/
void editValues(int *numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]) {
    chartValues(*numCategories, categories, quantities);
    int index;
    int userChoice;
    char userInput[MAX_NAME_LEN + 1];

    printf("%s",EDIT_VALUES);
    scanf(" %d", &userChoice);

    chartValues(*numCategories, categories, quantities);
    if (userChoice == 1)
    {
        do
        {
            printf("%s",ENTER_CATINDEX);
            scanf("%d", &index);
            if (index <= 0 || index > *numCategories)
            {
                printf("%s",INVALID_INPUT);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                continue; // Continue to prompt for new input
            }
            break;
        } while (1);

        printf("%s",ENTER_CATNAME);
        scanf("%s", userInput);

        for (int j = 0; j < *numCategories; j++)
        {
            if (strcmp(userInput, categories[j]) == 0)
            {
                printf("%s",CATNAME_EXISTS);
                scanf("%s", userInput);
                j = -1;
            }
        }

        // check if category name is too long
        if (strlen(categories[index]) > MAX_NAME_LEN)
        {
            printf("%s",CATNAME_LONG);
            scanf("%s", userInput);
        }
        strcpy(categories[index - 1], userInput);
    }
    else if (userChoice == 2)
    {
        do
        {
            printf("%s",ENTER_CATINDEX);
            scanf("%d", &index);
            if (index <= 0 || index > *numCategories)
            {
                printf("%s",INVALID_INPUT);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                continue; // Continue to prompt for new input
            }
            break;
        } while (1);

        do
        {
            printf("%s",ENTER_CATQUANTITY);
            if (scanf("%d", &quantities[index - 1]) != 1 || quantities[index - 1] <= 0)
            {
                printf("%s",INVALID_NEGATIVE);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                continue; // Continue to prompt for new input
            }
            // Check if the new input is a positive integer
            if (quantities[index - 1] <= 0)
            {
                printf("%s",INVALID_NEGATIVE);
                continue; // Continue to prompt for new input
            }
            // Break the loop if input is valid
            break;
        } while (1);
    }
    else if (userChoice == 3)
    {
        if (*numCategories != MAX_CATEGORIES)
        {

            printf("\n%s",ENTER_CATNAME);
            scanf("%s", userInput);

            for (int j = 0; j < *numCategories; j++)
            {
                if (strcmp(userInput, categories[j]) == 0)
                {
                    printf("%s",CATNAME_EXISTS);
                    scanf("%s", userInput);
                    j = -1;
                }
            }

            // check if category name is too long
            if (strlen(userInput) > MAX_NAME_LEN)
            {
                printf("%s",CATNAME_LONG);
                scanf("%s", userInput);
            }
            strcpy(categories[*numCategories], userInput);

            do
            {
                printf("%s",ENTER_CATQUANTITY);
                if (scanf("%d", &quantities[*numCategories]) != 1 || quantities[*numCategories] <= 0)
                {
                    printf("%s",INVALID_NEGATIVE);
                    // Clear input buffer
                    while (getchar() != '\n')
                        ;
                    continue; // Continue to prompt for new input
                }
                // Check if the new input is a positive integer
                if (quantities[*numCategories] <= 0)
                {
                    printf("%s",INVALID_NEGATIVE);
                    continue; // Continue to prompt for new input
                }
                // Break the loop if input is valid
                break;
            } while (1);
            (*numCategories)++;
        }
        else
        {
            printf("%s",INVLAID_MAX);
        }
    }
    else if (userChoice == 4)
    {
        do
        {
            printf("%s",ENTER_CATREMOVE);
            scanf("%d", &index);
            if (index <= 0 || index > *numCategories)
            {
                printf("%s\n",INVALID_INPUT);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                continue; // Continue to prompt for new input
            }
            break;
        } while (1);
        (*numCategories)--;
        for (int count = index - 1; count < *numCategories; count++)
        {
            quantities[count] = quantities[count + 1];
            strcpy(categories[count], categories[count + 1]);
        }
    }
    else
    {
        printf("%s",INVALID_INPUT);
        // editValues(&numCategories, categories, quantities);
    }
}
