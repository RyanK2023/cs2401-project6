/*

    Name: Ryan Kilkenney
    Date: 4/10/2020
    Purpose: Its the .h file for the spaces class. It's used to store information about each tile on the board
            

*/

#include <iostream>

using namespace std;

class spaces {

    public:
    spaces() { color = "empty";}
    void flip(string c);
    string get_color() const;
    void set_color(string c);
    void display() const;

    private:
    string color;
    

};