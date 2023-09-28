#pragma once
#include <iostream>
#include <cppconn/prepared_statement.h>

using namespace std;

class OrderItems {

private:

    int order_id = 0;
    int item_id = 0;
    int quantity = 0;
    string product_name;
    int prepare_time = 0;
    double cost = 0.0;
    string order;
    string itemStatus;
    bool baked = false;
    bool ovenBaked = false;
    int lastOven = 0;
    static std::string orderItemString1;

public:
    enum class ItemType {
        FOOD,
        DRINK,
        SAUCE,
    };
    static ItemType itemType;

    void setOvenStatus(bool ovenBaked);
    bool getOvenStatus() { return ovenBaked; };

    void setOrderId(int order_id);
    void setItemId(int item_id);
    void setLastOven(int lastOven);
    void setQuantity(int quantity);
    void setProductName(string product_name);
    void setPrepareTime(int prepare_time);
    void setCost(double cost);
    void setItemStatus(string itemStatus);
    void toString();
    void setOven(bool baked);

    int getLastOven(){return lastOven;};
    bool getOven() { return baked; };
    int getOrderId() { return order_id; } 
    int getItemId() { return item_id; }
    int getQuantity() { return quantity; }
    string getProductName() { return product_name; }
    int getPrepareTime() { return prepare_time; }
    double getCost() { return cost; }
    string getItemStatus() { return itemStatus; }

    static void setOrderItemString1(string& orderItemString1);
    static string getOrderItemString1();
    static void setType(ItemType newType);
    static ItemType getType();
};
