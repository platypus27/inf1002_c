#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CATEGORIES 12
#define MAX_TITLE_LEN 150
#define MAX_NAME_LEN 15

char *genWhitespace(int numSpaces);
char *alignCenter(char *title, int maxQuantity);
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
int multiplier(int n);

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

    printf("\n1. Change category name \n2. Change category quantity \n3. Add new category \n4. Remove category\nSelect one of the options above: ");
    scanf(" %d", &userChoice);

    chartValues(*numCategories, categories, quantities);
    if (userChoice == 1)
    {
        do
        {
            printf("\nEnter Index of item to change: ");
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

        printf("Enter category %d name: ", index);
        scanf("%s", userInput);

        for (int j = 0; j < *numCategories; j++)
        {
            if (strcmp(userInput, categories[j]) == 0)
            {
                printf("Category name already exists. Please enter a different name: ");
                scanf("%s", userInput);
                j = -1;
            }
        }

        // check if category name is too long
        if (strlen(categories[index]) > MAX_NAME_LEN)
        {
            printf("Category name is too long. Please enter a shorter name: ");
            scanf("%s", userInput);
        }
        strcpy(categories[index - 1], userInput);
    }
    else if (userChoice == 2)
    {
        do
        {
            printf("\nEnter Index of item to change: ");
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

        do
        {
            printf("Enter new quantity for category %d: ", index);
            if (scanf("%d", &quantities[index - 1]) != 1 || quantities[index - 1] <= 0)
            {
                printf("Input error: Please enter a positive integer.\n");
                // Clear input buffer
                while (getchar() != '\n')
                    ;
                continue; // Continue to prompt for new input
            }
            // Check if the new input is a positive integer
            if (quantities[index - 1] <= 0)
            {
                printf("Input error: Please enter a positive integer.\n");
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

            printf("Enter new category name: ");
            scanf("%s", userInput);

            for (int j = 0; j < *numCategories; j++)
            {
                if (strcmp(userInput, categories[j]) == 0)
                {
                    printf("Category name already exists. Please enter a different name: ");
                    scanf("%s", userInput);
                    j = -1;
                }
            }

            // check if category name is too long
            if (strlen(userInput) > MAX_NAME_LEN)
            {
                printf("Category name is too long. Please enter a shorter name: ");
                scanf("%s", userInput);
            }
            strcpy(categories[*numCategories], userInput);

            do
            {
                printf("Enter quantity for new category: ");
                if (scanf("%d", &quantities[*numCategories]) != 1 || quantities[*numCategories] <= 0)
                {
                    printf("Input error: Please enter a positive integer.\n");
                    // Clear input buffer
                    while (getchar() != '\n')
                        ;
                    continue; // Continue to prompt for new input
                }
                // Check if the new input is a positive integer
                if (quantities[*numCategories] <= 0)
                {
                    printf("Input error: Please enter a positive integer.\n");
                    continue; // Continue to prompt for new input
                }
                // Break the loop if input is valid
                break;
            } while (1);
            (*numCategories)++;
        }
        else
        {
            printf("MAX Categories reached, remove some before adding.\n");
        }
    }
    else if (userChoice == 4)
    {
        do
        {
            printf("\nEnter Index of item to remove: ");
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
        printf("\nInput Error. Please enter valid input.");
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
    FILE *file = fopen("graph.txt", "a");
    if (file == NULL)
    {
        printf("Error opening file for writing.\n");
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

    printf("Chart saved.\n");
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
    char title[MAX_TITLE_LEN + 1];
    char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
    int quantities[MAX_CATEGORIES];
    char xAxisLabel[MAX_NAME_LEN + 1];
    char sortChoice;
    int choice;
    int userChoice;
    int numCategories;
    int frontSpacing;
    int scaleofXaxis;

    // get user input
    // get title of bar chart
    printf("Enter the title of the bar chart: ");
    // fgets(title, MAX_TITLE_LEN, stdin);
    scanf(" %[^\n]", &title);
    title[strcspn(title, "\n")] = '\0'; // Remove trailing newline

    // get number of categories
    do
    {
        printf("Enter the number of categories: ");
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
        for (int j = 0; j < i; j++)
        {
            if (strcmp(categories[i], categories[j]) == 0)
            {
                printf("Category name already exists. Please enter a different name: ");
                scanf(" %s", categories[i]);
                j = -1;
            }
        }
        // check if category name is too long
        if (strlen(categories[i]) > MAX_NAME_LEN)
        {
            printf("Category name is too long. Please enter a shorter name: ");
            scanf("%s", categories[i]);
        }
        do
        {
            printf("Enter quantity for %s: ", categories[i]);
            if (scanf("%d", &quantities[i]) != 1 || quantities[i] <= 0)
            {
                printf("Input error: Please enter a positive integer.\n");
                // Clear input buffer
                while (getchar() != '\n')
                    ;
            }
        } while (quantities[i] <= 0);
    }

    printf("Enter label for x-axis: ");
    scanf(" %s", xAxisLabel); // Space to consume newline

    printf("Sort by (a) category name or (b) bar length? ");
    scanf(" %c", &sortChoice);

    // (Basic) Sorting - Implement your own sorting algorithm here
    if (sortChoice == 'a')
    {
        sortByCatName(quantities, categories, numCategories);
    } else if (sortChoice == 'b') {
        sortByBarLength(quantities, categories, numCategories);
    }

    displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);

    printf("1. Print Chart\n2. Edit Chart\n3. New Chart\n4. Export Chart\n5. Exit\n\nEnter option: ");
    scanf(" %d", &choice);

    while (choice == 1 || choice == 2 || choice == 3 || choice == 4)
    {
        if (choice == 1)
        {
            displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
        }
        else if (choice == 2)
        {
            editValues(&numCategories, categories, quantities);
        }
        else if (choice == 3)
        {
            newChart();
        }
        else if (choice == 4)
        {
            exportChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
        }
        printf("1. Print Chart\n2. Edit Chart\n3. New Chart\n4. Export Chart\n5. Exit\n\nEnter option: ");
        scanf(" %d", &choice);
    }

    return 0;
}