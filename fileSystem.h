#ifndef FILESYSTEM
#define FILESYSTEM

// C++ main libs
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <cctype>

// Extra
#include "./extra/checkDate.h"

using namespace std;

namespace Utils {
vector<string> split(const string& s, const string& delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;
    while ((pos_end = s.find(delimiter, pos_start)) != string::npos) {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    };
    res.push_back(s.substr(pos_start));
    return res;
};
// Check for digits in string
bool isDigits(const string& str)
{
    return str.find_first_not_of("0123456789") == string::npos;
};
// Check for chars in string
bool isChars(const string& str)
{
    return str.find_first_not_of(
               "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ")
        == string::npos;
};
// Check if given file exists
bool fileExists(const string& name)
{
    ifstream f(name.c_str());
    return f.good();
};
//validateID
bool validateID(const string& numer)
{
    if (numer.length() == 0 || numer.length() != 9)
        return false;
    if (!(isChars(numer.substr(0, 3))))
        return false;
    if (!(isDigits(numer.substr(3, 6))))
        return false;
    string letterValues = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    int suma = 0;
    suma = 7 * letterValues.find(numer[0]) + 3 * letterValues.find(numer[1]) + 1 * letterValues.find(numer[2]) + 7 * letterValues.find(numer[4]) + 3 * letterValues.find(numer[5]) + 1 * letterValues.find(numer[6]) + 7 * letterValues.find(numer[7]) + 3 * letterValues.find(numer[8]);
    suma %= 10;
    if (suma != letterValues.find(numer[3]))
        return false;
    return true;
};
};

/*
 *  User format:
 *  ADMIN:IMIE:NAZWISKO:PESEL:NR_DOWODU:DATA_URODZENIA:HASLO:WALUTA1:STAN_KONTA:WALUTA2:STAN_KONTA2:(...)
 *
 */

namespace FileSystem {

/*
 *  Save user function
 *
 */
 void saveUser(
              const int admin,
              const string& imie,
              const string& naziwsko,
              const string& pesel,
              const string& numerDowodu,
              const string& dataUrodzenia,
              const string& haslo,
              vector<vector<string>> stanKonta) {
        ofstream userFile("./users/" + pesel);
        if (userFile.is_open()) {
                userFile << to_string(admin) + ":" + imie + ":" + naziwsko + ":" + pesel + ":" + numerDowodu +
                        ":" + dataUrodzenia + ":" + haslo;
                //StanKonta handler
                for(int i = 0; i < stanKonta.size(); i++) {
                  userFile << ":" + stanKonta[i][0];
                  for(int j = 0; j < stanKonta[i].size() - 1; j++) {
                    userFile << ":" + stanKonta[i][1];
                  };
                };
                // Close file
                userFile.close();
        } else {
                throw runtime_error("Error opening file.");
        };
};

/*
 *  Create user function
 */
bool createUser()
{
    // Pesel logic
    cout << "Podaj pesel: " << endl;
    string pesel;
    while (getline(cin, pesel)) {
        if (Utils::isDigits(pesel)) {
            try {
                stoll(pesel, NULL, 0);
                // Check pesel length
                if (pesel.length() == 11) {
                    // Check if user already exists in db
                    if (Utils::fileExists("./users/" + pesel)) {
                        cout << "Uzytkownik juz istnieje." << endl;
                        return false;
                    };
                    // Pass if there is no user with given pesel
                    break;
                }
                else {
                    cout << "Numer pesel jest za krotki." << endl;
                    return false;
                };
            }
            catch (...) {
                cout << "Blad przy konwersji peselu na long long." << endl;
                return false;
            };
        }
        else {
            cout << "Pesel musi zawierac tylko cyfry." << endl;
            return false;
        };
    };

    // Imie, nazwisko logic
    string imie;
    cout << "Podaj imie: " << endl;
    while (getline(cin, imie)) {
        if (Utils::isChars(imie) && imie.length() > 2) {
            //Imie formating
            for (int i = 0; i < imie.length(); i++) {
                if (i == 0) {
                    imie[0] = toupper(imie[0]);
                }
                else {
                    imie[i] = tolower(imie[i]);
                };
            };
            break;
        }
        else {
            cout << "Imie jest za krotkie." << endl;
            return false;
        };
    };
    string naziwsko;
    cout << "Podaj nazwisko: " << endl;
    while (getline(cin, naziwsko)) {
        if (Utils::isChars(naziwsko) && naziwsko.length() > 2) {
            //Nazwisko formating
            for (int i = 0; i < naziwsko.length(); i++) {
                if (i == 0) {
                    naziwsko[0] = toupper(naziwsko[0]);
                }
                else {
                    naziwsko[i] = tolower(naziwsko[i]);
                };
            };
            break;
        }
        else {
            cout << "Nazwisko za krotkie." << endl;
            return false;
        };
    };

    // dataUrodzenia logic
    string dataUrodzenia;
    cout << "Podaj date urodzenia(Format: DD/MM/YYYY): " << endl;
    while (getline(cin, dataUrodzenia)) {
        vector<string> holder = Utils::split(dataUrodzenia, "/");
        if (holder.size() == 3) {
            // Check for characters
            if (Utils::isDigits(holder[0]) && Utils::isDigits(holder[1]) && Utils::isDigits(holder[2])) {
                // Holder for values
                int* data = new int[3];
                try {
                    data[0] = stoi(holder[0]);
                    data[1] = stoi(holder[1]);
                    data[2] = stoi(holder[2]);
                }
                catch (...) {
                    cout << "Blad przy konwersji daty na int." << endl;
                    return false;
                };
                // Verify date
                if (isValidDate(data[0], data[1], data[2])) {
                    delete[] data;
                    break;
                }
                else {
                    cout << "Data jest niepoprawna." << endl;
                    return false;
                };
            }
            else {
                cout << "Data powinna skladac sie tylko z cyfr." << endl;
                return false;
            };
        }
        else {
            cout << "niepoprawny format daty." << endl;
            return false;
        };
    };

    //numerDowodu logic
    string numerDowodu;
    cout << "Podaj numer dowodu osobistego(Format: ABS123456): " << endl;
    while (getline(cin, numerDowodu)) {
        for (int i = 0; i < numerDowodu.length(); i++) {
            numerDowodu[i] = toupper(numerDowodu[i]);
        };
        if (Utils::validateID(numerDowodu)) {
            break;
        }
        else {
            cout << "Numer dowodu jest niepoprawny." << endl;
            return false;
        };
    };

    string haslo;
    cout << "Podaj haslo: " << endl;
    while (getline(cin, haslo)) {
        if (haslo.length() > 5) {
            break;
        }
        else {
            cout << "Haslo jest zbyt krotkie." << endl;
            return false;
        };
    };

    // Save user to db
    try {
        vector<vector<string>> temp;
        temp.resize(1, vector<string>(2, ""));
        temp[0][0] = "PLN";
        temp[0][1] = "0";
        saveUser(0, imie, naziwsko, pesel, numerDowodu, dataUrodzenia, haslo, temp);
    }
    catch (const exception& e) {
        cout << e.what() << endl;
        return false;
    };

    return true;
};

/*
 *  Load user function
 *
 */
User loadUser(const string& pesel) {
        ifstream userFile("./users/" + pesel);
        if (userFile.is_open()) {
                string holder;
                getline(userFile, holder);
                // Read user data
                string delimiter = ":";
                vector<string> userData = Utils::split(holder, delimiter);
                userFile.close();
                // Handle waluty tj. od 7 pozycji w stringu
                vector<vector<string>> stanKontaData;
                stanKontaData.resize(((userData.size() - 7) / 2), vector<string>(2, ""));
                int temp = 0;
                for(int i = 0; i < ((userData.size() - 7) / 2); i++) {
                  stanKontaData[i][0] = userData[temp + 7];
                  temp++;
                  stanKontaData[i][1] = userData[temp + 7];
                  temp++;
                };
                return User(stoi(userData[0]), userData[1], userData[2], userData[3], userData[4], userData[5], userData[6], stanKontaData);
                cout << "Zalogowano";
        } else {
                throw runtime_error("Blad przy otwieraniu pliku.");
        };
};

};

#endif