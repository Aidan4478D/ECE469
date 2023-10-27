#include "boardLogic.h"
#include <stdlib.h>
#include <iostream> 

using namespace std; 

int board[BOARD_X][BOARD_Y]; 

void initializeBoard(bool std_pos) {

    int line_pos, white_square = 0; 
    
    //initialize board with zeros
    for(int i = 0; i < BOARD_X; i++) {
        for(int j = 0; j < BOARD_Y; j++) {
            
            //insert 1 and 2 into correct positions into initialized board
            if(std_pos) {
                if(i < 3 && line_pos++ % 2 == 0) board[i][j] = 49;
                else if (i > 4 && line_pos++ % 2 == 0) board[i][j] = 50;
                else board[i][j] = 32;
            }
            else board[i][j] = 32; //space in ascii 

            if (white_square++ % 2 == 1) board[i][j] = 33;  
        }
        line_pos++;
        white_square++; 
    }
}

void printBoard() {

    //draw rows in board
    cout << "     a     b     c     d     e     f     g     h   \n"; 
    cout << "  |-----|-----|-----|-----|-----|-----|-----|-----|\n"; 

    for(int i = 0; i < BOARD_X; i++) {
        
        //print row number
        cout << i << " "; 

        for(int j = 0; j < BOARD_Y; j++) {

            //if on an odd square, make it gray
            if(board[i][j] == '!') {
                
                cout << "|" << "\033[90;100m     \033[0m";
                if(j == BOARD_Y - 1) cout << "|"; 
                continue; 
            }
            else {
                cout << "|  "; 
            }
            //get piece {0, 1, 2, 3, 4}
            char piece = (char)board[i][j]; 
            
            //regular piece for player 1
            if(piece == '1') cout << "\033[1;44m.\033[0m" << "  ";
        
            //regular piece for player 2
            else if(piece == '2') cout << "\033[1;41m.\033[0m" << "  ";
            
            //king for player 1
            else if(piece == '3') cout << "\033[33;44m#\033[0m" << "  ";
            
            //king for player 2
            else if(piece == '4') cout << "\033[33;41m#\033[0m" << "  ";

            else cout << piece << "  ";
            
            //add wall at end
            if(j == BOARD_Y - 1) cout << "|"; 
        }
        cout << "\n  |-----|-----|-----|-----|-----|-----|-----|-----|\n"; 
    }
}

