#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_CATEGORIES 12
#define MAX_TITLE_LEN 150
#define MAX_NAME_LEN 15

char* genWhitespace(int numSpaces);

int main() {
    char title[MAX_TITLE_LEN + 1];
    char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
    int quantities[MAX_CATEGORIES];
    char xAxisLabel[MAX_NAME_LEN + 1];
    char sortChoice;
    int numCategories;
    int frontSpacing;

    // Get user input
    printf("Enter the title of the bar chart: ");
    fgets(title, MAX_TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the number of categories: ");
    scanf("%d", &numCategories);

    for (int i = 0; i < numCategories; i++) {
        printf("Enter category %d name: ", i + 1);
        scanf("%s", categories[i]);
        frontSpacing = strlen(categories[0]);
        for (int j = 0; j < i; j++) {
            if (strcmp(categories[i], categories[j]) == 0) {
                printf("Category name already exists. Please enter a different name: ");
                scanf("%s", categories[i]);
                j = -1;
            }
        }
        if (strlen(categories[i]) > MAX_NAME_LEN) {
            printf("Category name is too long. Please enter a shorter name: ");
            scanf("%s", categories[i]);
        }
        if (strlen(categories[i]) > frontSpacing) {
            frontSpacing = strlen(categories[i]);
        }
        printf("Enter quantity for %s: ", categories[i]);
        scanf("%d", &quantities[i]);
    }

    printf("Enter label for x-axis: ");
    scanf(" %s", xAxisLabel); // Space to consume newline

    printf("Sort by (a) category name or (b) bar length? ");
    scanf(" %c", &sortChoice);

    // (Basic) Sorting - Implement your own sorting algorithm here 
    if (sortChoice == 'b') {
        // ... (add sorting logic for quantities and categories)
    }

    // Find maximum quantity for scaling
    int maxQuantity = 0;
    for (int i = 0; i < numCategories; i++) {
        if (quantities[i] > maxQuantity) {
            maxQuantity = quantities[i];
        }
    }

    // Find maximum scaled quantity for x-axis scaling
    int maxScaledQty = 0;
    for (int i = 0; i < numCategories; i++) {
        int scaledQty = (quantities[i] * 60) / maxQuantity; 
        if (scaledQty > maxScaledQty) {
            maxScaledQty = scaledQty;
        }
    }

    // Print the bar chart
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
            printf("X");
        }
        printf("\n");
    }

    // Print x-axis
    printf("%s+", genWhitespace(frontSpacing));
    for (int i = 0; i < maxScaledQty; i++) {
        printf("-");
    }
    printf("+\n");

    // Print tick marks and labels
    int numTickMarks = (maxScaledQty / 10) + 1; // Roughly one tick every 10 units
    int tickSpacing = maxScaledQty / (numTickMarks - 1); 

    for (int i = 0; i <= maxScaledQty; i++) {
        if (i % tickSpacing == 0) {
            printf("%-10d", i * maxQuantity / 60); // Scale back to original values
        } else {
            printf(" "); // Single space for non-tick mark positions
        }
    }
    printf("\n");
    printf("\n");

    // ... Add more features here!

    return 0;
}

char* genWhitespace (int numSpaces) {
    char *spaces = malloc(numSpaces + 1); // Allocate memory for the spaces and the null terminator
    if (spaces != NULL) {
        memset(spaces, ' ', numSpaces); // Fill the memory with spaces
        spaces[numSpaces] = '\0'; // Add the null terminator
    }
    return spaces;
}