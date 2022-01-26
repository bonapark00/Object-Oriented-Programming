#include <iostream>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <cstring>  // for strlen() !! 
using namespace std;

/**********************/
/*******Problem 1******/
/**********************/
/* ID:     2020147519           */
/* NAME:     Jaeyeon Park         */
/**********************/

int main() {
    int loopNum;
    char dump[51]; // to ignore '\n' in first line

    ifstream infile("input1.txt");

    infile >> loopNum;
    infile.getline(dump, 51);

    for (int i = 0; i < loopNum; i++) {
        char inputString[51];
        
        // 한줄 한꺼번에 받기
        infile.getline(inputString, 51);
        
        // declare variables for counting
        int count_a = 0;
        int count_e = 0;
        int count_i = 0;
        int count_o = 0;
        int count_u = 0;


        // do count
        for (int j = 0; j < strlen(inputString); j++){
            if (inputString[j] == 'a') {
                count_a ++;
            }
            else if (inputString[j] == 'e') {
                count_e++;
            }
            else if (inputString[j] == 'i') {
                count_i++;
            }
            else if (inputString[j] == 'o') {
                count_o++;
            }
            else if (inputString[j] == 'u') {
                count_u++;
            }
        }

        // strlen은 char배열의 크기를 표시하는게 아니라
        // 배열에 등록되어있는 실제 알파벳 값만 리턴함
        // a[40] = {'a', 'b'}이면 2리턴함. 



        // output the result in alphabetic order.
        cout << count_a << " " << count_e << " " << count_i
            << " " << count_o << " " << count_u << endl;

    }
    infile.close();

    return 0;
}
