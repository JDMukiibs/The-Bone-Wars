//
// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/22/2020.
//


#include "Grid.h"

Grid::Grid(int board_size)
{
    if(board_size > 5)//in the event that values are given we still have to make sure that they are correct.
    {
        rows = board_size;
        columns = board_size;
    }
    else{
        rows = 5;
        columns = 5;
    }
    //first allocate memory for the rows by making an array of pointers that will be our rows.
    //then allocate for each column using a loop.
    G = new char*[rows];
    for(int i=0; i<columns; i++)
        G[i] = new char[columns];
    //And then I'm going to assign all chars in the array to simply 'X' for the sake of the line "X marks the spot".
    //Also X isn't taken as a symbol representation so I can use it do easily differentiate between places that haven't been checked
    //and those that have been checked if no resource was found I'll then switch to 'D' which will mean Discovered. Note to self figure this out later.
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            G[i][j] = 'X';
    }

    //Now need to allocate space for the private members of the Grid.
    G_Resources = new char*[rows];
    for(int i=0; i<columns; i++)
        G_Resources[i] = new char[columns];
    //and then for starters again we can assign it with X's too just like the normal board.
    //deploy_resources will be editing this board and not the board that Archaeologist's have access to.
    for(int i=0; i<rows; i++)
    {
        for(int j=0; j<columns; j++)
            G_Resources[i][j] = 'X';
    }
    bone_count = 3; bone_signal = 0;
    food_count = 3; food_signal = 0;
    water_count = 2; water_signal = 0;
    medical_count = 1; medkit_signal = 0;
    trap_count = 2;//I think the traps shouldn't be revealed to the players for sake of leaving somethings to chance, hence no trigger signal
    bone_score = 0;
}
Grid::~Grid()
{
    for(int i=0; i<rows; i++)
        delete [] G[i];
    delete [] G;
    for(int i=0; i<rows; i++)
        delete [] G_Resources[i];
    delete [] G_Resources;
}
int Grid::getsize() const
{
    return rows;//doesn't matter which one I call since they will be equal.
}
//This randomizer function I've implemented will help me randomize between 8 possible orientations for the rscs that have tile_size as 2.
//1 - Vertical Up
//2 - Vertical Down
//3 - Horizontal Right
//4 - Horizontal Left
//5 - Diagonal Right Up
//6 - Diagonal Right Down
//7 - Diagonal Left Up
//8 - Diagonal Left Down
int Grid::randomizer(int op)
{
    int r,r_index;
    int arr2[3] = {3, 6, 2};//array for case 2
    int arr3[3] = {4, 8, 2};//array for case 3
    int arr4[3] = {1, 5, 3};//array for case 4
    int arr5[3] = {1, 7, 4};//array for case 5
    int arr6[5] = {1, 5, 3, 6, 2};//array for case 6
    int arr7[5] = {1, 7, 4, 8, 2};//array for case 7
    int arr8[5] = {4, 8, 2, 6, 3};//array for case 8
    int arr9[5] = {4, 7, 1, 5, 3};//array for case 9
    switch (op)
    {
        case 1://this is the normal situation where a coordinate is not in any of the corners
            r = 1 + (rand()%8);//random number between 1 and 8 both inclusive of course.
            break;
        case 2://this will refer to the case where a coordinate is in [0][0]
            r_index = rand()%3;//random number between 0 and 2
            r = arr2[r_index];//get the value at the index and that is the orientation to go with
            break;
        case 3://this will refer to the case where a coordinate is in [0][last column]
            r_index = rand()%3;
            r = arr3[r_index];
            break;
        case 4://this will refer to the case where a coordinate is in [last row][0]
            r_index = rand()%3;
            r = arr4[r_index];
            break;
        case 5://this will refer to the case where a coordinate is in [last row][last column]
            r_index = rand()%3;
            r = arr5[r_index];
            break;
        case 6://this will refer to the case where we are in the first column of the board but not at the corners. We are in between the corners
            r_index = rand()%5;
            r = arr6[r_index];
            break;
        case 7://this will refer to the case where we are in the last column of the board but not at the corners. We are in between the corners
            r_index = rand()%5;
            r = arr7[r_index];
            break;
        case 8:
            r_index = rand()%5;
            r = arr8[r_index];
            break;
        case 9:
            r_index = rand()%5;
            r = arr9[r_index];
            break;
        default:
            cout << "Error in randomizer function!!" << endl;
            exit(1);
    }
    return r;
}
bool Grid::range_check(int low, int high, int x)
{
    return (low<=x && x<=high);
}
void Grid::coord_search(int *x, int *y)
{
    int flag;
    do{
        flag = 0;
        for(auto & cord : coordinates_list)
        {
            if(cord.first == *x && cord.second == *y)
            {
                flag = 1;
                *x = 0 + (rand()%(rows-1));
                *y = 0 + (rand()%(columns-1));
                break;
            }
        }
    }while (flag == 1);//we will stay in this do while loop until a fresh set of coordinates not already stored in our vector is found
}
void Grid::orientation_validity(int *ori, int x, int y, int op)
{
    int flag,tx,ty;
    do {
        flag = 0;
        switch (*ori)
        {
            case 1:
                tx = x - 1;
                ty = y;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 2:
                tx = x + 1;
                ty = y;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 3:
                tx = x;
                ty = y + 1;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 4:
                tx = x;
                ty = y - 1;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 5:
                tx = x - 1;
                ty = y + 1;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 6:
                tx = x + 1;
                ty = y + 1;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 7:
                tx = x - 1;
                ty = y - 1;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
            case 8:
                tx = x + 1;
                ty = y - 1;
                if(G_Resources[tx][ty] != 'X')
                    flag = 1;
                break;
        }
        if(flag == 1)
            *ori = randomizer(op);
        //this is why I sent the address so that I can change the orientation if after the "simulation" fails so that another one
        //is tested before we move forward.
    }while(flag==1);
}
int Grid::deploy_bones()
{
    int counter=0;
    int x,y;
    int orientation;//this variable will be used to determine the orientation or choice of deployment for a given resource.
    int option;
    //this last variable will help the randomizer function know which range of numbers to choose a random one from to get our orientation
    //mostly cause sometimes we might get coordinates that are placed in corners and that means not all 8 orientations can be used for a
    //two-tile resource.
    while(counter < bone_count)
    {
        //What I have come to realize is that essentially I might not need to keep track of the Bones as an object on its own so I create
        //when I need to place a resource and once the symbol has been copied onto our Grid for Resources then moving forward all I
        //have to do is match the symbol that is in a certain coordinate location picked hence why I free the memory that was allocated
        //to New_Bone at the end of this loop.
        Bone *New_Bone = new Bone;
        x = 0 + (rand()%(rows-1));
        y = 0 + (rand()%(columns-1));

        //check if our vector is empty this will only be once however since I've decided to deploy Bones first so for the
        //rest of the resources they will be calling my coord_search function to check if coordinates have already been used.
        //then we need to worry about how to place this resource on our Board now for Bone and others as well later on. Some types require
        //two tiles so that's where orientation comes into play and the randomizer function as well. if the tile size is one
        //then it's easy the coordinate we have randomly found is the one we are meant to place it at. So a simple else otherwise
        if(coordinates_list.empty())
        {
            coordinates_list.emplace_back(x,y);
            if(New_Bone->gettile_size()==2)
            {
                if(x==0 && y==0)
                {
                    option = 2;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==0 && y==(columns-1))
                {
                    option = 3;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==(rows-1) && y==0)
                {
                    option = 4;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==(rows-1) && y==(columns-1))
                {
                    option = 5;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(range_check(1,rows-2,x) && y==0)
                {
                    option = 6;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(range_check(1,rows-2,x) && y==(columns-1))
                {
                    option = 7;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==0 && range_check(1,rows-2,y))
                {
                    option = 8;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==(rows-1) && range_check(1,rows-2,y))
                {
                    option = 9;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else
                {
                    option = 1;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                int x1,y1;
                //these two new variables will be used to store the coordinate of the second tile to be taken up by the resource that uses 2 tiles
                //now since this will be the first ever coordinate being changed there will be no errors encountered of coordinates already
                //being occupied by other resources so whatever orientation is got that will be the orientation for that resource.
                switch (orientation)
                {
                    case 1:
                        x1 = x-1;
                        y1 = y;
                        coordinates_list.emplace_back(x1,y1);//we also need to add these coordinates to the vector so we are aware they contain a rsc.
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 2:
                        x1 = x+1;
                        y1 = y;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 3:
                        x1 = x;
                        y1 = y+1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 4:
                        x1 = x;
                        y1 = y-1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 5:
                        x1 = x-1;
                        y1 = y+1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 6:
                        x1 = x+1;
                        y1 = y+1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 7:
                        x1 = x-1;
                        y1 = y-1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 8:
                        x1 = x+1;
                        y1 = y-1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    default:
                        cout << "Failed to give an orientation for Bone Resource!!" << endl;
                        exit(1);
                }
            } else
            {
                G_Resources[x][y] = New_Bone->getsymbol();
            }
        }
        else
        {
            coord_search(&x,&y);//we search to see if the coordinates are new or not coord search will change them for us if they are repeated.
            coordinates_list.emplace_back(x,y);
            if(New_Bone->gettile_size()==2)
            {
                if(x==0 && y==0)
                {
                    option = 2;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==0 && y==(columns-1))
                {
                    option = 3;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==(rows-1) && y==0)
                {
                    option = 4;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                else if(x==(rows-1) && y==(columns-1))
                {
                    option = 5;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                } else
                {
                    option = 1;
                    orientation = randomizer(option);
                    orientation_validity(&orientation, x, y, option);
                }
                int x1,y1;
                //these two new variables will be used to store the coordinate of the second tile to be taken up by the resource that uses 2 tiles
                //now since this will be the first ever coordinate being changed there will be no errors encountered of coordinates already
                //being occupied by other resources so whatever orientation is got that will be the orientation for that resource.
                switch (orientation)
                {
                    case 1:
                        x1 = x-1;
                        y1 = y;
                        coordinates_list.emplace_back(x1,y1);//we also need to add these coordinates to the vector so we are aware they contain a rsc.
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 2:
                        x1 = x+1;
                        y1 = y;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 3:
                        x1 = x;
                        y1 = y+1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 4:
                        x1 = x;
                        y1 = y-1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 5:
                        x1 = x-1;
                        y1 = y+1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 6:
                        x1 = x+1;
                        y1 = y+1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 7:
                        x1 = x-1;
                        y1 = y-1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    case 8:
                        x1 = x+1;
                        y1 = y-1;
                        coordinates_list.emplace_back(x1,y1);
                        G_Resources[x][y] = New_Bone->getsymbol();
                        G_Resources[x1][y1] = New_Bone->getsymbol();
                        break;
                    default:
                        cout << "Failed to give an orientation for Bone Resource!!" << endl;
                        exit(1);
                }
            } else
            {
                G_Resources[x][y] = New_Bone->getsymbol();
            }
        }
        if(New_Bone->getsymbol()=='F')
            bone_score += 100;
        else if(New_Bone->getsymbol()=='S')
            bone_score += 50;
        else
            bone_score += 20;
        delete New_Bone;
        counter++;
    }
    return counter;
}
//deploy food since it share similar needs like Bones such as it has some two-tile items the functions will be similar.
int Grid::deploy_food()
{
    int counter=0;
    int x,y;
    int orientation;//this variable will be used to determine the orientation or choice of deployment for a given resource.
    int option;
    //this last variable will help the randomizer function know which range of numbers to choose a random one from to get our orientation
    //mostly cause sometimes we might get coordinates that are placed in corners and that means not all 8 orientations can be used for a
    //two-tile resource.
    while(counter < food_count)
    {
        //What I have come to realize is that essentially I might not need to keep track of the Bones as an object on its own so I create
        //when I need to place a resource and once the symbol has been copied onto our Grid for Resources then moving forward all I
        //have to do is match the symbol that is in a certain coordinate location picked hence why I free the memory that was allocated
        //to New_Food at the end of this loop.
        Food *New_Food = new Food;
        x = 0 + (rand()%(rows-1));
        y = 0 + (rand()%(columns-1));

        //As I mentioned earlier since I deploy the bones first for the rest of the resources it will always be straight to checking if the
        //randomized coordinates are new or not if they aren't coord search will change them for us if they are repeated.
        coord_search(&x,&y);
        coordinates_list.emplace_back(x,y);
        if(New_Food->gettile_size() == 2)
        {
            if(x==0 && y==0)
            {
                option = 2;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(x==0 && y==(columns-1))
            {
                option = 3;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(x==(rows-1) && y==0)
            {
                option = 4;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(x==(rows-1) && y==(columns-1))
            {
                option = 5;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(range_check(1,rows-2,x) && y==0)
            {
                option = 6;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(range_check(1,rows-2,x) && y==(columns-1))
            {
                option = 7;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(x==0 && range_check(1,rows-2,y))
            {
                option = 8;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else if(x==(rows-1) && range_check(1,rows-2,y))
            {
                option = 9;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            else
            {
                option = 1;
                orientation = randomizer(option);
                orientation_validity(&orientation, x, y, option);
            }
            int x1,y1;
            //these two new variables will be used to store the coordinate of the second tile to be taken up by the resource that uses 2 tiles
            //now since this will be the first ever coordinate being changed there will be no errors encountered of coordinates already
            //being occupied by other resources so whatever orientation is got that will be the orientation for that resource.
            switch (orientation)
            {
                case 1:
                    x1 = x-1;
                    y1 = y;
                    coordinates_list.emplace_back(x1,y1);//we also need to add these coordinates to the vector so we are aware they contain a rsc.
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 2:
                    x1 = x+1;
                    y1 = y;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 3:
                    x1 = x;
                    y1 = y+1;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 4:
                    x1 = x;
                    y1 = y-1;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 5:
                    x1 = x-1;
                    y1 = y+1;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 6:
                    x1 = x+1;
                    y1 = y+1;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 7:
                    x1 = x-1;
                    y1 = y-1;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                case 8:
                    x1 = x+1;
                    y1 = y-1;
                    coordinates_list.emplace_back(x1,y1);
                    G_Resources[x][y] = New_Food->getsymbol();
                    G_Resources[x1][y1] = New_Food->getsymbol();
                    break;
                default:
                    cout << "Failed to give an orientation for Bone Resource!!" << endl;
                    exit(1);
            }
        } else
        {
            G_Resources[x][y] = New_Food->getsymbol();
        }
        delete New_Food;
        counter++;
    }
    return counter;
}
int Grid::deploy_water()
{
    int counter=0;
    int x,y;
    while(counter < water_count)
    {
        auto *New_Water = new Water;
        x = 0 + (rand()%(rows-1));
        y = 0 + (rand()%(columns-1));

        //As I mentioned earlier since I deploy the bones first for the rest of the resources it will always be straight to checking if the
        //randomized coordinates are new or not if they aren't coord search will change them for us if they are repeated.
        coord_search(&x,&y);
        coordinates_list.emplace_back(x,y);
        //Now for the last set of resources their tile sizes are one so there will be no need to call up orientation and the other helper functions
        //we simply just place the resource.
        G_Resources[x][y] = New_Water->getsymbol();
        delete New_Water;
        counter++;
    }
    return counter;
}
int Grid::deploy_medkits()
{
    int counter=0;
    int x,y;
    while(counter < medical_count)
    {
        auto *New_MedKits = new Medical_Supplies;
        x = 0 + (rand()%(rows-1));
        y = 0 + (rand()%(columns-1));
        coord_search(&x,&y);
        coordinates_list.emplace_back(x,y);
        G_Resources[x][y] = New_MedKits->getsymbol();
        delete New_MedKits;
        counter++;
    }
    return counter;
}
int Grid::deploy_traps()
{
    int counter=0;
    int x,y;
    while(counter < trap_count)
    {
        auto *New_Traps = new Trap;
        x = 0 + (rand()%(rows-1));
        y = 0 + (rand()%(columns-1));
        coord_search(&x,&y);
        coordinates_list.emplace_back(x,y);
        G_Resources[x][y] = New_Traps->getsymbol();
        delete New_Traps;
        counter++;
    }
    return counter;
}
void Grid::deploy_resources()
{
    double base_multiplier;
    // this is the constant value I will use to store the floor of n^2/25 so that we can multiply it and find number of resources respectively
    base_multiplier = floor((rows*columns)/25);
    bone_count = 3 * (int)base_multiplier;
    food_count = 3 * (int) base_multiplier;
    water_count = 2 * (int) base_multiplier;
    medical_count = (int) base_multiplier;
    trap_count = 2 * (int) base_multiplier;

    if(deploy_bones()==bone_count)
        cout << "Bones successfully added!!" << endl;
    if(deploy_food()==food_count)
        cout << "The Island now has a wide variety of Food to keep you satisfied during your quest!! If you can find it that is!" << endl;
    if(deploy_water()==water_count)
        cout << "The Island has now also been filled with sources of liquid refreshment!!" << endl;
    if(deploy_medkits()==medical_count)
        cout << "Don't worry Medkits are in supply too!! These kits can stop any trap injury!!" << endl;
    if(deploy_traps()==trap_count)
        cout << "Did someone say traps?! Oops Well I guess this will remind you of MineSweeper ;)" << endl;
    cout << "Resources Have Been All ADDED. Time to... DISCOVER!!\n" << endl;
}
int Grid::getbone_score() const
{
    return bone_score;
}
char Grid::returncoordrsc(int x, int y)
{
    return G_Resources[x][y];
}
void Grid::changegridcharacter(int x, int y)
{
    G[x][y] = 'D';//where D will mean Discovered.
    //We make a change to the grid to show that a position has been Discovered that way players don't end up selecting coordinates again
}
void Grid::trigger_signals(char rsc)
{
    //the conditions have != 1 so if signal has already been changed that means you don't want to change it again.
    if((rsc=='F' || rsc=='S' || rsc=='O') && bone_signal != 1)
    {
        bone_signal = 1;//a bone has been discovered so as per game design specs
        for(int i=0; i<rows; i++)//other bones become visible
        {
            for(int j=0; j<columns; j++)
            {
                //we first check if the normal Grid is still showing an 'X' yet the Resources Grid has a bone if it's true then
                //all tiles on the normal grid that are still having an 'X' yet they are really a bone turn to the resource that
                //they actually contain.
                if(G[i][j] == 'X' && (G_Resources[i][j]=='F' || G_Resources[i][j]=='S' || G_Resources[i][j]=='O'))
                    G[i][j] = G_Resources[i][j];//all the other tiles having bones become visible.
            }
        }
    }
    else if((rsc=='B' || rsc=='N' || rsc=='C') && food_signal != 1)
    {
        food_signal = 1;
        for(int i=0; i<rows; i++)//other bones become visible
        {
            for(int j=0; j<columns; j++)
            {
                if(G[i][j] == 'X' && (G_Resources[i][j]=='B' || G_Resources[i][j]=='N' || G_Resources[i][j]=='C'))
                    G[i][j] = G_Resources[i][j];//all the other tiles having food become visible.
            }
        }
    }
    else if(rsc=='W' && water_signal != 1)
    {
        water_signal = 1;
        for(int i=0; i<rows; i++)//other bones become visible
        {
            for(int j=0; j<columns; j++)
            {
                if(G[i][j] == 'X' && G_Resources[i][j]=='W')
                    G[i][j] = G_Resources[i][j];//all the other tiles having water become visible.
            }
        }
    }
    else if(rsc=='M' && medkit_signal != 1)
    {
        medkit_signal = 1;
        for(int i=0; i<rows; i++)//other bones become visible
        {
            for(int j=0; j<columns; j++)
            {
                if(G[i][j] == 'X' && G_Resources[i][j]=='M')
                    G[i][j] = G_Resources[i][j];//all the other tiles having medkits become visible.
            }
        }
    }
}
ostream& operator<<(ostream& os, const Grid& g)
{
    os << endl;
    for(int i=0; i<g.rows; i++)
    {
        os << "|";
        for(int j=0; j<g.columns; j++)
            os << g.G[i][j] << "|";
        os << endl;
    }
    return os;
}
//helper function to calculate distance between two points because why not it's going to be a method used over and over for this function below
double distance(int x1, int y1, int x2, int y2)
{
    // Calculating distance and getting the absolute value for proper comparison later
    return abs(sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0));
}
//One interesting fact is that this function will purely just be for the two tile resources that are found the other resources
//once the coordinate that contains them is picked we are very okay to move on but for these we need to find their corresponding pair as well.
void Grid::coordinate_search(char rsc, int x, int y)
{
    //These resources are 'F', 'B', and 'N'
    int pos;
    pair<int,int> prev;
    pair<int,int> next;
    double dist1, dist2;
    switch (rsc)
    {
        case 'F':
        {
            pos=0;
            for(auto i=coordinates_list.cbegin(); i<coordinates_list.cend(); i++)
            {
                if(i->first==x && i->second==y)
                    break;
                pos++;//this pos will give us the position of the element before our element
            }
            if(pos == 0)
            {
                //if the coordinate we found is the beginning element of our vector that means the element in the next position is it's pair
                //by matter of the way I implemented. Once I create a two tile resource once it's pivot coordinate is located and added, right
                //after that we add it's partner coordinate. So this case is handled easily, the ones in-between will be hard!
                next = coordinates_list.at(pos + 1);
                picked_coords.emplace_back(next.first,next.second);
                changegridcharacter(next.first,next.second);
                //we then add those coordinates to picked coordinates. Even though they weren't really "picked" but for the game to flow it has to be
                //assumed that way.
            } else
            {
                //this will be the harder part
                prev = coordinates_list.at(pos);
                next = coordinates_list.at(pos + 2);//pos+2 because pos+1 will give us the coordinate pair we already know
                //this first case however is simple because if the next coordinate after ours isn't a two-tile one we are safe that means
                //the player instead found a partner to a pivot coordinate and hence prev will hold the other coordinate we want
                if(G_Resources[next.first][next.second]!= 'F')
                {
                    picked_coords.emplace_back(prev.first,prev.second);
                    changegridcharacter(prev.first,prev.second);
                }
                else if(G_Resources[next.first][next.second]=='F' && G_Resources[prev.first][prev.second]!='F')
                {
                    picked_coords.emplace_back(next.first,next.second);
                    changegridcharacter(next.first,next.second);
                }
                else
                {
                    //if all the above fail that means we are stuck in the middle of >=2 bones that are of tile_size 2
                    //so to choose the correct one we will have to measure the distance between the two points and our current point
                    dist1 = distance(x,y,prev.first,prev.second);
                    dist2 = distance(x,y,next.first,next.second);
                    if(dist1<dist2)
                    {
                        picked_coords.emplace_back(prev.first,prev.second);
                        changegridcharacter(prev.first,prev.second);
                    }
                    else
                    {
                        picked_coords.emplace_back(next.first,next.second);
                        changegridcharacter(next.first,next.second);
                    }
                }
            }
            break;
        }
        case 'B':
        {//follow a similar method like above so same code
            pos=0;
            for(auto i=coordinates_list.cbegin(); i<coordinates_list.cend(); i++)
            {
                if(i->first==x && i->second==y)
                    break;
                pos++;
            }
            if(pos == 0)
            {
                next = coordinates_list.at(pos + 1);
                picked_coords.emplace_back(next.first,next.second);
                changegridcharacter(next.first,next.second);
            } else
            {
                prev = coordinates_list.at(pos);
                next = coordinates_list.at(pos + 2);
                if(G_Resources[next.first][next.second]!= 'B')
                {
                    picked_coords.emplace_back(prev.first,prev.second);
                    changegridcharacter(prev.first,prev.second);
                }
                else if(G_Resources[next.first][next.second]=='B' && G_Resources[prev.first][prev.second]!='B')
                {
                    picked_coords.emplace_back(next.first,next.second);
                    changegridcharacter(next.first,next.second);
                }
                else
                {
                    dist1 = distance(x,y,prev.first,prev.second);
                    dist2 = distance(x,y,next.first,next.second);
                    if(dist1<dist2)
                    {
                        picked_coords.emplace_back(prev.first,prev.second);
                        changegridcharacter(prev.first,prev.second);
                    }
                    else
                    {
                        picked_coords.emplace_back(next.first,next.second);
                        changegridcharacter(next.first,next.second);
                    }
                }
            }
            break;
        }
        case 'N':
        {
            pos=0;
            for(auto i=coordinates_list.cbegin(); i<coordinates_list.cend(); i++)
            {
                if(i->first==x && i->second==y)
                    break;
                pos++;
            }
            if(pos == 0)
            {
                next = coordinates_list.at(pos + 1);
                picked_coords.emplace_back(next.first,next.second);
            } else
            {
                prev = coordinates_list.at(pos);
                next = coordinates_list.at(pos + 2);
                if(G_Resources[next.first][next.second]!= 'N')
                {
                    picked_coords.emplace_back(prev.first,prev.second);
                    changegridcharacter(prev.first,prev.second);
                }
                else if(G_Resources[next.first][next.second]=='N' && G_Resources[prev.first][prev.second]!='N')
                {
                    picked_coords.emplace_back(next.first,next.second);
                    changegridcharacter(next.first,next.second);
                }
                else
                {
                    dist1 = distance(x,y,prev.first,prev.second);
                    dist2 = distance(x,y,next.first,next.second);
                    if(dist1<dist2)
                    {
                        picked_coords.emplace_back(prev.first,prev.second);
                        changegridcharacter(prev.first,prev.second);
                    }
                    else
                    {
                        picked_coords.emplace_back(next.first,next.second);
                        changegridcharacter(next.first,next.second);
                    }
                }
            }
            break;
        }
        default:
            cout << "Appears there's an error trying to find my partner tile!\n" << endl;
            exit(1);
    }
}
