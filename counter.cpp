#include <iostream>
#include <string>

#ifdef _WIN32
    #include <conio.h> // write input easily (no pressing enter required)
#else
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

// cross-platform compatible system clear (same as in calculator)
#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

// cross-platform compatible system pause
#ifdef _WIN32
    #define PAUSE "PAUSE"
#else
    #define prompt "Press Enter to continue..."
    #define PAUSE "read -p prompt"
#endif

// cross-platform getch() function
#ifdef _WIN32
    #define GETCH _getch
#else
    int getch() {
        struct termios oldt, newt;
        int ch;
        tcgetattr(STDIN_FILENO, &oldt);
        newt = oldt;
        newt.c_lflag &= ~(ICANON | ECHO);
        tcsetattr(STDIN_FILENO, TCSANOW, &newt);
        ch = getchar();
        tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
        return ch;
    }
    #define GETCH getch
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
        choice = GETCH();

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