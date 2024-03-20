/**
 * Functions Header File
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/


#define FUNCTIONS_H
#include "../include/config.h"

//main.c
int getChoice();
int getCategories();
int inputs();
void displayChart(char *title, char categories[][MAX_NAME_LEN + 1], int quantities[], int numCategories, int scaleofXaxis, char *xAxisLabel);
char *genWhitespace(int numSpaces);
char *alignCenter(char *title, int maxQuantity);
void sortByBarLength(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
void sortByCatName(int quantities[], char categories[][MAX_NAME_LEN + 1], int numCategories);
int multiplier(int n);

//sort_function.c
int getSortMethod();