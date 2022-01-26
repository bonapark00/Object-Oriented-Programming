# include <iostream>
# include <string>
# include <cstdlib>
using namespace std;



class Person {


public:
	Person();
	Person(string ID, int PW, int TotalMoney);

	static bool Check_Existing_ID(string InputID);
	static bool Check_IDPW_Matching(string InputID, int InputPW);
	// 로그인시에 사용할 이 사람의 등록되어있던 순서
	static int get_signedup_order(string InputID);
	// 로그인시에 사용할 이사람의 순서에 맞는 돈 정보 끌어오기
	static int getMoney(int order);

	static void add_New_ID(string InputID);
	static void add_New_PW(int InputPW);
	static void add_New_Money(int InputMoney);

	//	static void addPerson(Person *thisPerson);
	static int getTotalPersonNum() { return TotalPersonNum; }
	static int TotalPersonNum;
	//	static Person* getAllPerson() { return AllPerson[0]; }
	string getID() { return ID; }
	int getPW() { return PW; }
	int getTotalMoney() { return TotalMoney; }
	void be_logined();
	void be_logout();

	void do_Order(int what_menu, int how_many, int how_much);
	void Add_DynamicList(int menu_type, int how_many);
	void Remove_Dynamiclist(int target_order);


	// menu Implementation(4-0)
	void Order();
	void OrderCondition();
	void Refund();




private:

	static string id_list[100];
	static int pw_list[100];
	static int money_list[100];
	int signedup_order = 0;

	// Personal Information
	string ID;
	int PW;
	int TotalMoney;
	int MoneySpent = 0;
	bool is_logined = false;

	// int menu_ordered_num[8];
	int ordered_menu_num = 0;
	int menu_ordered_num[8][2];
	int* menu_ordered_sequence = new int[1];

};

Person::Person() {
	ID = " ", PW = 0; TotalMoney = 0;
	// set all menu not ordered yet
	for (int i = 0; i < 8; i++) {
		// set menu type number
		menu_ordered_num[i][0] = (i + 1);
		// all menus are not ordered yet.
		menu_ordered_num[i][1] = 0;
	}

}

Person::Person(string ID, int PW, int TotalMoney) {
	this->ID = ID;
	this->PW = PW;
	this->TotalMoney = TotalMoney;

	// set all menu not ordered yet
	for (int i = 0; i < 8; i++) {
		// set menu type number
		menu_ordered_num[i][0] = (i + 1);
		// all menus are not ordered yet.
		menu_ordered_num[i][1] = 0;
	}

}

bool Person::Check_Existing_ID(string InputID) {

	for (int i = 0; i < TotalPersonNum; i++) {
		if (InputID == id_list[i]) {
			return true;
		}
	}

	return false;
}

bool Person::Check_IDPW_Matching(string InputID, int InputPW) {

	// get this person number

	for (int i = 0; i < TotalPersonNum; i++) {
		if (id_list[i] == InputID) {

			if (InputPW == pw_list[i]) {
				return true;
			}
			else { return false; }

			break;
		}
	}

}



void Person::add_New_ID(string InputID) {
	id_list[TotalPersonNum - 1] = InputID;
	for (int i = 0; i < TotalPersonNum; i++) {
		cout << id_list[i] << "!!" << endl;
	}


}

void Person::add_New_PW(int InputPW) {
	pw_list[TotalPersonNum - 1] = InputPW;
}

void Person::add_New_Money(int InputMoney) {
	money_list[TotalPersonNum - 1] = InputMoney;
}


int Person::get_signedup_order(string InputID) {
	for (int i = 0; i < TotalPersonNum; i++) {
		if (id_list[i] == InputID) {
			return i + 1;
		}
	}
}

int Person::getMoney(int order) {
	return money_list[order - 1];
}


void Person::Add_DynamicList(int menu_type, int how_many) {

	int* menu_ordered_sequence_new = new int[ordered_menu_num];

	// the first menu adding case
	if (ordered_menu_num - how_many == 0) {
		for (int i = 0; i < ordered_menu_num; i++) {
			menu_ordered_sequence_new[i] = menu_type;
		}
	}

	else {
		// copy the previous menu ordered sequence
		for (int i = 0; i < ordered_menu_num - how_many; i++) {
			menu_ordered_sequence_new[i] = menu_ordered_sequence[i];
		}
		for (int i = ordered_menu_num - how_many; i < ordered_menu_num; i++) {
			menu_ordered_sequence_new[i] = menu_type;
		}
	}
	delete[] menu_ordered_sequence;
	menu_ordered_sequence = menu_ordered_sequence_new;
}

void Person::Remove_Dynamiclist(int target_order) {

	// increase money
	switch (menu_ordered_sequence[target_order]) {

	case 1:
		TotalMoney += 1000; MoneySpent -= 1000;
		break;
	case 2:
		TotalMoney += 1500; MoneySpent -= 1500;
		break;
	case 3:
		TotalMoney += 3000; MoneySpent -= 3000;
		break;
	case 4:
		TotalMoney += 4000; MoneySpent -= 4000;
		break;
	case 5:
		TotalMoney += 5000; MoneySpent -= 5000;
		break;
	case 6:
		TotalMoney += 1500; MoneySpent -= 1500;
		break;
	case 7:
		TotalMoney += 2000; MoneySpent -= 2000;
		break;
	case 8:
		TotalMoney += 1500; MoneySpent -= 1500;
		break;

	}


	// 여기서 ordered_menu_num은 이미 하나 줄어든걸로 가정
	int* menu_ordered_sequence_new = new int[ordered_menu_num];

	for (int i = 0; i < target_order - 1; i++) {
		menu_ordered_sequence_new[i] = menu_ordered_sequence[i];
	}
	for (int i = target_order - 1; i < ordered_menu_num; i++) {
		menu_ordered_sequence_new[i] = menu_ordered_sequence[i + 1];
	}
	delete[] menu_ordered_sequence;
	menu_ordered_sequence = menu_ordered_sequence_new;



}

void Person::do_Order(int what_menu, int how_many, int how_much) {
	// do remaining money check, then mutate total money
	// enough money to order new food
	if (TotalMoney - how_many * how_much >= 0) {
		TotalMoney -= how_many * how_much;
		MoneySpent += how_many * how_much;
		ordered_menu_num += how_many;

		Add_DynamicList(what_menu, how_many);

	}
	// not enough money. Cannot order more.
	else {
		cout << "You don't have enough money!\n";
	}

}


void Person::Order() {

	int menu_option;
	int menu_num;


	while (true) {
		// get which menu to order
		cout << "Select menu number(0-to main menu) : ";
		cin >> menu_option;

		switch (menu_option) {
		case 0:
			cout << "Your total purchase amount is " << MoneySpent << endl;
			cout << "Your balance is " << (TotalMoney) << endl;
			cout << "Thanks\n\n";
			return;
			break;
		case 1:
			cout << "How many 'Hamburger' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 1000);
			break;
		case 2:
			cout << "How many 'Cheeseburger' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 1500);
			break;
		case 3:
			cout << "How many 'Big Mac' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 3000);
			break;
		case 4:
			cout << "How many 'Quarter Pounder Burger' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 4000);
			break;
		case 5:
			cout << "How many 'Double Quarter Pounder' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 5000);
			break;
		case 6:
			cout << "How many 'Fries' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 1500);
			break;
		case 7:
			cout << "How many 'Chicken McNuggets' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 2000);
			break;
		case 8:
			cout << "How many 'Coke' do you want : ";
			cin >> menu_num;
			this->do_Order(menu_option, menu_num, 1500);
			break;

		}
		cout << endl;

	}



}




void Person::OrderCondition() {


	for (int i = 0; i < ordered_menu_num; i++) {
		switch (menu_ordered_sequence[i]) {
		case 1:
			cout << (i + 1) << ". \'Hamburger\'" << endl;
			break;
		case 2:
			cout << (i + 1) << ". \'Cheeseburger\'" << endl;
			break;
		case 3:
			cout << (i + 1) << ". \'Big Mac\'" << endl;
			break;
		case 4:
			cout << (i + 1) << ". \'Quarter Pounder Burger\'" << endl;
			break;
		case 5:
			cout << (i + 1) << ". \'Double Quarter Pounder\'" << endl;
			break;
		case 6:
			cout << (i + 1) << ". \'Fries\'" << endl;
			break;
		case 7:
			cout << (i + 1) << ". \'Chicken McNuggets\'" << endl;
			break;
		case 8:
			cout << (i + 1) << ". \'Coke\'" << endl;
			break;
		default:
			cout << menu_ordered_sequence[i] << endl; break;
		}
	}

	cout << "\nYour total price is " << MoneySpent << endl;
	cout << "Your total moeny is " << TotalMoney << endl;

}

void Person::Refund() {
	OrderCondition();
	cout << "\n";
	int refund_option;

	while (true) {
		cout << "Choose number(0 - to main menu) : ";
		cin >> refund_option;

		if (refund_option == 0) {
			break;
			return;
		}
		else if (refund_option <= ordered_menu_num && refund_option > 0) {

			// minus 1 in total ordered number
			ordered_menu_num--;
			Remove_Dynamiclist(refund_option);
			cout << "Successfully returned\n\n";
		}

		else {
			cout << "Wrong input!\n\n";

		}

	}
}

void Person::be_logined() {
	is_logined = true;
}

void Person::be_logout() {
	int logout_option;

	while (true) {
		cout << "If you want to logout, Please enter 1 (0-to main menu) : ";
		cin >> logout_option;

		if (logout_option == 1) {
			is_logined = false;
			break;
		}
		else if (logout_option == 0) {
			cout << "Logout is canceled\n";
			return;
			break;
		}
		else {
			cout << "Wrong input!\n";
		}
	}




}

// global functions
void SignUp();
Person* Login(string login_id, Person AllPerson_list[]);
void ShowMenu();

// initialize the TotalPerson number as zero.
int Person::TotalPersonNum = 0;

string Person::id_list[] = { " " };
int Person::pw_list[] = { 0 };
int Person::money_list[] = { 0 };

int main() {

	bool ContinueProgram = true;
	char option;

	int login_time = 0;
	string Login_ID;
	Person* Logined_Person;
	Logined_Person = new Person("init", 0, 0);

	Person* AllPerson;
	AllPerson = new Person[100];

	while (ContinueProgram) {

		cout << "-----------------------------------\n"
			<< "-----Mcdonalds Delivery System-----\n"
			<< "-----------------------------------\n\n"
			<< "1. Sign up\n2. login\n3. Show Menu\n4. Order\n5. Order condition\n6. Refund\n7. Logout\n0. Exit\n"
			<< "Select ->";
		cin >> option;

		cout << "\n";

		switch (option) {
		case '1':
			// no login before
			if (login_time != 1) {
				SignUp();
				break;
			}
			// if already loginned
			else {
				cout << "You are already logged in to " << Logined_Person->getID() << " account\n";
				cout << "Return to main menu\n\n";
				break;
			}

		case '2':

			cout << "Input your ID(0-to main menu) : ";
			cin >> Login_ID;

			if (Person::Check_Existing_ID(Login_ID)) {
				Logined_Person = Login(Login_ID, AllPerson);
				login_time++;
				break;
			}

			// if ID is 0. return to main
			else if (!Person::Check_Existing_ID(Login_ID) && Login_ID == "0") {
				break;
			}


		case '3':
			ShowMenu();
			break;

		case '4':
			// If not logined first
			if (login_time != 1) {
				cout << "\nYou have to login first\n"
					<< "Return to main menu\n\n";
				break;
			}
			// if logined correctly
			else {
				Logined_Person->Order();
				break;
			}



		case '5':
			if (login_time != 1) {
				cout << "You have to login first\n"
					<< "Return to main menu\n\n";
				break;
			}

			else {
				Logined_Person->OrderCondition();
				break;
			}

		case '6':
			if (login_time != 1) {
				cout << "You have to login first\n"
					<< "Return to main menu\n\n";
				break;
			}

			else {
				Logined_Person->Refund();
				break;
			}


		case '7':

			if (login_time != 1) {
				cout << "You have to login first\n"
					<< "Return to main menu\n\n";
				break;
			}

			else {
				Logined_Person->be_logout();
				login_time--;
				break;
			}


		case '0':
			cout << "End the prgram";
			return 0;
			break;

		}

	}
}



void SignUp() {

	string Input_ID;
	int Input_PW;
	int Input_Money;

	while (true) {
		cout << "Input your ID(0-to main menu) : ";
		cin >> Input_ID;

		// if ID is 0. return to main
		if (Input_ID == "0") {
			return;
		}


		if (!Person::Check_Existing_ID(Input_ID)) {
			Person::TotalPersonNum++;
			Person::add_New_ID(Input_ID);
			cout << "Input your password : ";
			cin >> Input_PW;
			Person::add_New_PW(Input_PW);
			cout << "Input your total money : ";
			cin >> Input_Money;
			Person::add_New_Money(Input_Money);
			cout << "\n\nWelcome, " << Input_ID << endl;


			return;
		}
		else {
			cout << "Duplicated user id\n\n";
		}
	}
}

Person* Login(string login_id, Person AllPerson_list[]) {

	int Input_PW;
	Person* Person_to_login;

	while (true) {
		// Get Password
		cout << "Input your password : ";
		cin >> Input_PW;

		// ID matches with right Password
		if (Person::Check_IDPW_Matching(login_id, Input_PW)) {

			Person_to_login = new Person(login_id, Input_PW, Person::getMoney(Person::get_signedup_order(Input_ID)));

			cout << "\nWelcome, " << login_id << "\n\n";
			Person_to_login->be_logined();
			return Person_to_login;
		}

		// prompt user to write correct password
		else {
			cout << "Wrong password!\n";
			break;
		}

	}
}



void ShowMenu() {
	cout << "----------Mcdonalds Menu----------\n"
		<< "1. Hamburger - 1000\n"
		<< "2. Cheeseburger - 1500\n"
		<< "3. Big Mac - 3000\n"
		<< "4. Quarter Pounder Burger - 4000\n"
		<< "5. Double Quarter Pounder - 5000\n"
		<< "6. Fries - 1500\n"
		<< "7. Chicken McNuggets - 2000\n"
		<< "8. Coke - 1500\n\n";

}
