#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "config.h"

#define MAX_CATEGORIES 12
#define MAX_TITLE_LEN 150
#define MAX_NAME_LEN 15

char *genWhitespace(int numSpaces);
char *alignCenter(char *title, int maxQuantity);
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
int multiplier(int n);

char title[MAX_TITLE_LEN + 1];
char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
int quantities[MAX_CATEGORIES];
char xAxisLabel[MAX_NAME_LEN + 1];
char sortChoice;
int choice, userChoice, numCategories, frontSpacing, scaleofXaxis;

int getChoice() {
    int choice;
    printf(MAIN_PRINT);
    scanf(" %d", &choice);
    return choice;
}

int inputs() {
    do {
        printf("%s",INPUT_NUMCAT);
        if (scanf("%d", &numCategories) != 1 || numCategories < 1 || numCategories > MAX_CATEGORIES)
        {
            printf("Input error. Please enter a valid integer between 1 and %d.\n", MAX_CATEGORIES);
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
            if (scanf("%d", &quantities[i]) != 1 || quantities[i] <= 0)
            {
                printf(INVALID_NEGATIVE);
                // Clear input buffer
                while (getchar() != '\n')
                    ;
            }
        } while (quantities[i] <= 0);
    }

    // get number of categories
    printf("%s", INPUT_LABELX);
    scanf(" %s", xAxisLabel); // Space to consume newline

    // sorting method
    printf("%s", INPUT_SORT);
    scanf(" %c", &sortChoice);
    if (sortChoice == 'a')
    {
        sortByCatName(quantities, categories, numCategories);
    } else if (sortChoice == 'b') {
        sortByBarLength(quantities, categories, numCategories);
    }
}

void displayChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel)
{

    int maxQuantity = 0;
    int frontSpacing = 0;

    for (int i = 0; i < numCategories; i++)
    {
        // Find maximum quantity for scaling
        if (quantities[i] > maxQuantity)
        {
            maxQuantity = quantities[i];
        }
        // Get largest length of front spacing
        if (strlen(categories[i]) > frontSpacing)
        {
            frontSpacing = strlen(categories[i]);
        }
    }

    scaleofXaxis = multiplier(maxQuantity);

    // Find maximum scaled quantity for x-axis scaling
    int maxScaledQty = 0;
    for (int i = 0; i < numCategories; i++)
    {
        int scaledQty = (quantities[i] * 60) / maxQuantity;
        if (scaledQty > maxScaledQty)
        {
            maxScaledQty = scaledQty;
        }
    }

    // Print the bar chart
    title = alignCenter(title, maxScaledQty + frontSpacing);
    printf("\n%s\n", title);
    for (int i = 0; i < numCategories; i++)
    {
        int additionalSpacing = frontSpacing - strlen(categories[i]);
        printf("%s|\n", genWhitespace(frontSpacing)); // Adjust spacing as needed
        if (additionalSpacing > 0)
        {
            printf("%s%s|", genWhitespace(additionalSpacing), categories[i]);
        }
        else
        {
            printf("%s|", categories[i]);
        }
        int scaledQty = (quantities[i] * 60) / maxQuantity; // Adjust scaling as needed
        for (int j = 0; j < scaledQty; j++)
        {
            printf("\u2587");
        }
        printf(" %d \n", quantities[i]);
    }

    // Print tick marks and labels
    int numTickMarks = (maxScaledQty / 15) + 1; // Roughly one tick every 10 units
    int tickSpacing = maxScaledQty / (numTickMarks - 1);

    // Print x-axis
    printf("%s+", genWhitespace(frontSpacing));
    for (int i = 0; i < maxScaledQty; i++)
    {
        if ((i + 1) % tickSpacing == 0)
        {
            printf("+");
        }
        else
        {
            printf("-");
        }
    }
    printf("\n");

    printf("%s", genWhitespace(frontSpacing));
    char numStr[5];
    for (int i = 0; i <= 4; i++)
    {
        // formatNum((((double)maxQuantity / 4) * (i / scaleofXaxis)));
        double tickValue = ((double)maxQuantity / 4) * ((double)i / scaleofXaxis);
        if ((int)tickValue == tickValue)
        {
            sprintf(numStr, "%d", (int)tickValue);
        }
        else
        {
            sprintf(numStr, "%.2f", tickValue);
        }
        printf("%s", numStr);
        printf("%s", genWhitespace(15 - strlen(numStr)));
    }

    // print x-axis label
    xAxisLabel = alignCenter(xAxisLabel, maxScaledQty + frontSpacing);
    printf("\n%s(x%d)", xAxisLabel, scaleofXaxis);
    printf("\n");
    printf("\n");
}

void chartValues(int numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[])
{
    printf("\nChart Values\n------------\n");
    for (int i = 0; i < numCategories; i++)
    {
        printf("%d. %s %d\n", i + 1, categories[i], quantities[i]);
    }
}

// Function to check if a category name already exists in the list
int isDuplicateName(char name[], char categories[][MAX_NAME_LEN + 1], int numCategories)
{
    for (int i = 0; i < numCategories; i++)
    {
        if (strcmp(name, categories[i]) == 0)
        {
            return 1; // Name already exists
        }
    }
    return 0; // Name is unique
}

void editValues(int *numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[])
{
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
                printf("Input error: Please enter a valid index.\n");
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

void newChart()
{
    main();
}

void exportChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel)
{
    char filePath;
    // printf("\nEnter file path to save to: ");
    // scanf("%d", &filePath);
    // strcat(filePath, ".txt");

    // Open a file for writing
    FILE *file = fopen(FILE_PATH, "a");
    if (file == NULL)
    {
        printf("%s",FILE_ERROR);
    }

    // Write the chart to the file
    int maxQuantity = 0;
    int frontSpacing = 0;

    for (int i = 0; i < numCategories; i++)
    {
        // Find maximum quantity for scaling
        if (quantities[i] > maxQuantity)
        {
            maxQuantity = quantities[i];
        }
        // Get largest length of front spacing
        if (strlen(categories[i]) > frontSpacing)
        {
            frontSpacing = strlen(categories[i]);
        }
    }

    scaleofXaxis = multiplier(maxQuantity);

    // Find maximum scaled quantity for x-axis scaling
    int maxScaledQty = 0;
    for (int i = 0; i < numCategories; i++)
    {
        int scaledQty = (quantities[i] * 60) / maxQuantity;
        if (scaledQty > maxScaledQty)
        {
            maxScaledQty = scaledQty;
        }
    }

    // Print the bar chart
    title = alignCenter(title, maxScaledQty + frontSpacing);
    fprintf(file, "\n%s\n", title);
    for (int i = 0; i < numCategories; i++)
    {
        int additionalSpacing = frontSpacing - strlen(categories[i]);
        fprintf(file, "%s|\n", genWhitespace(frontSpacing)); // Adjust spacing as needed
        if (additionalSpacing > 0)
        {
            fprintf(file, "%s%s|", genWhitespace(additionalSpacing), categories[i]);
        }
        else
        {
            fprintf(file, "%s|", categories[i]);
        }
        int scaledQty = (quantities[i] * 60) / maxQuantity; // Adjust scaling as needed
        for (int j = 0; j < scaledQty; j++)
        {
            fprintf(file, "\u2588");
        }
        fprintf(file, " %d \n", quantities[i]);
    }

    // Print tick marks and labels
    int numTickMarks = (maxScaledQty / 15) + 1; // Roughly one tick every 10 units
    int tickSpacing = maxScaledQty / (numTickMarks - 1);

    // Print x-axis
    fprintf(file, "%s+", genWhitespace(frontSpacing));
    for (int i = 0; i < maxScaledQty; i++)
    {
        if ((i + 1) % tickSpacing == 0)
        {
            fprintf(file, "+");
        }
        else
        {
            fprintf(file, "-");
        }
    }
    fprintf(file, "\n");

    fprintf(file, "%s", genWhitespace(frontSpacing));
    char numStr[5];
    for (int i = 0; i <= 4; i++)
    {
        // formatNum((((double)maxQuantity / 4) * (i / scaleofXaxis)));
        double tickValue = ((double)maxQuantity / 4) * ((double)i / scaleofXaxis);
        if ((int)tickValue == tickValue)
        {
            sprintf(numStr, "%d", (int)tickValue);
        }
        else
        {
            sprintf(numStr, "%.2f", tickValue);
        }
        fprintf(file, "%s", numStr);
        fprintf(file, "%s", genWhitespace(15 - strlen(numStr)));
    }

    // print x-axis label
    xAxisLabel = alignCenter(xAxisLabel, maxScaledQty + frontSpacing);
    fprintf(file, "\n%s(x%d)", xAxisLabel, scaleofXaxis);

    // Close the file
    fclose(file);

    printf("%s", SUCCESS_SAVE);
}

char *genWhitespace(int numSpaces)
{
    char *spaces = malloc(numSpaces + 1); // Allocate memory for the spaces and the null terminator
    if (spaces != NULL)
    {
        memset(spaces, ' ', numSpaces); // Fill the memory with spaces
        spaces[numSpaces] = '\0';       // Add the null terminator
    }
    return spaces;
}

char *alignCenter(char *title, int maxQuantity)
{
    int spacing = (maxQuantity - strlen(title)) / 2;
    char *alignedTitle = malloc(strlen(title) + spacing + 1);
    for (int count = 0; count < spacing; count++)
    {
        alignedTitle[count] = ' ';
    }

    strcpy(alignedTitle + spacing, title);
    return alignedTitle;
}

void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories)
{
    for (int i = 0; i < numCategories - 1; i++)
    {
        for (int j = 0; j < numCategories - i - 1; j++)
        {
            if (quantities[j] > quantities[j + 1])
            {
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

void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories)
{
    for (int i = 0; i < numCategories - 1; i++)
    {
        for (int j = 0; j < numCategories - i - 1; j++)
        {
            if (strcmp(categories[j], categories[j + 1]) > 0)
            {
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

int multiplier(int n)
{
    int count = 0;
    while (n != 0)
    {
        n /= 10;
        ++count;
    }
    if (pow(10, count - 2) < 1)
    {
        return 1;
    }
    else
    {
        return pow(10, count - 2);
    }
}

int main()
{
    // get user input
    // get title of bar chart
    printf("%s",INPUT_TITLE);
    scanf(" %[^\n]", &title);
    title[strcspn(title, "\n")] = '\0'; // Remove trailing newline
    
    inputs();

    displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);

    choice = getChoice();
    while (choice >= 1 && choice <= 4) {
        switch (choice) {
            case 1:
                displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
                break;
            case 2:
                editValues(&numCategories, categories, quantities);
                break;
            case 3:
                newChart();
                break;
            case 4:
                exportChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
                break;
        }
        choice = getChoice();
    }
    return 0;
}