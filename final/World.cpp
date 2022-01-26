# include "World.hpp"
# include <iostream>


World::World(int w_val, int h_val, int numG, int numR, int numT)
{
    // constructor
    // initialize private members
    w = w_val; h = h_val; num_G = numG; num_T = numT; num_R = numR;
    H_TimeStep = 1; H_Life = 7; 
    num_Full = 0; num_Empty = w*h;
    lst_T_existence = new int[w*h]; lst_R_existence = new int[w*h]; lst_empty = new int[w*h]; lst_full = NULL;

    // initialize the world
    AllLives = new Cell[w * h + 1];

    // lst_empty contains addresses where addresses are not assigned.
    for(int i=0; i< w*h; i++){
        lst_empty[i] = i+1;
        AllLives[i+1].mutateAddress(i+1); // register address
    }


    // locate all lives randomly
    // locate Tigers
    int new_Address;
    for(int i=0; i< num_T; i++){

        new_Address = lst_empty[rand()%(num_Empty-1)];

        Create_T(new_Address);           

        DelFromLst(new_Address, lst_empty, num_Empty);
        AddToLst(new_Address, lst_full, num_Full);

    }
    // create Rabbits
    for(int i=0; i< num_R; i++){

        new_Address = lst_empty[rand()%(num_Empty-1)];

        Create_R(new_Address);
      
        AddToLst(new_Address, lst_full, num_Full);
        DelFromLst(new_Address, lst_empty, num_Empty);

    }
    // create Grasses
    for(int i=0; i< num_G; i++){
        new_Address = lst_empty[rand()%(num_Empty-1)];

        Create_G(new_Address);
      
        AddToLst(new_Address, lst_full, num_Full);
        DelFromLst(new_Address, lst_empty, num_Empty);
    }


    // create Hunter
    new_Address = lst_empty[rand()%(num_Empty-1)];
    H_Life = 7; 
    H_Address = new_Address;
    AllLives[new_Address].mutateType('H');
    AllLives[new_Address].mutateLife(7);
    AllLives[new_Address].mutateStep(1);
    AddToLst(new_Address, lst_full, num_Full);
    DelFromLst(new_Address, lst_empty, num_Empty);

}

void World::DisplayWorld()
{
    // Display the world
    cout << "\n==================================================\n\n";
    cout << "Time Step: " << H_TimeStep << "\t\t" 
         << "Life: " << H_Life << endl;

    for(int i=1; i<= w*h; i++){
        if(AllLives[i].getType() == 'R' || AllLives[i].getType() == 'T' || AllLives[i].getType() == 'H'){
            cout << AllLives[i].getType() << " ";
        }

        else if(AllLives[i].GrassExisting){
            cout << "* ";
        }
        else if(AllLives[i].FoodExisting){
            cout << "F ";
        }
        else{
            cout << "- ";
        }
        // line change
        if(i % w == 0){
            cout << endl;
        }
    }
    cout << endl;

}

void World::Create_T(int ad)
{
    // create new tiger to the given address
    AllLives[ad].mutateType('T');
    AllLives[ad].mutateLife(7);
    AllLives[ad].mutateAddress(ad);
    AllLives[ad].mutateStep(1);

}


void World::Create_R(int ad)
{
    // create new Rabbit to the given address
    AllLives[ad].mutateType('R');
    AllLives[ad].mutateLife(5);
    AllLives[ad].mutateAddress(ad);
    AllLives[ad].mutateStep(1);
}

void World::Create_G(int ad)
{
    // create new grass to the given address
    AllLives[ad].GrassExisting = true;
    AllLives[ad].mutateAddress(ad);
}

void World::Create_F(int ad)
{
    // create new Food to the given address
    AllLives[ad].FoodExisting = true;
    AllLives[ad].mutateAddress(ad);

}

void World::Shoot_H(int dir){
    // Implement the hunter's shooting

    // get the nearest animal's address in that direction
    int AddressTargetAnimal = FindNearestAnimal(dir);
    if(AddressTargetAnimal == -1){
        H_TimeStep++; H_Life--; // if no animal near, nothing happens
        return; 
    }

    else{   // do shoot

        if(AllLives[AddressTargetAnimal].getType() == 'T'){
            num_T --;
        }
        else if(AllLives[AddressTargetAnimal].getType() == 'R'){
            num_R--;
        }

        AllLives[AddressTargetAnimal].mutateType('F'); // animal becomes food.
        AllLives[AddressTargetAnimal].FoodExisting = true;
        AllLives[AddressTargetAnimal].GrassExisting = false;
        H_TimeStep++;
        H_Life--;
        return;
    }

}



void World::Move_H(int dir)
{
    // implement Hunter's movement

    // get the type of destination cell's type
    char destination_type = InvestigateNeighbor(H_Address, dir);
    int destination_address = DestinationAddress(H_Address, dir);

    // cannot move
    if(destination_type == 'B' || destination_type == 'T' || destination_type == 'R'){
        H_TimeStep++; H_Life--;
        return; // cannot go there 
    }
    else{
        // eat Food and move
        if(AllLives[destination_address].FoodExisting){
            H_Life = 7;
            Deleting(H_Address);
            H_Address = destination_address;
            AllLives[destination_address].mutateType('H');
            AllLives[destination_address].mutateLife(7);
            AllLives[destination_address].mutateStep(++H_TimeStep);
            AllLives[destination_address].FoodExisting = false;
        }

        // moving without eating
        else{
            Deleting(H_Address);
            H_Address = destination_address;
            AllLives[destination_address].mutateType('H');
            AllLives[destination_address].mutateLife(--H_Life);
            AllLives[destination_address].mutateStep(++H_TimeStep);           
        }
        
    }

}

void World::Finding_T_addresses(){
    // lst_T_existence stores the information of T existence
    // 1 element means Tiger exists in that cell with address (index + 1)
    // 0 element means Tiger doesn't exist in that cell.
    for(int i=0; i<w*h; i++){
        if(AllLives[i+1].getType() == 'T'){
            lst_T_existence[i] = 1;
        }
        else{lst_T_existence[i] = 0;}
    }
}

void World::Finding_R_addresses(){
    // lst_T_existence stores the information of R existence
    // 1 element means Rabbit exists in that cell with address (index + 1)
    // 0 element means Rabbit doesn't exist in that cell.
    for(int i=0; i<w*h; i++){
        if(AllLives[i+1].getType() == 'R'){
            lst_R_existence[i] = 1;
        }
        else{lst_R_existence[i] = 0;}
    }
}



void World::Handle_T(int ad){

    // check whether this address's character is Tiger or not
    if(lst_T_existence[ad-1] == 0){
        return;}

    int T_life = AllLives[ad].getLife();
    int T_step = AllLives[ad].getStep();

    // starvation check
    if(T_life == 1){
        Deleting(ad); // kill tiger if starving
        num_T--; return;
    }


    // get all 4 neighbors information
    char* neighbors = new char[4];
    for(int i=0; i<4; i++){
        neighbors[i] = InvestigateNeighbor(ad, i);
    }

    // check whether hunter is neighboring
    bool IsHunterNeighbors = false;
    for(int i=0; i<4; i++){
        if(neighbors[i] == 'H'){
            IsHunterNeighbors = true;
            break;
        }
    }
    if(IsHunterNeighbors){
        Is_H_Alive = false; // Tiger kills hunter
        return;
    }

    // check whether all surrounded by tigers
    int TigersAround =0;
    for(int i=0; i<4; i++){
        if(neighbors[i] == 'T'){TigersAround++;}
    }
    if(TigersAround == 4){
        AllLives[ad].mutateLife(T_life - 1);
        AllLives[ad].mutateStep(T_step + 1);
        return; // don't move
    }

    // check wheter to breed
    if(T_step % 10 == 0){
        int NumAvailableDirs = 0;
        for(int i=0; i<4; i++){
            if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'B' )
            {NumAvailableDirs++;}
        }
        int* AllAvailableDirs = new int[NumAvailableDirs]; // storing available directions
        int index = 0;
        for(int i=0; i<4; i++){
            if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'B'){
                AllAvailableDirs[index++] = i;
            }
        }
        int ChosenDir = AllAvailableDirs[rand()%NumAvailableDirs]; // choose random direction
        int BabyTigerAddress = DestinationAddress(ad, ChosenDir);
        Create_T(BabyTigerAddress); num_T++; // number of Tiger increases
        AllLives[ad].mutateLife(T_life - 1);
        AllLives[ad].mutateStep(T_step + 1);
        delete[] AllAvailableDirs; 
        return;
    }

    // check wheter to eat Rabbit
    int RabbitAround = 0;
    for(int i=0; i<4; i++){
        if(neighbors[i] == 'R'){RabbitAround++;}
    }
    if(RabbitAround > 0){
        int* AllAvailableDirs = new int[RabbitAround]; // storing Rabbits' directions
        int index = 0;
        for(int i=0; i<4; i++){
            if(neighbors[i] == 'R'){
                AllAvailableDirs[index++] = i;
            }
        }
        int ChosenDir = AllAvailableDirs[rand()%RabbitAround]; // choose rabbit randomly
        int Destination = DestinationAddress(ad, ChosenDir);
        num_R--; // kill rabbit
        AllLives[Destination].mutateType('T');
        AllLives[Destination].mutateLife(7); // restore full life capacity
        AllLives[Destination].mutateStep(AllLives[ad].getStep() + 1);

        Deleting(ad); // initialize before address too.
        delete[] AllAvailableDirs;
        return;
    }

    // if no rabbits around, just 'move' to available direction
    int NumAvailableDirs = 0;
    for(int i=0; i<4; i++){
        if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'B')
        {NumAvailableDirs++;}
    }
    int* AllAvailableDirs = new int[NumAvailableDirs]; // storing available directions
    int index = 0;
    for(int i=0; i<4; i++){
        if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'B'){
            AllAvailableDirs[index++] = i;
        }
    }
    int ChosenDir = AllAvailableDirs[rand()%NumAvailableDirs]; // choose random direction    
    int Destination = DestinationAddress(ad, ChosenDir);
    AllLives[Destination].mutateType('T');
    AllLives[Destination].mutateLife(AllLives[ad].getLife() - 1); 
    AllLives[Destination].mutateStep(AllLives[ad].getStep() + 1);
    Deleting(ad);
    delete[] AllAvailableDirs;  delete[] neighbors; 
    return;

}

void World::Handle_R(int ad){
     // check whether this address's character is Rabbit?
    if(lst_R_existence[ad-1] == 0){
        return;}

    int R_life = AllLives[ad].getLife();
    int R_step = AllLives[ad].getStep();

    // starvation check
    if(R_life == 1){
        Deleting(ad); // kill rabbit if starving
        num_R--; return;
    } 

    // get all 4 neighbors information
    char* neighbors = new char[4];
    for(int i=0; i<4; i++){
        neighbors[i] = InvestigateNeighbor(ad, i);
    }

    // check whether all surrounded by obstacles
    int AnimalssAround =0;
    for(int i=0; i<4; i++){
        if(neighbors[i] == 'T' || neighbors[i] == 'R' || neighbors[i] == 'H' || neighbors[i] == 'B'){
            AnimalssAround++;}
    }
    if(AnimalssAround == 4){ // all blocked
        AllLives[ad].mutateLife(R_life - 1);
        AllLives[ad].mutateStep(R_step + 1);
        return; // don't move, just stay
    }

    // check wheter to breed
    if(R_step % 7 == 0){
        int NumAvailableDirs = 0; 
        for(int i=0; i<4; i++){
            if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'H' && neighbors[i] != 'B')
            {NumAvailableDirs++;}
        }
        int* AllAvailableDirs = new int[NumAvailableDirs]; // storing available directions
        int index = 0;
        for(int i=0; i<4; i++){
            if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'H' && neighbors[i] != 'B'){
                AllAvailableDirs[index++] = i;
            }
        }
        int ChosenDir = AllAvailableDirs[rand()%NumAvailableDirs]; // choose random direction
        int BabyRabbitAddress = DestinationAddress(ad, ChosenDir);
        Create_R(BabyRabbitAddress); num_R++; // number of Rabit increases
        AllLives[ad].mutateLife(R_life - 1);
        AllLives[ad].mutateStep(R_step + 1);
        delete[] AllAvailableDirs;
        return;
    }


    // check whether to eat Grass
    int GrassAround = 0;
    for(int i=0; i<4; i++){
        if(neighbors[i] != 'R' && neighbors[i] != 'T' && neighbors[i] != 'H'&& neighbors[i] != 'B'){
            int NoAnimalAddress = DestinationAddress(ad, i);
            if(AllLives[NoAnimalAddress].GrassExisting){
                GrassAround++;
            }
        }
    }

    if(GrassAround > 0){
        int* AllAvailableDirs = new int[GrassAround]; // storing Rabbits' directions
        int index = 0;
        for(int i=0; i<4; i++){
            if(neighbors[i] != 'R' && neighbors[i] != 'T' && neighbors[i] != 'H'&& neighbors[i] != 'B'){
                int NoAnimalAddress = DestinationAddress(ad, i);
                if(AllLives[NoAnimalAddress].GrassExisting){
                    AllAvailableDirs[index++] = i;
                }
            }
        }       
     
        int ChosenDir = AllAvailableDirs[rand()%GrassAround]; // choose random grass
        int Destination = DestinationAddress(ad, ChosenDir);
        Deleting(Destination);  num_G--; // grass decreases
        AllLives[Destination].mutateType('R');
        AllLives[Destination].mutateLife(5); // restore full life capacity
        AllLives[Destination].mutateStep(AllLives[ad].getStep() + 1);
        AllLives[Destination].GrassExisting = false; // no more grass there!

        Deleting(ad); // initialize before address too.
        delete[] AllAvailableDirs;
        return;
    }


    // if no grass around, just 'move' to available direction randomly(no animal)
    int NumAvailableDirs = 0;
    for(int i=0; i<4; i++){
        if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'H'&& neighbors[i] != 'B')
        {NumAvailableDirs++;}
    }
    int* AllAvailableDirs = new int[NumAvailableDirs]; // storing available directions
    int index = 0;
    for(int i=0; i<4; i++){
        if(neighbors[i] != 'T' && neighbors[i] != 'R' && neighbors[i] != 'H'&& neighbors[i] != 'B'){
            AllAvailableDirs[index++] = i;
        }
    }
    int ChosenDir = AllAvailableDirs[rand()%NumAvailableDirs]; // choose random direction    
    int Destination = DestinationAddress(ad, ChosenDir);
    AllLives[Destination].mutateType('R');
    AllLives[Destination].mutateLife(AllLives[ad].getLife() - 1); 
    AllLives[Destination].mutateStep(AllLives[ad].getStep() + 1);
    Deleting(ad);  // remove Rabbit from previous address
    delete[] AllAvailableDirs; delete[] neighbors;
    return;


}


void World::Generate_G(){
    // generate Grass on empty cell with 10% probabilty

    // let's find out which cell can generate grass
    int* GrassGeneratingAvialabeCells = new int[w*h];
    for(int i=0; i<w*h; i++){
        GrassGeneratingAvialabeCells[i] = 0; // initialize to 0(not available to generate)
    }

    for(int i=1; i<= w*h; i++){
        if(AllLives[i].getType() != 'T' && AllLives[i].getType() != 'R' && AllLives[i].getType() != 'H'){
            if((!AllLives[i].FoodExisting) && (!AllLives[i].GrassExisting)){
                GrassGeneratingAvialabeCells[i-1] = 1;  // 1 means available to generate new grass
            }
        } 
    }

    int NumGeneratingAvailableCells = 0;
    for(int i=0; i<w*h; i++){
        if(GrassGeneratingAvialabeCells[i]==1){
            NumGeneratingAvailableCells++;
        }
    }

    int* AddressesOfGeneratingAvailable = new int[NumGeneratingAvailableCells]; // this list stores all available addresses
    int index = 0;
    for(int i=0; i<w*h; i++){
        if(GrassGeneratingAvialabeCells[i] == 1){
            AddressesOfGeneratingAvailable[index++] = i+1;
        }
    }
    
    // settings for getting 10% possibility
    int p;
    int* OneToTen = new int[10];
    for(int i=0; i<10; i++){
        OneToTen[i] = i+1;
    }

    for(int i=0; i< NumGeneratingAvailableCells; i++){
        // generate new grass with 10% probability
        p = OneToTen[rand() % 10];

        if(p == 1){ // possible with 10%
            AllLives[AddressesOfGeneratingAvailable[i]].GrassExisting = true; // generation success
        }
    }

    delete[] GrassGeneratingAvialabeCells; delete[] AddressesOfGeneratingAvailable; delete[] OneToTen;

}


void World::Deleting(int ad){
    // remove the charactr from the address
    AllLives[ad].mutateType('E');
}


bool World::IsDestinationOutOfWorld(int address, int dir)
{
    // finding out whether the destination where character wants to go is out of the World(Boader)    
    if(dir == 0){ 
        if( 1<= address && address <= w){
            return true;     // collide with top boarder
        }
    }
    else if(dir == 2){
        if(address % w == 0){
            return true;    // collide with bottom boarder
        }
    }
    else if(dir == 1){
        if((w*(h-1)+1) <= address){
            return true;    // collide with right-side boarder
        }
    }
    else if(dir == 3){
        if(address % w == 1){
            return true;    // collide with left-side boarder
        }
    }

    return false;
} 

char World::InvestigateNeighbor(int address, int dir){
    // finding out the 'type' of neighbor character

    if(IsDestinationOutOfWorld(address, dir)){
        return 'B'; // mean Boarder
    }

    int neighbor_address;
    char neighbor_type;
    if(dir == 0){
        neighbor_address = address - w;
        neighbor_type = AllLives[neighbor_address].getType();
        if(neighbor_type == 'H' || neighbor_type == 'R' || neighbor_type == 'T'){
            return neighbor_type;
        }
        else if (AllLives[neighbor_address].GrassExisting){
            return 'G';
        }
        else if (AllLives[neighbor_address].FoodExisting){
            return 'F';
        }
        else{return 'E';}
    }
    else if(dir == 2){
        neighbor_address = address + 1;
        neighbor_type = AllLives[neighbor_address].getType();
        if(neighbor_type == 'H' || neighbor_type == 'R' || neighbor_type == 'T'){
            return neighbor_type;
        }
        else if (AllLives[neighbor_address].GrassExisting){
            return 'G';
        }
        else if (AllLives[neighbor_address].FoodExisting){
            return 'F';
        }
        else{return 'E';}
    }
    else if(dir == 1){
        neighbor_address = address + w;
        neighbor_type = AllLives[neighbor_address].getType();
        if(neighbor_type == 'H' || neighbor_type == 'R' || neighbor_type == 'T'){
            return neighbor_type;
        }
        else if (AllLives[neighbor_address].GrassExisting){
            return 'G';
        }
        else if (AllLives[neighbor_address].FoodExisting){
            return 'F';
        }
        else{return 'E';}
    }
    else if(dir == 3){
        neighbor_address = address - 1;
        neighbor_type = AllLives[neighbor_address].getType();
        if(neighbor_type == 'H' || neighbor_type == 'R' || neighbor_type == 'T'){
            return neighbor_type;
        }
        else if (AllLives[neighbor_address].GrassExisting){
            return 'G';
        }
        else if (AllLives[neighbor_address].FoodExisting){
            return 'F';
        }
        else{return 'E';}
    }

}


int World::FindNearestAnimal(int dir){ // used for shooting
    // when hunter tries to shoot, he need to find the nearest animal in that direction.

    bool FindAnimal = false;

    if(IsDestinationOutOfWorld(H_Address, dir)){
        return -1;  // (-1) means no animal in that direction
    }

    int targetAddress = H_Address;
    if(dir == 0){ // up
        while(! IsDestinationOutOfWorld(targetAddress, 0)){
            targetAddress -= w;
            if(AllLives[targetAddress].getType() == 'T' || AllLives[targetAddress].getType() == 'R'){
                FindAnimal = true;
                break;
            }
        }
        if(FindAnimal){return targetAddress;}
        else{return -1;}
    }

    else if(dir == 1){
        while(! IsDestinationOutOfWorld(targetAddress, 1)){
            targetAddress += w;
            if(AllLives[targetAddress].getType() == 'T' || AllLives[targetAddress].getType() == 'R'){
                FindAnimal = true;
                break;
            }
        }
        if(FindAnimal){return targetAddress;}
        else{return -1;}        
    }

    else if(dir == 2){
        while(! IsDestinationOutOfWorld(targetAddress, 2)){
            targetAddress += 1;
            if(AllLives[targetAddress].getType() == 'T' || AllLives[targetAddress].getType() == 'R'){
                FindAnimal = true;
                break;
            }
        }
        if(FindAnimal){return targetAddress;}
        else{return -1;}        
    }

    else if(dir == 3){
        while(! IsDestinationOutOfWorld(targetAddress, 3)){
            targetAddress -= 1;
            if(AllLives[targetAddress].getType() == 'T' || AllLives[targetAddress].getType() == 'R'){
                FindAnimal = true;
                break;
            }
        }
        if(FindAnimal){return targetAddress;}
        else{return -1;}        
    }

}




bool World::ContinueGame(){
    // check wheter to continue game or finish
    // Game win condition
    if(num_T == 0){return false;}

    // Game Over conditions
    else if(H_Life == 0){return false;}
    else if(! Is_H_Alive){return false;}
    else if(num_R == 0){return false;}
    else{return true;}
}



void World::PrintGameFinished(){

    // Game Win Condition : no tiger exists
    if(num_T == 0){
        cout << "Tigers are all dead\n"
             << "You Win!";
    }

    // Game Over Condition
    //  (1) Hunter's life is zero
    else if(H_Life == 0){
        cout << "Hunter starved to death\n"
             << "Game Over!";
    }

    //  (2) Tiger eats Hunter
    else if(! Is_H_Alive){
        cout << "Hunter is dead\n"
             << "Game Over!";
    } 

    //  (3) no rabbit exists
    else if(num_R == 0){
        cout << "Rabbits are gone\n"
             << "Game over!";
    }

}

int World::DestinationAddress(int address, int dir)
{
    // get the neighbor's direction in that direction
    if(dir == 0){
        return address - w;
    }
    else if(dir == 2){
        return address + 1;
    }
    else if(dir == 1){
        return address + w;
    }
    else if(dir == 3){
        return address - 1;
    }
}

bool World::isEmptyCell(int ad)
{
    // find out wheter the cell is empty or not
    for(int i=0; i< num_Empty; i++){
        if(ad == lst_empty[i]){
            return true;
        }
    }
    return false;
}


void World::AddToLst(int ad, int* &lst, int& lst_size)  // used for assigning animals in the beginning of the game
{
    // add new 'ad' element to 'lst' list
    int* temp = lst;
    lst = new int[lst_size + 1];

    if(lst != NULL){
        for(int i=0; i < lst_size; i++){
            lst[i] = temp[i];
        }
    }
    lst[lst_size] = ad;
    delete[] temp;
    lst_size++;

}

void World::DelFromLst(int ad, int* &lst, int& lst_size) // used for assigning animals in the beginning of the game
{
    // remove 'ad' element from 'lst' list
    int* temp = lst;
    lst = new int[lst_size -1];

    int index = 0;
    for(int i=0; i<lst_size; i++){
        if(temp[i]==ad){
            continue;
        }     
        lst[index++] = temp[i];
    }

    delete[] temp;
    lst_size--;

}

World::~World(){
    // destructor
    delete[] AllLives;
    delete[] lst_empty; delete[] lst_full; 
    delete[] lst_T_existence; delete[] lst_R_existence;
}