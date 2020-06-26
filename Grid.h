//
// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/22/2020.
//

#ifndef BONE_WARS_GRID_H
#define BONE_WARS_GRID_H

#include "Resources.h"

//Add a variable that will store the total bonescore to be achieved. it will be calculated as you add the bones into the Grid.

class Grid {
private:
    char **G_Resources;//This second grid is one that will be similar to the main Grid but will have the resources correctly located.
    //And I will later be using it to match against the normal Grid that players can see to identify whether a resource has been located or not.
    int bone_count, water_count, food_count, medical_count, trap_count;
    vector<pair<int, int>> coordinates_list;//coordinates_list will keep track of Coordinates that have been changed to hide resources.
    //User won't or rather shouldn't have access to this information because he has to find it.
protected:
    char **G;//Making a 2D char array because then simply replacing the character in the array with the symbol will be easy.
    int rows, columns;
    int bone_score;
    int bone_signal, food_signal, water_signal, medkit_signal;
public:
    vector<pair<int,int>> picked_coords;//this vector will store all coordinates that have been selected by both players as the game progresses.
    //and for that purpose I have made it a public member variable because each player object should be able to know which coordinates have been used.
public:
    explicit Grid(int);//default size of array should at least be 5x5 so with this overloaded constructor I have declared my defaults too
    ~Grid();//We will need a destructor here to properly deal with freeing up memory used when creating the array.
    int getsize()const;
    void deploy_resources();
    int deploy_bones();//these helper functions will help make the deploy resources function a bit smaller they will carry the heavy load
    int deploy_food();//of actually placing the specific resources in their right places with the help of the other helper functions I've built
    int deploy_water();//deploy resources will just call them all one by one.
    int deploy_medkits();
    int deploy_traps();
    void coord_search(int *, int *);//this function will be used to ensure coordinates aren't repeated when creating resources.
    void orientation_validity(int *, int, int, int);//this function will be used to simulate whether the randomized orientation choice can be used.
    static bool range_check(int, int, int);//Idea essentially borrowed from GeeksforGeeks but either way needed it to check one more case that could happen.
    friend ostream& operator<<(ostream& os, const Grid&);
    static int randomizer(int);
    int getbone_score() const;
    char returncoordrsc(int, int);//this function will return the character being held in the picked location by the Archaeologist
    void changegridcharacter(int, int);//now remember we can't print our Resources grid so we need to keep changing 'X' to the corresponding char
    void coordinate_search(char, int, int);
    void trigger_signals(char);
    friend double distance(int, int, int, int);
};


#endif //BONE_WARS_GRID_H
