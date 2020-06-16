#include <Windows.h>
#include <conio.h>

void mainMenu();
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
  cout << "3 - Stwórz konto\n\n";
  cout << "Aby wyjść wprowadź dowolny inny znak\n";
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

void userWindow(User user) {
    cleaner();
    cout << "-----ZALOGUJ-----\n";
    cout << "Witaj: " << user.getImie() << " " << user.getNazwisko() << endl;

}

void loginWindow(){
  cleaner();
cout << "-----ZALOGUJ-----\n\n";
  cout << "Wprowadź login\n";
  string login;
  cin >> login;

  cout << "Wprowadź hasło\n";
  string haslo;
  cin >> haslo;

  User user = FileSystem::loadUser(login);
  if (user.passwordCheck(haslo) == true) {
      userWindow(user);
  }
  else
  {
      cleaner();
      cout << "\n!!! PODANO NIEPRAWIDŁOWE HASŁO LUB LOGIN !!! \n";
      cout << "\n Wciśnij ESC aby powrócić do menu głównego\n Aby ponownie podjąć próbę logowania, wciśnij inny klawisz\n";
      loginWindowExit();
      loginWindow();
  }
}


void mainMenuFunction(){
  int input;
  cin >> input;

 while(cin.fail()) {
      // cout << "Error" << endl;
       cin.clear();
       cin.ignore(256,'\n');
       cin >> input;
    }
   
  switch (input) {
	case 1:
        cleaner();
		loginWindow();
		break;
	
  case 2:
        cleaner();
		coutExchangeRates(exchangeRates);
        cout << "\n Aby powrócić kliknij dowolny przycisk\n";
        _getch();
        mainMenuText();
        mainMenuFunction();
      
  
  case 3:
        cleaner();
        FileSystem::createUser();
    break;

  default:
		mainMenu();
    break;
  }
}

void mainMenu(){
  mainMenuText();
  mainMenuFunction();
}