#include <iostream>
#include <cmath>

using namespace std;

double A, B;

void inputDouble() {
	system("clear");
	cout << "scegli il primo numero" << endl;
	cin >> A;
	cout << "scegli il secondo num." << endl;
	cin >> B;
}

void inputSingle() {
	system("clear");
	cout << "scegli un numero" << endl;
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
		cout << "non puoi dividere per ";
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

	system("clear");
	cout << "scegli cosa fare:" << endl;
	cout << "-----------------" << endl;
	cout << " 1. A + B        " << endl;
	cout << " 2. A - B        " << endl;
	cout << " 3. A × B        " << endl;
	cout << " 4. A ÷ B        " << endl;
	cout << " 5. √A           " << endl;
	cout << " 6. A²           " << endl;
	cout << " 7. sin(A)       " << endl;
	cout << " 8. cos(A)       " << endl;
	cout << " 9. tan(A)       " << endl;
	cout << "-----------------" << endl;
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
		default: {cout << "la scelta non è valida." << endl; break;}
	}
	return 0;
}
