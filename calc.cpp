#include <iostream>
#include <cmath>

#ifdef _WIN32
    #include <windows.h> // Needed for Windows ANSI activation
#endif

using namespace std;

// --- CROSS-PLATFORM COLOR CONFIG ---
const string RESET   = "\033[0m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";

void enableANSIColors() {
#ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) return;
    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) return;
    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    SetConsoleMode(hOut, dwMode);
#endif
}

// cross-platform compatible system clear
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

double A, B;

void inputDouble() {
        system(CLEAR_SCREEN);
        cout << "choose the first number → " << CYAN;
        cin >> A;
        cout << RESET << "choose the second number → " << CYAN;
        cin >> B;
        cout << RESET;
}

void inputSingle() {
        system(CLEAR_SCREEN);
        cout << "choose a number → " << CYAN;
        cin >> A;
        cout << RESET;
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
                cout << RED << "you cannot divide by " << RESET;
                return 0;
        }
}

// FIXED: Changed from recursive sqrt(num1) to std::sqrt(num1) to prevent crash
double sqrt(double num1) {
        return std::sqrt(num1);
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
        enableANSIColors(); // Activate Windows terminal color processing
        
        short unsigned int sceltaA, sceltaB;

        system(CLEAR_SCREEN);
        cout << BOLD << CYAN << "choose your operation:" << RESET << endl;
        cout << CYAN << "----------------------" << RESET << endl;
        cout << " 1. A + B             " << endl;
        cout << " 2. A - B             " << endl;
        cout << " 3. A × B             " << endl;
        cout << " 4. A ÷ B             " << endl;
        cout << " 5. √A                " << endl;
        cout << " 6. A²                " << endl;
        cout << " 7. sin(A)            " << endl;
        cout << " 8. cos(A)            " << endl;
        cout << " 9. tan(A)            " << endl;
        cout << CYAN << "----------------------" << RESET << endl;
        cout << "1/2/3/4/5/6/7/8/9 → " << YELLOW;
        cin >> sceltaA;
        cout << RESET;

        // Visual helper for the output
        cout << BOLD << GREEN << "Result: " << RESET;

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
                default: {cout << RED << "your choice is not valid." << RESET << endl; break;}
        }
        return 0;
}
