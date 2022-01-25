#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

/**********************/
/*******Problem 1******/
/**********************/
/* ID: 2020147519  */
/* NAME: Jaeyeon Park(¹ÚÁ¦¿¬) */
/**********************/

int main() {
	int loopNum;

	ofstream outfile;
	outfile.open("output1.txt");

	cout << "Enter the number of interations for the loop: ";
	cin >> loopNum;

	for (int i = 0; i < loopNum; i++) {
		int a, b, c, d;
		cout << "Enter the coefficients of the equation [y = ax^3 + bx^2 + cx + d]" << endl;
		cout << "a: "; cin >> a;
		cout << "b: "; cin >> b;
		cout << "c: "; cin >> c;
		cout << "d: "; cin >> d;

		// To fix the precision of floating numbers
		outfile << setprecision(3) << fixed;

		// differential expression: 3ax^2 + 2bx^2 + c
		// D/4 = b^2 - 3*a*c

		int discriminant_simple = b * b - 3 * a * c;
		a = double(a);
		b = double(b);
		c = double(c);

		// have two solutions
		if (discriminant_simple > 0) {

			discriminant_simple = double(discriminant_simple);
			outfile << ((-1.0) * b + sqrt(discriminant_simple)) / (3.0 * a) << " " << ((-1.0) * b - sqrt(discriminant_simple)) / (3.0 * a) << endl;
		}

		// have one solution
		else if (discriminant_simple == 0) {

			outfile << (-1.0) * b / (3.0 * a) << endl;
		}

		// have no solution
		else {
			outfile << "Not Available." << endl;
		}

	}

	outfile.close();

	return 0;
}
