#include "OrderClass.h"

using namespace std;

void OrderClass::setUserId(int user_id) {
    this->user_id = user_id;
}

void OrderClass::setUsername(string username) {
    this->username = username;
}

void OrderClass::setFullname(string fullname) {
    this->full_name = fullname;
}

void OrderClass::setAddress(string address) {
    this->address = address;
}

void OrderClass::setPhoneNumber(string phonenumber) {
    this->phone_number = phonenumber;
}

void OrderClass::setEmail(string email) {
    this->email = email;
}

void OrderClass::setOrderItems(list <string> orderItems) {
    this->orderItems = orderItems;
}

void OrderClass::setTimestamp(string timestamp) {
    this->timestamp = timestamp;
}

void OrderClass::setStatus(string status) {
    this->status = status;
}

void OrderClass::setInfo(string username, string full_name, string address, string email, string phone_number, sql::Connection* con) {
    this->username = username;
    this->full_name = full_name;
    this->address = address;
    this->email = email;
    this->phone_number = phone_number;
    OrderClass::userInsert(con);
}

void OrderClass::getUserInfo() {
    cout << "User ID = " << user_id << "\n";
    cout << "Username = " << username << "\n";
    cout << "Fullname = " << full_name << "\n";
    cout << "Address = " << address << "\n";
    cout << "PhoneNumber = " << phone_number << "\n";
    cout << "Email: = " << email << "\n";
    cout << "Timestamp = " << timestamp << "\n";
    cout << "Status = " << status << "\n";
}

void OrderClass::addItem(int order_id, int item_id, int quantity, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    pstm = con->prepareStatement("INSERT INTO order_items(order_id, item_id, quantity) VALUES (?,?,?)");
    pstm->setInt(1, order_id);
    pstm->setInt(2, item_id);
    pstm->setInt(3, quantity);
    pstm->execute();
    delete pstm;
}

void OrderClass::addOrder(int user_id, const vector<pair<int, int>>& items, sql::Connection* con) {
    unordered_map<int, int> itemCounts;
    for (const auto& item : items) {
        itemCounts[item.first] += item.second;
    }
    vector<pair<int, int>> sortedItems(itemCounts.begin(), itemCounts.end());
    sort(sortedItems.begin(), sortedItems.end(), [](const auto& lhs, const auto& rhs) {
        return lhs.second > rhs.second;
        });
    unordered_set<int> itemIDs;
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("INSERT INTO order_status(user_id) VALUES (?)");
    pstm->setInt(1, user_id);
    pstm->execute();
    delete pstm;

    pstm = con->prepareStatement("SELECT order_id FROM order_status "
        "JOIN users WHERE order_status.user_id = users.user_id "
        "ORDER BY order_id DESC LIMIT 1");
    rs = pstm->executeQuery();

    if (rs->next()) {
        int orderID = rs->getInt("order_id");
        for (const auto& item : sortedItems) {
            int itemID = item.first;
            if (itemIDs.find(itemID) == itemIDs.end()) {
                addItem(orderID, itemID, item.second, con);
                itemIDs.insert(itemID);
            }
            else {
                cout << "Item with ID " << itemID << " already exists in the order." << endl;
            }
        }
    }

    cout << "\nComanda adaugata! " << endl;
}
void OrderClass::displayOrders(sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT order_id, timestamp, status FROM order_status " 
                                 "JOIN users WHERE order_status.user_id = users.user_id "  
                                 "ORDER BY order_id DESC LIMIT 3");
    rs = pstm->executeQuery();
    cout << "\n" << endl;
    while (rs->next()) {
        int order_id = rs->getInt("order_id");
        int timestamp = rs->getInt("timestamp");
        string status = rs->getString("status");
        cout << "order_id: " << order_id << ", timestamp: " << timestamp << ", status: " << status << endl;
    }
}

//insereaza informatiile despre utilizator/client
void OrderClass::userInsert(sql::Connection* con) {
    sql::PreparedStatement* pstm;
    pstm = con->prepareStatement("INSERT INTO users(username,full_name,address,phone_number,e_mail) VALUES(?,?,?,?,?)");
    pstm->setString(1, username);
    pstm->setString(2, full_name);
    pstm->setString(3, address);
    pstm->setString(4, phone_number);
    pstm->setString(5, email);
    pstm->execute();
}

//afiseaza informatii despre utilizator
void OrderClass::displayUsers(sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT username,full_name,address,phone_number,e_mail FROM users");
    rs = pstm->executeQuery();
    cout << "\n" << endl;
    while (rs->next()) {
        string username = rs->getString("username");
        string full_name = rs->getString("full_name");
        string address = rs->getString("address");
        string phone_number = rs->getString("phone_number");
        string e_mail = rs->getString("e_mail");
        cout << "username: " << username << ", full_name: " << full_name << ", address: " << address << ", phone_number: " << phone_number << ", e_mail: " << e_mail << endl;
    }
}

//afiseaza informatii despre utilizator in functie de id
void OrderClass::displayUserById(int id, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT username,full_name,address,phone_number,e_mail FROM users " 
                                 "WHERE user_id =" + to_string(id));
    rs = pstm->executeQuery();
    cout << "\n" << endl;
    if (rs->next()) {
        string username = rs->getString("username");
        string full_name = rs->getString("full_name");
        string address = rs->getString("address");
        string phone_number = rs->getString("phone_number");
        string e_mail = rs->getString("e_mail");
        cout << "username: " << username << ", full_name: " << full_name << ", address: " << address << ", phone_number: " << phone_number << ", e_mail: " << e_mail << endl;
    }
}

