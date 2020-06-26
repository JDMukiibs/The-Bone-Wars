//
// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/21/2020.
//

#include "Resources.h"

Resources::Resources(int ts, char symb)
{
    tile_size = ts;
    symbol = symb;
}
Resources::~Resources() noexcept {}

//BONE SUB-CLASS IMPLEMENTATION
Bone::Bone()
{
    int r = 1 + (rand()%3);
    switch (r)
    {
        case 1:
            _bonetype = BoneType::FullBody;
            tile_size = 2;
            symbol = 'F';
            break;
        case 2:
            _bonetype = BoneType::Skull;
            tile_size = 1;
            symbol = 'S';
            break;
        case 3:
            _bonetype = BoneType::Ordinary;
            tile_size = 1;
            symbol = 'O';
            break;
        default:
            cout << "Error creating Bones for Archaeologists!! Are the Bone Wars a lie?!" << endl;
            exit(1);
    }
}
char Bone::getsymbol()
{
    return symbol;
}
int Bone::gettile_size()
{
    return tile_size;
}

Bone::~Bone() noexcept {}

//FOOD SUB-CLASS IMPLEMENTATION
Food::Food()
{
    int r = 1 + (rand()%3);
    switch (r)
    {
        case 1:
            _foodtype = FoodType::Burger;
            tile_size = 2;
            symbol = 'B';
            break;
        case 2:
            _foodtype = FoodType::Nuggets;
            tile_size = 2;
            symbol = 'N';
            break;
        case 3:
            _foodtype = FoodType::Chips;
            tile_size = 1;
            symbol = 'C';
            break;
        default:
            cout << "Error creating Food for Archaeologists!! They are going to starve!!" << endl;
            exit(1);
    }
}
int Food::gettile_size()
{
    return tile_size;
}
char Food::getsymbol()
{
    return symbol;
}

Food::~Food() noexcept {}

//WATER SUB-CLASS IMPLEMENTATION
Water::Water()
{
    tile_size = 1;
    symbol = 'W';
}
char Water::getsymbol()
{
    return symbol;
}
int Water::gettile_size()
{
    return tile_size;
}
Water::~Water() noexcept {}

//MEDICAL SUPPLIES SUB-CLASS IMPLEMENTATION
Medical_Supplies::Medical_Supplies()
{
    tile_size = 1;
    symbol = 'M';
}
char Medical_Supplies::getsymbol()
{
    return symbol;
}
int Medical_Supplies::gettile_size()
{
    return tile_size;
}
Medical_Supplies::~Medical_Supplies() noexcept {}

//TRAP SUB-CLASS IMPLEMENTATION
Trap::Trap()
{
    tile_size = 1;
    symbol = 'T';
}
char Trap::getsymbol()
{
    return symbol;
}
int Trap::gettile_size()
{
    return tile_size;
}
Trap::~Trap() noexcept {}