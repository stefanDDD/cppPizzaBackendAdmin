#include "OrderItems.h"
#include <cmath>
#include <sstream>
#include "CheckStatus.h"
#include <iomanip>
using namespace std;

std::string OrderItems::orderItemString1;
OrderItems::ItemType OrderItems::itemType;


OrderItems::ItemType OrderItems::getType(){
    return  OrderItems::itemType;
}

void OrderItems::setType(ItemType newType) {
    OrderItems::itemType = newType;
}

void OrderItems::setOrderItemString1(std::string& orderItemString1) {
    OrderItems::orderItemString1 = orderItemString1;
}

std::string OrderItems::getOrderItemString1() {
    return orderItemString1;
}

void OrderItems::setOvenStatus(bool ovenBaked)
{
    this->ovenBaked = ovenBaked;
}

void OrderItems::setOrderId(int order_id) {
    this->order_id = order_id;
}
void OrderItems::setItemId(int item_id) {
    this->item_id = item_id;
}
void OrderItems::setQuantity(int quantity) {
    this->quantity = quantity;
}
void OrderItems::setProductName(string product_name) {
    this->product_name = product_name;
}
void OrderItems::setPrepareTime(int prepare_time) {
    this->prepare_time = prepare_time;
}
void OrderItems::setCost(double cost) {
    this->cost = cost;
}
void OrderItems::setItemStatus(string itemStatus) {
    this->itemStatus = itemStatus;
}

void OrderItems::setOven(bool baked) {
    this->baked = baked;
}
void OrderItems::toString() {
    double cost2 = round(cost * 100.0) / 100.0;
    std::ostringstream stream;
    stream << std::fixed << std::setprecision(2) << cost2;
    std::string formattedCost2 = stream.str();
    std::string orderItemString1 = "Product: " + product_name + ", Prepare time: " + to_string(prepare_time) + ", Price: " + formattedCost2 + ", Quantity: " + to_string(quantity);
    OrderItems::setOrderItemString1(orderItemString1);

}

void OrderItems::setLastOven(int loven) {
    lastOven = loven;

}