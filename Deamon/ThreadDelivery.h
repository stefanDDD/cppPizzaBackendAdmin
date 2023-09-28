#pragma once
#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>
#include "OrderItems.h"
#include "OrderClass.h"
#include "CheckStatus.h"
#include <vector>
#include <map>
#include "GraphClass.h"
#include "OvenClass.h"
#include "DeliveryClass.h"
#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>
#include "OrderItems.h"
#include "OrderClass.h"
#include "CheckStatus.h"
#include <vector>
#include <map>
#include "GraphClass.h"

class ThreadDelivery
{

private:
	static std::map<int, std::vector<int>> globalPath;
	static std::map<int, std::list<int>> ordersSetDatabase;
	static std::map<int, int> globalRemainingTime;
	static std::map<int, double> globalDistance;
	static std::map<int, int> globalPercentage;
	static std::map<int, string> delivererStatusMessage;
	static std::map<int, string> delivererStatusMessageCustom;
	static std::map<int, string> delivererStatusMessageStatusBar;
	static std::string ordersInDeliverString;
	static std::string delivererReadyStatus;
	static std::map<int, double> percentageEachNodeVar;
	static std::map<int, string> locationEachNodeVar;
	static std::map<int, int> destinationNode;
	static std::map<int, int> globalRemainingTimeTotal;
	static std::map<int, std::string> statusBar;
	static std::map<int, int> percentageIfStatemens;
	static std::map<int, OrderClass> ordersIDsSetDatabase;
	static std::map<int, OrderClass> ordersIDsSetDatabaseNext;
	static std::map<int, int> percentageComplete;

public:

	static void deliveryThread(sql::Connection* con);
	static void checkDeliverersGraph(sql::Connection* con);
	static void processDeliverer(int delivererIndex, sql::Connection* con);
	static void processingDelivery(sql::Connection* con);
	static void addOrdersInPreparation(OrderClass& ord);
	static void setStatusToDelivery(CheckStatus::status_enum sts_delivery, int order_id, sql::Connection* con);
	static void delivery(sql::Connection* con);
	static int checkFreeDeliverers(sql::Connection*con);
	static void setItemsStatusDelivery(CheckStatus::status_enum sts, int order_id, sql::Connection* con);
	static void setItemandOrderStatusToDelivery(sql::Connection* con, int delivererId, int i);
	static list<int> ordersSort(list<int> &orders);
	static void displayAllStatusBars();
	static double waitForDelivery(double distance, int userId, int nextUserId, int delivererId);
	static void systemStatusDelivery();
	static void setGlobalPath(int delivererId, std::vector<int>& path);
	static std::vector<int> getGlobalPath(int delivererId);
	static void setGlobalRemainingTime(int delivererId, int& globalRemainingTime);
	static int getGlobalRemainingTime(int delivererId);
	static void setStatusBar(int delivererId, std::string& statusBar);
	static  std::string getStatusBar(int delivererId);
	static void setGlobalRemainingTimeTotal(int delivererId, int& globalRemainingTimeTotal);
	static int getGlobalRemainingTimeTotal(int delivererId);
	static void setGlobalDistance(int delivererId, double& globalDistance);
	static double getGlobalDistance(int delivererId);
	static void setGlobalPercentage(int delivererId, int& globalPercentage);
	static int getGlobalPercentage(int delivererId);
	static void setDelivererStatusMessage(int delivererID, string& delivererStatusMessage);
	static string getDelivererStatusMessage(int delivererID);
	static void setDelivererStatusMessageCustom(int delivererID, string& delivererStatusMessageCustom);
	static string getDelivererStatusMessageCustom(int delivererID);
	static void setDelivererStatusMessageStatusBar(int delivererID, string& delivererStatusMessageStatusBar);
	static string getDelivererStatusMessageStatusBar(int delivererID);
	static void setOrdersInDeliverString(string& ordersInDeliverString);
	static string getOrdersInDeliverString();
	static void setDelivererReadyStatus(string& delivererReadyStatus);
	static string getDelivererReadyStatus();
	static void setPercentageEachNode(int delivererID, double& percentageEachNodeVar);
	static double getPercentageEachNode(int delivererID);
	static void setLocationEachNodeVar(int delivererID, string& locationEachNodeVar);
	static string getLocationEachNodeVar(int delivererID);
	static void setDestinationNode(int delivererID, int& destinationNode);
	static int getDestinationNode(int delivererID);
	static void setOrdersSetDatabase(int delivererId, std::list<int>& ordersSetDatabase);
	static std::list<int> getOrdersSetDatabase(int delivererId);
	static void setPercentageIfStatemens(int delivererId, int& percentageIfStatemens);
	static int getPercentageIfStatemens(int delivererId);
	static float percentageEachNode(int delivererId, int userId, int nextUserId);
	static void displayEachNodeStatusBar();
	static void updateEachEdge(int deliverId, double percentageEachEdge, std::string edgeDesc, double edgeDistance, double totalDistance, double totalDistance_toDisplay);
	static void saveAproximativTimeDatabase(int i, sql::Connection* con);
	static void updateUserArrivalTime(sql::Connection* con, int userId, const std::_Timeobj<char, const tm*>& arrivalTime);
	static int selectDelivererTimeUsed(int deliverer_id, sql::Connection* con);
	static void calculateTimeUsedAndDeliveries(int deliverer_id, sql::Connection* con);
	static void updateDelivererUsedTime(sql::Connection* con, int userId, std::string formattedTime);
	static int selectCurrentNumberDeliveriesDB(sql::Connection* con, int deliverer_id);
	static void incrementDeliveriesDB(sql::Connection* con, int deliverer_id, int order_number);
	static void convertToTime(int value, int& hours, int& minutes, int& seconds);
	static void updateDeliveryStatus(sql::Connection* con, int deliverer_id, std::string delivererStatus);
	static void updateDeliveredTimeOrder(sql::Connection* con, int order_id, const std::_Timeobj<char, const tm*>& deliveredTime);
	static void setOrdersIDsSetDatabase(int delivererId, OrderClass ordersIDsSetDatabase_1);
	static OrderClass getOrdersIDsSetDatabase(int delivererId);
	static void setOrdersIDsSetDatabaseNext(int delivererId, OrderClass ordersIDsSetDatabaseNext_1);
	static OrderClass getOrdersIDsSetDatabaseNext(int delivererId);
	static void setPercentageComplete(int delivererID, int& percentageComplete_1);
	static int getPercentageComplete(int delivererID);
	static void updatePercentageProcedureDeliverers(sql::Connection* con);


};

