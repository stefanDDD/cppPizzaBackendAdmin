#pragma once
#include "mysql_connection.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

class Users
{private:
	 int user_id;
	 string username;
	 string full_name;
	 string address;
	 string phone_number;
	 string email;

public:

	 void setUserId(int user_id);
	 void setUsername(string username);
	 void setFullname(string full_name);
	 void setAddress(string address);
	 void setEmail(string email);
	 void setPhoneNumber(string phone_number);
	 void setInfo(string username, string full_name, string address, string email, string phone_number, sql::Connection * con);

	 int getUserId() { return user_id; }
     string getUsername() { return username; }
	 string getFullname() { return full_name; }
	 string getAddress() { return address; }
	 string getEmail() { return email; }
	 string getPhoneNumber() { return phone_number; }

	void getUserInfo();
    void userInsert(sql::Connection* con);
    void displayUsers(sql::Connection* con);
    void displayUserById(int user_id, sql::Connection* con);

};

