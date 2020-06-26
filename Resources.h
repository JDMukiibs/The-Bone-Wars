//
// Created by JOSHUA DANIEL MUKIIBI 2345825 on 5/21/2020.
//

#ifndef BONE_WARS_RESOURCES_H
#define BONE_WARS_RESOURCES_H

#include <iostream>
#include <vector>
#include <utility>
#include <ctime>
#include <cmath>

using namespace std;

class Resources {
protected:
    int tile_size;
    char symbol;
public:
    explicit Resources(int ts = 0, char symb = 'U');//using an overloaded constructor and my own default values for symbol and tile size
    virtual char getsymbol() = 0;
    virtual int gettile_size() = 0;
    virtual ~Resources();
    //this virtual destructor is just to ensure there are no surprises moving forward and similarly alike the same goes with the sub-classes
};

//BONE SUB-CLASS
class Bone: public Resources{
protected:
    enum class BoneType{FullBody, Skull, Ordinary};
    BoneType _bonetype;
public:
    Bone();
    char getsymbol() override;
    int gettile_size() override;
    ~Bone() override;
};

//FOOD SUB-CLASS
class Food: public Resources{
protected:
    enum class FoodType{Burger, Nuggets, Chips};
    FoodType _foodtype;
public:
    Food();
    char getsymbol() override;
    int gettile_size() override;
    ~Food() override;
};

//WATER SUB-CLASS
class Water: public Resources{
public:
    Water();
    char getsymbol() override;
    int gettile_size() override;
    ~Water() override;
};

//MEDICAL SUPPLIES SUB-CLASS
class Medical_Supplies: public Resources{
public:
    Medical_Supplies();
    char getsymbol() override;
    int gettile_size() override;
    ~Medical_Supplies() override;
};

//TRAP SUB-CLASS
class Trap: public Resources{
public:
    Trap();
    char getsymbol() override;
    int gettile_size() override;
    ~Trap() override;
};

#endif //BONE_WARS_RESOURCES_H
