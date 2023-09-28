#include "ThreadOvens.h"
#include "OvenClass.h"
#include "CheckStatus.h"
#include <thread>
#include <iostream>
#include "OrderClass.h"
#include "OrderItems.h"
#include "OvenClass.h"
#include <chrono>
#include <list>
#include <windows.h>
#include <cppconn/driver.h>
#include "DeliveryClass.h"
#include "GraphClass.h"
#include "ThreadDelivery.h"
#include <nlohmann/json.hpp>
#include "curl/curl.h"
#include "curl/easy.h"
#include <cstdlib>
#include <iomanip>

using namespace std;
using json = nlohmann::json;

OvenClass* oven = new OvenClass[5];
std::map<int, int> ThreadOvens::ovenPercentage;
std::map<int, string> ThreadOvens::ovenMessageCustom;
std::map<int, double> ThreadOvens::ovenRemainingTime;
std::map<int, string> ThreadOvens::ovenMessageCustomStatus;
std::string ThreadOvens::quantityRawMaterial;

std::map<int, std::vector<int>> itemRawMaterialMap = {
	{1, {1, 2, 3, 4, 5, 6, 7, 10, 16, 18, 19, 20, 21, 22, 24, 25, 26, 28, 34, 46}},
	{2, {1, 2, 3, 4, 5, 6, 7, 8, 11, 15, 21, 23, 27, 46}},
	{3, {1, 2, 3, 6, 7, 8, 11, 15, 16, 18, 28, 29, 30, 47, 31, 46}},
	{4, {1, 2, 3, 5, 6, 7, 9, 10, 11, 13, 23, 32, 46, 48}},
	{5, {1, 2, 3, 4, 5, 7, 9, 10, 11, 21, 22, 29, 32, 33, 34, 46}},
	{6, {1, 2, 3, 4, 5, 6, 7, 10, 11, 15, 16, 23, 33, 46}},
	{7, {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 15, 16, 21, 29, 32, 46}},
	{8, {1, 2, 3, 5, 6, 7, 8, 11, 12, 13, 14, 15, 46}},
	{9, {1, 2, 3, 4, 5, 6, 7, 8, 16, 18, 21, 29, 34, 35, 46}},
	{10, {1, 2, 3, 4, 5, 6, 7, 8, 11, 15, 20, 21, 23, 32, 36, 37, 46, 49}},
	{11, {1, 2, 3, 4, 5, 6, 7, 8, 11, 13, 33, 38, 39, 46}},
	{12, {1, 2, 3, 5, 6, 7, 8, 10, 11, 15, 22, 23, 24, 29, 40, 46}},
	{13, {1, 2, 3, 4, 5, 6, 7, 8, 9, 11, 13, 15, 21, 23, 38, 46}},
	{14, {1, 2, 3, 4, 5, 6, 7, 8, 11, 16, 17, 24, 29, 46}},
	{15, {1, 2, 3, 5, 6, 7, 8, 11, 28, 41, 42, 43, 46}},
	{16, {1, 2, 3, 4, 5, 6, 7, 8, 11, 18, 32, 44, 46}},
	{17, {1, 2, 3, 5, 6, 7, 15, 18, 21, 25, 28, 29, 32, 34, 46}},
	{18, {1, 2, 3, 4, 5, 6, 7, 8, 16, 24, 28, 29, 45, 46}},
	{19, {1, 5, 6, 9, 23, 16, 46, 50, 51, 52, 53, 55, 56, 57, 59}},
	{20, {5, 6, 23, 44, 46, 52, 54, 55, 56, 57, 59, 64, 65, 69, 70, 71}},
	{21, {5, 6, 9, 22, 23, 36, 43, 46, 52, 55, 56, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68}},
	{22, {1, 6, 9, 22, 23, 35, 36, 46, 52, 53, 54, 55, 56, 58, 59, 65, 72, 73}},
	{23, {3, 5, 6, 22, 23, 32, 37, 46, 59, 61, 74, 75, 76, 77, 78, 95}},
	{24, {6, 23, 35, 46, 59, 78, 79, 80, 81, 82, 95}},
	{25, {5, 6, 9, 13, 22, 23, 33, 46, 53, 59, 79, 83, 84, 95}},
	{26, {5, 6, 8, 9, 13, 23, 43, 46, 59, 79, 84, 95}},
	{27, {5, 6, 9, 15, 22, 23, 36, 41, 43, 46, 52, 55, 56, 57, 59, 68, 84, 90, 92, 93, 94, 96}},
	{28, {5, 6, 9, 17, 23, 36, 46, 52, 55, 56, 57, 59, 66, 98}},
	{29, {5, 6, 23, 9, 28, 36, 46, 52, 55, 56, 58, 59, 91}},
	{30, {1, 5, 6, 17, 23, 35, 46, 52, 55, 56, 58, 59, 72, 84, 90}},
	{31, {5, 6, 9, 10, 22, 23, 28, 32, 43, 46, 52, 56, 59, 62, 90, 93, 97, 98, 99, 100, 101}},
	{32, {5, 6, 9, 23, 41, 46, 52, 56, 59, 62, 84, 98, 102}},
	{33, {5, 6, 9, 22, 32, 46, 52, 56, 59, 84, 103}},
	{34, {1, 5, 6, 23, 35, 46, 52, 56, 59, 84, 90, 104}},
	{35, {105}},
	{36, {106}},
	{37, {107}},
	{38, {108}},
	{39, {85, 86}},
	{40, {85, 87}},
	{41, {85, 88}},
	{42, {85, 89}}
};


void ThreadOvens::setOvenQuantityRawMaterial(string& quantityRawMaterial_1) {
	quantityRawMaterial = quantityRawMaterial_1;
}

string ThreadOvens::getOvenQuantityRawMaterial() {
	return quantityRawMaterial;
}

void ThreadOvens::setOvenPercentage(int ovenID, int& ovenPercentage_1) {
	ovenPercentage[ovenID] = ovenPercentage_1;
}

int ThreadOvens::getOvenPercentage(int ovenID) {
	return ovenPercentage[ovenID];
}

void ThreadOvens::setOvenRemainingTime(int ovenID, double& ovenRemainingTime_1) {
	ovenRemainingTime[ovenID] = ovenRemainingTime_1;
}

double ThreadOvens::getOvenRemainingTime(int ovenID) {
	return ovenRemainingTime[ovenID];
}

void ThreadOvens::setOvenMessageCustomStatus(int ovenID, string& ovenMessageCustomStatus_1) {
	ovenMessageCustomStatus[ovenID] = ovenMessageCustomStatus_1;
}

string ThreadOvens::getOvenMessageCustomStatus(int ovenID) {
	return ovenMessageCustomStatus[ovenID];
}

void ThreadOvens::setOvenMessageCustom(int ovenID, string& ovenMessageCustom_1) {
	ovenMessageCustom[ovenID] = ovenMessageCustom_1;
}

string ThreadOvens::getOvenMessageCustom(int ovenID) {
	return ovenMessageCustom[ovenID];
}

size_t discardResponseThreadOvens(void*, size_t size, size_t nmemb, std::string* response) {
	return size * nmemb;
}

int ThreadOvens::verifyEmptyOvens(sql::Connection* con) {
	int counter{ 0 };
	for (int i = 0; i < 5; i++) {
		if (oven[i].isAvailable() == true) {
			counter++;
		}
	}
	return counter;
}


void ThreadOvens::checkOvens(sql::Connection* con) {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}


	while (true) {
		if (con->isValid()) {
			ovens(con);
			std::string quantityStatus;
			std::string quantityStatusJson;
			auto resultEnoughQuantity = ThreadOvens::statusRawMaterial(con, CheckStatus::toStringRawMaterials(CheckStatus::status_enum_raw_material::ENOUGH_QUANTITY));
			auto resultLowQuantity = ThreadOvens::statusRawMaterial(con, CheckStatus::toStringRawMaterials(CheckStatus::status_enum_raw_material::LOW_QUANTITY));
			auto resultNoQuantity = ThreadOvens::statusRawMaterial(con, CheckStatus::toStringRawMaterials(CheckStatus::status_enum_raw_material::OUT_OF_QUANTITY));

			int listSizeEnough = resultEnoughQuantity.second;
			int listSizeLow = resultLowQuantity.second;
			int listSizeNo = resultNoQuantity.second;
			if (listSizeLow == 0 && listSizeNo == 0) {
				quantityStatus = "Raw materials stock is currently enough!";
				quantityStatusJson = "Currently enough!";
				ThreadOvens::setOvenQuantityRawMaterial(quantityStatus);
			}
			else if (listSizeNo == 0 && listSizeLow > 0) {
				quantityStatus = "!!! WARNING !!! Quantity is low for some raw materials!";
				quantityStatusJson = "Low quantity!";
				ThreadOvens::setOvenQuantityRawMaterial(quantityStatus);
			}
			else if (listSizeNo > 0 && (listSizeLow > 0|| listSizeLow == 0)) {
				quantityStatus = "!!! ERROR !!! Out of stock for some raw materials!";
				quantityStatusJson = "Out of stock!";
				ThreadOvens::setOvenQuantityRawMaterial(quantityStatus);
			}
			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Content-Type: application/json");
			json jsonMessage;
			jsonMessage["rawMaterialStatus"] = true;
			jsonMessage["rawMaterialMessage"] = quantityStatusJson;

			std::string jsonStr = jsonMessage.dump();
			curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadOvens);
			CURLcode res = curl_easy_perform(curl);

			curl_slist_free_all(headers);

			std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		}
		else {
			std::string databaseMessage = "Can't connect to database.";
			CheckStatus::setDatabaseStatusMessage(databaseMessage);

		}

	}
	curl_easy_cleanup(curl);
}

bool ThreadOvens::allItemsDone(sql::Connection* con, int order_id) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;
	if (con->isValid()) {
		pstm = con->prepareStatement("SELECT item_status FROM order_items WHERE order_id = ?");
		pstm->setInt(1, order_id);
		rs = pstm->executeQuery();
		while (rs->next()) {
			if (rs->getString("item_status") != "DONE") {
				return false;
			}
		}
		return true;
	}
	else {
		std::string databaseMessage = "Can't connect to database.";
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
	return false;
}

void ThreadOvens::ovens(sql::Connection* con) {

	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	for (int i = 0; i < 5; i++) {
		const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
		const std::time_t curentTime_seconds = std::chrono::system_clock::to_time_t(currentTime);

		const std::chrono::time_point<std::chrono::system_clock> ovenTime_seconds = oven[i].getTime();
		const std::time_t t_ovenTime_seconds = std::chrono::system_clock::to_time_t(ovenTime_seconds);

		double prepareTime_seconds = oven[i].getItem().getPrepareTime();
		double remaining_prepared_time = 0;
		remaining_prepared_time = prepareTime_seconds - (curentTime_seconds - t_ovenTime_seconds);
		int percentage = static_cast<int>(((curentTime_seconds - t_ovenTime_seconds) * 100) / prepareTime_seconds);

		setOvenRemainingTime(i, remaining_prepared_time);
		setOvenPercentage(i, percentage);
		if (oven[i].isAvailable() == false && oven[i].isDoneBaking() == false) {
			if (curentTime_seconds - t_ovenTime_seconds >= prepareTime_seconds) {
				if (oven[i].getQuantity() == oven[i].getItem().getQuantity()) {
					CheckStatus::setItemStatus(CheckStatus::status_enum::DONE, oven[i].getItem().getItemId(), oven[i].getItem().getOrderId(), con);

					if (allItemsDone(con, oven[i].getItem().getOrderId()) == true) {
						CheckStatus::setOrderStatus(CheckStatus::status_enum::DONE, oven[i].getItem().getOrderId(), con);
					}
				}
				else if (oven[i].getQuantity() < oven[i].getItem().getQuantity()) {
					CheckStatus::setItemStatus(CheckStatus::status_enum::QUANTITY_IN_PROGRESS, oven[i].getItem().getItemId(), oven[i].getItem().getOrderId(), con);
					CheckStatus::setOrderStatus(CheckStatus::status_enum::QUANTITY_IN_PROGRESS, oven[i].getItem().getOrderId(), con);
				}
				oven[i].clearOven();
				std::string ovenMessageCustomStatus = "Oven " + to_string(i + 1) + " has finished baking " + oven[i].getItem().getProductName() + " from order " + to_string(oven[i].getItem().getOrderId());
				ThreadOvens::setOvenMessageCustomStatus(i + 1, ovenMessageCustomStatus);
				oven[i].setSystemStatusOvens(OvenClass::toStringOvens(OvenClass::status_enum_ovens::NOT_COOKING));
				updateOvenStatus(con, i + 1, OvenClass::toStringOvens(OvenClass::status_enum_ovens::NOT_COOKING));
				struct curl_slist* headers = NULL;
				headers = curl_slist_append(headers, "Content-Type: application/json");
				json jsonMessage;
				jsonMessage["ovenId"] = i + 1;
				jsonMessage["productName"] = oven[i].getItem().getProductName();
				jsonMessage["orderId"] = oven[i].getItem().getOrderId();
				jsonMessage["ovenStatus"] = OvenClass::toStringOvens(OvenClass::status_enum_ovens::NOT_COOKING);
				jsonMessage["prepareTime"] = prepareTime_seconds;

				std::string jsonStr = jsonMessage.dump();
				curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
				curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
				curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
				curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadOvens);
				CURLcode res = curl_easy_perform(curl);

				curl_slist_free_all(headers);
			}
		}
	}
	curl_easy_cleanup(curl);
}

void ThreadOvens::processingOrder(OrderClass ord, sql::Connection* con) {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}

	bool verifyFood = true;
	bool verifyDrinkSauce = true;

	for (auto& item : ord.getList()) {
		int itemId = item.getItemId();
		int orderId = item.getOrderId();

		if (itemId >= 35 && itemId <= 38) {
			item.setType(OrderItems::ItemType::DRINK);
		}
		else if (itemId >= 39 && itemId <= 42) {
			item.setType(OrderItems::ItemType::SAUCE);
		}
		else if (itemId >= 1 && itemId <= 34) {
			item.setType(OrderItems::ItemType::FOOD);
		}

		verifyFood = verifyFood && areItemsEligibleFood(con, orderId);
		verifyDrinkSauce = verifyDrinkSauce && areItemsEligibleDrinkSauce(con, orderId);
	}

	if (!verifyFood || !verifyDrinkSauce) {
		for (auto& item : ord.getList()) {
			int orderId = item.getOrderId();
			CheckStatus::setOrderStatusInItems(CheckStatus::status_enum::CANCELED, orderId, con);
			CheckStatus::setOrderStatus(CheckStatus::status_enum::CANCELED, orderId, con);
			std::string observations = "Not enough raw material for cooking! Order CANCELED!";
			updateOrderStatusObservations(con, orderId, observations);
			updateOrderItemsObservations(con, orderId, observations);
		}
		return;
	}

	for (auto& item : ord.getList()) {
		int quantity = item.getQuantity();
		int countItem = 1;

		while (quantity > 0) {
			if (verifyFood) {
				if (item.getType() == OrderItems::ItemType::FOOD) {
					for (int i = 0; i < 5; i++) {
						if (oven[i].isAvailable() && oven[i].isDoneBaking()) {
							updateItemsRawMaterial(item.getItemId(), con);
							oven[i].addNextItem(item);
							oven[i].setQuantity(countItem);
							ord.addItemToItemsList(item, i);
							std::string ovenMessageCustomStatus = "Oven " + std::to_string(i + 1) + " is now baking " + item.getProductName() + " From order " + std::to_string(item.getOrderId());
							ThreadOvens::setOvenMessageCustomStatus(i + 1, ovenMessageCustomStatus);
							oven[i].setSystemStatusOvens(OvenClass::toStringOvens(OvenClass::status_enum_ovens::COOKING));
							updateOvenStatus(con, i + 1, OvenClass::toStringOvens(OvenClass::status_enum_ovens::COOKING));
							calculateTimeUsedAndItemsCooked(i, con);

							struct curl_slist* headers = nullptr;
							headers = curl_slist_append(headers, "Content-Type: application/json");

							json jsonMessage;
							jsonMessage["ovenId"] = i + 1;
							jsonMessage["productName"] = item.getProductName();
							jsonMessage["orderId"] = item.getOrderId();
							jsonMessage["ovenStatus"] = OvenClass::toStringOvens(OvenClass::status_enum_ovens::COOKING);

							std::string jsonStr = jsonMessage.dump();
							curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
							curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
							curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
							curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadOvens);

							CURLcode res = curl_easy_perform(curl);
							curl_slist_free_all(headers);

							if (con->isValid()) {
								CheckStatus::setItemStatus(CheckStatus::status_enum::IN_PREPARATION, oven[i].getItem().getItemId(), oven[i].getItem().getOrderId(), con);
								CheckStatus::setOrderStatus(CheckStatus::status_enum::IN_PREPARATION, oven[i].getItem().getOrderId(), con);
								quantity--;
								countItem++;
								break;
							}
							else {
								std::string databaseMessage = "Can't connect to database.";
								CheckStatus::setDatabaseStatusMessage(databaseMessage);
							}
						}
					}
				}
			}
			if (verifyDrinkSauce) {
				if (item.getType() == OrderItems::ItemType::DRINK || item.getType() == OrderItems::ItemType::SAUCE) {
					updateItemsRawMaterial(item.getItemId(), con);
					CheckStatus::setItemStatus(CheckStatus::status_enum::DONE, item.getItemId(), item.getOrderId(), con);
					quantity--;
					countItem++;
					if (allItemsDone(con, item.getOrderId()) == true) {
						CheckStatus::setOrderStatus(CheckStatus::status_enum::DONE, item.getOrderId(), con);
					}
				}
			}
		}
	}
	ThreadDelivery::addOrdersInPreparation(ord);
	curl_easy_cleanup(curl);
}




void ThreadOvens::systemStatusOvens() {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	double prepareTime_seconds;
	std::string ovenMessageCustom;
	for (int i = 0; i < 5; i++) {
		double remaining_cooking_time = getOvenRemainingTime(i);
		int percentage = getOvenPercentage(i);
		if (oven[i].getSystemStatusOvens() == OvenClass::toStringOvens(OvenClass::status_enum_ovens::NOT_COOKING) || oven[i].getSystemStatusOvens() == OvenClass::toStringOvens(OvenClass::status_enum_ovens::COOKING)) {
			prepareTime_seconds = oven[i].getItem().getPrepareTime();
			ovenMessageCustom = "Oven " + to_string(i + 1) + ": " + oven[i].getSystemStatusOvens();
			std::string prepTime;
			if (oven[i].getSystemStatusOvens() == OvenClass::toStringOvens(OvenClass::status_enum_ovens::NOT_COOKING)) {
				prepareTime_seconds = 0;
			}
			if (prepareTime_seconds != 0) {
				std::ostringstream stream;
				stream << std::fixed << std::setprecision(2) << prepareTime_seconds;
				std::string formattedPrepSeconds = stream.str();
				prepTime += "! Prepare Time: " + formattedPrepSeconds + "";
			}
			if (remaining_cooking_time >= 0) {
				std::ostringstream stream;
				stream << std::fixed << std::setprecision(2) << remaining_cooking_time;
				std::string formattedPrepSeconds = stream.str();
				prepTime += "! Remaining Time: " + formattedPrepSeconds + "";
			}
			if (percentage >= 0 && percentage <= 100) {
				std::ostringstream stream;
				stream << std::fixed << std::setprecision(2) << percentage;
				std::string formattedPrepSeconds = stream.str();
				prepTime += "! Percentage: " + formattedPrepSeconds + "%!";
			}
			ovenMessageCustom += prepTime;
			ThreadOvens::setOvenMessageCustom(i + 1, ovenMessageCustom);
		}
		else {
			oven[i].setSystemStatusOvens(OvenClass::toStringOvens(OvenClass::status_enum_ovens::IDLE));
			ovenMessageCustom = "Oven " + to_string(i + 1) + ": " + oven[i].getSystemStatusOvens();
			prepareTime_seconds = 0;
			percentage = 0;
			ThreadOvens::setOvenMessageCustom(i + 1, ovenMessageCustom);
		}

		struct curl_slist* headers = nullptr;
		headers = curl_slist_append(headers, "Content-Type: application/json");

		json jsonMessage;
		jsonMessage["ovenId"] = i + 1;
		jsonMessage["ovenStatus"] = oven[i].getSystemStatusOvens();
		if (prepareTime_seconds != 0) {
			jsonMessage["prepareTime"] = prepareTime_seconds;
		}
		jsonMessage["remainingTime"] = remaining_cooking_time;
		jsonMessage["percentageOvens"] = percentage;
		jsonMessage["sendTrue"] = true;


		std::string jsonStr = jsonMessage.dump();
		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/messageCustom");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadOvens);

		CURLcode res = curl_easy_perform(curl);

		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);
}

int ThreadOvens::selectOvenTimeUsed(int oven_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;
	pstm = con->prepareStatement("SELECT oven_time_used FROM ovens WHERE oven_id = ?");
	pstm->setInt(1, oven_id);
	rs = pstm->executeQuery();

	int total_seconds = 0;

	if (rs->next()) {
		std::string oven_time_used = rs->getString("oven_time_used");
		int hours, minutes, seconds;
		int items_read = sscanf(oven_time_used.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);

		if (items_read == 3) {
			total_seconds = hours * 3600 + minutes * 60 + seconds;
		}
	}

	return total_seconds;
}

void ThreadOvens::calculateTimeUsedAndItemsCooked(int oven_id, sql::Connection* con) {
	std::string systemStatus = oven[oven_id].getSystemStatusOvens();
	if (systemStatus == OvenClass::toStringOvens(OvenClass::status_enum_ovens::COOKING)) {


		int current_ovens_number = 0;
		current_ovens_number = selectCurrentNumberOvensDB(con, oven_id + 1);
		current_ovens_number++;
		incrementOvensDB(con, oven_id + 1, current_ovens_number);

		double ovenOldUsedTime = selectOvenTimeUsed(oven_id + 1, con);
		int oven_prepare_time = oven[oven_id].getItem().getPrepareTime();
		int ovenNewUsedTime = static_cast<int>(ovenOldUsedTime + oven_prepare_time);
		int hours, minutes, seconds;
		ThreadDelivery::convertToTime(ovenNewUsedTime, hours, minutes, seconds);
		std::ostringstream formattedTimeStream;
		formattedTimeStream << std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds << std::endl;
		std::string formattedTime = formattedTimeStream.str();
		updateOvenUsedTime(con, oven_id + 1, formattedTime);

	}
}

void ThreadOvens::updateOvenUsedTime(sql::Connection* con, int oven_id, std::string formattedTime) {
	sql::PreparedStatement* pstmUpdateTime;

	try {

		pstmUpdateTime = con->prepareStatement("UPDATE ovens SET oven_time_used = ? WHERE oven_id = ?");
		pstmUpdateTime->setString(1, formattedTime);
		pstmUpdateTime->setInt(2, oven_id);
		pstmUpdateTime->executeUpdate();
		updatePercentageProcedureOvens(con);
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating oven used time: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadOvens::updatePercentageProcedureOvens(sql::Connection* con) {
	sql::PreparedStatement* pstmCalculatePercentages;
	try {
		pstmCalculatePercentages = con->prepareStatement("UPDATE ovens "
			"JOIN( SELECT SUM(oven_time_used) AS total_time_ovens "
			"FROM ovens) AS subquery ON 1 = 1 "
			" SET ovens.oven_percentage = ROUND((ovens.oven_time_used / subquery.total_time_ovens) * 100, 2); ");
		pstmCalculatePercentages->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating deliverer percentage: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadOvens::incrementOvensDB(sql::Connection* con, int oven_id, int order_number) {
	sql::PreparedStatement* pstmUpdateDeliveries;
	try {

		pstmUpdateDeliveries = con->prepareStatement("UPDATE ovens SET oven_items_cooked = ? WHERE oven_id = ?");
		pstmUpdateDeliveries->setString(1, to_string(order_number));
		pstmUpdateDeliveries->setInt(2, oven_id);
		pstmUpdateDeliveries->executeUpdate();

	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating oven number of items cooked: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

int ThreadOvens::selectCurrentNumberOvensDB(sql::Connection* con, int oven_id) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;
	pstm = con->prepareStatement("SELECT oven_items_cooked FROM ovens WHERE oven_id = ?");
	pstm->setInt(1, oven_id);
	rs = pstm->executeQuery();
	int cookedItems_number = 0;
	if (rs->next()) {
		std::string oven_itemsCooked = rs->getString("oven_items_cooked");
		cookedItems_number = stoi(oven_itemsCooked);
	}

	return cookedItems_number;

}

void ThreadOvens::updateOvenStatus(sql::Connection* con, int oven_id, std::string ovenStatus) {
	sql::PreparedStatement* pstm;

	try {
		pstm = con->prepareStatement("UPDATE ovens SET oven_status = ? WHERE oven_id = ?");
		pstm->setString(1, ovenStatus);
		pstm->setInt(2, oven_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating oven status: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadOvens::updateItemsRawMaterial(int item_id, sql::Connection* con) {
	try {

		if (itemRawMaterialMap.find(item_id) != itemRawMaterialMap.end()) {
			std::vector<int> rawMaterials = itemRawMaterialMap[item_id];
			std::string query = "UPDATE raw_material SET quantity_raw_material = quantity_raw_material - 1 WHERE id_raw_material IN (";
			for (size_t i = 0; i < rawMaterials.size(); ++i) {
				query += std::to_string(rawMaterials[i]);
				if (i < rawMaterials.size() - 1) {
					query += ", ";
				}
			}
			query += ")";

			sql::PreparedStatement* pstm = con->prepareStatement(query);
			pstm->executeUpdate();
			updatestatusRawMaterials(con);
		}
		else {
		}
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating raw material quantity: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}


std::pair<std::vector<int>, int> ThreadOvens::statusRawMaterial(sql::Connection* con, std::string rawMaterialStatus) {
	std::vector<int> idList;
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	updatestatusRawMaterials(con);
	pstm = con->prepareStatement("SELECT id_raw_material FROM raw_material WHERE status_raw_material = ?");
	pstm->setString(1, rawMaterialStatus);

	rs = pstm->executeQuery();

	while (rs->next()) {
		int id = rs->getInt("id_raw_material");
		idList.push_back(id);
	}

	int listSize = idList.size();
	return std::make_pair(idList, listSize);
}

void ThreadOvens::updatestatusRawMaterials(sql::Connection* con) {
	sql::PreparedStatement* pstmProcedures;
	try {
		pstmProcedures = con->prepareStatement("UPDATE raw_material "
			"SET status_raw_material = "
			"CASE "
			"WHEN quantity_raw_material > 10 THEN 'ENOUGH_QUANTITY' "
			"WHEN quantity_raw_material <= 10 AND quantity_raw_material > 0 THEN 'LOW_QUANTITY' "
			"WHEN quantity_raw_material <= 0 THEN 'OUT_OF_QUANTITY' "
			" END; ");
		pstmProcedures->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating raw material status: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}

}

std::string ThreadOvens::selectStatusRawMaterial(sql::Connection* con, int material_id) {
	sql::PreparedStatement* pstmProcedures;
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	pstm = con->prepareStatement("SELECT status_raw_material FROM raw_material WHERE id_raw_material = ?");
	pstm->setInt(1, material_id);
	rs = pstm->executeQuery();

	std::string status_raw_material = "";

	if (rs->next()) {
		status_raw_material = rs->getString("status_raw_material");
	}

	return status_raw_material;
}

int ThreadOvens::selectQuantityRawMaterial(sql::Connection* con, int material_id) {
	sql::PreparedStatement* pstmProcedures;
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	pstm = con->prepareStatement("SELECT quantity_raw_material FROM raw_material WHERE id_raw_material = ?");
	pstm->setInt(1, material_id);
	rs = pstm->executeQuery();

	int quantity_raw_material = 0;

	if (rs->next()) {
		quantity_raw_material = rs->getInt("quantity_raw_material");
	}

	return quantity_raw_material;
}

bool ThreadOvens::areItemsEligibleFood(sql::Connection* con, int order_id) {
	int item_id = 0;
	const std::vector<std::pair<int, int>>& orderItems = ThreadOvens::selectAllItemsForOrderFood(con, order_id);
	for (const auto& orderItem : orderItems) {
		item_id = orderItem.first;
		int quantity = orderItem.second;

		if (!ThreadOvens::isProductEligible(con, item_id, quantity)) {
			return false;
		}
	}
	return true;
}

bool ThreadOvens::areItemsEligibleDrinkSauce(sql::Connection* con, int order_id) {
	int item_id = 0;
	const std::vector<std::pair<int, int>>& orderItems = ThreadOvens::selectAllItemsForOrderDrinkSauce(con, order_id);
	for (const auto& orderItem : orderItems) {
		item_id = orderItem.first;
		int quantity = orderItem.second;

		if (!ThreadOvens::isProductEligible(con, item_id, quantity)) {
			return false;
		}
	}
	return true;
}

bool ThreadOvens::isProductEligible(sql::Connection* con, int item_id, int quantity) {
	if (itemRawMaterialMap.find(item_id) == itemRawMaterialMap.end()) {
		return false;
	}

	const std::vector<int>& requiredIngredients = itemRawMaterialMap[item_id];
	for (int ingredientId : requiredIngredients) {
		int availableQuantity = ThreadOvens::selectQuantityRawMaterial(con, ingredientId);

		if (availableQuantity <= 0 || availableQuantity < quantity) {
			return false;
		}
	}
	return true;
}

void ThreadOvens::updateOrderStatusObservations(sql::Connection* con, int order_id, std::string observations) {
	sql::PreparedStatement* pstm;

	try {
		pstm = con->prepareStatement("UPDATE order_status SET observations = ? WHERE order_id = ?");
		pstm->setString(1, observations);
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating the observations: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadOvens::updateOrderItemsObservations(sql::Connection* con, int order_id, std::string observations) {
	sql::PreparedStatement* pstm;

	try {
		pstm = con->prepareStatement("UPDATE order_items SET item_observations = ? WHERE order_id = ?");
		pstm->setString(1, observations);
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating the observations: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

std::vector<std::pair<int, int>> ThreadOvens::selectAllItemsForOrderFood(sql::Connection* con, int order_id) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	pstm = con->prepareStatement("SELECT item_id, quantity FROM order_items WHERE order_id = ? AND item_id >= 1 AND item_id <= 34;");
	pstm->setInt(1, order_id);
	rs = pstm->executeQuery();

	std::vector<std::pair<int, int>> orderItems;

	while (rs->next()) {
		int item_id = rs->getInt("item_id");
		int quantity = rs->getInt("quantity");
		orderItems.emplace_back(item_id, quantity);
	}

	return orderItems;
}

std::vector<std::pair<int, int>> ThreadOvens::selectAllItemsForOrderDrinkSauce(sql::Connection* con, int order_id) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;

	pstm = con->prepareStatement("SELECT item_id, quantity FROM order_items WHERE order_id = ? AND item_id >= 35 AND item_id <= 42;");
	pstm->setInt(1, order_id);
	rs = pstm->executeQuery();

	std::vector<std::pair<int, int>> orderItems;

	while (rs->next()) {
		int item_id = rs->getInt("item_id");
		int quantity = rs->getInt("quantity");
		orderItems.emplace_back(item_id, quantity);
	}

	return orderItems;
}