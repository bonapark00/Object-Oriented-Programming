#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
using namespace std;

/**********************/
/*******Problem 1******/
/**********************/
/* ID:     2020147519           */
/* NAME:     Jaeyeon Park         */
/**********************/

int main() {
    int loopNum;
    char dump[51]; // to ignore '\n' in first line

    ifstream infile("input1.txt");

    infile >> loopNum;
    cout << loopNum << " <- !loopnum finish !" << endl;
   
    infile.getline(dump, 51);
    cout << "iam dump" << dump << endl;
    cout << strlen(dump) << ": strlen dump" << endl;


    for (int i = 0; i < loopNum; i++) {
        char inputString[51];


        infile.getline(inputString, 51);
        cout << "i am inputstring:  " << inputString << endl;
        cout << "i am this strlen!  " << strlen(inputString) << endl;

         }


    infile.close();

    char arr[40] = { 'a', 'b' };
    cout << "this new ex: "<<strlen(arr) << endl;



    return 0;
}
