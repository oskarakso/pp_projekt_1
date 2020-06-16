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
  string getNazwisko() {
      return this->naziwsko;
  }

};

#endif