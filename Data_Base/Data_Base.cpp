#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <Windows.h>

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
//Проверка на пустую строку
bool check_string(string adress) {
	int count_probels = 0;
	for (int i = 0; adress[i] != '\0'; i++) {
		if ((char)(adress[i]) == 32){
			count_probels++;
		}
	}
	if (count_probels == adress.size()) return false;

	return true;
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
	// deleting an entry
	void delete_entrie(int id) {
		bool this_id_does_not_exist = true;
		for (auto it = arrDataAp.begin(); it != arrDataAp.end(); ++it) {
			if (id == it->getID()) {
				this_id_does_not_exist = false;
				arrDataAp.erase(it);

				break;
			}
		}
		if (this_id_does_not_exist) cout << "\nЭлемента с таким ID не существует\n\n=============================\n";
		else cout << "\nEntrie successfully deleted\n\n=============================\n";
	}
	// show all entries
	void print_data() {
		int null_elements = 0;
		for (auto it = arrDataAp.begin(); it != arrDataAp.end(); ++it) {
			cout << "\nАдрес: " << it->getAdress() << "\n";
			cout << "Цена: " << it->getPrice() << "\n";
			cout << "Кол-во комнат: " << it->getCountRooms() << "\n";
			cout << "Этаж: " << it->getStorey() << "\n";
			cout << "Площадь: " << it->getArea() << "\n";
			cout << "Дата: " << it->getDate() << "\n";
			cout << "ID: " << it->getID() << "\n\n";
			cout << "=============================\n";
			null_elements++;
		}
		if (!null_elements) { cout << "\nСписок пуст\n\n=============================\n"; }
	}
	// find entry from id 
	void find_by_ID(int id) {
		bool this_element_does_not_exist = true;
		for (auto it = arrDataAp.begin(); it != arrDataAp.end(); ++it) {
			if (id == it->getID()) {
				false;
				cout << "Адрес: " << it->getAdress() << "\n";
				cout << "Цена: " << it->getPrice() << "\n";
				cout << "Кол-во комнат: " << it->getCountRooms() << "\n";
				cout << "Этаж: " << it->getStorey() << "\n";
				cout << "Площадь: " << it->getArea() << "\n";
				cout << "ID: " << it->getID() << "\n";
			}
		}
		if (this_element_does_not_exist) cout << "Такого элемента не существует\n\n=============================\n";
	}

	vector<DataApartaments> getArray() {
		return arrDataAp;
	}


};
//struct to write from file
struct WriteDataFromFile {

	void writeData(vector<DataApartaments> arr, string path) {
		fstream file(path);
		ifstream ifile(path);

		int ID;

		file.open(path + ".txt", fstream::in | fstream::out | fstream::app);
		ifile.open(path + ".txt");

		if (file.is_open()) {
			ifile >> ID;
			for (auto it = arr.begin(); it != arr.end(); ++it) {
				if (ID > 0) {
					file << "\n" <<
						it->getID() << " " <<
						it->getCountRooms() << " " <<
						it->getStorey() << " " <<
						it->getArea() << " " <<
						it->getPrice() << " " <<
						it->getAdress() << " " <<
						it->getDate();
				}
				else {
					if (it->getID() == 1) {
						file <<
							it->getID() << " " <<
							it->getCountRooms() << " " <<
							it->getStorey() << " " <<
							it->getArea() << " " <<
							it->getPrice() << " " <<
							it->getAdress() << " " <<
							it->getDate();
					}
					else {
							file << "\n" <<
								it->getID() << " " <<
								it->getCountRooms() << " " <<
								it->getStorey() << " " <<
								it->getArea() << " " <<
								it->getPrice() << " " <<
								it->getAdress() << " " <<
								it->getDate();
					}
				}
			}
			file.close();
			cout << "\nЗапись произошла успешно\n";
			cout << "\n=============================\n";
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
			cout << "\nЗапись произошла успешно\n\n=============================\n";
			file.close();
		}
		else {
			cout << "Error open file.\n";
		}
	}
};
//struct to read from file
struct ReadDataFromFile {
	ArrayDataApartaments<DataApartaments> readData(ArrayDataApartaments<DataApartaments> arr, string path) {
		int counts_of_rooms;
		int storey;
		int area;
		int price;
		int ID;
		int number_of_items_read = 0;
		int size;
		string adress;
		string date;

		ifstream file(path);
		file.open(path + ".txt");
		if (file.is_open()) {
			while (!file.eof()) {
				file >> ID >> counts_of_rooms >> storey >> area >> price >> adress >> date;
				if (ID < 0) {
					cout << "\nError reading file\nmaybe file is empty\n";
					cout << "\n=============================\n";
					return arr;
				}
				else arr.add_entrie(counts_of_rooms, storey, area, price, adress, date);
				cout << "\nReading successfully\n\n=============================\n";
			}
		}
		else {
			cout << "Error open file.\n\n=============================\n";
		}
		return arr;
	}
};

int lifeCycle(ArrayDataApartaments<DataApartaments>& arrayDataApartaments, WriteDataFromFile writedatafromfile, ReadDataFromFile readdatafromfile) {
	cout << "=============================\n";
	cout << "list of available commands";
	cout << "\n1. Add entrie (add)";
	cout << "\n2. Delete entrie (delete)";
	cout << "\n3. Print data (print)";
	cout << "\n4. Find by ID (findbyid)";
	cout << "\n5. Write data from ID (writefromid)";
	cout << "\n6. Write data (write)";
	cout << "\n7. Read data (read)";
	cout << "\n8. Clear screen (clear)";
	cout << "\n9. Show menu (show)";
	cout << "\n10. Exit (exit)\n";
	cout << "=============================\n";


	string choise;
	bool user_wants_to_close_the_program = false;
	bool no_choise_made = true;

	do
	{
		cout << "\nEnter choice: ";
		cin >> choise;
		cout << "\n=============================\n";
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
			getline(cin, adress);
			while (!check_string(adress)) {
				getline(cin, adress);
				if (!check_string(adress)) cout << "Empty string entered\nadress: ";
			}
			cout << "date: ";
			cin >> date;
			while (!check_date(date)) {
				cout << "Wrong date format: " + date;
				cout << "\ndate: ";
				cin >> date;
			}
			arrayDataApartaments.add_entrie(counts_of_rooms, storey, area, price, adress, date);
			cout << "\n\nEntrie successfully added\n";
			cout << "\n=============================\n";
		}
		else if (choise == "Delete" || choise == "delete") {
			no_choise_made = true;
			int id;
			cout << "\nEnter id: ";
			cin >> id;
			arrayDataApartaments.delete_entrie(id);
		}
		else if (choise == "Print" || choise == "print") {
			arrayDataApartaments.print_data();
			no_choise_made = true;
		}
		else if (choise == "FindByID" || choise == "findbyid") {
			int id;
			cout << "\nEnter id: ";
			cin >> id;
			cout << "\n";
			arrayDataApartaments.find_by_ID(id);
			no_choise_made = true;
		}
		else if (choise == "WriteFromID" || choise == "writefromid") {
			string path;
			int id;

			cout << "\nEnter id: ";
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

			arrayDataApartaments = readdatafromfile.readData(arrayDataApartaments, path);

			no_choise_made = true;
		}
		else if (choise == "Exit" || choise == "exit") {
			return 1;
			user_wants_to_close_the_program = true;
		}
		else if (choise == "Show" || choise == "show") {
			cout << "\n=============================\n";
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
			cout << "\n10. Exit\n";
			cout << "=============================\n";
		}
		else if (choise == "Clear" || choise == "clear") {
			system("cls");
			cout << "=============================\n";
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
			cout << "\n10. Exit\n";
			cout << "=============================\n";
		}
		else {
			cout << "\nError! Unknown command: " + choise << "\n";
		}

	} while (!user_wants_to_close_the_program);

	return 0;
}

int main() {

	setlocale(LC_ALL, "rus");

	ArrayDataApartaments<DataApartaments> arrayDataApartaments = ArrayDataApartaments<DataApartaments>();
	WriteDataFromFile writedatafromfile = WriteDataFromFile();
	ReadDataFromFile readdatafromfile = ReadDataFromFile();

	lifeCycle(arrayDataApartaments, writedatafromfile, readdatafromfile);

	return 0;
}
