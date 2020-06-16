#include <iostream>
#include <fstream>
#include <string>

using namespace std;

string location = "./Data/exchangeRates.txt";

int exchangeRatesSize() {
	ifstream file(location);
	string line;
	long i;
	for (i = 0; getline(file, line); ++i);
	return i;
}

string** exchangeRatesGetTable(int rows) {
	int col = 2;
	int row = rows + 1;
	//create table
	string** table = new string * [row];
	for (int i = 0; i < row; i++) {
		table[i] = new string[col];
	}

	//push values from file to table
	ifstream inFile;
	inFile.open(location);
	string val1, val2;

	for (int i = 0; i < row - 1; i++) {
		getline(inFile, val1, ':'); // currency symbol
		getline(inFile, val2, '\n'); // rate
		table[i][0] = val1;
		table[i][1] = val2;
		//	cout << "symbol - " << val1 << " rate: " << val2 << endl; //debug values to cmd
	}
	inFile.close();
	return table;
}

void coutExchangeRates(string** exchangeRates) {
	cout << "Obecne kursy walut: " << endl;
	cout << "Symbol Waluty" << " - " << "Kurs wymiany na PLN" << endl;
	for (int i = 0; i < exchangeRatesSize(); i++) {
		cout << exchangeRates[i][0] << " - " << exchangeRates[i][1] << endl;
	}
}

string** exchangeRates = exchangeRatesGetTable(exchangeRatesSize());

/*
int main()
{
	//create table
	string** exchangeRates = exchangeRatesGetTable(exchangeRatesSize());
	//cout table
	coutExchangeRates(exchangeRates);
}
*/

