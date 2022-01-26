#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
using namespace std;

/*
class Price {
public:
	void set(double newPrice, char newCurrency);
	void print();

	double UnitPrice;
	char Currency;
};

void Price::set(double newPrice, char newCurrency) {
	UnitPrice = newPrice;
	Currency = newCurrency;
}

void Price::print() {
	cout <<  "UnitPrice: " << UnitPrice;
	cout <<  "Currency: " <<  Currency;
}



class Rectangle {
public:
	void getInfo(int new_width, int new_height);
	void mutateInfo(int change_w, int change_h);

private:
	int width;
	int height;
	int area;
};

void Rectangle::getInfo(int new_width, int new_height) {
	cout << "First width = ";
	cin >> width;
	cout << "First height = ";
	cin >> height;
}

*/

class Point {
public:
	Point(int x_value, int y_value);
	Point(int x_value);
	Point();

	void Move(int dx, int dy);
	int Get_X();
	int Get_Y();

private:
	int x_coor;
	int y_coor;
};


int main() {
	Point origin;
	Point bonaPoint(4, 4);

	cout << origin.Get_X() << " " << origin.Get_Y() << endl;
	cout << bonaPoint.Get_X() << " " << bonaPoint.Get_Y() << endl;

	cout << "move~" << endl;
	bonaPoint.Move(8, 10);
	cout << bonaPoint.Get_X() << " " << bonaPoint.Get_Y() << endl;


}





Point::Point(int x_value, int y_value) : x_coor(x_value), y_coor(y_value){ }
Point::Point(int x_value) : x_coor(x_value), y_coor(0){}
Point::Point() : x_coor(0), y_coor(0){}

void Point::Move(int dx, int dy) {
	x_coor += dx;
	y_coor += dy;
}

int Point::Get_X() {
	return  x_coor;
}

int Point::Get_Y() {
	return  y_coor;
}









