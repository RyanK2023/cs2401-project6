/*

    Name: Ryan Kilkenney
    Date: 4/10/2020
    Purpose: Its the .h file for the Othello class. It's used to create the board and update spaces on the board 
            

*/
#include<iostream>
#include"game.h"
#include"spaces.h"

using namespace std;

class Othello : public main_savitch_14::game {

    public:
    Othello() {move_num = 0;}
    game* clone()const;
    void compute_moves(queue<string>& moves)const;
    void display_status( ) const;
    int evaluate( )const;
    bool is_game_over( )const;
    bool is_legal(const string& move)const;
    void restart( );
    void make_move(const string& move);
    bool check_all(string color) const;
    void get_winner() const;
    who last_mover( ) const; 
    
    bool look_left(string color, int n, int let, int move) const;
    void flip_left(string color, int n, int let, int move);
    
    bool look_top(string color, int n, int let, int move) const;
    void flip_top(string color, int n, int let, int move);

    bool look_right(string color, int n, int let, int move) const;
    void flip_right(string color, int n, int let, int move);

    bool look_bottom(string color, int n, int let, int move) const;
    void flip_bottom(string color, int n, int let, int move);

    bool look_topleft(string color, int n, int let, int move) const;
    void flip_topleft(string color, int n, int let, int move);
    
    bool look_topright(string color, int n, int let, int move) const;
    void flip_topright(string color, int n, int let, int move);

    bool look_bottomright(string color, int n, int let, int move) const;
    void flip_bottomright(string color, int n, int let, int move);

    bool look_bottomleft(string color, int n, int let, int move) const;
    void flip_bottomleft(string color, int n, int let, int move);


    private:
    spaces board[8][8];
    int move_num;

};