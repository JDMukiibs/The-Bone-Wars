//
// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/26/2020.
//

#ifndef BONE_WARS_ARCHAEOLOGIST_H
#define BONE_WARS_ARCHAEOLOGIST_H

#include "Grid.h"
#include <cstring>

class Archaeologist {
protected:
    char* name;
    int bone_score;
    double energy_bar;
    char condition;
    vector<char> resources;
    Grid* game_board;
public:
    Archaeologist(Grid *, const char *, int);
    ~Archaeologist();
    bool coord_search(int, int);
    void effect_calculator(int,int,int);
    void energy_calculator();//calculate current energy of player based off resources in vector.
    void play_turn();
    int getbone_score()const;
    double getenergy()const;
    char* getname()const;
    void getcondition();
    void setcondition();//this function will be used to change the condition of the player whenever it is needed to change it
    friend void coordinate_validity(vector<pair<int, int>>&, pair<int, int>&);//it will check if coordinates have already been used or not.
};


#endif //BONE_WARS_ARCHAEOLOGIST_H
