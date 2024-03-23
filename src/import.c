/**
 * Import Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

// Include statements
#ifndef SORT_C
#define SORT_C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <commdlg.h>
#include "../include/config.h"
#include "../include/functions.h"

extern char title[MAX_NAME_LEN + 1];
extern char xAxisLabel[MAX_NAME_LEN + 1];
extern char sortChoice;
extern int numCategories;
extern char categories[MAX_CATEGORIES][MAX_NAME_LEN + 1];
extern int quantities[MAX_CATEGORIES];
extern int scaleofXaxis;
char* filenameStart;
char* token;

int importData() {
    char fileName[105] = "";

    // open file after being selected
    if (selectFile(fileName) == 0) {
        FILE* file = fopen(fileName, "r");
        if (file == NULL) {
            perror("Error opening file\n");
            return 1;
        }

        // get title and x-axis label from first line of file
        fscanf(file, "%[^,],%s\n", title, xAxisLabel);

        // get categories and quantities from file
        numCategories = 0;
        while (fscanf(file, "%[^,],%d\n", categories[numCategories], &quantities[numCategories]) == 2) {
            numCategories++;
        }

        fclose(file);
        displayChart(title, categories, quantities, numCategories, scaleofXaxis, xAxisLabel);
    } else {
        printf("Failed to select a file\n");
    }

    return 0;
}

int selectFile(char* fileName) {
    OPENFILENAME ofn;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = NULL;  // If you have a window to center over, put its HANDLE here
    ofn.lpstrFilter = "CSV Files\0*.csv\0Any File\0*.*\0";
    ofn.lpstrFile = fileName;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Select a File";
    ofn.Flags = OFN_DONTADDTORECENT | OFN_FILEMUSTEXIST;
    if (GetOpenFileName(&ofn)) {
        // replaceBackslashes(fileName);
        return 0;  // File selected successfully
    } else {
        return 1;  // Failed to select a file
    }
}

#endif