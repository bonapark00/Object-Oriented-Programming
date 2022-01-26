#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
using namespace std;

/**********************/
/*******Problem 3******/
/**********************/
/* ID:     2020147519       */
/* NAME: Jaeyeon Park   */
/**********************/

bool isEmptyArray(int arr[], int arr_size);
void BiggerIsBetter_game(int player_A[], int player_B[], int arr_size, int& score_player_A, int& score_player_B);
void moveCards(int arr_player[], int arr_size);


int main() {
	int loopNum;

	ifstream infile("input3.txt");

	infile >> loopNum;
	for (int i = 0; i < loopNum; i++) {
		
		// get the number of cards.
		int num_of_cards;
		infile >> num_of_cards;
		
		int arr_A[1000], arr_B[1000];
		int score_A = 0, score_B = 0;
		// assign card number streams
		for (int j = 0; j < num_of_cards; j++) {
			infile >> arr_A[j];
		}
		for (int j = 0; j < num_of_cards; j++) {
			infile >> arr_B[j];
		}
		
		// implement the game until one player has no more card.
		while ((!(isEmptyArray(arr_A, num_of_cards))) && (!(isEmptyArray(arr_B, num_of_cards)))) {
			BiggerIsBetter_game(arr_A, arr_B, num_of_cards, score_A, score_B);
		}
	
		// output the result.
		cout << score_A << " " << score_B << endl;
		}

	infile.close();

	return 0;
}


bool isEmptyArray(int arr[], int arr_size) {
	/*
	function for checking whether the player has card remaining.
	(-100) card number means the player has no card for that index.	
	return True when the player has no card at all.
	*/
		
	bool isEmpty = false;
	int count_num_of_empty_element = 0;
	
	// count empty(-100) element.
	for (int i = 0; i < arr_size; i++) {
		if (arr[i] == -100) { count_num_of_empty_element++; }
	}
	if (count_num_of_empty_element == arr_size) {
		isEmpty = true;
	}

	return isEmpty;

}

void BiggerIsBetter_game(int player_A[], int player_B[], int arr_size, int& score_player_A, int& score_player_B) {
	/*
	function for implenting the bigger is better game.
	1st, Compare the first card. One with bigger card is the winner.
	2nd, Winner's first card is degraded.
	3rd, Loser's card array changes.
	4th, Update the score.
	*/
	
	// when A has the larger card
	if (player_A[0] > player_B[0]) {
		player_A[0] -= player_B[0];

		// Discard the first card of B
		moveCards(player_B, arr_size);
		// Update the score.
		score_player_A++;
	}

	// when drawing
	else 	if (player_A[0] == player_B[0]) {
		moveCards(player_A, arr_size);
		moveCards(player_B, arr_size);
	}
	// when B has the larger card
	else 	if (player_A[0] < player_B[0]) {
		player_B[0] -= player_A[0];

		moveCards(player_A, arr_size);
		
		score_player_B++;

				
	}

};


void moveCards(int arr_player[], int arr_size) {
	/*
	function for moving card.
	used when loser needs to discard the card, or when drawing.	

	1st, Discard the first card
	2nd, Move the remaining card forward one by one.
	3rd, Assign the vacant place to (-100)
	*/
	int index = 0;
	while ((arr_player[index] != -100) && (index != arr_size - 1)) {
	
		arr_player[index] = arr_player[index + 1];
		index++;
	}

	// set the last  element to (-100)
	if (index == arr_size -1 ) {
		arr_player[index] = -100;
	}


}
