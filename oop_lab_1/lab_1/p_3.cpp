#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

/**********************/
/*******Problem 3******/
/**********************/
/* ID:  2020147519 */
/* NAME:   ¹ÚÁ¦¿¬  */
/**********************/

int main() {
	int loopNum;

	ifstream infile("input3.txt");

	cout << setprecision(3) << fixed;
	infile >> loopNum;
	for (int i = 0; i < loopNum; i++) {
		double start;
		infile >> start;

		double profit;
		infile >> profit;

		double target;
		infile >> target;


		// money after interest is added.
		double added_money;
		added_money = start * (1 + profit / 100.0);

		int day = 1;
			
	
		while (added_money < target) {
			cout << "Day #" << day << ": " << added_money << endl;
			
			// add interest
			added_money *= (1 + profit / 100.0);
			// add day +1
			day++;
		}

		cout << "Day #" << day << ": " << added_money << endl;
		cout << "Final income: " << (added_money - start) << endl;

	}

	infile.close();

	return 0;
}
