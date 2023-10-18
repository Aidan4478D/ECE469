#include "boardLogic.h"
#include <iostream> 

using namespace std; 

int board[BOARD_X][BOARD_Y]; 

void initializeBoard(bool std_pos) {
    
    //initialize board with zeros
    for(int i = 0; i < BOARD_X; i++) {
        for(int j = 0; j < BOARD_Y; j++) {
            board[i][j] = 32; //load[i][j]; 
        }
    }
}
/*
    if(std_pos) {
        if(i < 4) board[i][(j * 2) + i % 2] = 49;
        else board[i][(j * 2) + i % 2] = 50; 
    }
*/

void printBoard() {

    //draw rows in board
    cout << "|-----|-----|-----|-----|-----|-----|-----|-----|\n"; 

    for(int i = 0; i < BOARD_X; i++) {
        for(int j = 0; j < BOARD_Y; j++) {
            cout << "|  " << (char)board[i][j] << "  "; 
            if(j == BOARD_Y - 1) cout << "|"; 
        }
        cout << "\n|-----|-----|-----|-----|-----|-----|-----|-----|\n"; 
    }
}

