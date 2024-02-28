#include <stdio.h>
#include <string.h>

#define MAX_CATEGORIES 12
#define MAX_TITLE_LEN 150
#define MAX_NAME_LEN 15

int main() {
    char title[MAX_TITLE_LEN + 1];
    char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
    int quantities[MAX_CATEGORIES];
    char xAxisLabel[MAX_NAME_LEN + 1];
    char sortChoice;
    int numCategories;

    // Get user input
    printf("Enter the title of the bar chart: ");
    fgets(title, MAX_TITLE_LEN, stdin);
    title[strcspn(title, "\n")] = '\0'; // Remove trailing newline

    printf("Enter the number of categories: ");
    scanf("%d", &numCategories);

    for (int i = 0; i < numCategories; i++) {
        printf("Enter category %d name: ", i + 1);
        scanf("%s", categories[i]);
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

    // Print the bar chart
    printf("\n%s\n", title); 
    for (int i = 0; i < numCategories; i++) {
        printf("%s |", categories[i]);
        int scaledQty = (quantities[i] * 60) / maxQuantity; // Adjust scaling as needed
        for (int j = 0; j < scaledQty; j++) {
            printf("X");
        }
        printf("\n");
    }
    printf("------------+\n"); // Simple x-axis
    printf("%s\n", xAxisLabel);

    // ... Add more features here!

    return 0;
}