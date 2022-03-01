#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>
#include "Data_Base.h"

using namespace std;

//Проверка на валидность
bool is_number_char(char number[]) {
	for (int i = 0; i < 100; i++) {
		if ((char)number[i] != -52 && number[i] != '\0') {
			if (!((char)number[i] >= 48 && (char)number[i] <= 57 && number[i]))
				return false;
		}
		else
			return true;
	}
}
bool is_number_char(char number) {
	for (int i = 0; i < 100; i++) {
		if ((char)number != -52 && number != '\0') {
			if (!((char)number >= 48 && (char)number <= 57 && number))
				return false;
		}
		else
			return true;
	}
}

//Перевод в инт
int toInt(char number[]) {
	int number_of_digits = 0;

	for (int i = 0; number[i] != '\0'; i++) {
		if ((char)number[i] != -52) {
			number_of_digits++;
		}
	}

	if (number_of_digits == 1) {
		return ((char)(number[0] - 48));
	}
	if (number_of_digits == 2) {
		return ((char)(number[0] - 48) * 10 + (char)(number[1] - 48));
	}
	if (number_of_digits == 3) {
		return (((char)(number[0] - 48) * 100) + (((char)(number[1])) - 48) * 10 + (char)(number[2]) - 48);
	}
}
int toInt(char number) {
	return ((char)(number - 48));
}

//Проверка даты
bool check_date(string number) {
	
	if (number.length() < 10) return false;

	int days = ((char)(number[0]) - 48) * 10 + ((char)(number[1]) - 48);
	int month = ((char)(number[3]) - 48) * 10 + (char)(number[4]) - 48;
	int years = ((char)(number[6]) - 48) * 1000 + ((char)(number[7]) - 48) * 100 + ((char)(number[8]) - 48) * 10 + ((char)(number[9]) - 48);

	if (number[2] != '.' || number[5] != '.') {
		return false;
	}

	if (years > 1950 && years < 2022) {
		//Нечётные месяца первой половины года
		if (month < 8 && month > 0 && month % 2 != 0) {
			if (days <= 31) return true;//Янв., март, май, июль
		}
		//Нечётные месяца второй половины года
		if (month >= 8 && month <= 12 && month % 2 != 0)
			if (days <= 30) return true; //сент, нояб.
		//Четные месяца первой половины года
		if (month < 8 && month > 0 && month % 2 == 0) {
			if (month == 2 && days <= 28 && days > 0) return true;//Февраль
			if (days <= 30 && month != 2) return true;//апр., июнь
		}
		//Чётные месяца второй половины года
		if (month >= 8 && month <= 12 && month % 2 == 0) {
			if (days <= 31) return true;//авг, окт, дек.
		}
	}

	return false;
}

//Object of apartament
struct DataApartaments {
private:
	int counts_of_rooms;
	int storey;
	int area;
	int price;
	int ID;
	static int countElements;
	string date;
	string adress;
public:
	DataApartaments() {
		countElements++;
		ID = countElements;
		counts_of_rooms = 0;
		storey = 0;
		area = 0;
		price = 0;
		adress = "null";
		date = "xx.mm.yyyy";
	}

	DataApartaments(int counts_of_rooms, int storey, int area, int price, string adress, string date) {
		countElements++;
		ID = countElements;
		this->counts_of_rooms = counts_of_rooms;
		this->storey = storey;
		this->area = area;
		this->price = price;
		this->adress = adress;
		this->date = date;
	}

	int getCountRooms() { return counts_of_rooms; }
	int getStorey() { return storey; }
	int getArea() { return area; }
	int getPrice() { return price; }
	int getID() { return ID; }
	string getAdress() { return adress; }
	string getDate() { return date; }

};
int DataApartaments::countElements = 0;
//Array of apartaments object
template <typename T>
struct ArrayDataApartaments {
private:
	vector<DataApartaments> arrDataAp;
	vector<DataApartaments>::iterator it = arrDataAp.begin();

public:
	// enter in parameters (CountRooms, storey, area, price, adress)
	void add_entrie(int counts_of_rooms, int storey, int area, int price, string adress, string date) {
		arrDataAp.push_back(DataApartaments(counts_of_rooms, storey, area, price, adress, date));
	}
	void delete_entrie(int id) {
		for (auto it = arrDataAp.begin(); it != arrDataAp.end(); ++it) {
			if (id == it->getID()) {
				arrDataAp.erase(it);
				break;
			}
		}
	}
	void print_data() {
		int null_elements = 0;
		for (auto it = arrDataAp.begin(); it != arrDataAp.end(); ++it) {
			cout << "Адрес: " << it->getAdress() << "\n";
			cout << "Цена: " << it->getPrice() << "\n";
			cout << "Кол-во комнат: " << it->getCountRooms() << "\n";
			cout << "Этаж: " << it->getStorey() << "\n";
			cout << "Площадь: " << it->getArea() << "\n";
			cout << "Дата: " << it->getDate() << "\n";
			cout << "ID: " << it->getID() << "\n\n";
			null_elements++;
		}
		if (!null_elements) { cout << "\nСписок пуст"; }
	}
	void find_by_ID(int id) {
		for (auto it = arrDataAp.begin(); it != arrDataAp.end(); ++it) {
			if (id == it->getID()) {
				cout << "Адрес: " << it->getAdress() << "\n";
				cout << "Цена: " << it->getPrice() << "\n";
				cout << "Кол-во комнат: " << it->getCountRooms() << "\n";
				cout << "Этаж: " << it->getStorey() << "\n";
				cout << "Площадь: " << it->getArea() << "\n";
				cout << "ID: " << it->getID() << "\n\n";
			}
		}
	}

	vector<DataApartaments> getArray() {
		return arrDataAp;
	}


};
//struct to write from file
struct WriteDataFromFile {

	void writeData(vector<DataApartaments> arr, string path) {
		fstream file(path);

		file.open(path + ".txt", fstream::in | fstream::out | fstream::app);

		if (file.is_open()) {
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				file <<
					it->getID() << " " <<
					it->getCountRooms() << " " <<
					it->getStorey() << " " <<
					it->getArea() << " " <<
					it->getPrice() << " " <<
					it->getAdress() << " " <<
					it->getDate() << "\n";
			}
			file.close();
			cout << "\nЗапись произошла успешно";
		}
		else {
			cout << "Error open file.\n";
		}
	}
	void writeDataFromID(vector<DataApartaments> arr, string path, int id) {
		fstream file(path);

		file.open(path + ".txt", fstream::in | fstream::out | fstream::app);

		if (file.is_open()) {
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				if (id == it->getID()) {
					file <<
						it->getID() << " " <<
						it->getCountRooms() << " " <<
						it->getStorey() << " " <<
						it->getArea() << " " <<
						it->getPrice() << " " <<
						it->getAdress() << " " <<
						it->getDate() << "\n";
					break;
				}
			}
			cout << "Запись произошла успешно";
			file.close();
		}
		else {
			cout << "Error open file.\n";
		}
	}
};
//struct to read from file
struct ReadDataFromFile {
	void readData(ArrayDataApartaments<DataApartaments> arr, string path) {
		int counts_of_rooms;
		int storey;
		int area;
		int price;
		int ID;
		string adress;
		string date;
		
		fstream file(path);

		file.open(path + ".txt", fstream::in | fstream::out | fstream::app);
		cout << "\n";

		if (file.is_open()) {
			while (!file.eof()) {
				file >> ID >> counts_of_rooms >> storey >> area >> price >> adress >> date;
				if (ID < 0) cout << "Error reading file";
				else arr.add_entrie(counts_of_rooms, storey, area, price, adress, date);
				file.close();
			}
		}
		else {
			cout << "Error open file.\n";
		}
	}
};

int lifeCycle(ArrayDataApartaments<DataApartaments> arrayDataApartaments, WriteDataFromFile writedatafromfile, ReadDataFromFile readdatafromfile) {
	cout << "list of available commands";
	cout << "\n1. Add entrie";
	cout << "\n2. Delete entrie";
	cout << "\n3. Print data";
	cout << "\n4. Find by ID";
	cout << "\n5. Write data from ID";
	cout << "\n6. Write data";
	cout << "\n7. Read data";
	cout << "\n8. Clear screen";
	cout << "\n9. Show menu";
	cout << "\n10. Exit";


	string choise;
	bool user_wants_to_close_the_program = false;
	bool no_choise_made = true;

	do
	{
		cout << "\n\nEnter choice: ";
		cin >> choise;
		if (choise == "Add" || choise == "add") {
			no_choise_made = true;
			int counts_of_rooms;
			int storey;
			int area;
			int price;
			string adress;
			string date;
			cout << "\ncounts of rooms: ";
			cin >> counts_of_rooms;
			cout << "storey: ";
			cin >> storey;
			cout << "area: ";
			cin >> area;
			cout << "price: ";
			cin >> price;
			cout << "adress: ";
			cin.ignore();
			getline(cin, adress);
			cout << "date: ";
			cin >> date;
			while (!check_date(date)) {
				cout << "Wrong date format: " + date;
				cout << "\ndate: ";
				cin >> date;
			}
			arrayDataApartaments.add_entrie(counts_of_rooms, storey, area, price, adress, date);
			cout << "\n\nEntrie successfully added\n\n";
		}
		else if (choise == "Delete" || choise == "delete ") {
			no_choise_made = true;
			int id;
			cout << "Enter id: ";
			cin >> id;
			arrayDataApartaments.delete_entrie(id);
			cout << "Entrie successfully deleted\n\n";
		}
		else if (choise == "Print" || choise == "print") {
			arrayDataApartaments.print_data();
			no_choise_made = true;
		}
		else if (choise == "FindByID" || choise == "findbyid") {
			int id;
			cout << "Enter id: ";
			cin >> id;
			cout << "\n\n";
			arrayDataApartaments.find_by_ID(id);
			no_choise_made = true;
		}
		else if (choise == "WriteFromID" || choise == "writefromid") {
			string path;
			int id;

			cout << "Enter id: ";
			cin >> id;

			cout << "\nWrite filename: ";
			cin >> path;

			writedatafromfile.writeDataFromID(arrayDataApartaments.getArray(), path, id);
			no_choise_made = true;
		}
		else if (choise == "Write" || choise == "write") {

			string path;
			cout << "\nWrite filename: ";
			cin >> path;

			writedatafromfile.writeData(arrayDataApartaments.getArray(), path);
			no_choise_made = true;
		}
		else if (choise == "Read" || choise == "read") {
			string path;

			cout << "\nWrite filename: ";
			cin >> path;

			readdatafromfile.readData(arrayDataApartaments, path);

			no_choise_made = true;
		}
		else if (choise == "Exit" || choise == "exit") {
			return 1;
			user_wants_to_close_the_program = true;
		}
		else if (choise == "Show" || choise == "show") {
			cout << "\nlist of available commands";
			cout << "\n1. Add entrie";
			cout << "\n2. Delete entrie";
			cout << "\n3. Print data";
			cout << "\n4. Find by ID";
			cout << "\n5. Write data from ID";
			cout << "\n6. Write data";
			cout << "\n7. Read data";
			cout << "\n8. Clear screen";
			cout << "\n9. Show menu";
			cout << "\n10. Exit";
		}
		else if (choise == "Clear" || choise == "clear") {
			system("cls");
			cout << "list of available commands";
			cout << "\n1. Add entrie";
			cout << "\n2. Delete entrie";
			cout << "\n3. Print data";
			cout << "\n4. Find by ID";
			cout << "\n5. Write data from ID";
			cout << "\n6. Write data";
			cout << "\n7. Read data";
			cout << "\n8. Clear screen";
			cout << "\n9. Show menu";
			cout << "\n10. Exit";
		}
		else {
			cout << "Error! Unknown command: " + choise << "\n";
		}

	} while (!user_wants_to_close_the_program);

	return 0;
}

int main() {

	setlocale(LC_ALL, "rus");

	ArrayDataApartaments<DataApartaments> arrayDataApartaments= ArrayDataApartaments<DataApartaments>();
	WriteDataFromFile writedatafromfile = WriteDataFromFile();
	ReadDataFromFile readdatafromfile = ReadDataFromFile();
	
	lifeCycle(arrayDataApartaments, writedatafromfile, readdatafromfile);

	return 0;
}
