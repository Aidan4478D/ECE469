#include "boardLogic.h"
#include <iostream> 

using namespace std; 

void initializeBoard() {
    
    for(int i = 0; i < BOARD_X; i++) {
        
        for(int j = 0; j < BOARD_Y; j++) {
            
            board[i][j] = 0; 
        }
    }
}


int printBoard() {
    
    //draw rows in board
    for(int i = 0; i < BOARD_X; i++) {
        
        for(int j = 0; j < BOARD_Y; j++) {
            
            cout << board[i][j]; 
        }
        cout << "\n"; 
    }

    return 0; 
}

