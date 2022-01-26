# include "Cell.hpp"
# include "World.hpp"
# include <iostream>
# include "stdlib.h"
# include "stdio.h"
# include "time.h"

using namespace std;

int main(){
    srand(time(NULL));

    int h; int w;
    int init_num_G; int init_num_R; int init_num_T;

    // get initial information
    cout << "Enter grid height: "; cin >> h;
    cout << "Enter grid width: "; cin >> w; cout << "\n";

    cout << "Enter initial number of grasses: "; cin >> init_num_G;
    cout << "Enter initial number of rabbits: "; cin >> init_num_R;
    cout << "Enter initial number of tigers: "; cin >> init_num_T; cout<< "\n";
    
    // create the World
    World MyWorld(h, w, init_num_G, init_num_R, init_num_T);

    // display the first world
    MyWorld.DisplayWorld();

    while(true){
        // get command
        int command; int direction;
        cout << "Select next command [0: move / 1: shoot]: "; cin >> command;
        cout << "Enter the direction [0: up / 1: down / 2: right / 3: left]: "; cin >> direction;
        // handle Hunter according to the commmand
        if (command == 0){
            MyWorld.Move_H(direction);
        }
        else if(command == 1){
            MyWorld.Shoot_H(direction);
        }

        // check Game Finishing condition
        if (! MyWorld.ContinueGame()){
            break;
        }


        // handle Tiger 
        int cell = 1;
        MyWorld.Finding_T_addresses();
        while(cell <= w * h){
            MyWorld.Handle_T(cell++);
            // check Game Finishing condition after each action
            if (! MyWorld.ContinueGame()){
            break;
            }
        }

        // check Continuing condition 
        if (! MyWorld.ContinueGame()){
            break;
        }


        // handle Rabbits
        cell = 1;
        MyWorld.Finding_R_addresses();
        while(cell <= w * h){
           
            MyWorld.Handle_R(cell++);
            // check Game Finishing condition after each action
            if (! MyWorld.ContinueGame()){
            break;
            }
        }

        if (! MyWorld.ContinueGame()){
            break;
        }        


        // generating grasses
        MyWorld.Generate_G();
        if (! MyWorld.ContinueGame()){
            break;
        } 

        MyWorld.DisplayWorld();
    }

    // the game is finished, then print finishing ments.
    MyWorld.PrintGameFinished();


}

