#include "boardLogic.h"
#include "playerLogic.h"

#include <iostream> 
#include <stack>

//it would have been smart to implement the board as a 4x4 2D array to deal with less math
//then it would have to search less squares
//

/*
bool isAvailable(int i, int j) {
    
    if(board[k][l] == ' ') return true; 
    
    //now check for other stuff
    return false;
}*/

/*
//tile structure
typedef struct tile_s {
    int x; //tile x position
    int y; //tile y position
} tile_t;
*/

//sequence structure
//could make this a vector of tiles? Maybe a linked list?
typedef struct seq_s {
    tile_t start;
    tile_t end;
} seq_t;

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
vector<tuple<tile_t, bool>> createMoveset(tile_t start, tile_t end) {
    
    vector<tuple<tile_t, bool>> sequence; 

    //add starting square to tuple
    tuple<tile_t, bool> start_t = make_tuple(start, false); 
    sequence.push_back(start_t); 

    //put move into tuple -> put tuple into move sequence -> put move sequence into legal moves vector

    tuple<tile_t, bool> end_t = make_tuple(end, false); 
    sequence.push_back(end_t);

    return sequence;    
}


//function that checks if the jump you're trying to make works out
bool checkValidJump(tile_t start, tile_t end, tile_t *result_t) {
    
    int new_y = end.y;
    int new_x = end.x; 

    (start.y < end.y) ? ++new_y : --new_y; //horizontal movement
    (start.x < end.x) ? ++new_x : --new_x; //vertical movement

    //cout << "\ncheck square is " << new_x << " and " << new_y << "\n"; 

    //new square is invalid if:
    //  1. check square is outside bounds of matrix
    //  2. check square is already filled with a different piece
    //otherwise it should be good?
    

    if(new_y < 0 || new_y > BOARD_Y) return false;
    if(new_x < 0 || new_x > BOARD_X) return false;

    if(board[new_x][new_y] != ' ') return false; 

    *result_t = {new_x, new_y};

    return true; 
}

//tile is to tell you resulting tile, bool is to tell you whether or not you're jumping
vector<tuple<tile_t, bool>> findValidMoves(int x, int y, TURN player) {

    //get index bounds for each move
    int start_index_x = (x - 1) < 0 ? 0 : x - 1;
    int start_index_y = (y - 1) < 0 ? 0 : y - 1;
    int end_index_x = (x + 1) > (BOARD_Y) ? (BOARD_Y) : x + 1;
    int end_index_y = (y + 1) > (BOARD_X) ? (BOARD_X) : y + 1;

    //if standard piece, don't search for backwards moves
    if(player == COMPUTER && board[x][y] == '1') start_index_x = end_index_x;
    if(player == USER && board[x][y] == '2') end_index_x = start_index_x; 
    
    //vector to store the tiles you'll end up at if you make a valid move
    vector<tuple<tile_t, bool>> moves = {}; 

    //find valid moves given the player's piece
    for (int k = start_index_x; k < end_index_x + 1; k++) {
        for(int l = start_index_y; l < end_index_y + 1; l++) {

            char check = board[k][l]; 
            tile_t start = {x, y};  
            tile_t end = {k, l};
            tile_t result = {}; 
            
            //if the upcoming space is empty, add it to the potential moves
            if (check == ' ') { 
                
                //signifying end square is destination and you're not making a jump
                tuple<tile_t, bool> m = make_tuple(end, false); 
                moves.push_back(m);
            }
            
            //if the upcoming space is an enemy but is a valid jump, add it to the moveset
            else if(checkValidJump(start, end, &result)) {
                tuple<tile_t, bool> m = make_tuple(result, true);
                moves.push_back(m);
            }
            
            //otherwise we ain't valid chief
            else continue;
            
        }
    }

    return moves; 
}


vector<vector<tuple<tile_t, bool>>> legalMoves(TURN player) {

    //int starting_index_x, starting_index_y, ending_index_x, ending_index_y; 
    //letter, number, forced move boolean
    vector<vector<tuple<tile_t, bool>>> moves;

    //first two pieces are team, next two are enemy
    char pieces[4];
    
    //theres probably a better way to implement this
    //can probably do it with modulus as even pieces are blue & odd are red
    //player 1
    if (player == COMPUTER) { pieces[0] = '1'; pieces[1] = '3'; pieces[2] = '2'; pieces[3] = '4'; }
    else { pieces[0] = '2'; pieces[1] = '4'; pieces[2] = '1'; pieces[3] = '3'; }
    

    //look through all of the pieces on the board
    for(int i = 0; i < BOARD_X; i++) {
        for(int j = 0; j < BOARD_Y; j++) {
            
            //found a piece for the current player
            //now look at the available moves for the current piece
            if(board[i][j] == pieces[0] || board[i][j] == pieces[1]) {
                
                //get valid moves at a specific tile
                vector<tuple<tile_t, bool>> valid_moves = findValidMoves(i, j, player);     
                
                //queue to explore future expansions
                stack<tile_t> frontier; 
            

                for(int m = 0; m < valid_moves.size(); m++) {
                    
                    tuple<tile_t, bool> square = valid_moves[m];
                    
                    cout << "\nvalid jump to: " << (char)(get<0>(square).y + 97) << get<0>(square).x << " jump is " << get<1>(square); 
                }
                
                //add all jump tiles onto a frontier
                for(int k = 0; k < valid_moves.size(); k++) {
                    
                    tuple<tile_t, bool> square = valid_moves[k]; 
                    if(get<1>(square)) frontier.push(get<0>(square)); 
                    else moves.push_back(createMoveset({i, j}, get<0>(square))); 
                }

                
                //now go through all the tiles on the frontier
                vector<tile_t> m; 
                
                do {
                    
                    if(frontier.empty()) break; 

                    //get current tile from the frontier
                    tile_t cur_t = frontier.top();

                    m.push_back(frontier.top()); 
                    frontier.pop(); 

                    valid_moves = findValidMoves(cur_t.x, cur_t.y, player);

                    //add newly jumpable tiles onto the frontier
                    for(int k = 0; k < valid_moves.size(); k++) {
                        if(get<1>(valid_moves[k])) frontier.push(get<0>(valid_moves[k]));
                        m.push_back(get<0>(valid_moves[k]));  
                    }
                    
                    

                }
                while(!frontier.empty()); 
                            
                
                /*
                //resulting tile after jump is made
                tile_t result_t = {};
                bool first = true; 



                
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
                        
                        //cout << "enemy is currently: " << pieces[2] << " and " << pieces[3] << "\n"; 

                        //initialize tile structs
                        char check = board[k][l]; 
                        tile_t start = {i, j};  
                        tile_t end = {k, l};

                        //space represents empty black square
                        //any black square seen by a piece (forwards) is a legal move
                        if (check == ' ') moves.push_back(createMoveset(start, end)); 
                        
                        //if upcoming square is owned by an enemy
                        if(check == pieces[2] || check == pieces[3]) {
                            
                            
                            //resulting tile after jump is made
                            tile_t result_t = {};
                            queue<tile_t> frontier; 
                            bool first = true; 
                            
                            do {
                                if(first) first = false; 
                                else {
                                    start = frontier.pop(); 

                                }

                                if(!checkValidJump(start, end, &result_t)) continue; 
                                frontier.push(result_t);
                            }
                            while(!frontier.empty()); 
                            


                            //if the jump isn't valid, skip this iteration
                            if(!checkValidJump(start, end, &result_t)) continue; 
                            
                            cout << "found enemy tile!" << "\n"; 

                            frontier.push_back(result_t); 

                            for(int m = 0; m < frontier.size(); m++) {
                                
                                cout << "valid jump to: " << (char)(frontier[m].y + 97) << frontier[m].x << "\n"; 
                            }

                            
                        
                    }
                }*/
            }
        }
    }

    return moves; 
}



//prints out the legal moves determined in in the getLegalMoves function
void printLegalMoves(TURN player) {

    vector<vector<tuple<tile_t, bool>>> moves = legalMoves(player); 
    
    cout << "\nSelect your move: (0-" << moves.size() - 1 << ")\n\n";  

    for(int i = 0; i < moves.size(); i++) {

        cout << i << ". "; 
        
        //get move sequence
        vector<tuple<tile_t, bool>> move_sequence = moves[i]; 

        for(int j = 0; j < move_sequence.size(); j++) {
            
            //get tuple in move sequence
            tuple<tile_t, bool> square = move_sequence[j];
            
            cout << (char)(get<0>(square).y + 97) << get<0>(square).x;
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












