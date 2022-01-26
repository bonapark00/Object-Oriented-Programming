#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

/**********************/
/*******Problem 2******/
/**********************/
/* ID:  2020147519  */
/* NAME:     Jaeyeon Park     */
/**********************/

int main() {
	int loopNum;
	char dump[51];

	ifstream infile("input2.txt");

	infile >> loopNum;
	
	// skip first  \n
	infile.getline(dump, 51);

	
	for (int i = 0; i < loopNum; i++) {
		int num_digit, num_1_bit = 0;
		int arr_binary[50];
		int int_decimal = 0;
		char parity_bit;

		// get binary length
		infile >> num_digit;
		
		// get binary num
		for (int i = 0; i < num_digit; i++) {
			infile >> arr_binary[i];
			
			// count the total numer of 1-bits
			if (arr_binary[i] == 1) {
				num_1_bit++;
			}
		}
		
		// get a parity bit
		infile >> parity_bit;
	
		// restore a last bit by the parity bit.
		if (parity_bit == 'e') {
			if (num_1_bit % 2 == 1) { int_decimal++; }
		}
		else if (parity_bit == 'o') {
			if (num_1_bit % 2 == 0) { int_decimal++;  }
		}

		// convert the restored binary num into decimal num.
		int exponent = 1;
		for (int j = num_digit - 1; j >= 0; j--) {
			if(arr_binary[j] == 1){
			int_decimal += pow(pow(2, exponent), arr_binary[j]);
			}
			exponent++;
		}
		
		// output the result
		cout << int_decimal << endl;
		
		// go to the next line
		infile.getline(dump, 51);

	}
	infile.close();

	return 0;
}
