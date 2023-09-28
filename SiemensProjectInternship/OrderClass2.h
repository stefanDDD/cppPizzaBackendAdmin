#pragma once

#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>

using namespace std;

class OrderClass2
{
private:
	string username;
	string address;
	list <string> orderItems;
	string timestamp;

public:
	void setUsername(string username);
	void setAddress(string address);
	void setOrderItems(list <string> orderItems);
	void setTimestamp(string timestamp);

	string getUsername() { return username; }
	string getAddress() { return address; }
	list <string> getOrderItems() { return orderItems; }
	string getTimestamp() { return timestamp; }
};



