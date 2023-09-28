#include <iostream>
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <thread>
#include <string>
#include "OrderClass.h"
#include "OrderItems.h"

using namespace std;

const string ip = "tcp://89.39.7.10:3306";
const string name = "phiobaiqu_root";
const string pass = "Andreeas18MySql";

sql::Driver* driver;
sql::Connection* con;
sql::Statement* stm;
sql::PreparedStatement* pstm;
sql::ResultSet* rs;

int main()
{
    OrderItems ordItem;
    OrderClass ordClass;
    vector<pair<int, int >> items;
    try {
        driver = get_driver_instance();
        con = driver->connect(ip, name, pass);
        cout << "Connected to MySql.\n";
    }
    catch (sql::SQLException e) {
        cout << "Can't connect to MySQL.\n";
        system("pause");
        exit(1);
    }

    con->setSchema("phiobaiqu_siemensprojectdb");

    //ordClass.setInfo("uhi", "Andrei Mix","Codlea, BV","arh@yahoo.com", "0755632019", con);
    items = { {2,2}, {2,2} }; //{item_id, quantity},{{item2_id, quantity}...}
   
    ordClass.addOrder(1, items, con);
    //ordItem.displayMenuItemById(8,con);
    //ordClass.displayUsers(con);
    //ordClass.displayUserById(19, con);
    //ordItem.addMenuItems("Pizzuzzzza", 13, 33.33, con);
    //ordClass.displayOrders(con);
    delete con;
    system("pause");
    return 0;
}