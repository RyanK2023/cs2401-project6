/*

    Name: Ryan Kilkenney
    Date: 4/10/2020
    Purpose: Its the .cc file for the Othello class. It's used to create the board and update spaces on the board. Pretty sure that 
    I rewrote half of game.cc without meaning too lol
             

*/
#include <iostream>
#include "game.h"
#include "Othello.h"
#include "colors.h"

using namespace std;

main_savitch_14::game::who Othello::last_mover( ) const {
    return (move_num % 2 == 1 ? HUMAN : COMPUTER);
}

void Othello::compute_moves(queue<string>& moves)const {   
   for(char col = 'A'; col < 'I'; col++) {
       for (char row = '1'; row <= '8'; row++) {
           string tmp = "";
           tmp += row;
           tmp += col;
           if(is_legal(tmp)) {
               moves.push(tmp);
           }
       }
   }
}

int Othello::evaluate( )const {
    int white = 0;

    for (int i = 0; i < 8; i++){
        for(int j = 0; j < 8; j++) {
            if (board[i][j].get_color() == "white") {
                if(board[0][0].get_color() == "white") {
                    white = white + 10;
                } else if(board[0][8].get_color() == "white") {
                    white = white + 10;
                } else if(board[8][0].get_color() == "white") {
                    white = white + 10; 
                } else {
                    white++;
                }
            } 
        }
    }

    return white;
}

main_savitch_14::game* Othello::clone()const { 
   return new Othello(*this);
}

void Othello::display_status( ) const {
    
    //used to draw the board
    cout << "    A    B    C    D    E    F    G    H" << endl;
    cout << "   --------------------------------------" << endl;
    for(int i = 0; i < 8; i++) {
        cout << i+1 << " ";
        for (int j = 0; j < 8; j++) {
                cout << "| ";
                board[i][j].display();
                cout << " |";
        }
        cout << endl;
        cout << "   --------------------------------------" << endl;
    }
}

void Othello::restart( ) {
    //used to populate the board with empty spaces
    for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
                board[i][j].set_color("empty");
        }
    }
    board[3][3].set_color("white");
    board[3][4].set_color("black");
    board[4][3].set_color("black");
    board[4][4].set_color("white");
}

void Othello::make_move(const string& move) {
    string color = " ";
    if(move_num == 0 || (move_num % 2 == 0)) {
        color = "black";
    } else if(move_num % 2 != 0) {
        color = "white";
    }
    char letter = ' ';
    char num = ' ';

    letter = move.at(1);
    letter = toupper(letter);
    num = move.at(0);

    int let = 0;
    int n = 0;

    let = letter - 65;
    n = num - '0';
    n = n - 1;

    board[n][let].flip(color);

    if(check_all(color)) {
        if(look_left(color, n, let, move_num)) {
            flip_left(color, n, let, move_num);
        }
        
        if(look_top(color, n, let, move_num)) {
            flip_top(color, n, let, move_num);
        }
    
        if(look_right(color, n, let, move_num)) {
            flip_right(color, n, let, move_num);
        }

        if(look_bottom(color, n, let, move_num)) {
            flip_bottom(color, n, let, move_num);
        }
        
        if(look_topleft(color, n, let, move_num)) {
            flip_topleft(color, n, let, move_num);
        }

        if(look_topright(color, n, let, move_num)) {
            flip_topright(color, n, let, move_num);
        }

        if(look_bottomright(color, n, let, move_num)) {
            flip_bottomright(color, n, let, move_num);
        }

        if(look_bottomleft(color, n, let, move_num)) {
            flip_bottomleft(color, n, let, move_num);
        }
    }
    move_num++;
    
}



bool Othello::is_game_over( )const {
    return move_num >= 60;
}

void Othello::get_winner() const{
    int whitep;
    int blackp;

    for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
            if(board[i][j].get_color() == "white"){
                whitep++;
            } else {
                blackp++;
            }
        }
    }

    if(whitep > blackp) {
        cout << "White wins!" << endl;
    } else if(blackp > whitep) {
        cout << "Black wins" << endl;
    } else {
        cout << "It's a tie!" << endl;
    }
}

bool Othello::check_all(string color) const {
    for(int n = 1; n <= 8; n++) {
        for(int let = 1; let <= 8; let++) {
            if(look_left(color, n, let, move_num)) {
                return true;
            }

            if(look_top(color, n, let, move_num)) {
                return true;
            }

            if(look_right(color, n, let, move_num)) {
                return true;
            }

            if(look_bottom(color, n, let, move_num)) {
                return true;
            }
            
            if(look_topleft(color, n, let, move_num)) {
               return true;
            }

            if(look_topright(color, n, let, move_num)) {
                return true;
            }

            if(look_bottomright(color, n, let, move_num)) {
                return true;
            }

            if(look_bottomleft(color, n, let, move_num)) {
                return true;
            }
            
        }
    }
    return false;
}

bool Othello::is_legal(const string& move)const {
    string color = " ";
    if(move_num == 0 || (move_num % 2 == 0)) {
        color = "black";
    } else if(move_num % 2 != 0) {
        color = "white";
    }
    
    if(move == "quit") {
        exit(0);
    } else if (is_game_over()){
        get_winner();
        exit(0);
    }

    char letter = ' ';
    char num = ' ';

    letter = move.at(1);
    letter = toupper(letter);
    num = move.at(0);

    int let = 0;
    int n = 0;

    let = letter - 65;
    n = num - '0';

    n = n - 1;
    if((let >= 65 || let <= 72) && (n >= 0 && n <= 7)) {
       if(check_all(color)) {

           if(look_left(color, n, let, move_num)) {
                return true;
            }

            if(look_top(color, n, let, move_num)) {
                return true;
            }

            if(look_right(color, n, let, move_num)) {
                return true;
            }

            if(look_bottom(color, n, let, move_num)) {
                return true;
            }

            if(look_topleft(color, n, let, move_num)) {
               return true;
            }

            if(look_topright(color, n, let, move_num)) {
                return true;
            }

            if(look_bottomright(color, n, let, move_num)) {
                return true;
            }

            if(look_bottomleft(color, n, let, move_num)) {
                return true;
            }
       } else {
           //used to pass
           look_left(color, 9, 9,move_num);
       }
        
    } 
    
    return false;
    
}

bool Othello::look_left(string color, int n, int let, int move) const{
    
    if(n == 9 && let == 9) {
        return true;
    }

    if(let == 0) {
        return false;
    }

    if(move == 0 || (move % 2 == 0)) {
        if((board[n][let - 1].get_color() == "empty") || let == 0) {
            return false;
        }

        if(color == "black" && board[n][let - 1].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n][let - 1].get_color() == "white") {
            return look_left("white", n , let - 1, move_num);
        }

        if(color == "white" && board[n][let - 1].get_color() == "black") {
            return true;
        }
        if(color == "white" && board[n][let - 1].get_color() == "white") {
            return look_left("white", n , let - 1, move_num);
        }
    } else if(move % 2 != 0) {
        if((board[n][let - 1].get_color() == "empty") || let == 0) {
            return false;
        }

        if(color == "white" && board[n][let - 1].get_color() == "white") {
            return false;
        }

        if(color == "white" && board[n][let - 1].get_color() == "black") {
            return look_left("black", n , let - 1, move_num);
        }

        if(color == "black" && board[n][let - 1].get_color() == "black") {
            return look_left("black", n , let - 1, move_num);
        }

        if(color == "black" && board[n][let - 1].get_color() == "white") {
            return true;
        }
    } 
    return false;
}

void Othello::flip_left(string color, int n, int let, int move) {
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n][let - 1].get_color() == "empty") || let == 1) {
                return;
            }

            if(color == "black" && board[n][let - 1].get_color() == "black") {
                return;
            }

            if(color == "black" && board[n][let - 1].get_color() == "white") {
                flip_left("white", n , let - 1, move_num);
                board[n][let-1].flip("black");
            }

            if(color == "white" && board[n][let - 1].get_color() == "black") {
                
                return;
            }
            if(color == "white" && board[n][let - 1].get_color() == "white") {
                
                flip_left("white", n , let - 1, move_num);
                board[n][let-1].flip("black");
            }

    } else if(move % 2 != 0) {
        if((board[n][let - 1].get_color() == "empty") || let == 1) {
                return;
            }

            if(color == "white" && board[n][let - 1].get_color() == "white") {
                return;
            }

            if(color == "white" && board[n][let - 1].get_color() == "black") {
                flip_left("black", n , let - 1, move_num);
                board[n][let-1].flip("white");
            }

            if(color == "black" && board[n][let - 1].get_color() == "black") {
                flip_left("black", n , let - 1, move_num);
                board[n][let-1].flip("white");
            }

            if(color == "black" && board[n][let - 1].get_color() == "white") {
                return;
            }
    }
    
}

bool Othello::look_top(string color, int n, int let, int move) const {
    
    if(n == 0) {
        return false;
    }

    if(move == 0 || (move % 2 == 0)) {
        if((board[n-1][let].get_color() == "empty") || (n == 0)) {
                return false;
            }

        if(color == "black" && board[n-1][let].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n-1][let].get_color() == "white") {
            return look_top("white", n-1, let, move_num);
        }

        if(color == "white" && board[n-1][let].get_color() == "black") {
            return true;
        }
        
        if(color == "white" && board[n-1][let].get_color() == "white") {
            return look_top("white", n-1, let, move_num);
        }
    } else if(move % 2 != 0) {
        if((board[n-1][let].get_color() == "empty") || n == 0) {
                return false;
            }

            if(color == "white" && board[n-1][let].get_color() == "white") {
                return false;
            }

            if(color == "white" && board[n-1][let].get_color() == "black") {
                return look_top("black", n-1, let, move_num);
            }

            if(color == "black" && board[n-1][let].get_color() == "white") {
                return true;
            }

            if(color == "black" && board[n-1][let].get_color() == "black") {
                return look_top("black", n-1, let, move_num);
            }
    } 
    return false;
}

void Othello::flip_top(string color, int n, int let, int move) {
    
    if(move_num == 0 || (move_num % 2 == 0)) {
        if((board[n-1][let].get_color() == "empty") || n == 1) {
                return;
            }

            if(color == "black" && board[n-1][let].get_color() == "black") {
                return;
            }

            if(color == "black" && board[n-1][let].get_color() == "white") {
                flip_top("white", n-1, let, move_num);
                board[n-1][let].flip("black");
            }

            if(color == "white" && board[n-1][let].get_color() == "black") {
                return;
            }

            if(color == "white" && board[n-1][let].get_color() == "white") {
                flip_top("white", n-1, let, move_num);
                board[n-1][let].flip("black");
            }
    } else if(move_num % 2 != 0) {
        if((board[n-1][let].get_color() == "empty") || n == 1) {
                return;
            }

            if(color == "white" && board[n-1][let].get_color() == "white") {
                return;
            }

            if(color == "white" && board[n-1][let].get_color() == "black") {
                flip_top("black", n-1, let, move_num);
                board[n-1][let].flip("white");
            }

            if(color == "black" && board[n-1][let].get_color() == "white") {
                return;
            }

            if(color == "black" && board[n-1][let].get_color() == "black") {
                flip_top("black", n-1, let, move_num);
                board[n-1][let].flip("white");
            }
    }
    
}

bool Othello::look_right(string color, int n, int let, int move) const {
    
    if(let == 7) {
        return false;
    }

    if(move == 0 || (move % 2 == 0)) {
        if((board[n][let + 1].get_color() == "empty") || let == 7) {
                return false;
            }

        if(color == "black" && board[n][let + 1].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n][let + 1].get_color() == "white") {
            return look_right("white", n , let + 1, move_num);
        }

        if(color == "white" && board[n][let + 1].get_color() == "black") {
            return true;
        }
        if(color == "white" && board[n][let+1].get_color() == "white") {
            return look_right("white", n, let+1, move_num);
        }
    } else if(move % 2 != 0) {
        if((board[n][let + 1].get_color() == "empty") || let == 7) {
                return false;
            }

            if(color == "white" && board[n][let + 1].get_color() == "white") {
                return false;
            }

            if(color == "white" && board[n][let + 1].get_color() == "black") {
                return look_right("black", n , let + 1, move_num);
            }

            if(color == "black" && board[n][let + 1].get_color() == "white") {
                return true;
            }

            if(color == "black" && board[n][let+1].get_color() == "black") {
                return look_right("black", n, let+1, move_num);
            }
        }
        return false;
}
    
void Othello::flip_right(string color, int n, int let, int move) {
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n][let + 1].get_color() == "empty") || let == 8) {
            return;
        }

        if(color == "black" && board[n][let + 1].get_color() == "black") {
            return;
        }

        if(color == "black" && board[n][let + 1].get_color() == "white") {
            flip_right("white", n , let + 1, move_num);
            board[n][let+1].flip("black");
        }

        if(color == "white" && board[n][let + 1].get_color() == "black") {
            return;
        }
        if(color == "white" && board[n][let+1].get_color() == "white") {
                flip_right("white", n, let+1, move_num);
                board[n][let+1].flip("black");
        }

    } else if(move % 2 != 0) {
        if((board[n][let + 1].get_color() == "empty") || let == 8) {
            return;
        }

        if(color == "white" && board[n][let + 1].get_color() == "white") {
            return;
        }

        if(color == "white" && board[n][let + 1].get_color() == "black") {
            flip_right("black", n , let + 1, move_num);
            board[n][let+1].flip("white");
        }

        if(color == "black" && board[n][let + 1].get_color() == "white") {
            return;
        }
        if(color == "black" && board[n][let+1].get_color() == "black") {
                flip_right("black", n, let+1, move_num);
                board[n][let+1].flip("white");
        }
    }
    
}

bool Othello::look_bottom(string color, int n, int let, int move) const {
    
    if(n == 7) {
        return false;
    }

    if(move == 0 || (move % 2 == 0)) {
        if((board[n+1][let].get_color() == "empty") || n == 7) {
            return false;
        }

        if(color == "black" && board[n+1][let].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n+1][let].get_color() == "white") {
            return look_bottom("white", n+1, let, move_num);
        }

        if(color == "white" && board[n+1][let].get_color() == "black") {
            return true;
        }
        
        if(color == "white" && board[n+1][let].get_color() == "white") {
            return look_bottom("white", n+1, let, move_num);
        }
    } else if(move_num % 2 != 0) {
        if((board[n+1][let].get_color() == "empty") || n == 7) {
            return false;
        }

        if(color == "white" && board[n+1][let].get_color() == "white") {
            return false;
        }

        if(color == "white" && board[n+1][let].get_color() == "black") {
            return look_bottom("black", n+1, let, move_num);
        }

        if(color == "black" && board[n+1][let].get_color() == "white") {
            return true;
        }

        if(color == "black" && board[n+1][let].get_color() == "black") {
            return look_bottom("black", n+1, let, move_num);
        }
    }
    return false;
    
}

void Othello::flip_bottom(string color, int n, int let, int move) {
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n+1][let].get_color() == "empty") || n == 8) {
            return;
        }

        if(color == "black" && board[n+1][let].get_color() == "black") {
            return;
        }

        if(color == "black" && board[n+1][let].get_color() == "white") {
            flip_bottom("white", n+1, let, move_num);
            board[n+1][let].flip("black");
        }

        if(color == "white" && board[n+1][let].get_color() == "black") {
            return;
        }
        
        if(color == "white" && board[n+1][let].get_color() == "white") {
                flip_bottom("white", n+1, let, move_num);
                board[n+1][let].flip("black");
        }
    } else if(move % 2 != 0) {
        if((board[n+1][let].get_color() == "empty") || n == 8) {
            return;
        }

        if(color == "white" && board[n+1][let].get_color() == "white") {
            return;
        }

        if(color == "white" && board[n+1][let].get_color() == "black") {
            flip_bottom("black", n+1, let, move_num);
            board[n+1][let].flip("white");
        }

        if(color == "black" && board[n+1][let].get_color() == "white") {
            return;
        }
        if(color == "black" && board[n+1][let].get_color() == "black") {
                flip_bottom("black", n+1, let, move_num);
                board[n+1][let].flip("white");
        }
    }
    
}





bool Othello::look_topleft(string color, int n, int let, int move) const {
    
    if(n == 0 || let == 0) {
        return false;
    }
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n-1][let-1].get_color() == "empty") || let == 0) {
            return false;
        }

        if(color == "black" && board[n-1][let-1].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n-1][let - 1].get_color() == "white") {
            return look_topleft("white", n-1 , let - 1, move_num);
        }

        if(color == "white" && board[n-1][let - 1].get_color() == "black") {
            return true;
        }
        if(color == "white" && board[n-1][let - 1].get_color() == "white") {
            return look_topleft("white", n-1 , let - 1, move_num);
        }
    } else if(move % 2 != 0) {
        if((board[n-1][let - 1].get_color() == "empty") || let == 0) {
            return false;
        }

        if(color == "white" && board[n-1][let - 1].get_color() == "white") {
            return false;
        }

        if(color == "white" && board[n-1][let - 1].get_color() == "black") {
            return look_topleft("black", n -1, let - 1, move_num);
        }

        if(color == "black" && board[n-1][let - 1].get_color() == "black") {
            return look_topleft("black", n-1, let - 1, move_num);
        }

        if(color == "black" && board[n-1][let - 1].get_color() == "white") {
            return true;
        }
    } 
    return false;
}

void Othello::flip_topleft(string color, int n, int let, int move) {
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n-1][let - 1].get_color() == "empty") || let == 1) {
                
                return;
            }

            if(color == "black" && board[n-1][let - 1].get_color() == "black") {
                
                return;
            }

            if(color == "black" && board[n-1][let - 1].get_color() == "white") {
                
                flip_topleft("white", n-1, let - 1, move_num);
                board[n-1][let-1].flip("black");
            }

            if(color == "white" && board[n-1][let - 1].get_color() == "black") {
                
                return;
            }
            if(color == "white" && board[n-1][let - 1].get_color() == "white") {
                
                flip_topleft("white", n-1, let - 1, move_num);
                board[n-1][let-1].flip("black");
            }

    } else if(move % 2 != 0) {
        if((board[n-1][let - 1].get_color() == "empty") || let == 1) {
                return;
            }

            if(color == "white" && board[n-1][let - 1].get_color() == "white") {
                return;
            }

            if(color == "white" && board[n-1][let - 1].get_color() == "black") {
                flip_topleft("black", n-1, let - 1, move_num);
                board[n-1][let-1].flip("white");
            }

            if(color == "black" && board[n-1][let - 1].get_color() == "black") {
                flip_topleft("black", n-1, let - 1, move_num);
                board[n-1][let-1].flip("white");
            }

            if(color == "black" && board[n-1][let - 1].get_color() == "white") {
                return;
            }
    }
    
}
    
bool Othello::look_topright(string color, int n, int let, int move) const {
    
    if(n == 0 || let == 0) {
        return false;
    }
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n-1][let + 1].get_color() == "empty") || let == 0) {
            return false;
        }

        if(color == "black" && board[n-1][let + 1].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n-1][let + 1].get_color() == "white") {
            return look_topright("white", n-1 , let + 1, move_num);
        }

        if(color == "white" && board[n-1][let + 1].get_color() == "black") {
            return true;
        }
        if(color == "white" && board[n-1][let + 1].get_color() == "white") {
            return look_topright("white", n-1 , let + 1, move_num);
        }
    } else if(move % 2 != 0) {
        if((board[n-1][let + 1].get_color() == "empty") || let == 0) {
            return false;
        }

        if(color == "white" && board[n-1][let + 1].get_color() == "white") {
            return false;
        }

        if(color == "white" && board[n-1][let + 1].get_color() == "black") {
            return look_topright("black", n -1, let + 1, move_num);
        }

        if(color == "black" && board[n-1][let+1].get_color() == "black") {
            return look_topright("black", n-1, let + 1, move_num);
        }

        if(color == "black" && board[n-1][let+1].get_color() == "white") {
            return true;
        }
    } 
    return false;
}

void Othello::flip_topright(string color, int n, int let, int move) {
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n-1][let + 1].get_color() == "empty") || let == 1) {
                return;
            }

            if(color == "black" && board[n-1][let + 1].get_color() == "black") {
                return;
            }

            if(color == "black" && board[n-1][let + 1].get_color() == "white") {
                flip_topright("white", n-1, let + 1, move_num);
                board[n-1][let+1].flip("black");
            }

            if(color == "white" && board[n-1][let + 1].get_color() == "black") {
                return;
            }
            if(color == "white" && board[n-1][let + 1].get_color() == "white") {
                flip_topright("white", n-1, let + 1, move_num);
                board[n-1][let+1].flip("black");
            }

    } else if(move % 2 != 0) {
        if((board[n-1][let + 1].get_color() == "empty") || let == 1) {
                return;
            }

            if(color == "white" && board[n-1][let + 1].get_color() == "white") {
                return;
            }

            if(color == "white" && board[n-1][let + 1].get_color() == "black") {
                flip_topright("black", n-1, let + 1, move_num);
                board[n][let-1].flip("white");
            }

            if(color == "black" && board[n-1][let + 1].get_color() == "black") {
                flip_topright("black", n-1, let + 1, move_num);
                board[n-1][let+1].flip("white");
            }

            if(color == "black" && board[n-1][let + 1].get_color() == "white") {
                return;
            }
    }
    
}

bool Othello::look_bottomright(string color, int n, int let, int move) const {
    
    if(n == 7 || let == 7) {
        return false;
    }
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n+1][let+1].get_color() == "empty") || n == 7) {
            return false;
        }

        if(color == "black" && board[n+1][let+1].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n+1][let+1].get_color() == "white") {
            return look_bottomright("white", n+1, let+1, move_num);
        }

        if(color == "white" && board[n+1][let+1].get_color() == "black") {
            return true;
        }
        
        if(color == "white" && board[n+1][let+1].get_color() == "white") {
            return look_bottomright("white", n+1, let+1, move_num);
        }
    } else if(move_num % 2 != 0) {
        if((board[n+1][let+1].get_color() == "empty") || n == 7) {
            return false;
        }

        if(color == "white" && board[n+1][let+1].get_color() == "white") {
            return false;
        }

        if(color == "white" && board[n+1][let+1].get_color() == "black") {
            return look_bottomright("black", n+1, let+1, move_num);
        }

        if(color == "black" && board[n+1][let+1].get_color() == "white") {
            return true;
        }

        if(color == "black" && board[n+1][let+1].get_color() == "black") {
            return look_bottomright("black", n+1, let+1, move_num);
        }
    }
    return false;
}

void Othello::flip_bottomright(string color, int n, int let, int move) {

    if(move == 0 || (move % 2 == 0)) {
        if((board[n+1][let+1].get_color() == "empty") || n == 8) {
            return;
        }

        if(color == "black" && board[n+1][let+1].get_color() == "black") {
            return;
        }

        if(color == "black" && board[n+1][let+1].get_color() == "white") {
            flip_bottomright("white", n+1, let+1, move_num);
            board[n+1][let+1].flip("black");
        }

        if(color == "white" && board[n+1][let+1].get_color() == "black") {
            return;
        }
        
        if(color == "white" && board[n+1][let+1].get_color() == "white") {
                flip_bottomright("white", n+1, let+1, move_num);
                board[n+1][let+1].flip("black");
        }
    } else if(move % 2 != 0) {
        if((board[n+1][let+1].get_color() == "empty") || n == 8) {
            return;
        }

        if(color == "white" && board[n+1][let+1].get_color() == "white") {
            return;
        }

        if(color == "white" && board[n+1][let+1].get_color() == "black") {
            flip_bottomright("black", n+1, let+1, move_num);
            board[n+1][let].flip("white");
        }

        if(color == "black" && board[n+1][let+1].get_color() == "white") {
            return;
        }
        if(color == "black" && board[n+1][let+1].get_color() == "black") {
                flip_bottomright("black", n+1, let+1, move_num);
                board[n+1][let+1].flip("white");
        }
    }
}

bool Othello::look_bottomleft(string color, int n, int let, int move) const {
    
    if(n == 7 || let == 7) {
        return false;
    }
    
    if(move == 0 || (move % 2 == 0)) {
        if((board[n+1][let-1].get_color() == "empty") || n == 7) {
            return false;
        }

        if(color == "black" && board[n+1][let-1].get_color() == "black") {
            return false;
        }

        if(color == "black" && board[n+1][let-1].get_color() == "white") {
            return look_bottomleft("white", n+1, let-1, move_num);
        }

        if(color == "white" && board[n+1][let-1].get_color() == "black") {
            return true;
        }
        
        if(color == "white" && board[n+1][let-1].get_color() == "white") {
            return look_bottomleft("white", n+1, let-1, move_num);
        }
    } else if(move_num % 2 != 0) {
        if((board[n+1][let-1].get_color() == "empty") || n == 8) {
            return false;
        }

        if(color == "white" && board[n+1][let-1].get_color() == "white") {
            return false;
        }

        if(color == "white" && board[n+1][let-1].get_color() == "black") {
            return look_bottomleft("black", n+1, let-1, move_num);
        }

        if(color == "black" && board[n+1][let-1].get_color() == "white") {
            return true;
        }

        if(color == "black" && board[n+1][let-1].get_color() == "black") {
            return look_bottomleft("black", n+1, let-1, move_num);
        }
    }
    return false;
}

void Othello::flip_bottomleft(string color, int n, int let, int move) {

    if(move == 0 || (move % 2 == 0)) {
        if((board[n+1][let-1].get_color() == "empty") || n == 8) {
            return;
        }

        if(color == "black" && board[n+1][let-1].get_color() == "black") {
            return;
        }

        if(color == "black" && board[n+1][let-1].get_color() == "white") {
            flip_bottomleft("white", n+1, let-1, move_num);
            board[n+1][let-1].flip("black");
        }

        if(color == "white" && board[n+1][let-1].get_color() == "black") {
            return;
        }
        
        if(color == "white" && board[n+1][let-1].get_color() == "white") {
                flip_bottomleft("white", n+1, let-1, move_num);
                board[n+1][let-1].flip("black");
        }
    } else if(move % 2 != 0) {
        if((board[n+1][let-1].get_color() == "empty") || n == 8) {
            return;
        }

        if(color == "white" && board[n+1][let-1].get_color() == "white") {
            return;
        }

        if(color == "white" && board[n+1][let-1].get_color() == "black") {
            flip_bottomleft("black", n+1, let-1, move_num);
            board[n+1][let].flip("white");
        }

        if(color == "black" && board[n+1][let-1].get_color() == "white") {
            return;
        }
        if(color == "black" && board[n+1][let-1].get_color() == "black") {
                flip_bottomleft("black", n+1, let-1, move_num);
                board[n+1][let-1].flip("white");
        }
    }
}