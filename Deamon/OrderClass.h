#pragma once

#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>
#include "OrderItems.h"

using namespace std;

class OrderClass {

private:
    int user_id = 0;
    int order_id = 0;
    string username;
    string full_name;
    string address;
    string phone_number;
    string email;
    list <OrderItems> listorderItems;
    string timestamp;
    string status;
    string userDetails;
    double costTotal = 0.0;
    double distance = 0.0;
    double timeToDelivery = 0.0;
    list <OrderClass> listOrdersToDelivery;
    list <pair<OrderItems, int>> itemsList;
    static std::string orderIDString;
    static std::string orderUsernameString;
    static std::string orderFullnameString;
    static std::string orderAddressString;
    static std::string orderPhoneString;
    static std::string orderEmailString;
    static std::string orderStatusString;
    static std::string orderTimestampString;
    static std::string orderCostString;

public:

    void addItemToItemsList(OrderItems item, int ovenId);
    list <pair<OrderItems, int>> getItemsList() { return itemsList; };
    void setUserId(int user_id);
    void setDistance(double distance);
    double getDistance() { return distance; };
    double getTimeToDelivery() { return timeToDelivery; };
    void setOrderId(int order_id);
    void setUsername(string username);
    void setFullname(string full_name);
    void setAddress(string address);
    void setPhoneNumber(string phone_number);
    void setEmail(string email);
    void setOrderItems(OrderItems item);
    void setTimestamp(string timestamp);
    void setStatus(string status);
    void setInfo(int user_id, string username, string full_name, string address, string email, string phone_number);
    void setCostTotal(double costTotal);

    int getOrderId() { return order_id; }
    string getUsername() { return username; }
    string getFullname() { return full_name; }
    string getAddress() { return address; }
    string getPhoneNumber() { return phone_number; }
    string getEmail() { return email; }
    double getCostTotal() { return costTotal; }
    string getTimestamp() { return timestamp; }
    string getStatus() { return status; }
    int getUserId() { return user_id; }
    list <OrderItems> getList() { return listorderItems; }

    void getOrderItems();
    void toString();

    static void setOrderIDString(string& orderIDString);
    static string getOrderIDString();
    static void setOrderUsernameString(string& orderUsernameString);
    static string getOrderUsernameString();
    static void setOrderFullnameString(string& orderFullnameString);
    static string getOrderFullnameString();
    static void setOrderAddressString(string& orderAddressString);
    static string getOrderAddressString();
    static void setOrderPhoneString(string& orderPhoneString);
    static string getOrderPhoneString();
    static void setOrderEmailString(string& orderEmailString);
    static string getOrderEmailString();
    static void setOrderStatusString(string& orderStatusString);
    static string getOrderStatusString();
    static void setOrderTimestampString(string& orderTimestampString);
    static string getOrderTimestampString();
    static void setOrderCostString(string& orderCostString);
    static string getOrderCostString();
};