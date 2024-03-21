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

//alignment.c
char *alignCenter(char *title, int maxQuantity);
char *genWhitespace(int numSpaces);
int multiplier(int n);

//categories.c
int getCategories();

//chartgen.c
void displayChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);
void chartValues(int numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]);

//editchart.c
void editValues(int *numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]);
int changeCatName(int index, int *numCategories, char *userInput);
int changeCatQuant(int index, int *numCategories, char *userInput);
int addCategory(int index, int *numCategories, char *userInput);
int removeCategory(int index, int *numCategories, char *userInput);
int getCatIndex(int index, int *numCategories);

//error_handling.c
int isDuplicateName(char name[], char categories[][MAX_NAME_LEN + 1], int numCategories);
int checkLength(int i);

//export.c
int generateX(int maxQuantity, int scaleofXaxis, int maxScaledQty, int frontSpacing, int tickSpacing, FILE *file);
int generateChart(char title[], char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int maxQuantity, int maxScaledQty, int frontSpacing, FILE *file);
void exportChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);

//sort.c
int getSortMethod();
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);

#endif