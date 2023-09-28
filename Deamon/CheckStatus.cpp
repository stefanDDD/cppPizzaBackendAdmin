#pragma warning(disable : 4996)
#include "CheckStatus.h"
#include <thread>
#include <iostream>
#include "OrderClass.h"
#include "OrderItems.h"
#include "OvenClass.h"
#include <chrono>
#include <list>
#include <windows.h>
#include "OvenClass.h"
#include <vector>
#include "DeliveryClass.h"
#include "ThreadOvens.h"
#include "ThreadDelivery.h"
#include <nlohmann/json.hpp>
#include "curl/curl.h"
#include "curl/easy.h"
#include <cstdlib>

using json = nlohmann::json;
std::string CheckStatus::mainDatabaseMessage;
std::string CheckStatus::ovenStatusMessage1;
std::string CheckStatus::ovenStatusMessage2;
std::string CheckStatus::curlStatusMessage;
std::string CheckStatus::databaseStatusMessage;
std::string CheckStatus::orderHeaderString;

void CheckStatus::setOrderHeaderString(std::string& setOrderHeaderString) {
	CheckStatus::orderHeaderString = setOrderHeaderString;
}

std::string CheckStatus::getOrderHeaderString() {
	return orderHeaderString;
}

void CheckStatus::setDatabaseStatusMessage(std::string& databaseStatusMessage) {
	CheckStatus::databaseStatusMessage = databaseStatusMessage;
}

std::string CheckStatus::getDatabaseStatusMessage() {
	return databaseStatusMessage;
}

void CheckStatus::setCurlStatusMessage(std::string& curlStatusMessage) {
	CheckStatus::curlStatusMessage = curlStatusMessage;
}

std::string CheckStatus::getCurlStatusMessage() {
	return curlStatusMessage;
}

void CheckStatus::setOvenStatusMessage1(std::string& ovenStatusMessage1) {
	CheckStatus::ovenStatusMessage1 = ovenStatusMessage1;
}

std::string CheckStatus::getOvenStatusMessage1() {
	return ovenStatusMessage1;
}

void CheckStatus::setOvenStatusMessage2(std::string& ovenStatusMessage2) {
	CheckStatus::ovenStatusMessage2 = ovenStatusMessage2;
}

std::string CheckStatus::getOvenStatusMessage2() {
	return ovenStatusMessage2;
}

void CheckStatus::setMainDatabaseMessage(std::string& mainDatabaseMessage) {
	CheckStatus::mainDatabaseMessage = mainDatabaseMessage;
}

std::string CheckStatus::getMainDatabaseMessage(){
	return mainDatabaseMessage;
}

void CheckStatus::setCursorPosition(int x, int y)
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD cursorPosition = { static_cast<short>(x), static_cast<short>(y) };
	SetConsoleCursorPosition(consoleHandle, cursorPosition);
}

void CheckStatus::printMessage(const std::string& message, int x, int y)
{
	setCursorPosition(x, y);
	std::cout << message << std::endl;
}

int CheckStatus::getConsoleCursorY() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hConsole, &csbi);
	return csbi.dwCursorPosition.Y;
}

size_t discardResponseCheckStatus(void*, size_t size, size_t nmemb, std::string* response) {
	return size * nmemb;
}

//selecteaza informatii despre produsele disponibile
void CheckStatus::getOrderItemsInfo(OrderItems& item, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	std::string orderHeaderString = "ITEM ORDER ID " + to_string(item.getOrderId());
	CheckStatus::setOrderHeaderString(orderHeaderString);
	pstm = con->prepareStatement("SELECT menu_items.product_name, menu_items.prepare_time, menu_items.cost, order_items.quantity "
		"FROM menu_items "
		"JOIN order_items ON menu_items.item_id = order_items.item_id "
		"WHERE menu_items.item_id = " + to_string(item.getItemId()) + " "
		"AND order_items.order_id = " + to_string(item.getOrderId()) + ";");
	rs = pstm->executeQuery();

	if (rs->next()) {
		item.setProductName(rs->getString("product_name"));
		item.setPrepareTime(rs->getInt("prepare_time"));
		item.setCost(rs->getDouble("cost"));
		item.setQuantity(rs->getInt("quantity"));
	}
}

//selecteaza informatii despre utilizatorul care a realizat comanda precum si detalii despre comanda
void CheckStatus::getOrderInfo(OrderClass& ord, int order_id, string timestamp, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;
	sql::ResultSet* rs2;
	//selecteaza informatii despre utilizator
	pstm = con->prepareStatement("SELECT users.user_id, username, full_name, address, phone_number, e_mail FROM users"
		" JOIN order_status WHERE order_status.user_id = users.user_id"
		" AND order_status.order_id = " + to_string(order_id));
	rs = pstm->executeQuery();
	//selecteaza informatii despre comanda
	pstm = con->prepareStatement("SELECT order_id, item_id, quantity "
		"FROM order_items where order_id = " + to_string(order_id) + "; ");
	rs2 = pstm->executeQuery();

	if (rs->next()) {
		ord.setOrderId(order_id);
		ord.setUserId(rs->getInt("user_id"));
		ord.setUsername(rs->getString("username"));
		ord.setFullname(rs->getString("full_name"));
		ord.setAddress(rs->getString("address"));
		ord.setPhoneNumber(rs->getString("phone_number"));
		ord.setEmail(rs->getString("e_mail"));
		ord.setStatus("PROCESSING");
		ord.setTimestamp(timestamp);
		ord.toString();

		double costTotal = 0;
		while (rs2->next()) {
			OrderItems item;
			item.setOrderId(rs2->getInt("order_id"));
			item.setItemId(rs2->getInt("item_id"));
			item.setQuantity(rs2->getInt("quantity"));

			getOrderItemsInfo(item, con);
			costTotal = getCostTotalDatabase(order_id, con);
			ord.setOrderItems(item);

		}
		
		ord.setCostTotal(costTotal);

		setOrderStatus(status_enum::PROCESSING, order_id, con);
		ord.getOrderItems();
	}
}

double CheckStatus::getCostTotalDatabase(int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;
	pstm = con->prepareStatement("SELECT total FROM "
		" order_status where order_id = ? ");
	pstm->setInt(1, order_id);
	rs = pstm->executeQuery();
	double costTotal = 0;
	if (rs->next()) {
		costTotal = rs->getDouble("total");
	}
	return costTotal;
}

void CheckStatus::getOrder(OrderClass& ord, int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	try {
		pstm = con->prepareStatement("SELECT order_id, user_id, timestamp, status FROM "
			" order_status where order_id = ? ");
		pstm->setInt(1, order_id);
		rs = pstm->executeQuery();

		if (rs->next()) {
			CheckStatus::setCursorPosition(0, 42);
			getOrderInfo(ord, rs->getInt("order_id"), rs->getString("timestamp"), con);
		}
	}
	catch (const sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

}

//schimba statusul functiei in "IN_PROCESSING" in functie de ID-ul pe care il primeste
void CheckStatus::setOrderStatus(status_enum sts, int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	try {
		pstm = con->prepareStatement("UPDATE order_status SET status = ? WHERE order_id = ?");
		pstm->setString(1, toString(sts));
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {

		std::string databaseMessage = "Error in updating order status : " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void CheckStatus::setItemStatus(status_enum sts, int item_id, int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	try {
		pstm = con->prepareStatement("UPDATE order_items SET item_status = ? WHERE item_id = ? AND order_id = ?");
		pstm->setString(1, toString(sts));
		pstm->setInt(2, item_id);
		pstm->setInt(3, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating item status : " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);

	}
}

void CheckStatus::setOrderStatusInItems(status_enum sts, int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	try {
		pstm = con->prepareStatement("UPDATE order_items SET item_status = ? WHERE order_id = ?");
		pstm->setString(1, toString(sts));
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating item status : " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);

	}
}

void CheckStatus::ordersThread(sql::Connection* con2) {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	sql::ResultSet* rs;
	sql::PreparedStatement* pstm;
	while (true) {
		if (con2->isValid()) {
			pstm = con2->prepareStatement("SELECT order_id, item_id FROM order_items "
				" WHERE item_status = 'PENDING' ORDER BY order_id ASC limit 1");

			rs = pstm->executeQuery();
			if (rs->next()) {
				CheckStatus::setOrderStatus(CheckStatus::status_enum::PROCESSING, rs->getInt("order_id"), con2);
				CheckStatus::setItemStatus(CheckStatus::status_enum::PROCESSING, rs->getInt("item_id"), rs->getInt("order_id"), con2);
				OrderClass ord;
				CheckStatus::getOrder(ord, rs->getInt("order_id"), con2);
				ThreadOvens::processingOrder(ord, con2);
				time_t now = time(0);
				char* dt = ctime(&now);
				std::ostringstream oss1;
				std::ostringstream oss2;
				oss1 << dt;
				oss2 << "Not new orders. Empty ovens : " << ThreadOvens::verifyEmptyOvens(con2) << "/5";

				std::string ovenStatusMessage1 = oss1.str();
				std::string ovenStatusMessage2 = oss2.str();

				CheckStatus::setOvenStatusMessage1(ovenStatusMessage1);
				CheckStatus::setOvenStatusMessage2(ovenStatusMessage2);
				ThreadDelivery::displayAllStatusBars();
				ThreadDelivery::displayEachNodeStatusBar();

				std::this_thread::sleep_for(chrono::seconds(1));
			}
			else {
				time_t now = time(0);
				char* dt = ctime(&now);
				std::ostringstream oss1;
				std::ostringstream oss2;
				oss1 << dt;
				oss2 << "Not new orders. Empty ovens : " << ThreadOvens::verifyEmptyOvens(con2) << "/5";

				std::string ovenStatusMessage1 = oss1.str();
				std::string ovenStatusMessage2 = oss2.str();
				CheckStatus::setOvenStatusMessage1(ovenStatusMessage1);
				CheckStatus::setOvenStatusMessage2(ovenStatusMessage2);

				
				struct curl_slist* headers = NULL;
				headers = curl_slist_append(headers, "Content-Type: application/json");
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
				json jsonMessage;
				jsonMessage["statusDisplay"] = true;
				jsonMessage["currentTime"] = dt;
				jsonMessage["emptyOvens"] = ThreadOvens::verifyEmptyOvens(con2);
				std::string jsonStr = jsonMessage.dump();
				curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseCheckStatus);


				CURLcode res = curl_easy_perform(curl);
				curl_slist_free_all(headers);

				ThreadDelivery::displayAllStatusBars();
				ThreadDelivery::displayEachNodeStatusBar();

				std::this_thread::sleep_for(chrono::seconds(1));
			}
		}
		else {

			std::string databaseMessage = "Can't connect to database.";
			CheckStatus::setDatabaseStatusMessage(databaseMessage);
		}
	}
	curl_easy_cleanup(curl);
}

void CheckStatus::systemStatus() {
	while (true) {
		CheckStatus::consoleDisplay();
		ThreadOvens::systemStatusOvens();
		ThreadDelivery::systemStatusDelivery();
		std::this_thread::sleep_for(chrono::seconds(1));
	}
}

void CheckStatus::consoleDisplay() {
	system("cls");
	CheckStatus::printMessage("################################################################################", 0, 0);
	for (int i = 0; i < 5; i++) {
		CheckStatus::printMessage(ThreadOvens::getOvenMessageCustom(i + 1), 0, i + 1);
	}
	CheckStatus::printMessage("################################################################################", 0, 6);
	for (int i = 0; i < 5; i++) {
		CheckStatus::printMessage(ThreadDelivery::getDelivererStatusMessage(i + 1), 0, 7 + 2 * i);
	}
	CheckStatus::printMessage("################################################################################", 0, 17);
	for (int i = 0; i < 5; i++) {
		CheckStatus::printMessage(ThreadOvens::getOvenMessageCustomStatus(i + 1), 0, i + 18);
	}
	CheckStatus::printMessage("################################################################################", 0, 23);
	for (int i = 0; i < 5; i++) {
		CheckStatus::printMessage(ThreadDelivery::getDelivererStatusMessageCustom(i + 1), 0, i * 2 + 24);
	}
	CheckStatus::printMessage("################################################################################", 0, 34);
	CheckStatus::printMessage("################################################################################", 85, 0);
	CheckStatus::printMessage(CheckStatus::getOvenStatusMessage1(), 85, 1);
	CheckStatus::printMessage(CheckStatus::getOvenStatusMessage2(), 85, 2);
	CheckStatus::printMessage("################################################################################", 85, 3);
	CheckStatus::printMessage(ThreadDelivery::getDelivererReadyStatus(), 85, 4);
	CheckStatus::printMessage("################################################################################", 85, 5);
	for (int i = 0; i < 5; i++) {
		CheckStatus::printMessage(ThreadDelivery::getDelivererStatusMessageStatusBar(i + 1), 85, i + 6);
	}
	CheckStatus::printMessage("################################################################################", 85, 11);
	CheckStatus::printMessage(CheckStatus::getOrderHeaderString(), 85, 12);
	CheckStatus::printMessage(OrderClass::getOrderIDString(), 85, 13);
	CheckStatus::printMessage(OrderClass::getOrderUsernameString(), 85, 14);
	CheckStatus::printMessage(OrderClass::getOrderFullnameString(), 85, 15);
	CheckStatus::printMessage(OrderClass::getOrderAddressString(), 85, 16);
	CheckStatus::printMessage(OrderClass::getOrderPhoneString(), 85, 17);
	CheckStatus::printMessage(OrderClass::getOrderEmailString(), 85, 18);
	CheckStatus::printMessage(OrderClass::getOrderStatusString(), 85, 19);
	CheckStatus::printMessage(OrderClass::getOrderTimestampString(), 85, 20);
	CheckStatus::printMessage("################################################################################", 85, 21);
	CheckStatus::printMessage(OrderItems::getOrderItemString1(), 85, 22);
	CheckStatus::printMessage(OrderClass::getOrderCostString(), 85, 23);
	CheckStatus::printMessage("################################################################################", 85, 24);
	CheckStatus::printMessage(ThreadDelivery::getOrdersInDeliverString(), 85, 25);
	CheckStatus::printMessage("################################################################################", 85, 26);
	CheckStatus::printMessage(CheckStatus::getMainDatabaseMessage(), 85, 27);
	CheckStatus::printMessage("################################################################################", 85, 28);
	CheckStatus::printMessage(CheckStatus::getDatabaseStatusMessage(), 85, 29);
	CheckStatus::printMessage("################################################################################", 85, 30);
	CheckStatus::printMessage(CheckStatus::getCurlStatusMessage(), 85, 31);
	CheckStatus::printMessage("################################################################################", 85, 32);
	CheckStatus::printMessage(ThreadOvens::getOvenQuantityRawMaterial(), 85, 33);
	CheckStatus::printMessage("################################################################################", 85, 34);
}