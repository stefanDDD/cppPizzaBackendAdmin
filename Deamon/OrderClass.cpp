
#include "OrderClass.h"
#include "OrderItems.h"
#include <random>
#include <format>
#include "CheckStatus.h"
#include <iomanip>
#include <sstream>

std::string OrderClass::orderIDString;
std::string OrderClass::orderUsernameString;
std::string OrderClass::orderFullnameString;
std::string OrderClass::orderAddressString;
std::string OrderClass::orderPhoneString;
std::string OrderClass::orderEmailString;
std::string OrderClass::orderStatusString;
std::string OrderClass::orderTimestampString;
std::string OrderClass::orderCostString;

void OrderClass::setOrderCostString(std::string& orderCostString) {
	OrderClass::orderCostString = orderCostString;
}

std::string OrderClass::getOrderCostString() {
	return orderCostString;
}

void OrderClass::setOrderIDString(std::string& orderIDString) {
	OrderClass::orderIDString = orderIDString;
}

std::string OrderClass::getOrderIDString() {
	return orderIDString;
}

void OrderClass::setOrderUsernameString(std::string& orderUsernameString) {
	OrderClass::orderUsernameString = orderUsernameString;
}

std::string OrderClass::getOrderUsernameString() {
	return orderUsernameString;
}

void OrderClass::setOrderFullnameString(std::string& orderFullnameString) {
	OrderClass::orderFullnameString = orderFullnameString;
}

std::string OrderClass::getOrderFullnameString() {
	return orderFullnameString;
}

void OrderClass::setOrderAddressString(std::string& orderAddressString) {
	OrderClass::orderAddressString = orderAddressString;
}

std::string OrderClass::getOrderAddressString() {
	return orderAddressString;
}

void OrderClass::setOrderPhoneString(std::string& orderPhoneString) {
	OrderClass::orderPhoneString = orderPhoneString;
}

std::string OrderClass::getOrderPhoneString() {
	return orderPhoneString;
}

void OrderClass::setOrderEmailString(std::string& orderEmailString) {
	OrderClass::orderEmailString = orderEmailString;
}

std::string OrderClass::getOrderEmailString() {
	return orderEmailString;
}

void OrderClass::setOrderStatusString(std::string& orderStatusString) {
	OrderClass::orderStatusString = orderStatusString;
}

std::string OrderClass::getOrderStatusString() {
	return orderStatusString;
}

void OrderClass::setOrderTimestampString(std::string& orderTimestampString) {
	OrderClass::orderTimestampString = orderTimestampString;
}

std::string OrderClass::getOrderTimestampString() {
	return orderTimestampString;
}

void OrderClass::setOrderId(int order_id) {
	this->order_id = order_id;
}

void OrderClass::addItemToItemsList(OrderItems item, int ovenId)
{
	this->itemsList.push_back(make_pair(item, ovenId));
}

void OrderClass::setUserId(int user_id) {
	this->user_id = user_id;
}
void OrderClass::setUsername(string username) {
	this->username = username;
}

void OrderClass::setFullname(string full_name) {
	this->full_name = full_name;
}

void OrderClass::setAddress(string address) {
	this->address = address;
}

void OrderClass::setPhoneNumber(string phone_number) {
	this->phone_number = phone_number;
}

void OrderClass::setEmail(string email) {
	this->email = email;
}

void OrderClass::setOrderItems(OrderItems item) {
	listorderItems.push_front(item);
}

void OrderClass::setTimestamp(string timestamp) {
	this->timestamp = timestamp;
}

void OrderClass::setStatus(string status) {
	this->status = status;
}

void OrderClass::setCostTotal(double costTotal) {
	this->costTotal = costTotal;
}

void OrderClass::setDistance(double distance) {
	this->distance = distance;
	this->timeToDelivery = 2.5 * distance;
}



void OrderClass::setInfo(int orderid, string username, string full_name, string address, string email, string phone_number) {
	this->order_id = orderid;
	this->username = username;
	this->full_name = full_name;
	this->address = address;
	this->email = email;
	this->phone_number = phone_number;
}

void OrderClass::toString() {

	std::string orderIDString = "Order ID = " + to_string(order_id);
	std::string orderUsernameString = "Username = " + username;
	std::string orderFullnameString = "Fullname = " + full_name;
	std::string orderAddressString = "Address = " + address;
	std::string orderPhoneString = "PhoneNumber = " + phone_number;
	std::string orderEmailString = "Email: = " + email;
	std::string orderStatusString = "Status = " + status;
	std::string orderTimestampString = "Timestamp = " + timestamp;
	OrderClass::setOrderIDString(orderIDString);
	OrderClass::setOrderUsernameString(orderUsernameString);
	OrderClass::setOrderFullnameString(orderFullnameString);
	OrderClass::setOrderAddressString(orderAddressString);
	OrderClass::setOrderPhoneString(orderPhoneString);
	OrderClass::setOrderEmailString(orderEmailString);
	OrderClass::setOrderStatusString(orderStatusString);
	OrderClass::setOrderTimestampString(orderTimestampString);

}

void OrderClass::getOrderItems() {
	OrderItems item;
	for (auto& item : listorderItems) {
		item.toString();
	}
	std::ostringstream stream;
	stream << std::fixed << std::setprecision(2) << costTotal;
	std::string formattedCostTotal = stream.str();

	std::string orderCostString = "Cost total comanda: " + formattedCostTotal + " lei";
	OrderClass::setOrderCostString(orderCostString);

}

