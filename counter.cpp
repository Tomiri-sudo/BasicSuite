#include <iostream>
#include <string>
#include <conio.h> //write input easily (no pressing enter required)
using namespace std;

// cross-platform compatible system clear (same as in calculator)
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif


//now a cross-platform compatible system pause

#ifdef _WIN32
    #define PAUSE "PAUSE"
#else
    #define prompt "Press Enter to continue..."
    #define PAUSE "read -p prompt"
#endif

int main() {
    double count = 0;
    char choice;
    while (choice != 'c') {
        system(CLEAR_SCREEN);
        cout << "-----------------------" << endl;
        cout << count << endl << endl;
        cout << "-----------------------" << endl;
        cout << " '+' to increase count" << endl;
        cout << " '-' to decrease count" << endl;
        cout << "      'c' to exit" << endl;
        choice = _getch();

        //check user response
        switch (choice) {
            case '+': {
                count++;
                break;
            }
            case '-': {
                count--;
                break;
            }
        }
    }
    system(PAUSE);
    return 0;
}
