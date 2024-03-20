/**
 * Export Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#define SORT_C
#include <stdio.h>
#include "../include/config.h"
#include "functions.h"

/**
 * Function to export the chart to a file
 * File path can be found in config file
 * @param char *title
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int quantities[]
 * @param int numCategories
 * @param int scaleofXaxis
 * @param char *xAxisLabel
 * @return void
*/
void exportChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel) {
    char filePath;
    // printf("\nEnter file path to save to: ");
    // scanf("%d", &filePath);
    // strcat(filePath, ".txt");

    // Open a file for writing
    FILE *file = fopen(FILE_PATH, "a");
    if (file == NULL) {
        printf("%s",FILE_ERROR);
    }

    // Write the chart to the file
    int maxQuantity = 0;
    int frontSpacing = 0;

    for (int i = 0; i < numCategories; i++) {
        // Find maximum quantity for scaling
        if (quantities[i] > maxQuantity) {
            maxQuantity = quantities[i];
        }
        // Get largest length of front spacing
        if (strlen(categories[i]) > frontSpacing) {
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