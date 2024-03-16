#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CATEGORIES 12
#define MAX_TITLE_LEN 150
#define MAX_NAME_LEN 15

char* genWhitespace(int numSpaces);
char* alignCenter(char *title, int maxQuantity);
// void formatNum(double num);
int multiplier(int n);

int main() {
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
    fgets(title, MAX_TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove trailing newline

    // get number of categories
    do {
        printf("Enter the number of categories: ");
        scanf("%d", &numCategories);
        while (getchar() != '\n');
    } while (numCategories < 1 || numCategories > MAX_CATEGORIES);

    for (int i = 0; i < numCategories; i++) {
        printf("Enter category %d name: ", i + 1);
        scanf("%s", categories[i]);
        frontSpacing = strlen(categories[0]);
        for (int j = 0; j < i; j++) {
            if (strcmp(categories[i], categories[j]) == 0) {
                printf("Category name already exists. Please enter a different name: ");
                scanf(" %s", categories[i]);
                j = -1;
            }
        }
        // check if category name is too long
        if (strlen(categories[i]) > MAX_NAME_LEN) {
            printf("Category name is too long. Please enter a shorter name: ");
            scanf("%s", categories[i]);
        }
        // get largest length of front spacing
        if (strlen(categories[i]) > frontSpacing) {
            frontSpacing = strlen(categories[i]);
        }
        do {
            printf("Enter quantity for %s: ", categories[i]);
            scanf("%d", &quantities[i]);
            while (getchar() != '\n');
        } while (quantities[i] <= 0);
    }

    printf("Enter label for x-axis: ");
    scanf(" %s", xAxisLabel); // Space to consume newline

    printf("Sort by (a) category name or (b) bar length? ");
    scanf(" %c", &sortChoice);

    // (Basic) Sorting - Implement your own sorting algorithm here 
    if (sortChoice == 'b') {
        // ... (add sorting logic for quantities and categories)
    }

    displayChart(title, categories, quantities, numCategories, frontSpacing, scaleofXaxis, xAxisLabel);

    printf("1. Print Chart\n2. Edit Chart\n3. New Chart\n4. Export Chart\n5. Exit\n\nEnter option: ");
    scanf(" %d", &choice);

    while (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
        if (choice == 1) {
            displayChart(title, categories, quantities, numCategories, frontSpacing, scaleofXaxis, xAxisLabel);        
        }
        else if (choice == 2) {
            editValues(numCategories, categories, quantities);        
        }
        else if (choice == 3) {
            newChart();
        }
        else if (choice == 4) {
            exportChart(title, categories, quantities, numCategories, frontSpacing, scaleofXaxis, xAxisLabel);
        }
        else {

        }
        printf("1. Print Chart\n2. Edit Chart\n3. New Chart\n4. Export Chart\n5. Exit\n\nEnter option: ");
        scanf(" %d", &choice);
    }

    return 0;
}

void displayChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int frontSpacing, int scaleofXaxis, char *xAxisLabel) {
    // Find maximum quantity for scaling
    int maxQuantity = 0;
    for (int i = 0; i < numCategories; i++) {
        if (quantities[i] > maxQuantity) {
            maxQuantity = quantities[i];
        }
    }

    scaleofXaxis = multiplier(maxQuantity);

    // Find maximum scaled quantity for x-axis scaling
    int maxScaledQty = 0;
    for (int i = 0; i < numCategories; i++) {
        int scaledQty = (quantities[i] * 60) / maxQuantity; 
        if (scaledQty > maxScaledQty) {
            maxScaledQty = scaledQty;
        }
    }

    // Print the bar chart
    title = alignCenter(title, maxScaledQty+frontSpacing);
    printf("\n%s\n", title); 
    for (int i = 0; i < numCategories; i++) {
        int additionalSpacing = frontSpacing - strlen(categories[i]);
        printf("%s|\n", genWhitespace(frontSpacing)); // Adjust spacing as needed
        if (additionalSpacing > 0) {
            printf("%s%s|", genWhitespace(additionalSpacing),categories[i]);
        }
        else {
            printf("%s|", categories[i]);
        }
        int scaledQty = (quantities[i] * 60) / maxQuantity; // Adjust scaling as needed
        for (int j = 0; j < scaledQty; j++) {
            printf("\u2587");
        }
        printf("\n");
    }

    // Print tick marks and labels
    int numTickMarks = (maxScaledQty / 15) + 1; // Roughly one tick every 10 units
    int tickSpacing = maxScaledQty / (numTickMarks - 1); 
        
    // Print x-axis
    printf("%s+", genWhitespace(frontSpacing));
    for (int i = 0; i < maxScaledQty; i++) {
        if ((i + 1) % tickSpacing == 0) {
            printf("+");
        } else {
            printf("-");
        }
    }
    printf("\n");

    printf("%s", genWhitespace(frontSpacing));
    char numStr[5];
    for (int i = 0; i <= 4; i++) {
        // formatNum((((double)maxQuantity / 4) * (i / scaleofXaxis)));
        sprintf(numStr, "%.2f", (((double)maxQuantity / 4) * ((double)i / scaleofXaxis)));
        printf("%s", numStr);
        printf("%s", genWhitespace(15-strlen(numStr)));
    }

    // print x-axis label
    xAxisLabel = alignCenter(xAxisLabel, maxScaledQty+frontSpacing);
    printf("\n%s(x%d)", xAxisLabel, scaleofXaxis);
    printf("\n");
    printf("\n");
}


void chartValues(int numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]) {
    printf("\nChart Values\n------------\n");
    for (int i = 0; i < numCategories; i++) { 
        printf("%d. %s %d\n", i + 1, categories[i], quantities[i]);
    }
}

void editValues(int numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]) {
    chartValues(numCategories, categories, quantities);
    int index;
    int userChoice;
    printf("\nEnter Index of item to change: ");
        scanf(" %d", &index);

        if (index <= numCategories) {
            printf("\nEnter 1 to change category %d name or 2 to change category %d quantity: ", index, index);
            scanf(" %d", &userChoice);

            if (userChoice == 1) {
                printf("Enter new name for index %d: ", index);
                scanf("%s", categories[index - 1]);
            }
            else if (userChoice == 2) {
                printf("Enter new quantity for category %d: ", index);
                scanf("%d", &quantities[index - 1]);
            }
            else {
                printf("\nInput Error. Please enter valid input.");
                editValues(numCategories, categories, quantities);        
            }
        }

        else {
            printf("\nInput Error. Please enter valid input.");
            editValues(numCategories, categories, quantities);   
        }
}

void newChart() {
    main();
}

void exportChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int frontSpacing, int scaleofXaxis, char *xAxisLabel) {
    // Open a file for writing
    FILE *file = fopen("D:/Documents/SIT Cyber/Programming Fundamentals/C Project/graph.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing.\n");
    }
    // Write the chart to the file
    // Find maximum quantity for scaling
    int maxQuantity = 0;
    for (int i = 0; i < numCategories; i++) {
        if (quantities[i] > maxQuantity) {
            maxQuantity = quantities[i];
        }
    }

    scaleofXaxis = multiplier(maxQuantity);

    // Find maximum scaled quantity for x-axis scaling
    int maxScaledQty = 0;
    for (int i = 0; i < numCategories; i++) {
        int scaledQty = (quantities[i] * 60) / maxQuantity; 
        if (scaledQty > maxScaledQty) {
            maxScaledQty = scaledQty;
        }
    }

    // Print the bar chart
    fprintf(file, "\n%s\n", title); 
    for (int i = 0; i < numCategories; i++) {
        int additionalSpacing = frontSpacing - strlen(categories[i]);
        fprintf(file, "%s|\n", genWhitespace(frontSpacing)); // Adjust spacing as needed
        if (additionalSpacing > 0) {
            fprintf(file, "%s%s|", genWhitespace(additionalSpacing),categories[i]);
        }
        else {
            fprintf(file, "%s|", categories[i]);
        }
        int scaledQty = (quantities[i] * 60) / maxQuantity; // Adjust scaling as needed
        for (int j = 0; j < scaledQty; j++) {
            fprintf(file, "\u2587");
        }
        fprintf(file, "\n");
    }

    // Print tick marks and labels
    int numTickMarks = (maxScaledQty / 15) + 1; // Roughly one tick every 10 units
    int tickSpacing = maxScaledQty / (numTickMarks - 1); 
        
    // Print x-axis
    fprintf(file, "%s+", genWhitespace(frontSpacing));
    for (int i = 0; i < maxScaledQty; i++) {
        if ((i + 1) % tickSpacing == 0) {
            fprintf(file, "+");
        } else {
            fprintf(file, "-");
        }
    }
    fprintf(file, "\n");

    fprintf(file, "%s", genWhitespace(frontSpacing));
    for (int i = 0; i <= 4; i++){
        fprintf(file, "%d", maxQuantity / 4 * i / scaleofXaxis);
        fprintf(file, "%s", genWhitespace(14));
    }

    // print x-axis label
    fprintf(file, "\n%s(x%d)", xAxisLabel, scaleofXaxis);

    // Close the file
    fclose(file);

    printf("Chart saved.\n");      
}

char* genWhitespace (int numSpaces) {
    char *spaces = malloc(numSpaces + 1); // Allocate memory for the spaces and the null terminator
    if (spaces != NULL) {
        memset(spaces, ' ', numSpaces); // Fill the memory with spaces
        spaces[numSpaces] = '\0'; // Add the null terminator
    }
    return spaces;
}

char* alignCenter(char *title, int maxQuantity) {
    int spacing = (maxQuantity - strlen(title)) / 2;
    char *alignedTitle = malloc(strlen(title) + spacing + 1);
    for (int count = 0; count < spacing; count++) {
        alignedTitle[count] = ' ';
    }

    strcpy(alignedTitle+spacing, title);
    return alignedTitle;
}

/* void formatNum(double num) {
    if ((int)num == num) {
        printf("%.0f", num);
        printf("%s", genWhitespace(14));
    } else {
        printf("%.2f", num);
        printf("%s", genWhitespace(10));
    }
} */

int multiplier(int n) {
    int count = 0;
    while (n != 0) {
        n /= 10;
        ++count;
    }
    if (pow(10, count - 2) < 1) {
        return 1;
    } else {
        return pow(10, count - 2);
    }
}