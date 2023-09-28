#pragma once
#include "mysql_connection.h"
#include <iostream>
#include <cppconn/prepared_statement.h>


class MenuItems {
public:
    static void addMenuItems(std::string product_name, int prepare_time, double cost, sql::Connection* con);

    static void displayMenuItems(sql::Connection* con);

    static void displayMenuItemById(int item_id, sql::Connection* con);
};

