#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
using namespace std;

/**********************/
/*******Problem 2******/
/**********************/
/* ID:  2020147519  */
/* NAME:  ¹ÚÁ¦¿¬    */
/**********************/

int main() {
	int loopNum;

	ifstream infile("input2.txt");

	infile >> loopNum;
	for (int i = 0; i < loopNum; i++) {

		int lineNum;
		infile >> lineNum;
		
		for (int i = 0; i < lineNum; i++) {
			
			// print blanks first
			for (int j =0; j < (lineNum - i - 1) ; j++) {
				cout << " ";
			}

			// print stars
			for (int j = 0; j< (2*i + 1)  ; j++) {
				cout << "*" ;
			}
		
			// change the line
			cout << endl;
		}
	}


	infile.close();

	return 0;
}
