/*

    Name: Ryan Kilkenney
    Date: 4/10/2020
    Purpose: Its the .cc file for the spaces class. It's used to store information about each tile on the board
             

*/
#include <iostream>
#include "spaces.h"
using namespace std;

void spaces::flip(string c){
    if(c == "black") {
        color = "black";
    } else if(c == "white"){
        color = "white";
    }
}

string spaces::get_color()const {
        return color;
}

void spaces::set_color(string c) {
    if(c == "white") {
        color = "white";
    } else if (c == "black") {
        color = "black";
    } else {
        color = "empty";
    }
}

void spaces::display() const {
    if (color == "white") {
        cout << 'O';
    } else if (color == "black") {
        cout << 'X';
    } else if(color == "empty") {
        cout << '-';
    } else {
        cout << '-';
    }
}