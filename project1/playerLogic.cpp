#include "boardLogic.h"
#include "playerLogic.h"

#include <iostream> 

//it would have been smart to implement the board as a 4x4 2D array to deal with less math
//then it would have to search less squares
vector<vector<tuple<char, int, bool>>> legalMoves(TURN player) {

    //int starting_index_x, starting_index_y, ending_index_x, ending_index_y; 
    //letter, number, forced move boolean
    vector<vector<tuple<char, int, bool>>> moves;


    for(int i = 0; i < BOARD_X; i++) {
        for(int j = 0; j < BOARD_Y; j++) {

            if(board[i][j] == player) {
                
                bool legal_move_found = false;  
                vector<vector<int>> legal_squares;
                vector<tuple<char, int, bool>> move_sequence; 

                //get starting index bounds for each move
                int start_index_x = (i - 1) < 0 ? 0 : i - 1;
                int start_index_y = (j - 1) < 0 ? 0 : j - 1;
                int end_index_x = (i + 1) > (BOARD_X - 1) ? (BOARD_X - 1) : i + 1;
                int end_index_y = (j + 1) > (BOARD_Y - 1) ? (BOARD_Y - 1) : j + 1;
                
                //find valid moves given the player's piece
                for (int k = start_index_x; k < end_index_x; k++) {
                    for(int l = start_index_y; l < end_index_y; l++) {
                        
                        if (board[k][l] == '!') {
                            legal_squares.push_back({k, l});
                            legal_move_found = true; 
                        }
                    }
                }

                //add starting square to the start of the move sequence
                if(legal_move_found) {
                    tuple<char, int, bool> start = make_tuple(char(j) + 97, i, false); 
                    move_sequence.push_back(start); 
                }

                //put move into tuple -> put tuple into move sequence -> put move sequence into legal moves vector
                for(int k = 0; k < legal_squares.size() - 1; k++) {
                    
                    vector<int> square_v = legal_squares[k];
                    char letter = (char)square_v[1] + 97; //convert int (0-7) to char (a-h) 
                    int number = square_v[0]; 
                    
                    tuple<char, int, bool> square_t = make_tuple(letter, number, false); 

                    move_sequence.push_back(square_t);
                }
                moves.push_back(move_sequence); 
            }

        }
    }

    return moves; 
}



//prints out the legal moves determined in in the getLegalMoves function
void printLegalMoves(TURN player) {

    vector<vector<tuple<char, int, bool>>> moves = legalMoves(player); 
    
    cout << "\nSelect your move: (0-" << moves.size() << ")\n\n";  

    for(int i = 0; i < moves.size() - 1; i++) {

        cout << i << ". "; 
        
        //get move sequence
        vector<tuple<char, int, bool>> move_sequence = moves[i]; 

        for(int j = 0; j < move_sequence.size() - 1; j++) {
            
            //get tuple in move sequence
            tuple<char, int, bool> square = move_sequence[j];
            
            cout << get<0>(square) << get<1>(square) << " -> ";
        }
        cout << "\n"; 
    }
}



void makeMove(TURN *player) {

    //player number (1 or 2)
    int p_num = *player; 

    cout << "\n\nIt is Player " << p_num << "'s turn!";
    printLegalMoves(*player); 
}   












