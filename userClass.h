#ifndef USERCLASS
#define USERCLASS

#include <vector>

using namespace std;

/*
  StanKonta prawdziwy = StanKonta/100
*/

class User {
private:
    int admin = 0;
    string imie;
    string naziwsko;
    string pesel;
    string numerDowodu;
    string dataUrodzenia;
    string haslo;
    //2d vector of strings
    vector<vector<string>> stanKonta;

public:
    User(int admin, string imie, string naziwsko, string pesel, string numerDowodu,
        string dataUrodzenia, string haslo, vector<vector<string>> stanKonta)
        : admin(admin), imie(imie), naziwsko(naziwsko), dataUrodzenia(dataUrodzenia),
        numerDowodu(numerDowodu), pesel(pesel), haslo(haslo), stanKonta(stanKonta) {};
    friend void test(User& user);
    bool passwordCheck(string password) {
        if (password == this->haslo)
            return true;
        else
            return false;
    }
    string getImie() {
        return this->imie;
    } 
    int getAdmin() {
        return this->admin;
    }
    string getNazwisko() {
        return this->naziwsko;
    }
    string getPesel() {
        return this->pesel;
    };
    string getNumerDowodu() {
        return this->numerDowodu;
    };
    string getDataUrodzenia() {
        return this->dataUrodzenia;
    };
    string getHaslo() {
        return this->haslo;
    };
    vector<vector<string>> getStanKonta() {
        return this->stanKonta;
    };

    //Debug
    void StanKonta() {
        for (int i = 0; i < this->stanKonta.size(); i++) {
            cout << this->stanKonta[i][0] << endl;
            cout << this->stanKonta[i][1] << endl;
        };
    };

    bool przelew(User& user, string waluta, long long value) {
        //Find waluta in stanKonta vector for this user
        for (int i = 0; i < this->stanKonta.size(); i++) {
            if (this->stanKonta[i][0] == waluta) {
                if ((stoll(this->stanKonta[i][1], NULL, 0) - value) < 0) {
                    cout << "Brak wystarczaj¹cych œrodków na t¹ operacjê." << endl;
                    return false;
                };
                //Find waluta in stanKonta vector for given user
                for (int j = 0; j < user.stanKonta.size(); j++) {
                    //If there is a waluta entry in stanKonta of given user
                    if (user.stanKonta[j][0] == waluta) {
                        this->stanKonta[i][1] = to_string(stoll(this->stanKonta[i][1], NULL, 0) - value);
                        user.stanKonta[j][1] = to_string(stoll(user.stanKonta[j][1], NULL, 0) + value);
                        return true;
                    };
                };
                //If there is no entry resize given user vector and add entry + value on 2d vector
                int temp = user.stanKonta.size();
                user.stanKonta.resize(temp + 1, vector<string>(2, ""));
                this->stanKonta[i][1] = to_string(stoll(this->stanKonta[i][1], NULL, 0) - value);
                user.stanKonta[temp][0] = waluta;
                user.stanKonta[temp][1] = to_string(value);
                return true;
            };
        };
        cout << "Brak œrodków w tej walucie." << endl;
        return false;
    };


};

#endif
