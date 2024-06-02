#include <iostream>
#include <mysql.h>
#include <mysqld_error.h>
#include <Windows.h>
#include <sstream>
using namespace std;

const char* HOST = "localhost";
const char* USER = "root";
const char* PW = "3112";
const char* DB = "password_Manager";

class Passwords {
private:
	string Name, UserId, UserPw;
public:
	Passwords() :Name(""), UserId(""), UserPw("") {};

	void setName(string name) {
		Name = name;
	}
	void setId(string id) {
		UserId = id;
	}
	void setPw(string pw) {
		UserPw = pw;
	}

	string getName() {
		return Name;
	}
	string getId() {
		return UserId;
	}
	string getPw() {
		return UserPw;
	}
};

void addInfo(MYSQL* conn, Passwords p) {
	string name, userId, userPw;
	cout << "Enter the name under which you want to save the details:"; cin >> name;
	cout << "Enter userID:"; cin >> userId;
	cout << "Enter password:"; cin >> userPw;
	p.setName(name);
	p.setId(userId);
	p.setPw(userPw);

	string add = "INSERT INTO Informations(Purpose, USerID, Password) VALUES('" +p.getName()+ "','" + p.getId() + "','" + p.getPw() + "')";
	if (mysql_query(conn, add.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		cout << "Data inserted successfully!" << endl;
	}
}

void updateInfo(MYSQL* conn, Passwords p) {
	int a;
	cout << "1. UserID" << endl;
	cout << "2. Password" << endl;
	cout << "which information you wanna update?"; cin >> a;
	string name;
	cout << "Enter Purpose:"; cin >> name;

	if (a == 1) {
		string userId;
		cout << "Enter new UserID:"; cin >> userId;
		p.setId(userId);
		string upd1 = "UPDATE Informations SET UserID = '" + p.getId() + "' WHERE Purpose = '" + p.getName() + "'";
		if (mysql_query(conn, upd1.c_str())) {
			cout << "Error:" << mysql_error(conn) << endl;
		}
		else {
			cout << "Data updated successfully!" << endl;
		}

	}
	else if (a == 2) {
		string userPw;;
		cout << "enter new password:"; cin >> userPw;
		p.setPw(userPw);
		string upd2 = "UPDATE Informations SET Password = '" + p.getPw() + "' WHERE Purpose = '" + p.getName() + "'";
		if (mysql_query(conn, upd2.c_str())) {
			cout << "Error:" << mysql_error(conn) << endl;
		}
		else {
			cout << "Data updated successfully!" << endl;
		}
	}
}

void searchInfo(MYSQL* conn, Passwords p) {
	string name;
	cout << "Enter purpose:"; cin >> name;
	p.setName(name);
	string show = "SELECT * FROM Informations WHERE Purpose = '" + p.getName() + "'";
	if (mysql_query(conn, show.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		MYSQL_RES* res;
		res = mysql_store_result(conn);
		if (res) {
			MYSQL_ROW row = mysql_fetch_row(res);
			if (row) {
				int num = mysql_num_fields(res);
				for (int i = 0; i < num; i++) {
					cout << " " << row[i];
				}
			}
			mysql_free_result(res);
		}
	}
	Sleep(3000);
}

void deleteInfo(MYSQL* conn, Passwords p) {
	string name;
	cout << "Enter purpose:"; cin >> name;
	p.setName(name);
	string del = "DELETE FROM Informations WHERE Purpose = '" + p.getName() + "'";
	if (mysql_query(conn, del.c_str())) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		cout << "Data deleted successfully!" << endl;
	}
	Sleep(3000);
}


int main() {
	Passwords p;

	MYSQL* conn;
	conn = mysql_init(NULL);

	if (!mysql_real_connect(conn, HOST, USER, PW, DB, 3306, NULL, 0)) {
		cout << "Error:" << mysql_error(conn) << endl;
	}
	else {
		cout << "Logged in!" << endl;
	}
	Sleep(3000);

	bool exit = false;
	while (!exit) {
		system("cls");
		int n;
		cout << "PASSWORD MANAGER SYSTEM" << endl;
		cout << "-----------------------" << endl;
		cout << "1. Add information \n2. Update information \n3. Search information" << endl;
		cout << "4. Delete information \n5. Exit" << endl;
		cout << "Enter your choice:"; cin >> n;

		if (n == 1) {
			addInfo(conn, p);
		}
		else if (n == 2) {
			updateInfo(conn, p);
		}
		else if (n == 3) {
			searchInfo(conn, p);
		}
		else if (n == 4) {
			deleteInfo(conn, p);
		} else if (n==5){
			exit = true;
			cout << "EXITED!" << endl;
			Sleep(3000);
		}
		else {
			cout << "enter valid option" << endl;
		}
	}

	return 0;
}