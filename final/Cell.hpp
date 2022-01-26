#ifndef __CELL_H__
#define __CELL_H__

# include <iostream>
# include "stdlib.h"
# include "stdio.h"
# include "time.h"

class Cell{
public:

    // Constructor
    Cell();

    // get functions                                
    char getType();
    int getLife();
    int getStep();
    int getAddress();

    // mutate functions
    void mutateType(char newType);
    void mutateLife(int newLife);
    void mutateAddress(int newAddress);
    void mutateStep(int newStep);

    bool GrassExisting = false;
    bool FoodExisting = false;

private:
    char type;
    int life;
    int step;
    int address;


};

#endif