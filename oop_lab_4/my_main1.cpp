#include "my_class.hpp" // It is enough to include only class.hpp.

int main()
{

	Class OOP("OOP", "Kim");
	
	OOP.Register("Moon", 2020123123); 
	OOP.Register("Biden", 2020123124);
	OOP.Register("Trump", 2020123125);
	OOP.Display();

	
	Class DATA = OOP;
	DATA.SetClassName("Data Structure", "Yang");
	DATA.Withdraw(2020123123);
	DATA.Display();


	OOP.Display();


	Class AI(OOP);

	AI.SetClassName("Artificial Intelligence", "Hwang");
	AI.Register("Siri", 2020123126);
  AI.Register("Bixby", 2020123127);
	AI.Display();


	OOP.Display();

}
