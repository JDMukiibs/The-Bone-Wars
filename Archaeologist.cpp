//
// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/26/2020.
//

#include "Archaeologist.h"

Archaeologist::Archaeologist(Grid *g, const char* str, int energy)
{
    name = new char[50];
    strcpy(name,str);
    bone_score = 0;
    game_board = g;//this is a pointer to the board that way every Archaeologist object created is created pointing to the same board.
    energy_bar = energy;//random number between n and 2n is energy where n is boardsize it'll be calculated in the main.
    condition = 'H'; //starting condition will be 'H' to signify healthy. If the player is injured their condition will be 'I'.
}
Archaeologist::~Archaeologist()
{
    delete [] name;
}

//this function as I said checks to ensure players don't repeat coordinates. When it is confirmed that the coordinates are valid it adds them
//to the vector of picked coordinates. I send the address of the pair so I can change the values within here by asking the player to enter
//a different set of coordinates.
void coordinate_validity(vector<pair<int, int>>& pc, pair<int, int>& coord)
{
    int flag;
    if(pc.empty())
        pc.emplace_back(coord.first,coord.second);
    else
    {
        do {
            flag = 0;
            for(auto & point : pc)
            {
                if(point.first==coord.first && point.second==coord.second)
                {
                    flag = 1;
                    cout << "\n\nThis coordinate has already been marked D for Discovered! Check the grid again and then\nPlease select another coordinate: ";
                    cin >> coord.first; cin >> coord.second;
                    break;
                }
            }
        }while (flag==1);
        pc.emplace_back(coord.first,coord.second);
    }
}
bool Archaeologist::coord_search(int x, int y)
{
    for(auto coord : game_board->picked_coords)
    {
        if(coord.first==x && coord.second==y)
            return false;//It will return false because that means the user can't take the resource from this coordinate because it's already been
            //taken from
    }
    return true;
}
void Archaeologist::effect_calculator(int dice_effect, int x, int y)
{
    char rsc;
    if(dice_effect==6)
    {
        cout << "\nBINGO!! Let's hope you actually scored!" << endl;
        if(x==0 && y==0)
        {
            if(coord_search(x+1,y))
            {
                rsc = game_board->returncoordrsc(x+1,y);
                if(rsc=='T')//If the resource is a trap in the neighbour we are just ignoring it but deactivating it as well hence change it to D
                {
                    game_board->picked_coords.emplace_back(x+1,y);
                    game_board->changegridcharacter(x+1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y);
                    game_board->picked_coords.emplace_back(x+1,y);
                }
            }
            if(coord_search(x+1,y+1))
            {
                rsc = game_board->returncoordrsc(x+1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y+1);
                    game_board->changegridcharacter(x+1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y+1);
                    game_board->picked_coords.emplace_back(x+1,y+1);
                }
            }
            if(coord_search(x,y+1))
            {
                rsc = game_board->returncoordrsc(x,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y+1);
                    game_board->changegridcharacter(x,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y+1);
                    game_board->picked_coords.emplace_back(x,y+1);
                }
            }
        }
        else if(x==(game_board->getsize()-1) && y==(game_board->getsize()-1))
        {
            if(coord_search(x-1,y))
            {
                rsc = game_board->returncoordrsc(x-1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y);
                    game_board->changegridcharacter(x-1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y);
                    game_board->picked_coords.emplace_back(x-1,y);
                }
            }
            if(coord_search(x-1,y-1))
            {
                rsc = game_board->returncoordrsc(x-1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y-1);
                    game_board->changegridcharacter(x-1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y-1);
                    game_board->picked_coords.emplace_back(x-1,y-1);
                }
            }
            if(coord_search(x,y-1))
            {
                rsc = game_board->returncoordrsc(x,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y-1);
                    game_board->changegridcharacter(x,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y-1);
                    game_board->picked_coords.emplace_back(x,y-1);
                }
            }
        }
        else if(x==(game_board->getsize()-1) && y==0)
        {
            if(coord_search(x-1,y))
            {
                rsc = game_board->returncoordrsc(x-1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y);
                    game_board->changegridcharacter(x-1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y);
                    game_board->picked_coords.emplace_back(x-1,y);
                }
            }
            if(coord_search(x-1,y+1))
            {
                rsc = game_board->returncoordrsc(x-1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y+1);
                    game_board->changegridcharacter(x-1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y+1);
                    game_board->picked_coords.emplace_back(x-1,y+1);
                }
            }
            if(coord_search(x,y+1))
            {
                rsc = game_board->returncoordrsc(x,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y+1);
                    game_board->changegridcharacter(x,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y+1);
                    game_board->picked_coords.emplace_back(x,y+1);
                }
            }
        }
        else if(x==0 && y==(game_board->getsize()-1))
        {
            if(coord_search(x+1,y))
            {
                rsc = game_board->returncoordrsc(x+1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y);
                    game_board->changegridcharacter(x+1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y);
                    game_board->picked_coords.emplace_back(x+1,y);
                }
            }
            if(coord_search(x+1,y-1))
            {
                rsc = game_board->returncoordrsc(x+1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y-1);
                    game_board->changegridcharacter(x+1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y-1);
                    game_board->picked_coords.emplace_back(x+1,y-1);
                }
            }
            if(coord_search(x,y-1))
            {
                rsc = game_board->returncoordrsc(x,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y-1);
                    game_board->changegridcharacter(x,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y-1);
                    game_board->picked_coords.emplace_back(x,y-1);
                }
            }
        }
        else if(Grid::range_check(1,game_board->getsize()-2,x) && y==0)
        {
            if(coord_search(x+1,y))
            {
                rsc = game_board->returncoordrsc(x+1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y);
                    game_board->changegridcharacter(x+1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y);
                    game_board->picked_coords.emplace_back(x+1,y);
                }
            }
            if(coord_search(x+1,y+1))
            {
                rsc = game_board->returncoordrsc(x+1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y+1);
                    game_board->changegridcharacter(x+1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y+1);
                    game_board->picked_coords.emplace_back(x+1,y+1);
                }
            }
            if(coord_search(x-1,y))
            {
                rsc = game_board->returncoordrsc(x-1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y);
                    game_board->changegridcharacter(x-1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y);
                    game_board->picked_coords.emplace_back(x-1,y);
                }
            }
            if(coord_search(x-1,y+1))
            {
                rsc = game_board->returncoordrsc(x-1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y+1);
                    game_board->changegridcharacter(x-1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y+1);
                    game_board->picked_coords.emplace_back(x-1,y+1);
                }
            }
            if(coord_search(x,y+1))
            {
                rsc = game_board->returncoordrsc(x,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y+1);
                    game_board->changegridcharacter(x,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y+1);
                    game_board->picked_coords.emplace_back(x,y+1);
                }
            }
        }
        else if(Grid::range_check(1,game_board->getsize()-2,x) && y==(game_board->getsize()-1))
        {
            if(coord_search(x-1,y))
            {
                rsc = game_board->returncoordrsc(x-1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y);
                    game_board->changegridcharacter(x-1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y);
                    game_board->picked_coords.emplace_back(x-1,y);
                }
            }
            if(coord_search(x-1,y-1))
            {
                rsc = game_board->returncoordrsc(x-1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y-1);
                    game_board->changegridcharacter(x-1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y-1);
                    game_board->picked_coords.emplace_back(x-1,y-1);
                }
            }
            if(coord_search(x+1,y))
            {
                rsc = game_board->returncoordrsc(x+1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y);
                    game_board->changegridcharacter(x+1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y);
                    game_board->picked_coords.emplace_back(x+1,y);
                }
            }
            if(coord_search(x+1,y-1))
            {
                rsc = game_board->returncoordrsc(x+1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y-1);
                    game_board->changegridcharacter(x+1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y-1);
                    game_board->picked_coords.emplace_back(x+1,y-1);
                }
            }
            if(coord_search(x,y-1))
            {
                rsc = game_board->returncoordrsc(x,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y-1);
                    game_board->changegridcharacter(x,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y-1);
                    game_board->picked_coords.emplace_back(x,y-1);
                }
            }
        }
        else if(x==0 && Grid::range_check(1,game_board->getsize()-2,y))
        {
            if(coord_search(x+1,y))
            {
                rsc = game_board->returncoordrsc(x+1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y);
                    game_board->changegridcharacter(x+1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y);
                    game_board->picked_coords.emplace_back(x+1,y);
                }
            }
            if(coord_search(x+1,y+1))
            {
                rsc = game_board->returncoordrsc(x+1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y+1);
                    game_board->changegridcharacter(x+1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y+1);
                    game_board->picked_coords.emplace_back(x+1,y+1);
                }
            }
            if(coord_search(x,y+1))
            {
                rsc = game_board->returncoordrsc(x,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y+1);
                    game_board->changegridcharacter(x,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y+1);
                    game_board->picked_coords.emplace_back(x,y+1);
                }
            }
            if(coord_search(x+1,y-1))
            {
                rsc = game_board->returncoordrsc(x+1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y-1);
                    game_board->changegridcharacter(x+1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y-1);
                    game_board->picked_coords.emplace_back(x+1,y-1);
                }
            }
            if(coord_search(x,y-1))
            {
                rsc = game_board->returncoordrsc(x,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y-1);
                    game_board->changegridcharacter(x,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y-1);
                    game_board->picked_coords.emplace_back(x,y-1);
                }
            }
        }
        else if(x==(game_board->getsize()-1) && Grid::range_check(1,game_board->getsize()-2,y))
        {
            if(coord_search(x-1,y))
            {
                rsc = game_board->returncoordrsc(x-1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y);
                    game_board->changegridcharacter(x-1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y);
                    game_board->picked_coords.emplace_back(x-1,y);
                }
            }
            if(coord_search(x-1,y-1))
            {
                rsc = game_board->returncoordrsc(x-1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y-1);
                    game_board->changegridcharacter(x-1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y-1);
                    game_board->picked_coords.emplace_back(x-1,y-1);
                }
            }
            if(coord_search(x,y-1))
            {
                rsc = game_board->returncoordrsc(x,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y-1);
                    game_board->changegridcharacter(x,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y-1);
                    game_board->picked_coords.emplace_back(x,y-1);
                }
            }
            if(coord_search(x-1,y+1))
            {
                rsc = game_board->returncoordrsc(x-1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y+1);
                    game_board->changegridcharacter(x-1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y+1);
                    game_board->picked_coords.emplace_back(x-1,y+1);
                }
            }
            if(coord_search(x,y+1))
            {
                rsc = game_board->returncoordrsc(x,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y+1);
                    game_board->changegridcharacter(x,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y+1);
                    game_board->picked_coords.emplace_back(x,y+1);
                }
            }
        }
        else
        {
            if(coord_search(x+1,y))
            {
                rsc = game_board->returncoordrsc(x+1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y);
                    game_board->changegridcharacter(x+1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y);
                    game_board->picked_coords.emplace_back(x+1,y);
                }
            }
            if(coord_search(x+1,y+1))
            {
                rsc = game_board->returncoordrsc(x+1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y+1);
                    game_board->changegridcharacter(x+1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y+1);
                    game_board->picked_coords.emplace_back(x+1,y+1);
                }
            }
            if(coord_search(x,y+1))
            {
                rsc = game_board->returncoordrsc(x,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y+1);
                    game_board->changegridcharacter(x,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y+1);
                    game_board->picked_coords.emplace_back(x,y+1);
                }
            }
            if(coord_search(x-1,y))
            {
                rsc = game_board->returncoordrsc(x-1,y);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y);
                    game_board->changegridcharacter(x-1,y);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y);
                    game_board->picked_coords.emplace_back(x-1,y);
                }
            }
            if(coord_search(x-1,y-1))
            {
                rsc = game_board->returncoordrsc(x-1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y-1);
                    game_board->changegridcharacter(x-1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y-1);
                    game_board->picked_coords.emplace_back(x-1,y-1);
                }
            }
            if(coord_search(x,y-1))
            {
                rsc = game_board->returncoordrsc(x,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x,y-1);
                    game_board->changegridcharacter(x,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x,y-1);
                    game_board->picked_coords.emplace_back(x,y-1);
                }
            }
            if(coord_search(x+1,y-1))
            {
                rsc = game_board->returncoordrsc(x+1,y-1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x+1,y-1);
                    game_board->changegridcharacter(x+1,y-1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x+1,y-1);
                    game_board->picked_coords.emplace_back(x+1,y-1);
                }
            }
            if(coord_search(x-1,y+1))
            {
                rsc = game_board->returncoordrsc(x-1,y+1);
                if(rsc=='T')
                {
                    game_board->picked_coords.emplace_back(x-1,y+1);
                    game_board->changegridcharacter(x-1,y+1);
                }
                else
                {
                    resources.emplace_back(rsc);
                    game_board->changegridcharacter(x-1,y+1);
                    game_board->picked_coords.emplace_back(x-1,y+1);
                }
            }
        }
    }
    else if(dice_effect==1)
    {
        if(game_board->returncoordrsc(x,y)=='T')
        {
            cout << "\nTrap effect nullified!! You've been saved" << endl;
            resources.pop_back();//My implementation has a vector of resources storing all sorts of resources so since this will be calculated
            //right after the item has been added if the player gets this effect and the trap effect is nullified I just simply remove it from
            //his resource bag because I use the same resource bag later to calculate his condition so if this was the trap that would have hurt him
            //it's no longer there.
        } else
            cout << "Well I guess if it were a trap you'd be happier you rolled a " << dice_effect << endl;
    } else
        cout << "\nSad! You rolled a " << dice_effect << ". No special effects!" << endl;
}
void Archaeologist::energy_calculator()
{
    for(auto & resource : resources)
    {
        if(resource == 'B')
            energy_bar += 4;
        else if(resource == 'N')
            energy_bar += 3;
        else if(resource == 'C')
            energy_bar += 2;
        else if(resource == 'W')
            energy_bar += 1;
        else if(resource == 'T')
            energy_bar -= 0.25;
        else if(resource == 'M')
            energy_bar += 0.25;//I guess if it nullifies it simply adds back the 0.25 you lose.
    }
    //we need to also check for the special energy boost case
    int count=0;
    for(auto & resource : resources)
    {
        if(resource == 'B')
        {
            count++;
            break;
        }
    }
    for(auto & resource : resources)
    {
        if(resource == 'N')
        {
            count++;
            break;
        }
    }
    for(auto & resource : resources)
    {
        if(resource == 'C')
        {
            count++;
            break;
        }
    }
    if(count==3)
    {
        cout << "It appears you are quite the health freak!!\nBut Don't Worry WE Reward you with +10 energy! Go and Win" << endl;
        energy_bar += 10;
    } else
        cout << "\nWell there's no other special effect for you!!\nTry get all three types of food to unlock an Energy boost" << endl;
}
//Now notice I use this function in the Archaeologist and then will have to call on the function in Grid that matches the coordinate to our
//private board that knows the location of the resources
void Archaeologist::play_turn()
{
    char rsc;
    pair<int, int> selection;
    cout << "\nEnter a pair of coordinates (separated by a space e.g: '2 3'): ";
    cin >> selection.first; cin >> selection.second;

    coordinate_validity(game_board->picked_coords,selection);

    rsc = game_board->returncoordrsc(selection.first,selection.second);

    if(rsc == 'X')//In this case there is nothing to add to the players' resource vector.
    {
        cout << "Unlucky mate!! You just discovered more land instead!!\nTry harder the next round!!" << endl;
        game_board->changegridcharacter(selection.first,selection.second);
    }
    else
    {
        //now again with the way I've implemented there will be need for another helper function more so for the case where a resource that spans more
        //than two tiles is found. I need to make sure that it's partner is located too. And, that coordinate as well is updated in our coordinates
        //That function has been created in the Grid class.
        if(rsc == 'F')
        {
            cout << "A FULL BODY!! What will you name this Full Body of Bones you just found?\nTyrannosaurus Rex is already taken!!" << endl;
            game_board->coordinate_search(rsc,selection.first,selection.second);
            bone_score += 100;
        }
        else if(rsc == 'S')
        {
            cout << "A SKULL! I wonder what predator ate this poor fellow and left his skull so far from his body." << endl;
            bone_score += 50;
        }
        else if(rsc == 'O')
        {
            cout << "Well this is very ORDINARY! But at least you have another bone to your collection!!" << endl;
            bone_score += 20;
        }
        else if(rsc == 'B')
        {
            cout << "See I told you there was food. Here's a BURGER to carry with you for your journey!! There might be more!" << endl;
            game_board->coordinate_search(rsc,selection.first,selection.second);
        }
        else if(rsc == 'N')
        {
            cout << "Ah NUGGETS! Very delicious but not quite as filling as a BURGER! Try and find some if you're in need of energy!" << endl;
            game_board->coordinate_search(rsc,selection.first,selection.second);
        }
        else if(rsc == 'C')
        {
            cout << "Hopefully you aren't on your last bit of energy! But here's some CHIPS. Game's not over yet!" << endl;
        }
        else if(rsc == 'W')
        {
            cout << "Did you know that 70% of the Human Brain is WATER. Well, you just found some more! That should quench some thirst!" << endl;
        }
        else if(rsc == 'M')
        {
            cout << "Yes you wanted the option to be able to heal from traps. Here is a MEDKIT!!" << endl;
        }
        else if(rsc == 'T')
        {
            cout << "Oh come on " << name << ", why did you have to go and find a trap! Beware there are more than one!!" << endl;
        }
        resources.emplace_back(rsc);
        game_board->changegridcharacter(selection.first,selection.second);
        game_board->trigger_signals(rsc);
    }
    int dice_effect = 1 + (rand()%6);
    effect_calculator(dice_effect,selection.first,selection.second);
    setcondition();
}

int Archaeologist::getbone_score() const
{
    return bone_score;
}
double Archaeologist::getenergy() const
{
    return energy_bar;
}
void Archaeologist::getcondition()
{
    if(condition == 'H')
        cout << name << ", you're still healthy!" << endl;
    else
        cout << name << ", I'd recommend you discover some MEDKITS soon!" << endl;
}
void Archaeologist::setcondition()
{
    int flag;
    cout << "Current Condition: ";
    for(char resource : resources)
    {
        if(resource == 'M')//if the Archaeologist has a medkit in his resource vector then traps landed on current or future won't affect him
        {
            flag = 1;
            break;
        }
        if(resource == 'T')
            flag = 0;
    }
    if(flag==0)
    {
        cout << name << ", you're going to be losing 0.25 units of energy every round!!" << endl;
        condition = 'I';
    } else
    {
        if(flag==1)
            cout << "That MEDKIT is saving you from a lot of current and possible future pain!!" << endl;
        else
            cout << "It appears you're quite lucky! No MEDKITS and surviving the island!!" << endl;

        condition = 'H';
    }
}
char * Archaeologist::getname() const
{
    return name;
}