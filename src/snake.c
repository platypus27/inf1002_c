/**
 * Get Categories Function
 * @version 1.0
 * @author Ng Ao Yu 2303697
 * @author Jay Lim Jun Han 2303699
 * @author Yeo Hiong Kai 2303688
 * @author Lee Cheng Kae 2303702
*/

#ifndef SNAKE_C
#define SNAKE_C
#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <conio.h> 
#include "../include/config.h"
#include "../include/functions.h"

int i, j, height = 20, width = 20; 
int gameover, score; 
int x, y, fruitx, fruity, flag; 

/**
 * Setup function of snake game
 * @return void
*/
void setup() 
{ 
    gameover = 0; 

    // Stores height and width 
    x = height / 2; 
    y = width / 2; 
label1: 
    fruitx = rand() % 20; 
    if (fruitx == 0) 
        goto label1; 
label2: 
    fruity = rand() % 20; 
    if (fruity == 0) 
        goto label2; 
    score = 0; 
} 

/**
 * Draw function of snake game
 * @return void
*/
void draw() 
{ 
    system("cls"); 
    for (i = 0; i < height; i++) { 
        for (j = 0; j < width; j++) { 
            if (i == 0 || i == width - 1 
                || j == 0 
                || j == height - 1) { 
                printf("#"); 
            } 
            else { 
                if (i == x && j == y) 
                    printf("0"); 
                else if (i == fruitx 
                        && j == fruity) 
                    printf("*"); 
                else
                    printf(" "); 
            } 
        } 
        printf("\n"); 
    } 

    // Print the score after the 
    // game ends 
    printf("score = %d", score); 
    printf("\n"); 
    printf(EXIT_SNAKE); 
} 

/**
 * Input function of snake game
 * @return void
*/
void input() 
{ 
    if (kbhit()) { 
        switch (getch()) { 
        case 'a': 
            flag = 1; 
            break; 
        case 's': 
            flag = 2; 
            break; 
        case 'd': 
            flag = 3; 
            break; 
        case 'w': 
            flag = 4; 
            break; 
        case 'x': 
            gameover = 1; 
            break; 
        } 
    } 
} 

/**
 * Logic function of snake game
 * @return void
*/
void logic() 
{ 
    Sleep(SLEEP_TIME); 
    switch (flag) { 
    case 1: 
        y--; 
        break; 
    case 2: 
        x++; 
        break; 
    case 3: 
        y++; 
        break; 
    case 4: 
        x--; 
        break; 
    default: 
        break; 
    } 

    // If the game is over 
    if (x < 0 || x > height 
        || y < 0 || y > width) 
        gameover = 1; 

    // If snake reaches the fruit 
    // then update the score 
    if (x == fruitx && y == fruity) { 
    label3: 
        fruitx = rand() % 20; 
        if (fruitx == 0) 
            goto label3; 

    // After eating the above fruit 
    // generate new fruit 
    label4: 
        fruity = rand() % 20; 
        if (fruity == 0) 
            goto label4; 
        score += 10; 
    } 
} 

/**
 * Function to run snake game
 * @return int
*/
void snake() { 
    int m, n; 

    // Generate boundary 
    setup(); 

    // Until the game is over 
    while (!gameover) { 

        // Function Call 
        draw(); 
        input(); 
        logic(); 
    } 
} 

#endif