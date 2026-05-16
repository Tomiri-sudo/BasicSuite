#include <iostream>
#include <fstream>
#include <string>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

inline bool fileExists (const std::string& name) {
  struct stat buffer;
  return (stat (name.c_str(), &buffer) == 0);
}

int main() {
    string newContactName, newContactEmail, contactCountStr;
    int contactCount = 0;
    char choice;

    cout << "Welcome to your contacts book!\n";
    cout << "Choose your operation:\n -> '1' to Create New Contact\n -> '2' to List All Contacts\n";
    cin >> choice;
    cin.ignore(); // Clears the newline character after cin >> choice

    switch (choice) {
        case '1': {
            //check if file actually exists
            ifstream countReader("contact_count.txt");
            if (!countReader) {
                // File doesn't exist, so let's assume count is 0
                contactCount = 0;
            } else {
                countReader >> contactCount;
                countReader.close();
            }

            // 2. Get User Input
            cout << "Enter contact name: ";
            getline(cin, newContactName); // Allows spaces in names
            cout << "Enter e-mail address: ";
            getline(cin, newContactEmail);

            // 3. Increment and save new count
            contactCount++;
            ofstream countWriter("contact_count.txt");
            countWriter << contactCount;
            countWriter.close();

            // 4. Create the contact file (e.g., "1.txt", "2.txt")
            string fileName = to_string(contactCount) + ".txt";
            ofstream contactFile(fileName);
            contactFile << "Name: " << newContactName << "\n";
            contactFile << "Email: " << newContactEmail << "\n";
            contactFile.close();


            cout << "Contact saved as " << fileName << endl;
            break;
        }
        case '2':
            cout << "List functionality coming soon!" << endl;
            break;
        default:
            cout << "Invalid choice." << endl;
    }

    return 0;
}
