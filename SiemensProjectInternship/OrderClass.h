#pragma once
#include "mysql_connection.h"
#include <iostream>
#include <cppconn/prepared_statement.h>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class OrderClass{	
private:
    int user_id;
    string username;
    string full_name;
    string address;
    string phone_number;
    string email;
    list <string> orderItems;
    string timestamp;
    string status;
    string userDetails;

public:
    void setUserId(int user_id);
    void setUsername(string username);
    void setFullname(string full_name);
    void setAddress(string address);
    void setPhoneNumber(string phone_number);
    void setEmail(string email);
    void setOrderItems(list <string> orderItems);
    void setTimestamp(string timestamp);
    void setStatus(string status);
    void setInfo(string username, string full_name, string address, string email, string phone_number, sql::Connection* con);

    int setUserId() { return user_id; }
    string getUsername() { return username; }
    string getFullname() { return full_name; }
    string getAddress() { return address; }
    string getPhoneNumber() { return phone_number; }
    string getEmail() { return email; }
    list <string> getOrderItems() { return orderItems; }
    string getTimestamp() { return timestamp; }
    string getStatus() { return status; }
    void getUserInfo();

	    //adauga un item comandat in tabelul order_items
	static void addItem(int order_id, int item_id, int quantity, sql::Connection* con);
		//adauga o comanda 
	static void addOrder(int user_id, const vector<pair<int, int>>& items, sql::Connection* con);
		//afiseaza comenzile
	static void displayOrders(sql::Connection* con);
    void userInsert(sql::Connection* con);
    void displayUsers(sql::Connection* con);
    void displayUserById(int user_id, sql::Connection* con);
};

