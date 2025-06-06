#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

const string FILE_NAME = "passwords5.txt";
const string JOHN_LIST_PATH = "~/usr/share/wordlists/john.lst";
const string WIFITE_LIST_PATH = "~/usr/share/wordlists/wifite.txt";
const string ROCKYOU_LIST_PATH = "~/usr/share/wordlists/rockyou.txt";
const string CHARACTERS = "abcdefghijklmnopqrstuvwxyz0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ@Ł!&#$/<>*ł?£&{}[]€;:-_÷^";

// Učitaj prethodno generirane lozinke s brojačem
unordered_map<string, int> readPasswords() {
    unordered_map<string, int> passwords;
    ifstream file(FILE_NAME);
    if (file.is_open()) {
        string password;
        int count;
        while (file >> password >> count) {
            passwords[password] = count;
        }
        file.close();
    }
    return passwords;
}

// Zapiši sve lozinke i broj generiranja u datoteku
void writePasswords(const unordered_map<string, int>& passwords) {
    ofstream file(FILE_NAME);
    if (file.is_open()) {
        for (const auto& entry : passwords) {
            file << entry.first << " " << entry.second << "\n";
        }
        file.close();
    }
}

// Učitaj wordlist i zapamti sve lozinke koje se ne smiju koristiti
unordered_set<string> readWordlist(const string& path) {
    unordered_set<string> blacklist;
    ifstream file(path);
    if (file.is_open()) {
        string word;
        while (getline(file, word)) {
            blacklist.insert(word);
        }
        file.close();
    }
    return blacklist;
}

// Generiraj slučajnu lozinku
string generatePassword(int length) {
    string password;
    for (int i = 0; i < length; i++) {
        password += CHARACTERS[rand() % CHARACTERS.length()];
    }
    return password;
}

// Glavna funkcija aplikacije
void passwordGenerator() {
    srand(time(0));
    unordered_map<string, int> passwords = readPasswords();
    unordered_set<string> blacklist;

    int choice;
    cout << "\n================== Password Generator App ==================\n\n";
    cout << "Select a wordlist to load:\n";
    cout << "1. john.lst\n";
    cout << "2. wifite.txt\n";
    cout << "3. rockyou.txt\n";
    cout << "4. all (john + wifite + rockyou)\n";
    cout << "Enter your choice (1/2/3/4): ";
    cin >> choice;

    if (choice == 1) {
        blacklist = readWordlist(JOHN_LIST_PATH);
    } else if (choice == 2) {
        blacklist = readWordlist(WIFITE_LIST_PATH);
    } else if (choice == 3) {
        blacklist = readWordlist(ROCKYOU_LIST_PATH);
    } else if (choice == 4) {
        unordered_set<string> johnBlacklist = readWordlist(JOHN_LIST_PATH);
        unordered_set<string> wifiteBlacklist = readWordlist(WIFITE_LIST_PATH);
        unordered_set<string> rockyouBlacklist = readWordlist(ROCKYOU_LIST_PATH);
        blacklist.insert(johnBlacklist.begin(), johnBlacklist.end());
        blacklist.insert(wifiteBlacklist.begin(), wifiteBlacklist.end());
        blacklist.insert(rockyouBlacklist.begin(), rockyouBlacklist.end());
    } else {
        cout << "Invalid choice. Loading no wordlist.\n";
    }

    // Glavna petlja za neograničeno generiranje
    while (true) {
        int option;
        cout << "\n\nSelect an option:\n";
        cout << "1. Generate a password manually\n";
        cout << "2. Generate a password automatically and avoid wordlist\n";
        cout << "3. Scan and generate new passwords (completely unique)\n";
        cout << "0. Exit\n";
        cout << "Enter your choice: ";
        cin >> option;

        if (option == 0) {
            cout << "Exiting program...\n";
            break;
        }

        switch (option) {
            case 1: {
                int passlen;
                cout << "Enter the length of password (8-15): ";
                cin >> passlen;

                if (cin.fail() || passlen < 8 || passlen > 15) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nPassword length should be between 8 and 15 characters.\n";
                    break;
                }

                string password;
                do {
                    password = generatePassword(passlen);
                } while (blacklist.find(password) != blacklist.end());

                if (passwords.find(password) != passwords.end()) {
                    passwords[password]++;
                    cout << "\n\nYour password is: " << password;
                    cout << "\nThis password has been generated " << passwords[password] << " times.";
                } else {
                    passwords[password] = 1;
                    cout << "\n\nYour password is: " << password;
                }
                break;
            }

            case 2: {
                int passlen;
                cout << "Enter the length of password (8-15): ";
                cin >> passlen;

                if (cin.fail() || passlen < 8 || passlen > 15) {
                    cin.clear();
                    cin.ignore(10000, '\n');
                    cout << "\nPassword length should be between 8 and 15 characters.\n";
                    break;
                }

                string password;
                do {
                    password = generatePassword(passlen);
                } while (blacklist.find(password) != blacklist.end());

                if (passwords.find(password) != passwords.end()) {
                    passwords[password]++;
                    cout << "\n\nYour password is: " << password;
                    cout << "\nThis password has been generated " << passwords[password] << " times.";
                } else {
                    passwords[password] = 1;
                    cout << "\n\nYour password is: " << password;
                }
                break;
            }

            case 3: {
                string password;
                bool unique = false;
                while (!unique) {
                    password = generatePassword(rand() % 8 + 8);
                    if (passwords.find(password) == passwords.end() && blacklist.find(password) == blacklist.end()) {
                        unique = true;
                    }
                }

                passwords[password] = 1;
                cout << "\n\nYour unique password is: " << password;
                break;
            }

            default:
                cout << "Invalid option!\n";
                break;
        }

        // Spremanje svih lozinki u datoteku nakon svake operacije
        writePasswords(passwords);
    }
}

int main() {
    passwordGenerator();
    return 0;
}
