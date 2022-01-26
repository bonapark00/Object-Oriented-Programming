#ifndef __WORLD_H__
#define __WORLD_H__

# include <iostream>
# include "stdlib.h"
# include "stdio.h"
# include "time.h"
# include "Cell.hpp"
using namespace std;

class World{
public:

    // constructor
    World(int w_val, int h_val, int numG, int numR, int numT);

    // display function
    void DisplayWorld();

    // create new character        
    void Create_T(int ad); 
    void Create_R(int ad); 
    void Create_G(int ad); 
    void Create_F(int ad); 

    // functions for handling character
    void Shoot_H(int dir); 
    void Move_H(int dir); 
    void Finding_T_addresses();
    void Finding_R_addresses();
    void Handle_T(int ad);
    void Handle_R(int ad);
    void Generate_G();   
    void Deleting(int ad); 

    // functions etc
    bool IsDestinationOutOfWorld(int address, int dir); 
    char InvestigateNeighbor(int address, int dir); 
    int DestinationAddress(int address, int dir); 
    int FindNearestAnimal(int dir); 
    bool ContinueGame(); 
    void PrintGameFinished(); 
    bool isEmptyCell(int ad); 
    void AddToLst(int ad, int* &lst, int& lst_size); 
    void DelFromLst(int ad, int* &lst, int& lst_size); 

    ~World();

private:
    int w; int h;
    int num_G; int num_R; int num_T;
    int num_Full;
    int num_Empty;

    Cell* AllLives;

    int* lst_empty; int* lst_full;
    int* lst_T_existence; int* lst_R_existence;

    int H_TimeStep; int H_Life; int H_Address;
    bool Is_H_Alive = true;

};

#endif