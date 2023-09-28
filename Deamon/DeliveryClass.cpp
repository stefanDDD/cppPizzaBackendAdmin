#include "DeliveryClass.h"
#include "OrderClass.h"
#include "OvenClass.h"
#include "CheckStatus.h"
#include <chrono>
#include <random>
#include <thread>
#include <string>
#include "ThreadDelivery.h"

void DeliveryClass::setSystemStatusDelivery(string systemStatusDelivery) {
	this->systemStatusDelivery = systemStatusDelivery;
}

void DeliveryClass::setDelivererId(int delivererId) {
	this->delivererId = delivererId;
}

void DeliveryClass::addTotalDistance(double totalDistance) {
	this->totalDistance = totalDistance;
}

void DeliveryClass::setDelivererAvailable(bool availablem) {
	available = availablem;
}
void DeliveryClass::setListOfItems(list <OrderItems> ordItems) {
	for (auto& ordItem : ordItems) {
		if (ordItem.getOrderId() == item.getOrderId()) {
			item = ordItem;
		}
	}
}
void DeliveryClass::addItemInList(OrderItems item) {
	listOrderItems.push_front(item);
}

void DeliveryClass::setUserId( int user_id) {
	this->user_id = user_id;
}
void DeliveryClass::setOrderId(int order_id) {
	this->order_id = order_id;
}


void DeliveryClass::setTime() {
	time_start_delivery = std::chrono::system_clock::now();
}

void DeliveryClass::waitForNewReadyOrders() {
	time_start_wait = std::chrono::system_clock::now();
}
void DeliveryClass::addIdOrdertoOrderList(OrderClass ord)
{
	this->listOrders.push_back(ord.getUserId());
	this->userIdOrderIdList.push_back(std::make_pair(ord.getUserId(), ord.getOrderId()));
	this->deliverer_capacity=deliverer_capacity-1;
}

int DeliveryClass::getOrderId(int userId)
{
	for (const auto &pair : userIdOrderIdList) {
		if (pair.first == userId)
			return pair.second;
	}

	return 0;

}

void DeliveryClass::setTimeAndDistanceToDelivery(double distance) {
	this->timeToDelivery = 2.5 * distance;
	this->distance = distance;
	
}

void DeliveryClass::setDoneDelivering(bool isDoneDelivering) {
	this->isdoneDelivering = isDoneDelivering;
}

void DeliveryClass::startDelivery() {
	setTime();
	setDelivererAvailable(false);
	setDoneDelivering(false);
}
void DeliveryClass::endDelivery() {
	setDoneDelivering(true);
	setDelivererAvailable(true);
	this->listOrders.clear();
}

bool DeliveryClass::checkWaitTime(std::chrono::time_point<std::chrono::system_clock> waitTime) {
	const std::chrono::time_point<std::chrono::system_clock> currentTime = std::chrono::system_clock::now();
	const std::time_t t_currentTime = std::chrono::system_clock::to_time_t(currentTime);

	const std::chrono::time_point<std::chrono::system_clock> deliveryTime_seconds = waitTime;
	const std::time_t t_deliveryTime_seconds = std::chrono::system_clock::to_time_t(deliveryTime_seconds);

	const std::chrono::time_point<std::chrono::system_clock> delivererTime = this->time_start_wait;
	const std::time_t t_delivererTime = std::chrono::system_clock::to_time_t(delivererTime);

	if (t_currentTime - t_delivererTime >= t_deliveryTime_seconds) {
		return true;
	}

	return false;
}

void DeliveryClass::updateCapacity()
{
	this->deliverer_capacity--;
}

void DeliveryClass::setReturnUserId(int returnUserId)
{
	this->returnUserId = returnUserId;
}

