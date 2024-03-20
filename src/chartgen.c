/**
 * Generate Chart Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef CHARTGEN_C
#define CHARTGEN_C
#include <stdio.h>
#include <stdlib.h>
#include "../include/config.h"
#include "functions.h"

extern char title[MAX_TITLE_LEN + 1];
extern int numCategories;
extern char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
extern int quantities[MAX_CATEGORIES];

/**
 * Function to display the bar chart
 * Essentially creates bar chart
 * @param char *title
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int quantities[]
 * @param int numCategories
 * @param int scaleofXaxis
 * @param char *xAxisLabel
 * @return void
*/
void displayChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel) {

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

/**
 * Function to display the chart values
 * @param int numCategories
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int quantities[]
 * @return void
*/
void chartValues(int numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]) {
    printf("%s",PRINT_CHART);
    for (int i = 0; i < numCategories; i++) {
        printf("%d. %s %d\n", i + 1, categories[i], quantities[i]);
    }
}

#endif