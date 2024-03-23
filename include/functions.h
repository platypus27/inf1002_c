/**
 * Functions Header File
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"

//main.c
int getChoice();
int inputs();
int manualGen();

//alignment.c
char *alignCenter(char *title, int maxQuantity);
char *genWhitespace(int numSpaces);
int multiplier(int n);

//categories.c
int getCategories();

//chartgen.c
void displayChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, char *xAxisLabel);
void chartValues(int numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]);

//editchart.c
int changeCatName(int index, int *numCategories);
int changeCatQuant(int index, int *numCategories);
int addCategory(int index, int *numCategories);
int deleteCategory(int index, int *numCategories);
int getCatIndex(int index, int *numCategories);
int editTitle(char title[]);
int editXLabel(char xAxisLabel[]);

//editmenu.c
void editmenu(int *numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]);

//error_handling.c
int isDuplicateName(char name[], char categories[][MAX_NAME_LEN + 1], int numCategories);
int checkLength(int i);

//export.c
int generateX(int maxQuantity, int scaleofXaxis, int maxScaledQty, int frontSpacing, int tickSpacing, FILE *file);
int generateChart(char title[], char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int maxQuantity, int maxScaledQty, int frontSpacing, FILE *file);
void exportChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);
void exportData(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);

//import.c
int importData();
int selectFile(char *fileName);

//sort.c
int getSortMethod();
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);

#endif