# include "Cell.hpp"

Cell::Cell()
{
    // initialize to empty cell
    type = 'E'; life = 0; step = 0; address = 0;    
}

char Cell::getType(){return type;}
int Cell::getLife(){return life;}
int Cell::getStep(){return step;}
int Cell::getAddress(){return address;}

void Cell::mutateType(char newType){type = newType;}
void Cell::mutateLife(int newLife){life = newLife;}
void Cell::mutateAddress(int newAddress){address = newAddress;}
void Cell::mutateStep(int newStep){step = newStep;}

