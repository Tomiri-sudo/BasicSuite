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

void printContactFile(int index) {
    string fileName = to_string(index) + ".txt";
    ifstream file(fileName);
    
    if (file.is_open()) {
        string line;
        cout << CYAN << "--- Contact #" << index << " ---" << RESET << endl;
        while (getline(file, line)) {
            cout << line << endl;
        }
        cout << endl;
        file.close();
    }
}


int main() {
    // Magic step to make colors work seamlessly on Windows
    enableANSIColors();

    string newContactName, newContactEmail, newContactPhoneNumber, contactCountStr;
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
	    cout << "Enter contact phone number: ";
            getline(cin, newContactPhoneNumber);
            cout << "Enter e-mail address: ";
            getline(cin, newContactEmail);

            contactCount++;
            // 3. Increment and save new count
            contactCount++;
            
            // Loop forward if a file with this number somehow already exists
            // This prevents accidentally overwriting old data!
            while (fileExists(to_string(contactCount) + ".txt")) {
                contactCount++;
            }

            ofstream countWriter("contact_count.txt");
            countWriter << contactCount;
            countWriter.close();

            // 4. Create the unique contact file safely
            string fileName = to_string(contactCount) + ".txt";
            ofstream contactFile(fileName);
            contactFile << "Name: " << newContactName << "\n";
            contactFile << "Phone: " << newContactPhoneNumber << "\n";
            contactFile << "Email: " << newContactEmail << "\n";
            contactFile.close();

            // Success message in green
            cout << GREEN << "✔ Saved " << newContactName << " to your contacts!" << RESET << endl;
            break;
        }
        case '2': {
            int totalContacts = 0;
            ifstream countReader("contact_count.txt");
            
            // Try to read how many contacts we have total
            if (countReader) {
                countReader >> totalContacts;
                countReader.close();
            }

            // If the file doesn't exist or count is 0
            if (totalContacts == 0) {
                cout << YELLOW << "ℹ Your contacts book is empty!" << RESET << endl;
            } else {
                cout << BOLD << GREEN << "\nShowing " << totalContacts << " contact(s):\n" << RESET << endl;
                
                // Loop through from 1 to the exact count of contacts
                for (int i = 1; i <= totalContacts; i++) {
                    printContactFile(i);
                }
            }
            break;
        }

        default:
            // Error message in red
            cout << RED << "✖ Invalid choice." << RESET << endl;
    }

    return 0;
}
