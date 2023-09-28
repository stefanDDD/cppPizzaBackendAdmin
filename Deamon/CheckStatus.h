#pragma once
#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>
#include "OrderItems.h"
#include "OrderClass.h"
#include "OvenClass.h"

class CheckStatus
{
private:
    static std::string mainDatabaseMessage;
    static std::string ovenStatusMessage1;
    static std::string ovenStatusMessage2;
    static std::string curlStatusMessage;
    static std::string databaseStatusMessage;
    static std::string orderHeaderString;

public:

    enum class status_enum {
        PENDING,
        PROCESSING,
        IN_PREPARATION,
        IN_DELIVERY,
        DELIVERED,
        READY_FOR_DELIVERY,
        CANCELED,
        DONE,
        QUANTITY_IN_PROGRESS
    };
    static string toString(status_enum val) {
        switch (val) {
        case status_enum::PENDING:
            return "PENDING";
        case status_enum::PROCESSING:
            return "PROCESSING";
        case status_enum::IN_PREPARATION:
            return "IN_PREPARATION";
        case status_enum::IN_DELIVERY:
            return "IN_DELIVERY";
        case status_enum::DELIVERED:
            return "DELIVERED";
        case status_enum::READY_FOR_DELIVERY:
            return "READY_FOR_DELIVERY";
        case status_enum::CANCELED:
            return "CANCELED";
        case status_enum::DONE:
            return "DONE";
        case status_enum::QUANTITY_IN_PROGRESS:
            return "QUANTITY_IN_PROGRESS";
        default:
            return "";
        }
    }
    enum class status_enum_raw_material {
        ENOUGH_QUANTITY,
        LOW_QUANTITY,
        OUT_OF_QUANTITY
    };
    static string toStringRawMaterials(status_enum_raw_material val) {
        switch (val) {
        case status_enum_raw_material::ENOUGH_QUANTITY:
            return "ENOUGH_QUANTITY";
        case status_enum_raw_material::LOW_QUANTITY:
            return "LOW_QUANTITY";
        case status_enum_raw_material::OUT_OF_QUANTITY:
            return "OUT_OF_QUANTITY";
        default:
            return "";
        }
    }
    static void getOrderInfo(OrderClass& ord, int order_id, string timestamp, sql::Connection* con);
    static void getOrderItemsInfo(OrderItems& item, sql::Connection* con);
    static void ordersThread(sql::Connection* con);
    static void setOrderStatus(status_enum sts, int order_id, sql::Connection* con);
    static void setItemStatus(status_enum sts, int item_id, int order_id, sql::Connection* con);
    static void getOrder(OrderClass& ord, int order_id, sql::Connection* con);
    static void systemStatus();
    static void setCursorPosition(int x, int y);
    static int getConsoleCursorY();
    static void printMessage(const std::string& message, int x, int y);
    static void consoleDisplay();

    static void setMainDatabaseMessage(string& mainDatabaseMessage);
    static string getMainDatabaseMessage();

    static void setOvenStatusMessage1(string& ovenStatusMessage1);
    static string getOvenStatusMessage1();
    static void setOvenStatusMessage2(string& ovenStatusMessage2);
    static string getOvenStatusMessage2();

    static void setCurlStatusMessage(string& curlStatusMessage);
    static string getCurlStatusMessage();

    static void setDatabaseStatusMessage(string& databaseStatusMessage);
    static string getDatabaseStatusMessage();

    static void setOrderHeaderString(string& orderHeaderString);
    static string getOrderHeaderString();
    static double getCostTotalDatabase(int order_id, sql::Connection* con);
    static void setOrderStatusInItems(status_enum sts, int order_id, sql::Connection* con);

};