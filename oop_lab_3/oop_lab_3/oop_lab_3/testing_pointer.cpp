# include <iostream>
using namespace std;


int main() {

	int arr[3] = { 1,2,3 };

	cout << arr << " " << &arr << endl;

	int(*ptr_arr_1)[3];
	ptr_arr_1 = &arr;

	for (int i = 0; i < 3; i++) {
		cout << (*ptr_arr_1)[i] << " ";
	}
	cout << endl; 

	int* ptr_arr_2;
	ptr_arr_2 = arr;
	for (int i = 0; i < 3; i++) {
		cout << ptr_arr_2[i] << " ";
	}

}