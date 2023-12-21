#include "boardLogic.h"
#include "playerLogic.h"

#include <iostream> 

//it would have been smart to implement the board as a 4x4 2D array to deal with less math
//then it would have to search less squares
//

/*
bool isAvailable(int i, int j) {
    
    if(board[k][l] == ' ') return true; 
    
    //now check for other stuff
    return false;
}*/

typedef struct tile_s {
    int x; //tile x position
    int y; //tile y position
} tile_t;

/*
    //put move into tuple -> put tuple into move sequence -> put move sequence into legal moves vector
    for(int k = 0; k < legal_squares.size() - 1; k++) {

        vector<int> square_v = legal_squares[k];
        char letter = (char)square_v[1] + 97; //convert int (0-7) to char (a-h) 
        int number = square_v[0]; 

        tuple<char, int, bool> square_t = make_tuple(letter, number, false); 

        move_sequence.push_back(square_t);
 */


//create a moveset
vector<tuple<char, int, bool>> createMoveset(tile_t start, tile_t end) {
    
    vector<tuple<char, int, bool>> sequence; 

    //add starting square to tuple
    tuple<char, int, bool> start_t = make_tuple(start.y + 97, start.x, false); 
    sequence.push_back(start_t); 

    //put move into tuple -> put tuple into move sequence -> put move sequence into legal moves vector

    tuple<char, int, bool> end_t = make_tuple(end.y + 97, end.x, false); 

    sequence.push_back(end_t);

    return sequence;    
}


//function that checks if the jump you're trying to make works out
bool checkValidJump(tile_t start, tile_t end) {
    
    int d_hor = 0, d_vert = 0; 

    (start.y < end.y) ? ++d_hor : --d_hor; //horizontal movement
    (start.x < end.x) ? ++d_vert : --d_vert; //vertical movement

    int new_y = start.y + d_hor;
    int new_x = start.x + d_vert; 

    //new square is invalid if:
    //  1. check square is outside bounds of matrix
    //  2. check square is already filled with a different piece
    //otherwise it should be good?
    

    if(new_y < 0 || new_y > BOARD_Y) return false;
    if(new_x < 0 || new_x > BOARD_X) return false;

    if(board[new_x][new_y] != ' ') return false; 

    return true; 
}


vector<vector<tuple<char, int, bool>>> legalMoves(TURN player) {

    //int starting_index_x, starting_index_y, ending_index_x, ending_index_y; 
    //letter, number, forced move boolean
    vector<vector<tuple<char, int, bool>>> moves;

    //first two pieces are team, next two are enemy
    char pieces[4];
    
    //theres probably a better way to implement this
    //player 1
    if (player == COMPUTER) { pieces[0] = '1'; pieces[1] = '3'; pieces[2] = '2'; pieces[3] = '4'; }
    else { pieces[0] = '2'; pieces[1] = '4'; pieces[2] = '1'; pieces[3] = '3'; }
    

    //look through all of the pieces on the board
    for(int i = 0; i < BOARD_X; i++) {
        for(int j = 0; j < BOARD_Y; j++) {
            
            //found a piece for the current player
            //now look at the available moves for the current piece
            if(board[i][j] == pieces[0] || board[i][j] == pieces[1]) {
                
                //get index bounds for each move
                int start_index_x = (i - 1) < 0 ? 0 : i - 1;
                int start_index_y = (j - 1) < 0 ? 0 : j - 1;
                int end_index_x = (i + 1) > (BOARD_Y) ? (BOARD_Y) : i + 1;
                int end_index_y = (j + 1) > (BOARD_X) ? (BOARD_X) : j + 1;

                //if standard piece, don't search for backwards moves
                if(player == COMPUTER && board[i][j] == '1') start_index_x = end_index_x;
                if(player == USER && board[i][j] == '2') end_index_x = start_index_x; 

                
                //find valid moves given the player's piece
                for (int k = start_index_x; k < end_index_x + 1; k++) {
                    for(int l = start_index_y; l < end_index_y + 1; l++) {
                        
                        //doing this is probably a recursive process
                        //
                        //make a function that takes in a current state as input (being the 3x3 grid)
                        //find any tiles around it that are jumpable
                        //add to thing
                        //if already in the thing stop
                        
                        //cout << "\nlegal move is found! from i = " << i << ", j = " << j << ", at x = " << k << " and y = " << l; 
                        //cout << "\nstart x is " << start_index_x << " end x is " << end_index_x << "\n";
                        //cout << "start y is " << start_index_y << " end y is " << end_index_y << "\n";
                        
                        char check = board[k][l]; 

                        //space represents empty black square
                        //any black square seen by a piece (forwards) is a legal move
                        if (check == ' ') {
                            
                            //initialize tile structs
                            tile_t start = {i, j};  
                            tile_t end = {k, l};
                            
                            moves.push_back(createMoveset(start, end)); 
                        }
                        
                        //if upcoming square is owned by an enemy
                        if(check == pieces[2] || check == pieces[3]) {
                            
                        }
                    }
                }
            }
        }
    }

    return moves; 
}



//prints out the legal moves determined in in the getLegalMoves function
void printLegalMoves(TURN player) {

    vector<vector<tuple<char, int, bool>>> moves = legalMoves(player); 
    
    cout << "\nSelect your move: (0-" << moves.size() - 1 << ")\n\n";  

    for(int i = 0; i < moves.size(); i++) {

        cout << i << ". "; 
        
        //get move sequence
        vector<tuple<char, int, bool>> move_sequence = moves[i]; 

        for(int j = 0; j < move_sequence.size(); j++) {
            
            //get tuple in move sequence
            tuple<char, int, bool> square = move_sequence[j];
            
            cout << get<0>(square) << get<1>(square);
            j == move_sequence.size() - 1 ? cout << "\n" : cout << " -> "; 
        }
        //cout << "\n"; 
    }
}



void makeMove(TURN *player) {

    //player number (1 or 2)
    int p_num = *player; 

    cout << "\n\nIt is Player " << p_num << "'s turn!";
    printLegalMoves(*player); 
    
    cout << "\nMove I want is: "; 
    int move = 0; 
    cin >> move; 
    
    //change player after each turn
    p_num == COMPUTER ? *player = USER : *player = COMPUTER; 
}   












