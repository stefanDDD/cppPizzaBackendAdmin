#pragma once
#include "OrderItems.h"
#include <iostream>
#include <vector>
#include <list>
#include "CheckStatus.h"
#include "OrderClass.h"
#include <chrono>


class DeliveryClass
{

private:

	int delivererId = 0;
	int deliverer_capacity = 2;
	list <int> listOrders;
	double totalDistance = 0.0;

	OrderItems item;
	list <OrderItems> listOrderItems;
	list <pair <int, int>> userIdOrderIdList;
	int order_id = 0;
	int user_id = 0;
	bool isdoneDelivering = true;
	bool available = true;

	std::chrono::time_point<std::chrono::system_clock> time_start_delivery;
	std::chrono::time_point<std::chrono::system_clock> time_start_wait;

	double timeToDelivery = 0.0;
	double distance = 0.0;
	int returnUserId = 0;
	bool delivererReturn = true;

	int statusBarStart = 0;
	int statusBarEnd = 100;

	string systemStatusDelivery;


public:

	enum class status_enum_deliverers {
		DELIVERING,
		NOT_DELIVERING,
		IDLE
	};
	static string toStringDeliverers(status_enum_deliverers val) {
		switch (val) {
		case status_enum_deliverers::DELIVERING:
			return "DELIVERING";
		case status_enum_deliverers::NOT_DELIVERING:
			return "NOT_DELIVERING";
		case status_enum_deliverers::IDLE:
			return "IDLE";
		default:
			return "";
		}
	}
	void setReturnUserId(int returnUserId);
	int getReturnUserId() { return returnUserId; };
	double getTotalDistance() { return totalDistance; };
	void waitForNewReadyOrders();
	std::chrono::time_point<std::chrono::system_clock> getWaitTime() { return time_start_wait; };
	void addIdOrdertoOrderList(OrderClass ord);
	int getOrderId(int userId);
	bool isDelivererReturn() { return delivererReturn; };
	void setTimeAndDistanceToDelivery(double distance);
	double getDistance() { return distance; };
	double getTimeToDelivery() { return timeToDelivery; };
	void addItemInList(OrderItems item);
	void setOrderId(int order_id);
	void setUserId(int user_id);
	void addTotalDistance(double distanceUntilFinish);
	void setDelivererAvailable(bool available);
	void setListOfItems(list <OrderItems> listOrderItems);
	void setDoneDelivering(bool isdoneDelivering);
	void setTime();
	bool isDelivererAvailable() { return available; };


	void startDelivery();
	void endDelivery();

	list <int> getOrdersList() { return listOrders; };
	int getDelivererCapacity() { return deliverer_capacity; };
	void setDelivererId(int delivererId);
	int getDelivererId() { return delivererId; };
	list <OrderItems> getListOrderItems() { return listOrderItems; };
	list <OrderItems> getListOfItems() { return listOrderItems; };
	bool isDoneDelivering() { return isdoneDelivering; }
	int getUserId() { return user_id; };

	const std::chrono::time_point<std::chrono::system_clock> getTime() { return time_start_delivery; }
	bool checkWaitTime(std::chrono::time_point<std::chrono::system_clock> waitTime);

	void updateCapacity();

	void setSystemStatusDelivery(string systemStatusDelivery);
	string getSystemStatusDelivery() { return systemStatusDelivery; };

};
extern DeliveryClass* deliverer;
