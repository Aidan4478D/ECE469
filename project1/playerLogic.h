#ifndef PLAYER_LOGIC_H
#define PLAYER_LOGIC_H

#include <vector>
#include <tuple>

using namespace std; 

typedef enum {

  COMPUTER = 1,
  USER = 2
} TURN;

typedef struct tile_s {
    int x;
    int y;
} tile_t; 


//first vector = vector of total move sequences
//second vector = vector of tuples that make up move sequence
//tuple = individual square
vector<vector<tuple<tile_t, bool>>> legalMoves(TURN player); 

//prints the legal moves
void printLegalMoves(TURN player); 

//performs a move
void makeMove(TURN *player); 

#endif //PLAYER_LOGIC_H
