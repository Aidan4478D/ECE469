#ifndef BOARD_LOGIC_H_
#define BOARD_LOGIC_H_

#include <vector>
#include <tuple>

#define BOARD_X 8
#define BOARD_Y 8

extern int board[BOARD_X][BOARD_Y]; 
int printBoard(); 

class Player {

    int num_pieces; 
    
    //vector<tuple<char, int>> legalMoves(); 
};



#endif //BOARD_LOGIC_H
