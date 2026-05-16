#include <iostream>
#include <string>

#ifdef _WIN32
    #include <conio.h> // write input easily (no pressing enter required)
    #include <windows.h> // Needed for Windows ANSI activation
#else
    #include <termios.h>
    #include <unistd.h>
#endif

using namespace std;

// --- CROSS-PLATFORM COLOR CONFIG ---
const string RESET   = "\033[0m";
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
    enableANSIColors(); // Activate Windows terminal color processing

    double count = 0;
    char choice = 0; // Fixed: uninitialized choice variable

    while (choice != 'c') {
        system(CLEAR_SCREEN);
        cout << CYAN << "-----------------------" << RESET << endl;
        cout << BOLD << YELLOW << " " << count << RESET << endl << endl;
        cout << CYAN << "-----------------------" << RESET << endl;
        cout << " '" << GREEN << "+" << RESET << "' to increase count" << endl;
        cout << " '" << YELLOW << "-" << RESET << "' to decrease count" << endl;
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
