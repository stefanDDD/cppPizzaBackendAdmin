#include "Users.h"


void Users::setUserId(int user_id_m) {
    user_id = user_id_m;
}

void Users::setUsername(string usernamem) {
    username = usernamem;
}

void Users::setAddress(string addressm) {
    address = addressm;
}

void Users::setEmail(string emailm) {
    email = emailm;
}

void Users::setFullname(string fullname) {
    full_name = fullname;
}

void Users::setPhoneNumber(string phonenumber) {
    phone_number = phonenumber;
}

void Users::setInfo(string usernamem, string full_namem, string addressm, string emailm, string phone_numberm, sql::Connection * con) {
    username = usernamem;
    full_name = full_namem;
    address = addressm;
    phone_number = phone_numberm;
    email = emailm;
    Users:userInsert(con);
}

void Users::getUserInfo() {
    cout << "User ID = " << user_id << "\n";
    cout << "Username = " << username << "\n";
    cout << "Fullname = " << full_name << "\n";
    cout << "Address = " << address << "\n";
    cout << "PhoneNumber = " << phone_number << "\n";
}


void Users::userInsert(sql::Connection* con) {
    sql::PreparedStatement* pstm;
    pstm = con->prepareStatement("INSERT INTO users(username,full_name,address,phone_number,e_mail) VALUES(?,?,?,?,?)");
    pstm->setString(1, username);
    pstm->setString(2, full_name);
    pstm->setString(3, address);
    pstm->setString(4, phone_number);
    pstm->setString(5, email);
    pstm->execute();
}

void Users::displayUsers(sql::Connection* con) {
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

void Users::displayUserById(int id, sql::Connection* con) {
    sql::PreparedStatement* pstm;
    sql::ResultSet* rs;
    pstm = con->prepareStatement("SELECT username,full_name,address,phone_number,e_mail FROM users WHERE user_id =" + to_string(id));
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