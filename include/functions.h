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
void welcome();
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
void changeCatName(int index, int *numCategories);
void changeCatQuant(int index, int *numCategories);
void addCategory(int index, int *numCategories);
void deleteCategory(int index, int *numCategories);
void editTitle(char *title);
void editXLabel(char *xAxisLabel);
int getCatIndex(int index, int *numCategories);

//editmenu.c
void editmenu(int *numCategories, char categories[][MAX_NAME_LEN + 1], int quantities[]);

//error_handling.c
int isDuplicateName(char name[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void checkLength(int i);

//export.c
void generateX(int maxQuantity, int scaleofXaxis, int maxScaledQty, int frontSpacing, int tickSpacing, FILE *file);
void generateChart(char title[], char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int maxQuantity, int maxScaledQty, int frontSpacing, FILE *file);
void exportChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);
void exportData(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);

//import.c
int importData();
int selectFile(char *fileName);

//snake.c
void setup();
void draw();
void input();
void logic();
void snake();

//sort.c
void getSortMethod();
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);


#endif