#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>

// Windows-specific header for enabling ANSI colors
#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

using namespace std;

// --- COLOR DEFINITIONS ---
const string RESET   = "\033[0m";
const string RED     = "\033[31m";
const string GREEN   = "\033[32m";
const string YELLOW  = "\033[33m";
const string BLUE    = "\033[34m";
const string CYAN    = "\033[36m";
const string BOLD    = "\033[1m";

inline bool fileExists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

// Function to enable ANSI escape codes on Windows
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

int main() {
    // Magic step to make colors work seamlessly on Windows
    enableANSIColors();

    string newContactName, newContactEmail, contactCountStr;
    int contactCount = 0;
    char choice;

    // Added bold and cyan to the welcome message
    cout << BOLD << CYAN << "Welcome to your contacts book!\n" << RESET;
    cout << "Choose your operation:\n -> '1' to " << GREEN << "Create New Contact" << RESET << "\n -> '2' to " << BLUE << "List All Contacts" << RESET << "\n";
    cin >> choice;
    cin.ignore(); 

    switch (choice) {
        case '1': {
            ifstream countReader("contact_count.txt");
            if (!countReader) {
                contactCount = 0;
            } else {
                countReader >> contactCount;
                countReader.close();
            }

            cout << "Enter contact name: ";
            getline(cin, newContactName); 
            cout << "Enter e-mail address: ";
            getline(cin, newContactEmail);

            contactCount++;
            ofstream countWriter("contact_count.txt");
            countWriter << contactCount;
            countWriter.close();

            string fileName = to_string(contactCount) + ".txt";
            ofstream contactFile(fileName);
            contactFile << "Name: " << newContactName << "\n";
            contactFile << "Email: " << newContactEmail << "\n";
            contactFile.close();

            // Success message in green
            cout << GREEN << "✔ Contact saved as " << fileName << RESET << endl;
            break;
        }
        case '2':
            // Info message in yellow
            cout << YELLOW << "ℹ List functionality coming soon!" << RESET << endl;
            break;
        default:
            // Error message in red
            cout << RED << "✖ Invalid choice." << RESET << endl;
    }

    return 0;
}
