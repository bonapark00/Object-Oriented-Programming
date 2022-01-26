#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

/**********************/
/*******Problem 4******/
/**********************/
/* ID:  2020147519 */
/* NAME:  Jaeyeon Park   */
/**********************/

void print_seat_state(int& first, int& business, int& economy);

void add_passenger(int& first, int& business, int& economy, ifstream& file);
void add_passenger_to_seats(int num_to_be_added, int& num_of_existing, int max);

void delete_passenger(int& first, int& business, int& economy, ifstream& file);
void delete_passenger_to_seats(int num_to_be_deleted, int& num_of_existing, int max);


int main() {
	int first_class = 0; //MAX: 5
	int business_class = 0; // MAX: 25
	int economy_class = 0; // MAX: 50

	int loopNum;

	ifstream infile("input4.txt");

	infile >> loopNum;

	for (int i = 0; i < loopNum; i++) {
		
		// decide wheter to add or delete
		char menu;
		infile >> menu;
		switch (menu) {
		case '1':
			add_passenger(first_class, business_class, economy_class, infile);
			break;
		case '2':
			delete_passenger(first_class, business_class, economy_class, infile);
			break;
		default:
			cout << "Wrong Input!" << "\n";
		}
	}

	// output the result seats
	print_seat_state(first_class, business_class, economy_class);
	cout << "end the program" << "\n";

	infile.close();

	return 0;
}

void add_passenger(int& first, int& business, int& economy, ifstream& file) {
	int seat_type;
	int num_to_be_added;
	file >> seat_type;
	file >> num_to_be_added;
	
	// for each type of seat, add the given number of passengers to the remaining seats.
	switch (seat_type) {
	case 1:
		add_passenger_to_seats(num_to_be_added, first, 5);
		break;
	case 2:
		add_passenger_to_seats(num_to_be_added, business, 25);
		break;
	case 3:
		add_passenger_to_seats(num_to_be_added, economy, 50);
		break;
	}
}

void add_passenger_to_seats(int num_to_be_added, int& num_of_existing, int max) {
	/*
	function for adding the passengers to the remaining seats
	But, if the reamaining seat are not enough, output 'full seat'
	*/
	
	if (num_to_be_added <= (max - num_of_existing)) {
		// add
		num_of_existing += num_to_be_added;
		cout << "add complete" << endl;
	}

	else {
		cout << "full seat" << endl;
	}
}




void delete_passenger(int& first, int& business, int& economy, ifstream& file) {
	int seat_type;
	int num_to_be_deleted;
	file >> seat_type;
	file >> num_to_be_deleted;
	
	// for each type of seat, delete the given number of passengers.
	switch (seat_type) {
	case 1:
		delete_passenger_to_seats(num_to_be_deleted, first, 5);
		break;
	case 2:
		delete_passenger_to_seats(num_to_be_deleted, business, 25);
		break;
	case 3:
		delete_passenger_to_seats(num_to_be_deleted, economy, 50);
		break;
	}


}




void delete_passenger_to_seats(int num_to_be_deleted, int& num_of_existing, int max) {
	/*
	function for deleting the passengers from the reserved seats
	But, if the reserved seat are not enough, output 'wrong input'
	
	*/
	
	if (num_to_be_deleted <=  num_of_existing) {
		// delete
		num_of_existing -= num_to_be_deleted;
		cout << "delete complete" << endl;
	}

	else {
		cout << "wrong input" << endl;
	}
}

void print_seat_state(int& first, int& business, int& economy) {
	cout << "current vacant seats" << endl;
	cout << "first class: " << (5 - first) << "/" << 5 << endl;
	cout << "business class: " <<(25 - business) << "/" << 25 << endl;
	cout << "economy class: " << (50-economy) << "/" << 50 << endl;

		
	// print seats symbol: first class
	cout << "first class" << endl;
	for (int i = 0; i < first; i++) {
		cout << "X";
	}
	for (int i = 0; i < (5 - first); i++) {
		cout << "O";
	}
	cout << endl;

	// print seats symbol: business class
	int printed_seats = 0;
	cout << "business class" << endl;
	for (int i = 0; i < business; i++) {
		cout << "X";
		printed_seats++;

		if (printed_seats % 5 == 0) {
			cout << endl;
		}
	}
	for (int i = 0; i < 25 - business; i++) {
		cout << "O";
		printed_seats++;

		if (printed_seats % 5 == 0) {
			cout << endl;
		}

	}

	// print seats symbol: economy class
	printed_seats = 0;
	cout << "economy class" << endl;
	for (int i = 0; i < economy; i++) {
		cout << "X";
		printed_seats++;

		if (printed_seats % 5 == 0) {
			cout << endl;
		}
	}
	for (int i = 0; i < 50 - economy; i++) {
		cout << "O";
		printed_seats++;

		if (printed_seats % 5 == 0) {
			cout << endl;
		}

	}

}

