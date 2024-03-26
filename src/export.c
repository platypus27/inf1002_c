/**
 * Export Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef SORT_C
#define SORT_C
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "../include/config.h"
#include "../include/functions.h"

int tickSpacing;

/**
 * Function to generate x-axis
 * @param int maxQuantity
 * @param int scaleofXaxis
 * @param int maxScaledQty
 * @param int frontSpacing
 * @param int tickSpacing
 * @param FILE *file
 * @return int
*/
void generateX(int maxQuantity, int scaleofXaxis, int maxScaledQty, int frontSpacing, int tickSpacing, FILE *file) {
    // Print x-axis
    fprintf(file, "%s+", genWhitespace(frontSpacing));
    for (int i = 0; i < maxScaledQty; i++) {
        if ((i + 1) % tickSpacing == 0) {
            fprintf(file, "+");
        }
        else {
            fprintf(file, "-");
        }
    }
    fprintf(file, "\n");

    fprintf(file, "%s", genWhitespace(frontSpacing));
    char numStr[5];
    for (int i = 0; i <= 4; i++) {
        // formatNum((((double)maxQuantity / 4) * (i / scaleofXaxis)));
        double tickValue = ((double)maxQuantity / 4) * ((double)i / scaleofXaxis);
        if ((int)tickValue == tickValue) {
            sprintf(numStr, "%d", (int)tickValue);
        }
        else {
            sprintf(numStr, "%.2f", tickValue);
        }
        fprintf(file, "%s", numStr);
        fprintf(file, "%s", genWhitespace(15 - strlen(numStr)));
    }


}

void generateChart(char title[], char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int maxQuantity, int maxScaledQty, int frontSpacing, FILE *file){
    // Center the title and print it to the file
    title = alignCenter(title, maxScaledQty + frontSpacing);
    fprintf(file, "\n%s\n", title);

    // Loop through each category
    for (int i = 0; i < numCategories; i++) {
        // Calculate the additional spacing needed for each category
        int additionalSpacing = frontSpacing - strlen(categories[i]);

        // Print the category name to the file, adjusting the spacing as needed
        fprintf(file, "%s|\n", genWhitespace(frontSpacing));
        if (additionalSpacing > 0) {
            fprintf(file, "%s%s|", genWhitespace(additionalSpacing), categories[i]);
        }
        else {
            fprintf(file, "%s|", categories[i]);
        }

        // Calculate the scaled quantity for the category and print it to the file
        int scaledQty = (quantities[i] * 60) / maxQuantity;
        for (int j = 0; j < scaledQty; j++) {
            fprintf(file, "\u2588");
        }
        fprintf(file, " %d \n", quantities[i]);
    }

    // Calculate the number of tick marks and the spacing between them
    int numTickMarks = (maxScaledQty / 15) + 1;
    tickSpacing = maxScaledQty / (numTickMarks - 1);
}

int generatedFolder() {
    char* folderPath = "generated/";
    DWORD dwAttrib = GetFileAttributes(folderPath);
    if (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) {
        return 1;
    } else {
        if (!CreateDirectory(folderPath, NULL)) {
            return 0;
        } else {
            return 1;
        }
    }

    return 0;
}

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
    if (generatedFolder()) {
        char input[30];
        char filePath[] = "generated/";
        printf("\nEnter file path to save to: ");
        scanf(" %[^\n]", input);    
        strcat(filePath, input);
        strcat(filePath, ".txt");

        // Open a file for writing
        FILE *file = fopen(filePath, "a");
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


        generateChart(title, categories, quantities, numCategories, maxQuantity, maxScaledQty, frontSpacing, file);
        generateX(maxQuantity, scaleofXaxis, maxScaledQty, frontSpacing, tickSpacing, file);

        // print x-axis label
        xAxisLabel = alignCenter(xAxisLabel, maxScaledQty + frontSpacing);
        fprintf(file, "\n%s(x%d)", xAxisLabel, scaleofXaxis);

        // Close the file
        fclose(file);

        printf("%s", SUCCESS_SAVE);
    } else {
        printf("%s",FILE_ERROR);
    }
}

/**
 * Function to export data to a datasheet
 * @param char categories[][MAX_NAME_LEN + 1]
 * @param int quantities[]
 * @param int numCategories
 * @param int scaleofXaxis
 * @param char *xAxisLabel
 * @return int
*/
void exportData(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel){
    if (generatedFolder()) {
        char filePath[155];
        // Ask for input for the file name
        char fileName[100];
        printf("Enter file name: ");
        scanf("%s", fileName);

        sprintf(filePath, "%s%s.csv", DIR_PATH, fileName);
        FILE *fileExists = fopen(filePath, "r");
        if (fileExists != NULL) {
            printf("File with the same name already exists.\n");
            fclose(fileExists);
            return; // or handle the situation accordingly
        }

        // Open a file for writing
        FILE *file = fopen(filePath, "w");
        if (file == NULL) {
            printf("Failed to open file\n");
            printf("%s", FILE_ERROR);
            return; // or handle the situation accordingly
        }

        // Write the data to the file
        fprintf(file, "title,xAxisLabel\n");
        for (int i = 0; i < numCategories; i++) {
            fprintf(file, "%s,%d\n", categories[i], quantities[i]);
        }

        // Close the file
        fclose(file);

        printf("%s %s%s\n", SUCCESS_SAVE_DATA, DIR_PATH, fileName);
    } else {
        printf("%s", FILE_ERROR);
    }
}
#endif