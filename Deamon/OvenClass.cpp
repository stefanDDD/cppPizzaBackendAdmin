#include "OvenClass.h"
#include "CheckStatus.h"
#include <thread>
#include <iostream>
#include "OrderClass.h"
#include "OrderItems.h"
#include "OvenClass.h"
#include <chrono>
#include <list>
#include <windows.h>
#include <cppconn/driver.h>

void OvenClass::setSystemStatusOvens(string systemStatusOvens) {
	this->systemStatusOvens = systemStatusOvens;
}

void OvenClass::setQuantity(int quantity) {
	this->quantity = quantity;
}

void OvenClass::setLastItemId(list <OrderItems>itemsList) {
	this->last_item_id = static_cast<int>(itemsList.size());
}

void OvenClass::setAvailable(bool available) {
	this->available = available;
}

void OvenClass::setOrderId(int order_id) {
	this->order_id = order_id;
}
void OvenClass::addNextItem(OrderItems item) {
	this->item = item;
	setTime();
	setAvailable(false);
	setDoneBaking(false);
}

void OvenClass::setTime() {
	time_start = std::chrono::system_clock::now();
}

void OvenClass::setDoneBaking(bool set) {
	isdoneBaking = set;
}

void OvenClass::clearOven() {
	quantity = 0;
	setAvailable(true);
	setDoneBaking(true);
}