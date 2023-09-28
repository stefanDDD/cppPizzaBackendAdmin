#pragma once
#include "mysql_connection.h"
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;


class OrderItems {
private:
    int order_id;
    int item_id;
    int quantity;
    string product_name;
    int prepare_time;
    double cost;
    string order;
    string itemStatus;

public:
    void setOrderId(int order_id);
    void setItemId(int item_id);
    void setQuantity(int quantity);
    void setProductName(string product_name);
    void setPrepareTime(int prepare_time);
    void setCost(double cost);
    void setOrder();
    void setItemStatus(string itemStatus);

    int getOrderId() { return order_id; }
    int getItemId() { return item_id; }
    int getQuantity() { return quantity; }
    string getProductName() { return product_name; }
    int getPrepareTime() { return prepare_time; }
    double getCost() { return cost; }
    string getOrder() { return order; }
    string getItemStatus() { return itemStatus; }

public:
    //adaugare produs in baza de date
    static void addMenuItems(std::string product_name, int prepare_time, double cost, sql::Connection* con);

    //afiseaza toate produsele din baza de date
    static void displayMenuItems(sql::Connection* con);

    //afiseaza produsele din baza de date in functie de id-ul acestora
    static void displayMenuItemById(int item_id, sql::Connection* con);
};

