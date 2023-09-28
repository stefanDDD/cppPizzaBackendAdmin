#include "OrderItems.h"

using namespace std;

void OrderItems::setOrderId(int order_id) {
    this->order_id = order_id;
}

void OrderItems::setItemId(int item_id) {
    this->item_id = item_id;
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


void OrderItems::addMenuItems(string product_name, int prepare_time, double cost, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    pstm = con->prepareStatement("INSERT INTO menu_items(product_name,prepare_time,cost) VALUES (?,?,?)");
    pstm->setString(1, product_name);
    pstm->setInt(2, prepare_time);
    pstm->setDouble(3, cost);
    pstm->execute();
    cout << "\nA fost adaugat un produs nou! " << endl;
}

void OrderItems::displayMenuItems(sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT product_name,prepare_time,cost FROM menu_items");
    rs = pstm->executeQuery();
    cout << "\n" << endl;
    while (rs->next()) {
        string product_name = rs->getString("product_name");
        int prepare_time = rs->getInt("prepare_time");
        double cost = rs->getDouble("cost");
        cout << "product_name: " << product_name << ", prepare_time: " << prepare_time << ", cost: " << cost << endl;
    }
}

void OrderItems::displayMenuItemById(int item_id, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT product_name,prepare_time,cost FROM menu_items " 
                                 "WHERE item_id =" + to_string(item_id));
    rs = pstm->executeQuery();
    cout << "\n" << endl;
    if (rs->next()) {
        string product_name = rs->getString("product_name");
        int prepare_time = rs->getInt("prepare_time");
        double cost = rs->getDouble("cost");
        cout << "product_name: " << product_name << ", prepare_time: " << prepare_time << ", cost: " << cost << endl;
    }
}
