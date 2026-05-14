#include <iostream>
#include <cmath>

using namespace std;

// cross-platform compatible system clear
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif


double A, B;

void inputDouble() {
	system(CLEAR_SCREEN);
	cout << "choose the first number → ";
	cin >> A;
	cout << "choose the second number → ";
	cin >> B;
}

void inputSingle() {
	system(CLEAR_SCREEN);
	cout << "choose a number → ";
        cin >> A;
}




double sum(double num1, double num2) {
	return (num1 + num2);
}

double sub(double num1, double num2) {
	return (num1 - num2);
}

double mul(double num1, double num2) {
	return (num1 * num2);
}

double div(double num1, double num2) {
	if (num2 != 0) {
		return (num1 / num2);
	} else {
		cout << "you cannot divide by ";
		return 0;
	}
}

double sqrt(double num1) {
	return sqrt(num1);
}

double pwr(double num1) {
	return num1 * num1;
}

double msin(double num1) {
	return std::sin(num1);
}

double mcos(double num1) {
	return std::cos(num1);
}

double mtan(double num1) {
        return std::tan(num1);
}

int main() {
	short unsigned int sceltaA, sceltaB;

	system(CLEAR_SCREEN);
	cout << "choose your operation:" << endl;
	cout << "----------------------" << endl;
	cout << " 1. A + B             " << endl;
	cout << " 2. A - B             " << endl;
	cout << " 3. A × B             " << endl;
	cout << " 4. A ÷ B             " << endl;
	cout << " 5. √A                " << endl;
	cout << " 6. A²                " << endl;
	cout << " 7. sin(A)            " << endl;
	cout << " 8. cos(A)            " << endl;
	cout << " 9. tan(A)            " << endl;
	cout << "----------------------" << endl;
	cout << "1/2/3/4/5/6/7/8/9 → ";
	cin >> sceltaA;

	switch (sceltaA) {
		case 1:  {inputDouble(); cout << sum(A, B) << endl; break;}
		case 2:  {inputDouble(); cout << sub(A, B) << endl; break;}
		case 3:  {inputDouble(); cout << mul(A, B) << endl; break;}
		case 4:  {inputDouble(); cout << div(A, B) << endl; break;}
		case 5:  {inputSingle(); cout << sqrt(A) << endl; break;}
		case 6:  {inputSingle(); cout << pwr(A) << endl; break;}
		case 7:  {inputSingle(); cout << msin(A) << endl; break;}
		case 8:  {inputSingle(); cout << mcos(A) << endl; break;}
		case 9:  {inputSingle(); cout << mtan(A) << endl; break;}
		default: {cout << "your choice is not valid." << endl; break;}
	}
	return 0;
}
