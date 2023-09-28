#pragma once
#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>
#include "OrderItems.h"
#include "OrderClass.h"
#include <chrono>

class ThreadOvens
{

private:

	static std::map<int, string> ovenMessageCustom;
	static std::map<int, string> ovenMessageCustomStatus;
	static std::map<int, double> ovenRemainingTime;
	static std::map<int, int> ovenPercentage;
	static std::string quantityRawMaterial;

	
public:
	static void ovens(sql::Connection* con);
	static void processingOrder(OrderClass ord, sql::Connection* con);
	static void checkOvens(sql::Connection*con);
	static int verifyEmptyOvens(sql::Connection*con);
	static bool allItemsDone(sql::Connection* con, int order_id);
	static void systemStatusOvens();

	static void setOvenMessageCustom(int ovenID, string& ovenMessageCustom);
	static string getOvenMessageCustom(int ovenID);

	static void setOvenMessageCustomStatus(int ovenID, string& ovenMessageCustomStatus);
	static string getOvenMessageCustomStatus(int ovenID);
	static void setOvenRemainingTime(int ovenID, double& ovenRemainingTime);
	static double getOvenRemainingTime(int ovenID);

	static void setOvenPercentage(int ovenID, int& ovenPercentage_1);
	static int getOvenPercentage(int ovenID);

	static int selectOvenTimeUsed(int oven_id, sql::Connection* con);
	static void calculateTimeUsedAndItemsCooked(int oven_id, sql::Connection* con);
	static void updateOvenUsedTime(sql::Connection* con, int oven_id, std::string formattedTime);
	static void incrementOvensDB(sql::Connection* con, int oven_id, int order_number);
	static int selectCurrentNumberOvensDB(sql::Connection* con, int oven_id);
	static void updateOvenStatus(sql::Connection* con, int oven_id, std::string ovenStatus);
	static void updateItemsRawMaterial(int item_id, sql::Connection* con);
	static std::pair<std::vector<int>, int> statusRawMaterial(sql::Connection* con, std::string rawMaterialStatus);
	static void setOvenQuantityRawMaterial(string& quantityRawMaterial_1);
	static string getOvenQuantityRawMaterial();
	static bool isProductEligible(sql::Connection* con, int item_id, int quantity);
	static std::string selectStatusRawMaterial(sql::Connection* con, int material_id);
	static void updatePercentageProcedureOvens(sql::Connection* con);
	static void updatestatusRawMaterials(sql::Connection* con);
	static void updateOrderStatusObservations(sql::Connection* con, int order_id, std::string observations);
	static void updateOrderItemsObservations(sql::Connection* con, int order_id, std::string observations);
	static int selectQuantityRawMaterial(sql::Connection* con, int material_id);
	static std::vector<std::pair<int, int>> selectAllItemsForOrderFood(sql::Connection* con, int order_id);
	static std::vector<std::pair<int, int>> selectAllItemsForOrderDrinkSauce(sql::Connection* con, int order_id);
	static bool areItemsEligibleFood(sql::Connection* con, int order_id);
	static bool areItemsEligibleDrinkSauce(sql::Connection* con, int order_id);

};
