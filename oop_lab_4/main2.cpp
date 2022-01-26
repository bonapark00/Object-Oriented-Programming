#include "class.hpp" // It is enough to include only class.hpp.

int main()
{

	Class OOP("OOP", "Kim");
	OOP.Display();
	OOP.Register("Moon", 2020123123);
	OOP.Display(); 
	OOP.Register("Biden", 2020123124);
	OOP.Display();
	OOP.Register("Trump", 2020123125);
	OOP.Display();
	OOP.Register("Siri", 2020123126);
	OOP.Display();
	OOP.Register("Bixby", 2020123127);
	OOP.Display();

	OOP.Withdraw(2020123123);
	OOP.Display();
	OOP.Withdraw(2020123125);
	OOP.Display();
	OOP.Withdraw(2020123127);
	OOP.Display();
	OOP.Withdraw(2020123126);
	OOP.Display();
	OOP.Withdraw(2020123124);
	OOP.Display();

}
