#include <Windows.h>
#include <conio.h>

//Admin - lista użytkowników, mozliwośc usunięcia pliku, (edycji jego zasobów, danych -> zmienia plik na xxx_data i tworzy nowy)

void mainMenu();
void userWindow(User& user);
void cleaner() {
    system("cls");
}

int cinChecker(int x){
  if (cin.fail() == true){
    return x = 0;
  }
  else
    return x;
}

void mainMenuText(){
  cleaner();
  cout << "-----MENU-----"<<endl<<endl;
  cout << "1 - Zaloguj\n";
  cout << "2 - Sprawdz kursy wymiany walut\n";
  cout << "3 - Stworz konto\n\n";
  cout << "Aby wyjsc wprowadz dowolny inny znak\n";
}
void loginWindowExit() {
    _getch();
    if (GetKeyState(VK_ESCAPE) & 0x8000)
    {
        mainMenu();
    }
    else
        ;
}

void balancePrint(User& user) {
    cout << "\nTwoje konta i ich balansy:\n";
    for (int i = 0; i < user.getStanKonta().size(); i++) { // printing the 2D vector.
        for (int j = 0; j < user.getStanKonta()[i].size(); j++)
            cout << user.getStanKonta()[i][j] << " ";
        cout << endl;
    }
}
void currencyPrint(User& user) {
    for (int i = 0; i < user.getStanKonta().size(); i++) { // printing the 2D vector.
            cout << user.getStanKonta()[i][0] << " ";
    }
}

void exchangeWindow(User& user) {
    cout << "-----KANTOR-----\n\n";
       
}

string getReciver() {
    string pesel;

    cout << "Wprowadz numer pesel odbiorcy: ";
    cin >> pesel;

    if (Utils::fileExists("./users/" + pesel) == false) {
        cout << "\nUzytkownika nie znaleziono\n";
        cout << "Czy ponowic? (Tak - enter | Nie - ESC)";
        _getch();
        if (GetKeyState(VK_ESCAPE) & 0x8000) {
            return pesel = "x";
        }
        else {
            cleaner();
            cout << "-----NOWY PRZELEW-----\n\n";
            getReciver();
        }
    }
    else return pesel;
}

void transferWindow(User& user) {
    string waluta;
    long long value;
    string reciver;
    cout << "-----NOWY PRZELEW-----\n\n";
    cout << "Dostępne waluty: \n";
    currencyPrint(user);
    cout << "\n\nAby wykonac przelew wcisnij Enter\n";
    cout << "Aby powrocic wcisnij ESC\n";
    _getch();
    if (GetKeyState(VK_ESCAPE) & 0x8000) {
        cleaner();
        userWindow(user);
    }
 
    else if (GetKeyState(VK_RETURN) & 0x8000) {
        string reciver = getReciver();
        string pass;
        if (reciver.length() < 2) {
            cleaner();
            transferWindow(user);
        }
        else if (reciver == user.getPesel()) {
            cout << "Nie mozna robic przelewow do siebie!";
            _getch();
            cleaner();
            transferWindow(user);
        }
        else if (reciver.length() == 11) {
        cout << "Wprowadz walute: ";
        cin >> waluta;
        cout << "Wprowadz wartosc: ";
        cin >> value;
        cleaner();
        cout << "\n Wykonasz teraz przelew do uzytkownika: " << reciver;
        cout << "\n Na kwote: " << waluta << " "  << value;
        cout << "\n Wprowadz haslo aby potwierdzic: ";
        cin >> pass;
        if (user.passwordCheck(pass) == false) {
            cout << "Zle haslo";
            _getch;
            cleaner();
            transferWindow(user);
        }
        else {
            User user_reciver = FileSystem::loadUser(reciver);
            user.przelew(user_reciver, waluta, value);
            cout << "Wykonywanie....";
            FileSystem::saveUser(user);
            Sleep(2000);
            cout << "50%.....";
            FileSystem::saveUser(user_reciver);
            cout << "99%.....";
            Sleep(500);
            cout << "\nPrzelew wykonany!";
            Sleep(4000);
            userWindow(user);
             }
        }
        else {
            cleaner();
            transferWindow(user);
        }
     }
 }
void detailsWindow(User& user) {
   cout << "Oto twoje dane: \n";
   cout << "Czy admin: " << user.getAdmin();
   cout << "\nimie: " << user.getImie();
   cout << "\nnazwisko: " << user.getNazwisko();
   cout << "\npesel: " << user.getPesel();
   cout << "\nnumerDowodu: " << user.getNumerDowodu();
   cout << "\ndataUrodzenia: " << user.getDataUrodzenia();
   cout << "\nhaslo: " << user.getHaslo();
   cout << "\n\nAby powrocic wcisnij ESC\n";
   _getch();
   if (GetKeyState(VK_ESCAPE) & 0x8000) {
       cleaner();
       cleaner();
       userWindow(user);
   }
}
void userWindow(User& user) {
    cleaner();
    cout << "-----TWOJE KONTO-----\n";
    cout << "Witaj: " << user.getImie() << " " << user.getNazwisko() << endl;
    cout << "1 - Kantor\n";
    cout << "2 - Przelewy\n";
    cout << "3 - Moje dane\n\n";
    balancePrint(user);
    cout << "\n\nAby sie wylogowac wcisnij ESC";
    _getch();
    if (GetKeyState(0x31) & 0x8000) {
        cleaner();
        exchangeWindow(user);
    }
    else if (GetKeyState(0x32) & 0x8000) {
        cleaner();
        transferWindow(user);
    }
    else if (GetKeyState(0x33) & 0x8000) {
        cleaner();
        detailsWindow(user);
    }
    else if (GetKeyState(VK_ESCAPE) & 0x8000) {
        cleaner();
        cout << "Pomyslnie wylogowano";
        mainMenu();
    }
    
}

void loginWindow(){
  cleaner();
cout << "-----ZALOGUJ-----\n\n";
  cout << "Wprowadz login\n";
  string login;
  cin >> login;

  cout << "Wprowadz haslo\n";
  string haslo;
  cin >> haslo;

  User user = FileSystem::loadUser(login);

  if (user.passwordCheck(haslo) == true) {
      userWindow(user);
  }
  else
  {
      cleaner();
      cout << "\n!!! PODANO NIEPRAWIDLOWE HASLO LUB LOGIN !!! \n";
      cout << "\n Wcisnij ESC aby powrocic do menu głownego\n Aby ponownie podjac probr logowania, wcisnij inny klawisz\n";
      loginWindowExit();
      loginWindow();
  }
}


void mainMenuFunction() {
    _getch();
    if (GetKeyState(0x31) & 0x8000) {
        cleaner();
        loginWindow();
    }
    else if (GetKeyState(0x32) & 0x8000) {
        cleaner();
        coutExchangeRates(exchangeRates);
        cout << "\n Aby powrocic kliknij dowolny przycisk\n";
        _getch();
        mainMenuText();
        mainMenuFunction();
    }
    else if (GetKeyState(0x33) & 0x8000) {
        cleaner();
        if (FileSystem::createUser() == true) {
            cout << "Pomyslnie utworzono uzytkownika! \n";
            cout << "Aby powrocić kliknij dowolny przycisk \n";
            _getch();
            mainMenu();
        }
        else {
            cout << "\nAby powrocic kliknij dowolny przycisk \n";
            _getch();
            mainMenu();
        }

    }
    else {
        cleaner();
        cout << "Do widzenia!";
        _exit;
    }
}

void mainMenu(){
  mainMenuText();
  mainMenuFunction();
}