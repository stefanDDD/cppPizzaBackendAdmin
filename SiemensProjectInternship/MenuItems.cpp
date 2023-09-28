#include "MenuItems.h"

using namespace std;

void MenuItems::addMenuItems(string product_name, int prepare_time, double cost, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    pstm = con->prepareStatement("INSERT INTO menu_items(product_name,prepare_time,cost) VALUES (?,?,?)");
    pstm->setString(1, product_name);
    pstm->setInt(2, prepare_time);
    pstm->setDouble(3, cost);
    pstm->execute();
    cout << "\nA fost adaugat un produs nou! " << endl;
}

void MenuItems::displayMenuItems(sql::Connection* con) {
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

void MenuItems::displayMenuItemById(int item_id, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT product_name,prepare_time,cost FROM menu_items WHERE item_id =" + to_string(item_id));
    rs = pstm->executeQuery();
    cout << "\n" << endl;
    while (rs->next()) {
        string product_name = rs->getString("product_name");
        int prepare_time = rs->getInt("prepare_time");
        double cost = rs->getDouble("cost");
        cout << "product_name: " << product_name << ", prepare_time: " << prepare_time << ", cost: " << cost << endl;
    }
}
