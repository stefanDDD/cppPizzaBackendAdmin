#define NOMINMAX
#include "ThreadDelivery.h"
#include "OvenClass.h"
#include "CheckStatus.h"
#include "DeliveryClass.h"
#include <thread>
#include <iostream>
#include "OrderClass.h"
#include "OrderItems.h"
#include "OvenClass.h"
#include <chrono>
#include <list>
#include <windows.h>
#include <cppconn/driver.h>
#include <format>
#include "GraphClass.h"
#include "ThreadOvens.h"
#include <nlohmann/json.hpp>
#include "curl/curl.h"
#include "curl/easy.h"
#include <string>
#include <vector>
#include <sstream>
#include <boost/algorithm/string.hpp>
#include <algorithm>
#include <unordered_map>
#include <ctime>
using json = nlohmann::json;

DeliveryClass* deliverer = new DeliveryClass[5];
GraphClass graphUsersClass;
std::unique_ptr<Graph> graphUsers; 
list <OrderClass> listOrdersToDeliver;
list <OrderClass> listOrdersInPreparation;

std::map<int, std::vector<int>> ThreadDelivery::globalPath;
std::map<int, std::list<int>> ThreadDelivery::ordersSetDatabase;
std::map<int, OrderClass> ThreadDelivery::ordersIDsSetDatabase;
std::map<int, OrderClass> ThreadDelivery::ordersIDsSetDatabaseNext;
std::map<int, int> ThreadDelivery::globalRemainingTime;
std::map<int, std::string> ThreadDelivery::statusBar;
std::map<int, int> ThreadDelivery::globalRemainingTimeTotal;
std::map<int, double> ThreadDelivery::globalDistance;
std::map<int, int> ThreadDelivery::globalPercentage;
std::map<int, string> ThreadDelivery::delivererStatusMessage;
std::map<int, string> ThreadDelivery::delivererStatusMessageCustom;
std::map<int, string> ThreadDelivery::delivererStatusMessageStatusBar;
std::string ThreadDelivery::ordersInDeliverString;
std::string ThreadDelivery::delivererReadyStatus;
std::map<int, double> ThreadDelivery::percentageEachNodeVar;
std::map<int, string> ThreadDelivery::locationEachNodeVar;
std::unordered_map<int, double> deliveryStatusMapEachEdge;
std::unordered_map<int, std::string> deliveryLocationMapEachEdge;
std::unordered_map<int, int> deliveryStatusMap;
std::unordered_map<int, std::string> deliveryLocationMap;
std::map<int, int> ThreadDelivery::destinationNode;
std::map<int, int> ThreadDelivery::percentageIfStatemens;
std::map<int, int> ThreadDelivery::percentageComplete;


void ThreadDelivery::setPercentageComplete(int delivererID, int& percentageComplete_1) {
	percentageComplete[delivererID] = percentageComplete_1;
}

int ThreadDelivery::getPercentageComplete(int delivererID) {
	return percentageComplete[delivererID];
}

void ThreadDelivery::setStatusBar(int delivererID, std::string& statusBar_1) {
	statusBar[delivererID] = statusBar_1;
}

std::string ThreadDelivery::getStatusBar(int delivererID) {
	return statusBar[delivererID];
}

void ThreadDelivery::setDestinationNode(int delivererID, int& destinationNode_1) {
	destinationNode[delivererID] = destinationNode_1;
}

int ThreadDelivery::getDestinationNode(int delivererID) {
	return destinationNode[delivererID];
}

void ThreadDelivery::setLocationEachNodeVar(int delivererID, string& locationEachNodeVar_1) {
	locationEachNodeVar[delivererID] = locationEachNodeVar_1;
}

string ThreadDelivery::getLocationEachNodeVar(int delivererID) {
	return locationEachNodeVar[delivererID];
}

void ThreadDelivery::setPercentageEachNode(int delivererID, double& percentageEachNodeVar_1) {
	percentageEachNodeVar[delivererID] = percentageEachNodeVar_1;
}

double ThreadDelivery::getPercentageEachNode(int delivererID) {
	return percentageEachNodeVar[delivererID];
}

void ThreadDelivery::setDelivererReadyStatus(std::string& delivererReadyStatus) {
	ThreadDelivery::delivererReadyStatus = delivererReadyStatus;
}

std::string ThreadDelivery::getDelivererReadyStatus() {
	return delivererReadyStatus;
}

void ThreadDelivery::setOrdersInDeliverString(std::string& ordersInDeliverString) {
	ThreadDelivery::ordersInDeliverString = ordersInDeliverString;
}

std::string ThreadDelivery::getOrdersInDeliverString() {
	return ordersInDeliverString;
}

void ThreadDelivery::setDelivererStatusMessageStatusBar(int delivererID, std::string& delivererStatusMessageStausBar_1) {
	delivererStatusMessageStatusBar[delivererID] = delivererStatusMessageStausBar_1;
}

std::string ThreadDelivery::getDelivererStatusMessageStatusBar(int delivererID) {
	return delivererStatusMessageStatusBar[delivererID];
}

void ThreadDelivery::setDelivererStatusMessageCustom(int delivererID, std::string& delivererStatusMessageCustom_1) {
	delivererStatusMessageCustom[delivererID] = delivererStatusMessageCustom_1;
}

std::string ThreadDelivery::getDelivererStatusMessageCustom(int delivererID) {
	return delivererStatusMessageCustom[delivererID];
}

void ThreadDelivery::setDelivererStatusMessage(int delivererID, std::string& delivererStatusMessage_1) {
	delivererStatusMessage[delivererID] = delivererStatusMessage_1;
}

std::string ThreadDelivery::getDelivererStatusMessage(int delivererID) {
	return delivererStatusMessage[delivererID];
}

void ThreadDelivery::setGlobalPath(int delivererId, std::vector<int>& path) {
	globalPath[delivererId] = path;
}

std::vector<int> ThreadDelivery::getGlobalPath(int delivererId) {
	return globalPath[delivererId];

}

void ThreadDelivery::setOrdersIDsSetDatabaseNext(int delivererId, OrderClass ordersIDsSetDatabaseNext_1) {
	ordersIDsSetDatabaseNext[delivererId] = ordersIDsSetDatabaseNext_1;
}

OrderClass ThreadDelivery::getOrdersIDsSetDatabaseNext(int delivererId) {
	return ordersIDsSetDatabaseNext[delivererId];

}

void ThreadDelivery::setOrdersIDsSetDatabase(int delivererId, OrderClass ordersIDsSetDatabase_1) {
	ordersIDsSetDatabase[delivererId] = ordersIDsSetDatabase_1;
}

OrderClass ThreadDelivery::getOrdersIDsSetDatabase(int delivererId) {
	return ordersIDsSetDatabase[delivererId];

}

void ThreadDelivery::setOrdersSetDatabase(int delivererId, std::list<int>& ordersSetDatabase_1) {
	ordersSetDatabase[delivererId] = ordersSetDatabase_1;
}

std::list<int> ThreadDelivery::getOrdersSetDatabase(int delivererId) {
	return ordersSetDatabase[delivererId];

}

void ThreadDelivery::setGlobalRemainingTime(int delivererId, int& remainingTime_1) {
	globalRemainingTime[delivererId] = remainingTime_1;
}

int ThreadDelivery::getGlobalRemainingTime(int delivererId) {
	return globalRemainingTime[delivererId];

}

void ThreadDelivery::setGlobalRemainingTimeTotal(int delivererId, int& remainingTimeTotla_1) {
	globalRemainingTimeTotal[delivererId] = remainingTimeTotla_1;
}

int ThreadDelivery::getGlobalRemainingTimeTotal(int delivererId) {
	return globalRemainingTimeTotal[delivererId];

}

void ThreadDelivery::setGlobalDistance(int delivererId, double& distance_1) {
	globalDistance[delivererId] = distance_1;
}

double ThreadDelivery::getGlobalDistance(int delivererId) {
	return globalDistance[delivererId];

}

void ThreadDelivery::setGlobalPercentage(int delivererId, int& percentage_1) {
	globalPercentage[delivererId] = percentage_1;
}

int ThreadDelivery::getGlobalPercentage(int delivererId) {
	return globalPercentage[delivererId];

}

void ThreadDelivery::setPercentageIfStatemens(int delivererId, int& percentageIfStatemens_1) {
	percentageIfStatemens[delivererId] = percentageIfStatemens_1;
}

int ThreadDelivery::getPercentageIfStatemens(int delivererId) {
	return percentageIfStatemens[delivererId];

}

std::string convertFunctionToString(const  Graph::edge_descriptor& edge) {
	Graph::vertex_descriptor sourceVertex = source(edge, *graphUsers);
	Graph::vertex_descriptor targetVertex = target(edge, *graphUsers);

	std::string edgeString = "Edge [ " + std::to_string(sourceVertex) + " " + std::to_string(targetVertex) + " ]";
	return edgeString;
}
std::vector<int> convertFunction(const std::string& functie) {
	std::vector<std::string> tokens;
	boost::split(tokens, functie, boost::is_any_of("->"), boost::token_compress_on);

	std::vector<int> lista_numere(tokens.size());
	std::transform(tokens.begin(), tokens.end(), lista_numere.begin(), [](const std::string& token) { return std::stoi(token); });

	return lista_numere;
}

std::vector<int> convertFunctionEachPath(const std::string& input) {
	std::vector<std::string> tokens;
	std::string cleanedString = input.substr(1, input.size() - 2); 
	boost::split(tokens, cleanedString, boost::is_any_of(" "), boost::token_compress_on);

	std::vector<int> result;
	for (const auto& token : tokens) {
		std::stringstream ss(token);
		float num;
		if (ss >> num) {
			result.push_back(static_cast<int>(num));
		}
	}

	return result;
}

size_t discardResponseThreadDelivery(void*, size_t size, size_t nmemb, std::string* response) {
	return size * nmemb;
}

void showOrdersInDeliverList() {
	for (auto& order : listOrdersToDeliver) {
		std::string ordersInDeliverString = order.getUserId() + " " + order.getOrderId();
		ThreadDelivery::setOrdersInDeliverString(ordersInDeliverString);
	}
}

void ThreadDelivery::addOrdersInPreparation(OrderClass& ord) {
	listOrdersInPreparation.push_back(ord);
}

void removeOrdfromOrdersInPreparationord(OrderClass& ord) {
	int userId = ord.getUserId();
	for (auto it = listOrdersInPreparation.begin(); it != listOrdersInPreparation.end(); ++it) {
		if (it->getUserId() == userId) {
			it = listOrdersInPreparation.erase(it);
		}
	}
}

void addNewOrderInDeliverList(OrderClass& ord) {
	listOrdersToDeliver.push_back(ord);
}

void ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum sts_delivery, int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	try {
		pstm = con->prepareStatement("UPDATE order_status SET status = ? WHERE order_id = ?");
		pstm->setString(1, CheckStatus::toString(sts_delivery));
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating order status : " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadDelivery::setItemsStatusDelivery(CheckStatus::status_enum sts, int order_id, sql::Connection* con) {
	sql::PreparedStatement* pstm;
	try {
		pstm = con->prepareStatement("UPDATE order_items SET item_status = ? WHERE order_id = ?");
		pstm->setString(1, CheckStatus::toString(sts));
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating order status : " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);

	}
}

void ThreadDelivery::setItemandOrderStatusToDelivery(sql::Connection* con, int delivererId, int userId) {
	int orderId = deliverer[delivererId].getOrderId(userId);
	setItemsStatusDelivery(CheckStatus::status_enum::DELIVERED, orderId, con);
	setStatusToDelivery(CheckStatus::status_enum::DELIVERED, orderId, con);
}


void updateStatusBar(int deliverId, int percentage, const std::string& location) {
	deliveryStatusMap[deliverId] = percentage;
	deliveryLocationMap[deliverId] = location;
}

void ThreadDelivery::displayAllStatusBars() {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	for (const auto& pair : deliveryStatusMap) {
		int deliverId = pair.first;
		int percentage = pair.second;
		const std::string& location = deliveryLocationMap[deliverId];

		int numChars = percentage / 10;

		std::string statusBar;
		statusBar += '[';
		for (int i = 0; i < numChars; i++) {
			statusBar += '#';
		}
		for (int i = numChars; i < 10; i++) {
			statusBar += ' ';
		}
		statusBar += ']';
		std::string delivererStatusMessageStatusBar = "Deliverer " + to_string(deliverId + 1) + ": " + string(statusBar) + " " + to_string(percentage) + "% " + string(location);
		ThreadDelivery::setDelivererStatusMessageStatusBar(deliverId + 1, delivererStatusMessageStatusBar);

		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		json jsonMessage;
		jsonMessage["delivererId"] = deliverId + 1;
		jsonMessage["statusBar"] = statusBar;
		jsonMessage["percentage"] = percentage;
		jsonMessage["location"] = location;
		jsonMessage["isDeliveringMap"] = true;

		std::string jsonStr = jsonMessage.dump();

		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

		CURLcode res = curl_easy_perform(curl);
		curl_slist_free_all(headers);


	}
	std::cout.flush();
	curl_easy_cleanup(curl);

}

double ThreadDelivery::waitForDelivery(double distance, int userId, int nextUserId, int delivererId) {

	const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	const std::time_t t_currentTime = std::chrono::system_clock::to_time_t(currentTime);

	const std::chrono::time_point<std::chrono::system_clock> delivery_start_time = deliverer[delivererId].getTime();
	const std::time_t t_delivery_start_time = std::chrono::system_clock::to_time_t(delivery_start_time);

	double deliveryTime_seconds = distance;
	string msg;

	if (nextUserId == 0) {
		msg = "Comeback | " + std::to_string(userId) + " -> " + std::to_string(nextUserId);
	}
	else {
		msg = "In Delivery |" + std::to_string(userId) + " -> " + std::to_string(nextUserId);
	}
	if (t_currentTime - t_delivery_start_time <= deliveryTime_seconds) {
		int percentage = static_cast<int>(((t_currentTime - t_delivery_start_time) * 100) / deliveryTime_seconds);
		updateStatusBar(delivererId, percentage, msg);
		setPercentageComplete(delivererId, percentage);
		setPercentageIfStatemens(delivererId, percentage);
		return 0;
	}
}

int getFreeDeliverers() {
	int nr{ 0 };
	for (int i = 0; i < 5; i++) {
		if (deliverer[i].isDelivererAvailable()==true) {
			nr++;
		}
	}
	return nr;
}
list<int> ThreadDelivery::ordersSort(list<int>& orders) {
	for (auto ord = orders.begin(); ord != orders.end(); ++ord) {
		double distance = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, *ord);
		auto nextOrd = std::next(ord);
		double distance2;
		if (nextOrd != orders.end()) {
			int nextUserId = *nextOrd;
			distance2 = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, nextUserId);
			if (distance2 < distance) {
				std::iter_swap(ord, nextOrd);
			}
		}
	}
	orders.unique();
	orders.push_back(0);
	orders.push_front(0);
	return orders;
}
void ThreadDelivery::checkDeliverersGraph(sql::Connection* con) {
	graphUsers = graphUsersClass.generateGraph();

	std::vector<std::thread> threads;
	for (int i = 0; i < 5; i++) {
		threads.emplace_back(&ThreadDelivery::processDeliverer, i, con);
	}

	for (auto& thread : threads) {
		thread.join();
	}
}

void lastNodeDestination() {

}


void ThreadDelivery::updateUserArrivalTime(sql::Connection* con, int userId, const std::_Timeobj<char, const tm*>& arrivalTime) {
	sql::PreparedStatement* pstm;

	try {
		int hour = arrivalTime._Tptr->tm_hour;
		int min = arrivalTime._Tptr->tm_min;
		int sec = arrivalTime._Tptr->tm_sec;

		std::ostringstream formattedTime;
		formattedTime << std::setfill('0') << std::setw(2) << hour << ":"
			<< std::setfill('0') << std::setw(2) << min << ":"
			<< std::setfill('0') << std::setw(2) << sec;
		pstm = con->prepareStatement("UPDATE users SET arrivalTime = ? WHERE user_id = ?");
		pstm->setString(1, formattedTime.str());
		pstm->setInt(2, userId);
		pstm->executeUpdate();
		delete pstm;
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating user distance: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadDelivery::updateDeliveredTimeOrder(sql::Connection* con, int order_id, const std::_Timeobj<char, const tm*>& deliveredTime) {
	sql::PreparedStatement* pstm;

	try {
		int hour = deliveredTime._Tptr->tm_hour;
		int min = deliveredTime._Tptr->tm_min;
		int sec = deliveredTime._Tptr->tm_sec;

		std::ostringstream formattedTime;
		formattedTime << std::setfill('0') << std::setw(2) << hour << ":"
			<< std::setfill('0') << std::setw(2) << min << ":"
			<< std::setfill('0') << std::setw(2) << sec;
		pstm = con->prepareStatement("UPDATE order_status SET deliveredTime = ? WHERE order_id = ?");
		pstm->setString(1, formattedTime.str());
		pstm->setInt(2, order_id);
		pstm->executeUpdate();
		delete pstm;
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating user distance: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}


void ThreadDelivery::saveAproximativTimeDatabase(int i, sql::Connection* con) {
	int userIdOrders = 0;
	int nextUserIdOrders = 0;


	const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	const std::time_t t_currentTime = std::chrono::system_clock::to_time_t(currentTime);

	for (int num : ThreadDelivery::getOrdersSetDatabase(i)) {
		if (num == 0) {
			continue;
		}
		else if (userIdOrders == 0) {
			userIdOrders = num;
		}
		else if (nextUserIdOrders == 0) {
			nextUserIdOrders = num;
			break;
		}
	}
	double arrivalTime_firstUser = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, userIdOrders);

	double total_arrivalTime_firstUser = t_currentTime + arrivalTime_firstUser;
	time_t total_arrivalTime_firstUser_seconds = static_cast<time_t>(total_arrivalTime_firstUser);
	const auto time_clock_arrival_firstUser = std::put_time(std::localtime(&total_arrivalTime_firstUser_seconds), "%T.\n");

	OrderClass ord = getOrdersIDsSetDatabase(i);
	OrderClass ordNext = getOrdersIDsSetDatabaseNext(i);
	
	updateUserArrivalTime(con, userIdOrders, time_clock_arrival_firstUser);

	if (ord.getUserId() != userIdOrders) {
		updateDeliveredTimeOrder(con, ordNext.getOrderId(), time_clock_arrival_firstUser);
	}
	else if(ord.getUserId() == userIdOrders) {
		updateDeliveredTimeOrder(con, ord.getOrderId(), time_clock_arrival_firstUser);
	}
	if (nextUserIdOrders != 0) {
		double arrivalTime_secondUser = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, userIdOrders, nextUserIdOrders);
		double total_arrivalTime_secondUser = t_currentTime + arrivalTime_firstUser + arrivalTime_secondUser;
		time_t total_arrivalTime_seconds = static_cast<time_t>(total_arrivalTime_secondUser);
		const auto time_clock_arrival_secondUser = std::put_time(std::localtime(&total_arrivalTime_seconds), "%T.\n");
		updateUserArrivalTime(con, nextUserIdOrders, time_clock_arrival_secondUser);
		if (ordNext.getUserId() != nextUserIdOrders) {
			updateDeliveredTimeOrder(con, ord.getOrderId(), time_clock_arrival_secondUser);
		}
		else if (ordNext.getUserId() == nextUserIdOrders) {
			updateDeliveredTimeOrder(con, ordNext.getOrderId(), time_clock_arrival_secondUser);
		}
	}
}

void ThreadDelivery::processDeliverer(int i, sql::Connection* con) {
	std::string delivererStatusMessageCustom;
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	while (true) {
		if (deliverer[i].isDelivererAvailable() == false && deliverer[i].isDoneDelivering() == false) {
			updateStatusBar(i, 0, "In Delivery");

			list<int> orders = deliverer[i].getOrdersList();
			orders = ordersSort(orders);
			ThreadDelivery::setOrdersSetDatabase(i, orders);
			ThreadDelivery::saveAproximativTimeDatabase(i, con);
			std::string delivererMessage = "Deliverer " + std::to_string(i + 1) + " path: ";
			deliverer[i].setSystemStatusDelivery(DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING));
			updateDeliveryStatus(con, i + 1, DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING));
			ThreadDelivery::calculateTimeUsedAndDeliveries(i, con);
			std::string ordersStr;
			for (auto ordInt : orders) {
				ordersStr += std::to_string(ordInt) + " ";
			}
			delivererStatusMessageCustom = delivererMessage + ordersStr;
			ThreadDelivery::setDelivererStatusMessageCustom(i + 1, delivererStatusMessageCustom);
			struct curl_slist* headers = NULL;
			headers = curl_slist_append(headers, "Content-Type: application/json");
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

			json jsonMessage;
			jsonMessage["delivererId"] = i + 1;
			jsonMessage["isDelivering"] = 0;
			jsonMessage["delivererStatus"] = DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING);

			std::string jsonStr = jsonMessage.dump();

			curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
			curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
			curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);


			CURLcode res = curl_easy_perform(curl);

			auto ord = orders.begin();
			auto nextOrd = std::next(ord);
			bool path = false;
			bool isReturning = false;
			int percentage = 0;
			for (; ord != orders.end();) {

				int userId = *ord;
				int nextUserId = *nextOrd;
				int userIdEach = *ord;
				int nextUserIdEach = *nextOrd;
				double distance = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, userId, nextUserId);
				std::vector<Graph::edge_descriptor> eachEdge = graphUsersClass.dijkstraShortestPathGetEachEdge(*graphUsers, userIdEach, nextUserIdEach);
				percentageEachNode(i, userIdEach, nextUserIdEach);
				waitForDelivery(distance, userId, nextUserId, i);
				if (path == false) {
					path = true;
					delivererStatusMessageCustom = "Deliverer " + to_string(i + 1) + " current path: " + graphUsersClass.dijkstraShortestPathGetPath(*graphUsers, userId, nextUserId) + ".";
					ThreadDelivery::setDelivererStatusMessageCustom(i + 1, delivererStatusMessageCustom);
					struct curl_slist* headers = NULL;
					headers = curl_slist_append(headers, "Content-Type: application/json");
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
					std::string shortestPath = graphUsersClass.dijkstraShortestPathGetPath(*graphUsers, userId, nextUserId);
					std::size_t lastSpacePos = shortestPath.rfind(' ');
					std::string lastElementString = shortestPath.substr(lastSpacePos + 1);
					int lastNode = std::stoi(lastElementString);
					setDestinationNode(i + 1, lastNode);
					json jsonMessage;
					jsonMessage["delivererId"] = i + 1;
					jsonMessage["currentPath"] = convertFunction(graphUsersClass.dijkstraShortestPathGetPath(*graphUsers, userId, nextUserId));
					jsonMessage["isDelivering"] = 1;
					jsonMessage["delivererStatus"] = DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING);

					std::string jsonStr = jsonMessage.dump();

					curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

					CURLcode res = curl_easy_perform(curl);
					curl_slist_free_all(headers);
				}

				if (getPercentageIfStatemens(i) == 100) {
					if (nextUserId != 0) {
						setItemandOrderStatusToDelivery(con, i, nextUserId);
						std::ostringstream stream;
						stream << std::fixed << std::setprecision(2) << distance * 2;
						std::string formattedTime = stream.str();

						std::ostringstream stream2;
						stream2 << std::fixed << std::setprecision(2) << distance;
						std::string formattedDistance = stream2.str();
						delivererStatusMessageCustom = "Deliverer " + to_string(i + 1) + " has finished the delivery from " + to_string(userId) + " to " + to_string(nextUserId)
							+ " in \n            " + formattedTime + " minutes and distance " + formattedDistance + ".";
						ThreadDelivery::setDelivererStatusMessageCustom(i + 1, delivererStatusMessageCustom);
						struct curl_slist* headers = NULL;
						headers = curl_slist_append(headers, "Content-Type: application/json");
						curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

						json jsonMessage;
						jsonMessage["delivererId"] = i + 1;
						jsonMessage["userId"] = userId;
						jsonMessage["nextUserId"] = nextUserId;
						jsonMessage["deliveryTime"] = distance * 2;
						jsonMessage["distance"] = distance;
						jsonMessage["isDelivering"] = 3;
						jsonMessage["delivererStatus"] = DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING);


						std::string jsonStr = jsonMessage.dump();

						curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
						curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
						curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

						CURLcode res = curl_easy_perform(curl);

						curl_slist_free_all(headers);
					}
					deliverer[i].setTime();

					if (nextUserId == 0) {
						delivererStatusMessageCustom = "Deliverer " + to_string(i + 1) + " has finished the delivery to all customers.";
						ThreadDelivery::setDelivererStatusMessageCustom(i + 1, delivererStatusMessageCustom);
						struct curl_slist* headers = NULL;
						headers = curl_slist_append(headers, "Content-Type: application/json");
						curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

						json jsonMessage;
						jsonMessage["delivererId"] = i + 1;
						jsonMessage["isDelivering"] = 4;
						jsonMessage["delivererStatus"] = DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING);


						std::string jsonStr = jsonMessage.dump();

						curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
						curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
						curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
						curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

						CURLcode res = curl_easy_perform(curl);
						curl_slist_free_all(headers);
						isReturning = true;
					}
					++ord, ++nextOrd;
					path = false;
				}
				else if (getPercentageIfStatemens(i) == 50) {
					std::ostringstream stream;
					stream << std::fixed << std::setprecision(2) << (distance / 2) * 2.0;
					std::string formattedRemainingTime = stream.str();

					std::ostringstream stream2;
					stream2 << std::fixed << std::setprecision(2) << distance / 2;
					std::string formattedDistance = stream2.str();
					delivererStatusMessageCustom = "Deliverer " + to_string(i + 1) + " is at half of distance: " + formattedDistance
						+ " from " + to_string(userId) + " to " + to_string(nextUserId) + ",\n            remaining time - " + formattedRemainingTime
						+ " minutes.";
					ThreadDelivery::setDelivererStatusMessageCustom(i + 1, delivererStatusMessageCustom);
					struct curl_slist* headers = NULL;
					headers = curl_slist_append(headers, "Content-Type: application/json");
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

					json jsonMessage;
					jsonMessage["delivererId"] = i + 1;
					jsonMessage["halfDistance"] = distance / 2;
					jsonMessage["userId"] = userId;
					jsonMessage["nextUserId"] = nextUserId;
					jsonMessage["halfTime"] = (distance / 2) * 2.0;
					jsonMessage["isDelivering"] = 2;
					jsonMessage["delivererStatus"] = DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING);


					std::string jsonStr = jsonMessage.dump();

					curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

					CURLcode res = curl_easy_perform(curl);
					curl_slist_free_all(headers);
					path = false;

				}

				if (isReturning && nextOrd == orders.end()) {
					delivererStatusMessageCustom = "Deliverer " + to_string(i + 1) + " has returned to the restaurant.";
					ThreadDelivery::setDelivererStatusMessageCustom(i + 1, delivererStatusMessageCustom);
					deliverer[i].setSystemStatusDelivery(DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::NOT_DELIVERING));
					updateDeliveryStatus(con, i + 1, DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING));
					struct curl_slist* headers = NULL;
					headers = curl_slist_append(headers, "Content-Type: application/json");
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


					json jsonMessage;
					jsonMessage["delivererId"] = i + 1;
					jsonMessage["isDelivering"] = 5;
					jsonMessage["delivererStatus"] = DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::NOT_DELIVERING);

					std::string jsonStr = jsonMessage.dump();

					curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

					CURLcode res = curl_easy_perform(curl);

					curl_slist_free_all(headers);

					deliverer[i].endDelivery();
					updateStatusBar(i, 0, "Home");
					break;
				}
			}
		}
		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	curl_easy_cleanup(curl);
}
double totalDistanceF(OrderClass ord, OrderClass ordNext, bool &distanceOk, double distanceMax) {
	double distanceOrd = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, ord.getUserId());
	double distanceOrdNext = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, ordNext.getUserId());
	double distanceBetween = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, ord.getUserId(), ordNext.getUserId());
	double totalDistance = 0;

	if (distanceOrd < distanceOrdNext) {
		if ((distanceOrd + distanceBetween) <= distanceMax) {
			distanceOk = true;
			return totalDistance = distanceOrd + distanceBetween;
		}
		else {
			return -1;
		}
	}
	else {
		if ((distanceOrdNext + distanceBetween) <= distanceMax) {
			distanceOk = true;
			return totalDistance = distanceOrdNext + distanceBetween;
		}
		else {
			return -1;
		}
	}
}
bool verifyDistanceBetween(OrderClass ord, OrderClass ordNext) {
	double distanceOrd = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, ord.getUserId());
	double distanceOrdNext = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, ordNext.getUserId());
	double distanceBetween = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, ord.getUserId(), ordNext.getUserId());

	if (distanceBetween < distanceOrd /2.0) {
		return true;
	}
	return false;
}


bool waitForAnotherOrd() {
	for (auto &ord : listOrdersInPreparation) {
		bool allItemsReady = true;
		for (auto &item : ord.getItemsList()) {
			if (!item.first.getOvenStatus()) {
				allItemsReady = false;
				break;
			}
		}
		if (allItemsReady) {
			return true;
		}
	}
	return false;
}

void ThreadDelivery::processingDelivery(sql::Connection* con) {
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	while (1) {
		std::this_thread::sleep_for(std::chrono::seconds(10));
		while (!listOrdersToDeliver.empty()) {
			bool orderAdded = false;
			bool delivererFound = false;
			int delivererId;
			auto it = listOrdersToDeliver.begin();
			while (it != listOrdersToDeliver.end()) {
				auto ord = *it;
				bool distanceOk = false;

				if (listOrdersToDeliver.size() > 1) {
					auto nextIt = std::next(it);
					if (nextIt != listOrdersToDeliver.end()) {
						auto ordNext = *nextIt;
						double totalDistance = totalDistanceF(ord, ordNext, distanceOk, 50);
						bool distanceBetween = verifyDistanceBetween(ord, ordNext);
						int freeDeliverers = getFreeDeliverers();
						bool worth2deliverers = verifyDistanceBetween(ord, ordNext);
					    for (int i = 0; i < 5; i++) {
							if (deliverer[i].isDelivererAvailable() && deliverer[i].isDoneDelivering()) {
								if (distanceOk == true && worth2deliverers == true) {
									deliverer[i].addIdOrdertoOrderList(ord);
									ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, ord.getOrderId(), con);
									deliverer[i].addIdOrdertoOrderList(ordNext);
									ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, ordNext.getOrderId(), con);
									deliverer[i].startDelivery();
									deliverer[i].addTotalDistance(totalDistance);
									it = listOrdersToDeliver.erase(it);
									nextIt = listOrdersToDeliver.erase(nextIt);
									setOrdersIDsSetDatabase(i, ord);
									setOrdersIDsSetDatabaseNext(i, ordNext);
									break;
								}

								if (freeDeliverers<=2) {
									deliverer[i].addIdOrdertoOrderList(ord);
									ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, ord.getOrderId(), con);
									deliverer[i].addIdOrdertoOrderList(ordNext);
									ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, ordNext.getOrderId(), con);
									deliverer[i].startDelivery();
									deliverer[i].addTotalDistance(totalDistance);
									it = listOrdersToDeliver.erase(it);
									nextIt = listOrdersToDeliver.erase(nextIt);
									setOrdersIDsSetDatabase(i, ord);
									setOrdersIDsSetDatabaseNext(i, ordNext);
									break;
								}

								else
								{
									deliverer[i].addIdOrdertoOrderList(ord);
									ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, ord.getOrderId(), con);
									it = listOrdersToDeliver.erase(it);
									deliverer[i].startDelivery();
									setOrdersIDsSetDatabase(i, ord);
									break;

								}
							}
						}
						break;
					}

					else {
						++it;
					}
				}
				else {
					for (int i = 0; i < 5; i++) {
						if (deliverer[i].isDelivererAvailable() && deliverer[i].isDoneDelivering()) {
							deliverer[i].addIdOrdertoOrderList(ord);
							ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, ord.getOrderId(), con);
							deliverer[i].addTotalDistance(2*graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, ord.getUserId()));
							orderAdded = true;
							delivererFound = true;
							delivererId = i;
							setOrdersIDsSetDatabase(i, ord);
							break;
						}
					}
					it = listOrdersToDeliver.erase(it);
					break;
				}
			}
			
			if (delivererFound && orderAdded) {
				if (waitForAnotherOrd()){
					std::string delivererStatusMessageCustom = "Deliverer " + to_string(delivererId) + " is waiting for an order to be done.";
					ThreadDelivery::setDelivererStatusMessageCustom(delivererId + 1, delivererStatusMessageCustom);

					struct curl_slist* headers = NULL;
					headers = curl_slist_append(headers, "Content-Type: application/json");

					json jsonMessage;
					jsonMessage["delivereId"] = delivererId;
					jsonMessage["waitingTooLong"] = true;

					std::string jsonStr = jsonMessage.dump();

					curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
					curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
					curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
					curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

					CURLcode res = curl_easy_perform(curl);

					curl_slist_free_all(headers);
					std::this_thread::sleep_for(std::chrono::seconds(3));

				}

				auto nextIt = listOrdersToDeliver.begin();
				if (nextIt != listOrdersToDeliver.end()) {
					auto &nextOrd = *nextIt;
					deliverer[delivererId].addIdOrdertoOrderList(nextOrd);
					ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::IN_DELIVERY, nextOrd.getOrderId(), con);
					listOrdersToDeliver.erase(nextIt);
					deliverer[delivererId].startDelivery();
					setOrdersIDsSetDatabaseNext(delivererId, nextOrd);
					break;
				}
				deliverer[delivererId].startDelivery();
				break;
			}

			std::this_thread::sleep_for(std::chrono::seconds(3));
		}

		std::this_thread::sleep_for(std::chrono::seconds(3));
	}
	curl_easy_cleanup(curl);
}


bool existFreeDeliver() {
	int var{ 0 };
	for (int i{ 0 }; i < 5; i++) {
		if (deliverer[i].isDelivererAvailable() == true) {
			return true;
		}
	}
	return false;
}

int ThreadDelivery::checkFreeDeliverers(sql::Connection* con) {
	int var{ 0 };
	for (int i{ 0 }; i < 5; i++) {
		if (deliverer[i].isDelivererAvailable() == true) {
			var++;
		}
	}
	return var;
}

void ThreadDelivery::delivery(sql::Connection* con) {

	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}

	sql::ResultSet* rs;
	sql::PreparedStatement* pstm;

	pstm = con->prepareStatement("SELECT user_id,order_id FROM order_status "
		"WHERE status = 'DONE' ORDER BY order_id asc");
	rs = pstm->executeQuery();

	if (rs->next()) {
		OrderClass ord;
		CheckStatus::getOrder(ord, rs->getInt("order_id"), con);
		addNewOrderInDeliverList(ord);
		removeOrdfromOrdersInPreparationord(ord);
		ThreadDelivery::setStatusToDelivery(CheckStatus::status_enum::READY_FOR_DELIVERY, rs->getInt("order_id"), con);
		ThreadDelivery::setItemsStatusDelivery(CheckStatus::status_enum::READY_FOR_DELIVERY, rs->getInt("order_id"), con);
		std::this_thread::sleep_for(chrono::seconds(3));
	}
	else {
		std::string delivererReadyStatus = "Not new done orders. Deliverer ready " + to_string(checkFreeDeliverers(con)) + "/5.";
		ThreadDelivery::setDelivererReadyStatus(delivererReadyStatus);
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);


		json jsonMessage;
		jsonMessage["freeDeliverers"] = checkFreeDeliverers(con);
		jsonMessage["freeDeliverersCheck"] = true;

		std::string jsonStr = jsonMessage.dump();

		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/message");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

		CURLcode res = curl_easy_perform(curl);

		curl_slist_free_all(headers);
		std::this_thread::sleep_for(chrono::seconds(3));
	}
	curl_easy_cleanup(curl);
}



void ThreadDelivery::deliveryThread(sql::Connection* con) {
	graphUsers = graphUsersClass.generateGraph();
	while (true) {
		if (con->isValid()) {
			delivery(con);
			std::this_thread::sleep_for(std::chrono::seconds(3));
		}
		else {
			std::string databaseMessage = "Can't connect to database.";
			CheckStatus::setDatabaseStatusMessage(databaseMessage);

		}

	}

}

void ThreadDelivery::systemStatusDelivery() {
	ThreadDelivery threadDeliveryInstance;
	CURL* curl = curl_easy_init();
	if (!curl) {
		std::string curlMessage = "Failed to initialize curl";
		CheckStatus::setCurlStatusMessage(curlMessage);
		return;
	}
	for (int i = 0; i < 5; i++) {
		std::vector<int> path = threadDeliveryInstance.getGlobalPath(i + 1);
		double remainingTime = threadDeliveryInstance.getGlobalRemainingTime(i + 1);
		double remainingTimeTotal = threadDeliveryInstance.getGlobalRemainingTimeTotal(i + 1);
		double distance = threadDeliveryInstance.getGlobalDistance(i + 1);
		int percentage = threadDeliveryInstance.getGlobalPercentage(i + 1);
		std::string statusBar = threadDeliveryInstance.getStatusBar(i + 1);
		int percentageComplete = threadDeliveryInstance.getPercentageComplete(i + 1);

		std::string systemStatus = deliverer[i].getSystemStatusDelivery();
		std::string delivererMessage = "Deliverer " + std::to_string(i + 1) + ": " + systemStatus;

		if (systemStatus == DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING)) {
			if (!path.empty()) {
				std::string pathMessage = "! Edge: [ ";
				for (int element : path) {
					pathMessage += std::to_string(element) + " ";
				}
				pathMessage += "]";
				delivererMessage += pathMessage;
			}
		}
		else if (systemStatus == DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::NOT_DELIVERING)) {
			remainingTime = 0.0;
			distance = 0.0;
			percentage = 0;
			path.clear();
		}
		else {
			deliverer[i].setSystemStatusDelivery(DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::IDLE));
			remainingTime = 0.0;
			distance = 0.0;
			percentage = 0;
			path.clear();
		}
		
		ThreadDelivery::setDelivererStatusMessage(i + 1, delivererMessage);
		if (systemStatus != DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::NOT_DELIVERING) || !path.empty()) {
			std::string statusMessage;
			if (percentage != 0) {
				statusMessage +=  + "! Progress: "+ statusBar + "! Percentage: " + std::to_string(percentage) + "%!";
			}

			if (distance != 0) {
				std::ostringstream stream;
				stream << std::fixed << std::setprecision(2) << distance;
				std::string formattedDistance = stream.str();
				statusMessage += "\n             Total distance: " + formattedDistance + "";
			}
			if (remainingTime != 0) {
				std::ostringstream stream;
				stream << std::fixed << std::setprecision(2) << remainingTime;
				std::string formattedRemainingTime = stream.str();
				statusMessage +=  + "! Edge time: " + formattedRemainingTime + "! " ;
			}
			if (remainingTimeTotal != 0) {
				std::ostringstream stream;
				stream << std::fixed << std::setprecision(2) << remainingTimeTotal;
				std::string formattedRemainingTime = stream.str();
				statusMessage += "Total time: " + formattedRemainingTime + "!";
			}
			delivererMessage += statusMessage;

		}
		ThreadDelivery::setDelivererStatusMessage(i + 1, delivererMessage);
		struct curl_slist* headers = NULL;
		headers = curl_slist_append(headers, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

		json jsonMessage;
		jsonMessage["delivererId"] = i + 1;
		jsonMessage["delivererStatus"] = deliverer[i].getSystemStatusDelivery();
		jsonMessage["delivererDistance"] = threadDeliveryInstance.getGlobalDistance(i + 1);
		jsonMessage["delivererPath"] = threadDeliveryInstance.getGlobalPath(i + 1);
		jsonMessage["delivererTimeToArrival"] = threadDeliveryInstance.getGlobalRemainingTime(i + 1);
		jsonMessage["delivererTimeToArrivalTotal"] = threadDeliveryInstance.getGlobalRemainingTimeTotal(i + 1);
		jsonMessage["delivererPercentage"] = threadDeliveryInstance.getGlobalPercentage(i + 1);
		jsonMessage["delivererDestination"] = threadDeliveryInstance.getDestinationNode(i + 1);
		jsonMessage["delivererPercentageComplete"] = threadDeliveryInstance.getPercentageComplete(i + 1);
		jsonMessage["delivererSendTrue"] = true;

		std::string jsonStr = jsonMessage.dump();

		curl_easy_setopt(curl, CURLOPT_URL, "http://127.0.0.1:5502/messageCustom");
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, jsonStr.c_str());
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, discardResponseThreadDelivery);

		CURLcode res = curl_easy_perform(curl);

		curl_slist_free_all(headers);
	}
	curl_easy_cleanup(curl);


}
void ThreadDelivery::updateEachEdge(int deliverId, double percentageEachEdge, std::string edgeDesc, double edgeDistance, double totalDistance, double totalDistance_toDisplay) {
	deliveryStatusMapEachEdge[deliverId] = percentageEachEdge;

	std::ostringstream streamPercentage;
	streamPercentage << std::fixed << std::setprecision(2) << percentageEachEdge;
	std::string formattedStreamPercentage = streamPercentage.str();
	deliveryLocationMapEachEdge[deliverId] = edgeDesc;
	std::vector<int> edgeDesc_vec =  convertFunctionEachPath(edgeDesc);
	setGlobalPath(deliverId + 1, edgeDesc_vec);
	double remainingTimeEdge = edgeDistance - ((percentageEachEdge / 100) * edgeDistance);
	int remainingTimeEdge_int = static_cast<int>(remainingTimeEdge);
	setGlobalRemainingTime(deliverId + 1, remainingTimeEdge_int);
	setGlobalDistance(deliverId + 1, totalDistance_toDisplay);
	int percentage = static_cast<int>(percentageEachEdge);
	setGlobalPercentage(deliverId + 1, percentage);
	double remainingTimeTotal = totalDistance - ((percentageEachEdge / 100) * edgeDistance);
	int remainingTimeTotal_int = static_cast<int>(remainingTimeTotal);
	setGlobalRemainingTimeTotal(deliverId + 1, remainingTimeTotal_int);

	int numChars = percentage / 10;

	std::string statusBar;
	statusBar += '[';
	for (int i = 0; i < numChars; i++) {
		statusBar += '#';
	}
	for (int i = numChars; i < 10; i++) {
		statusBar += ' ';
	}
	statusBar += ']';

	setStatusBar(deliverId + 1, statusBar);

}

float ThreadDelivery::percentageEachNode(int delivererId, int userId, int nextUserId) {
	std::vector<Graph::edge_descriptor> shortestPathEdges = graphUsersClass.dijkstraShortestPathGetEachEdge(*graphUsers, userId, nextUserId);
	int totalEdges = static_cast<int>(shortestPathEdges.size());
	int completedEdges = 0;
	double time_bank = 0;
	double totalDistance = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, userId, nextUserId);
	double totalDistance_toDisplay = totalDistance;
	const std::chrono::time_point<std::chrono::system_clock> delivery_start_time = deliverer[delivererId].getTime();
	const std::time_t t_delivery_start_time = std::chrono::system_clock::to_time_t(delivery_start_time);

	for (int i = completedEdges; i < totalEdges; i++) {
		std::vector<double> distancesOfEdges = graphUsersClass.dijkstraShortestPathGetDistanceEachEdge(*graphUsers, userId, nextUserId);
		double edgeDistance = distancesOfEdges[i];

		const std::chrono::time_point<std::chrono::system_clock> current_time = std::chrono::system_clock::now();
		const std::time_t t_current_time = std::chrono::system_clock::to_time_t(current_time);

		int time_elapsed = static_cast<int>(t_current_time - t_delivery_start_time - time_bank);
		double percentage = 0.0;

		if (time_elapsed <= edgeDistance) {
			percentage = (time_elapsed * 100.0) / edgeDistance;
			totalDistance -= time_bank;

			updateEachEdge(delivererId, percentage, convertFunctionToString(shortestPathEdges[i]), edgeDistance, totalDistance, totalDistance_toDisplay);
		}

		if (time_elapsed >= edgeDistance) {
			time_bank += edgeDistance;
			completedEdges += 1; 
		}
		else {
			return 0.0;
		}
	}
	return 0.0;
}


void ThreadDelivery::displayEachNodeStatusBar() {
	for (const auto& pair : deliveryStatusMapEachEdge) {
		int delivererId = pair.first;
		double percentage = pair.second;
		const std::string& location = deliveryLocationMapEachEdge[delivererId];
		std::string locationCopy = location;
	}
	std::cout.flush();
}

void ThreadDelivery::convertToTime(int value, int& hours, int& minutes, int& seconds) {
	hours = value / 3600;       
	value %= 3600;
	minutes = value / 60;       
	seconds = value % 60;
}



int ThreadDelivery::selectDelivererTimeUsed(int deliverer_id, sql::Connection* con) {
	sql::PreparedStatement* pstm = nullptr;
	sql::ResultSet* rs = nullptr;
	int total_seconds = 0;

	try {
		pstm = con->prepareStatement("SELECT deliverer_time_used FROM deliverers WHERE deliverer_id = ?");
		pstm->setInt(1, deliverer_id);
		rs = pstm->executeQuery();

		if (rs->next()) {
			std::string deliverer_time_used = rs->getString("deliverer_time_used");
			int hours, minutes, seconds;
			int items_read = sscanf(deliverer_time_used.c_str(), "%d:%d:%d", &hours, &minutes, &seconds);

			if (items_read == 3) {
				total_seconds = hours * 3600 + minutes * 60 + seconds;
			}
		}
	}

	catch (const sql::SQLException& e) {
		std::cerr << "SQL Error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;

	}

	delete rs;
	delete pstm;

	return total_seconds;
}

void ThreadDelivery::calculateTimeUsedAndDeliveries(int deliverer_id, sql::Connection* con) {
	std::string systemStatus = deliverer[deliverer_id].getSystemStatusDelivery();
	if (systemStatus == DeliveryClass::toStringDeliverers(DeliveryClass::status_enum_deliverers::DELIVERING)) {
		int userIdOrders = 0;
		int nextUserIdOrders = 0;
		double arrivalTime_firstUser = 0;
		double arrivalTime_secondUser = 0;
		int current_deliveries_number = 0;
		int add_deliveries_number = 0;
		for (int num : ThreadDelivery::getOrdersSetDatabase(deliverer_id)) {
			if (num == 0) {
				continue;
			}
			else if (userIdOrders == 0) {
				userIdOrders = num;
			}
			else if (nextUserIdOrders == 0) {
				nextUserIdOrders = num;
				break;
			}
		}
		arrivalTime_firstUser = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, 0, userIdOrders);
		if (nextUserIdOrders != 0) {
			arrivalTime_secondUser = graphUsersClass.dijkstraShortestPathGetDistance(*graphUsers, userIdOrders, nextUserIdOrders);
			add_deliveries_number = 2;
		}
		else {
			add_deliveries_number = 1;
		}
		double delivererOldUsedTime = selectDelivererTimeUsed(deliverer_id + 1, con);
		int delivererNewUsedTime = static_cast<int>(delivererOldUsedTime + arrivalTime_firstUser + arrivalTime_secondUser);
		int hours, minutes, seconds;
		convertToTime(delivererNewUsedTime, hours, minutes, seconds);
		std::ostringstream formattedTimeStream;
		formattedTimeStream << std::setfill('0') << std::setw(2) << hours << ":"
			<< std::setfill('0') << std::setw(2) << minutes << ":"
			<< std::setfill('0') << std::setw(2) << seconds << std::endl;
		std::string formattedTime = formattedTimeStream.str();

		updateDelivererUsedTime(con, deliverer_id + 1, formattedTime);
		
		current_deliveries_number = selectCurrentNumberDeliveriesDB(con, deliverer_id + 1);
		current_deliveries_number += add_deliveries_number;
		incrementDeliveriesDB(con, deliverer_id + 1, current_deliveries_number);
	}
}

void ThreadDelivery::updateDelivererUsedTime(sql::Connection* con, int deliverer_id, std::string formattedTime) {
	sql::PreparedStatement* pstmUpdateTime;

	try {

		pstmUpdateTime = con->prepareStatement("UPDATE deliverers SET deliverer_time_used = ? WHERE deliverer_id = ?");
		pstmUpdateTime->setString(1, formattedTime);
		pstmUpdateTime->setInt(2, deliverer_id);
		pstmUpdateTime->executeUpdate();
		updatePercentageProcedureDeliverers(con);

		delete pstmUpdateTime;
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating deliverer used time: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadDelivery::updatePercentageProcedureDeliverers(sql::Connection* con) {
	sql::PreparedStatement* pstmCalculatePercentages;
	try {
		pstmCalculatePercentages = con->prepareStatement("UPDATE deliverers "
			"JOIN( SELECT SUM(deliverer_time_used) AS total_time_deliverers "
			"FROM deliverers) AS subquery ON 1 = 1 "
			" SET deliverers.deliverer_percentage = ROUND((deliverers.deliverer_time_used / subquery.total_time_deliverers) * 100, 2); ");
		pstmCalculatePercentages->executeUpdate();

		delete pstmCalculatePercentages;
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating deliverer percentage: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

void ThreadDelivery::incrementDeliveriesDB(sql::Connection* con, int deliverer_id, int order_number) {
	sql::PreparedStatement* pstmUpdateDeliveries;
	try {

		pstmUpdateDeliveries = con->prepareStatement("UPDATE deliverers SET deliverer_deliveries = ? WHERE deliverer_id = ?");
		pstmUpdateDeliveries->setString(1, to_string(order_number));
		pstmUpdateDeliveries->setInt(2, deliverer_id);
		pstmUpdateDeliveries->executeUpdate();

	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating deliverer number of deliveries: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}

int ThreadDelivery::selectCurrentNumberDeliveriesDB(sql::Connection* con, int deliverer_id) {
	sql::PreparedStatement* pstm;
	sql::ResultSet* rs;
	int deliveries_number = 0;
	try {
		pstm = con->prepareStatement("SELECT deliverer_deliveries FROM deliverers WHERE deliverer_id = ?");
		pstm->setInt(1, deliverer_id);
		rs = pstm->executeQuery();
		
		if (rs->next()) {
			std::string deliverer_deliveries = rs->getString("deliverer_deliveries");
			deliveries_number = stoi(deliverer_deliveries);
		}
		delete rs;
		delete pstm;
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating deliverer number of deliveries: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}

	return deliveries_number;
}


void ThreadDelivery::updateDeliveryStatus(sql::Connection* con, int deliverer_id, std::string delivererStatus) {
	sql::PreparedStatement* pstm;

	try {
		pstm = con->prepareStatement("UPDATE deliverers SET deliverer_status = ? WHERE deliverer_id = ?");
		pstm->setString(1, delivererStatus);
		pstm->setInt(2, deliverer_id);
		pstm->executeUpdate();

		delete pstm;
	}
	catch (sql::SQLException& e) {
		std::string databaseMessage = "Error in updating deliverer status: " + std::string(e.what());
		CheckStatus::setDatabaseStatusMessage(databaseMessage);
	}
}