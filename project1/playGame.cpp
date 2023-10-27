#include <fstream> 
#include <iostream> 
#include <string>
#include <algorithm> 

#include "boardLogic.h"
#include "playerLogic.h"

using namespace std; 
 

void loadBoard(ifstream &lb) {
    
    string line = "";
    int line_counter = 0; 
    while(!lb.eof()) {
        
        //get content of line from file, if line is empty quit the loop
        getline(lb, line);
        if(line.empty()) continue;
        
        //remove spaces from line
        line.erase(remove(line.begin(), line.end(), ' '), line.end()); 
        
        /* if the file is formatted properly, there are four characters per line
         * on a board. Additionally, there are 8 lines. Final two lines are 
         * player turn and time limit respectively. */

        if(line_counter < 8) {
            for(int i = 0; i < line.length() - 1; i++) {
                //set every other character on board = character at line
                board[line_counter][(i * 2) + (line_counter % 2)] = (line[i] == 48 ? 32 : line[i]);
            }
        }
        line_counter++; 
    }
}


void initialActions() {

    char input, buffer_gc; 
    do {
        cout << "Would you like to load a game from a file? (Y/N): "; 
        input = getchar();
        buffer_gc = getchar();
        fflush(stdout);
    } while (input != 'Y' && input != 'N');

    if(input == 'Y') {
        
        //initialze board with spaces
        initializeBoard(false);

        string filename;
        cout << "file name to load: "; 
        cin >> filename; 

        ifstream b(filename);
        loadBoard(b); 
    }
    else {

        //initialze board in standard starting position
        initializeBoard(true); 
    }

}


int main() {
    
    bool gameOver = false;

    //set player to be player 1
    TURN player = COMPUTER; 

    //initialize board with all zeros
    initialActions(); 
    
    while(!gameOver) {
        printBoard(); 
        makeMove(&player);        
    }

    return 0; 
}
