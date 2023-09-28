#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <thread>
#include "CheckStatus.h"
#include "OrderClass.h"
#include "DeliveryClass.h"
#include "ThreadOvens.h"
#include "ThreadDelivery.h"
#include <Windows.h>


using namespace std;
sql::Driver* driver;
sql::Connection* con;
sql::Driver* driver2;
sql::Connection* con2;
sql::Driver* driver3;
sql::Connection* con3;
sql::Driver* driver4;
sql::Connection* con4;
sql::Driver* driver5;
sql::Connection* con5;


void setConsoleWindowSize(int width, int height) {
	HWND console = GetConsoleWindow();
	RECT rect;
	GetWindowRect(console, &rect);
	MoveWindow(console, rect.left, rect.top, width, height, TRUE);
}

void HideConsoleCursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(consoleHandle, &cursorInfo);
	cursorInfo.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &cursorInfo);
}

void DisableTextSelection() {
	HANDLE consoleHandle = GetStdHandle(STD_INPUT_HANDLE);
	DWORD consoleMode;
	GetConsoleMode(consoleHandle, &consoleMode);
	SetConsoleMode(consoleHandle, consoleMode & ~(ENABLE_QUICK_EDIT_MODE | ENABLE_EXTENDED_FLAGS));
}

int main()
{
	int choice = MessageBox(nullptr, TEXT("Console MODE ON?"), TEXT("Message"), MB_YESNO | MB_ICONQUESTION);

	if (choice == IDNO) {
		HWND consoleWindow = ::GetConsoleWindow();
		if (consoleWindow != nullptr) {
			::ShowWindow(consoleWindow, SW_HIDE);
		}
		while (true) {
			if (GetAsyncKeyState(VK_MENU) & 0x8000 && GetAsyncKeyState('X') & 0x8000) {

				int closeChoice = MessageBox(nullptr, TEXT("STOP the application?"), TEXT("Exit"), MB_YESNO | MB_ICONQUESTION);
				if (closeChoice == IDYES) {
					return 0;
				}
			}
		}
	}

	HideConsoleCursor();
	DisableTextSelection();
	setConsoleWindowSize(1355, 615);
	HWND console = GetConsoleWindow();

	SetWindowLongPtr(console, GWL_STYLE, GetWindowLongPtr(console, GWL_STYLE) & ~(WS_SIZEBOX | WS_MAXIMIZEBOX));
	ShowScrollBar(console, SB_VERT, FALSE);
	HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hStdOut, &csbi);
	csbi.dwSize.Y = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
	SetConsoleScreenBufferSize(hStdOut, csbi.dwSize);

	try {

		driver = get_driver_instance();
		con = driver->connect("tcp://89.39.7.10:3306", "phiobaiqu_root", "Andreeas18MySql");

		if (!con->isValid()) {
			std::cerr << "Failed to establish a valid connection to the database." << std::endl;
			system("pause");
			exit(1);
		}

		con->setSchema("phiobaiqu_siemensprojectdb");
		std::string mainDatabaseMessage = "Connected to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::string mainDatabaseMessage = "Can't connect to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
		system("pause");
		exit(1);
	}

	try {

		driver2 = get_driver_instance();
		con2 = driver2->connect("tcp://89.39.7.10:3306", "phiobaiqu_root", "Andreeas18MySql");

		if (!con2->isValid()) {
			std::cerr << "Failed to establish a valid connection to the database." << std::endl;
			system("pause");
			exit(1);
		}

		con2->setSchema("phiobaiqu_siemensprojectdb");
		std::string mainDatabaseMessage = "Connected to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::string mainDatabaseMessage = "Can't connect to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
		system("pause");
		exit(1);
	}

	try {
		driver3 = get_driver_instance();
		con3 = driver3->connect("tcp://89.39.7.10:3306", "phiobaiqu_root", "Andreeas18MySql");

		if (!con3->isValid()) {
			std::cerr << "Failed to establish a valid connection to the database." << std::endl;
			system("pause");
			exit(1);
		}

		con3->setSchema("phiobaiqu_siemensprojectdb");
		std::string mainDatabaseMessage = "Connected to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::string mainDatabaseMessage = "Can't connect to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
		system("pause");
		exit(1);
	}

	try {
		driver4 = get_driver_instance();
		con4 = driver4->connect("tcp://89.39.7.10:3306", "phiobaiqu_root", "Andreeas18MySql");

		if (!con4->isValid()) {
			std::cerr << "Failed to establish a valid connection to the database." << std::endl;
			system("pause");
			exit(1);
		}

		con4->setSchema("phiobaiqu_siemensprojectdb");
		std::string mainDatabaseMessage = "Connected to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::string mainDatabaseMessage = "Can't connect to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
		system("pause");
		exit(1);
	}

	try {
		driver5 = get_driver_instance();
		con5 = driver5->connect("tcp://89.39.7.10:3306", "phiobaiqu_root", "Andreeas18MySql");

		if (!con5->isValid()) {
			std::cerr << "Failed to establish a valid connection to the database." << std::endl;
			system("pause");
			exit(1);
		}

		con5->setSchema("phiobaiqu_siemensprojectdb");
		std::string mainDatabaseMessage = "Connected to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
	}
	catch (sql::SQLException& e) {
		std::cerr << "MySQL error: " << e.what() << std::endl;
		std::string mainDatabaseMessage = "Can't connect to MySQL.";
		CheckStatus::setMainDatabaseMessage(mainDatabaseMessage);
		system("pause");
		exit(1);
	}

	std::thread checkOvens(ThreadOvens::checkOvens, con);
	std::thread takeNewOrders(CheckStatus::ordersThread, con2);
	std::thread moveToDelivery(ThreadDelivery::checkDeliverersGraph, con3);
	std::thread checkDeliverer(ThreadDelivery::deliveryThread, con4);
	std::thread processingDelivery(ThreadDelivery::processingDelivery, con5);
	std::thread systemStatus(CheckStatus::systemStatus);

	takeNewOrders.join();
	checkOvens.join();
	moveToDelivery.join();
	checkDeliverer.join();
	processingDelivery.join();
	systemStatus.join();

	return 0;
}

