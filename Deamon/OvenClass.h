#pragma once
#include "mysql_connection.h"
#include <cppconn/prepared_statement.h>
#include <iostream>
#include "OrderItems.h"
#include "OrderClass.h"
#include <list>
#include <chrono>

class OvenClass
{

    

private:
    int oven_id = 0;
    int order_id = 0;
    OrderItems item;
    std::chrono::time_point<std::chrono::system_clock> time_start;
    bool available = true;
    bool isdoneBaking = true;
    int quantity = 0;
    int last_item_id = 0;
    string systemStatusOvens;

public:
    enum class status_enum_ovens {
        COOKING,
        NOT_COOKING,
        IDLE
    };
    static string toStringOvens(status_enum_ovens val) {
        switch (val) {
        case status_enum_ovens::COOKING:
            return "COOKING";
        case status_enum_ovens::NOT_COOKING:
            return "NOT_COOKING";
        case status_enum_ovens::IDLE:
            return "IDLE";
        default:
            return "";
        }
    }

    void setOrderId(int order_id);
    void setLastItemId(list <OrderItems> itemsList);
    int getLastItemId() { return last_item_id; };

    int getOrderId() { return order_id; };
    void setQuantity(int quantity);
    int getQuantity() { return quantity; };
    void clearOven();
    void setTime();
    void addNextItem(OrderItems itemm);
    std::chrono::time_point<std::chrono::system_clock> getTime() { return time_start; }
    void setAvailable(bool available);
    bool isAvailable() { return available; };
    OrderItems getItem() { return item; };
    bool isDoneBaking() { return isdoneBaking; }
    void setDoneBaking(bool isdoneBaking);

    void setSystemStatusOvens(string systemStatusOvens);
    string getSystemStatusOvens() { return systemStatusOvens; };


    
};
