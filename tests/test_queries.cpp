#include <gtest/gtest.h>
#include <string>
extern "C" {
#include "queries.h"
#include "db.h"
}

TEST(QueriesTest, ComputeDateDiffWorksCorrectly) {
    int diff = compute_date_diff("2025-04-01", "2025-04-06");
    EXPECT_EQ(diff, 5);
    diff = compute_date_diff("2025-04-01", "2025-04-01");
    EXPECT_EQ(diff, 0);
    diff = compute_date_diff("2025-04-01", "2025-03-31");
    EXPECT_LT(diff, 0);
}

static void setup_test_db(sqlite3* db) {
    char* errMsg = nullptr;
    sqlite3_exec(db,
        "CREATE TABLE ORANGERIE_ORDERS (order_id INTEGER PRIMARY KEY, order_date TEXT, fulfillment_date TEXT, composition_id INTEGER, quantity INTEGER, customer_id INTEGER);"
        , nullptr, nullptr, &errMsg);
    sqlite3_exec(db,
        "CREATE TABLE ORANGERIE_COMPOSITION_FLOWERS (composition_id INTEGER, flower_id INTEGER, quantity INTEGER);"
        , nullptr, nullptr, &errMsg);
    sqlite3_exec(db,
        "CREATE TABLE ORANGERIE_FLOWERS (flower_id INTEGER PRIMARY KEY, flower_name TEXT, flower_sort TEXT, price REAL);"
        , nullptr, nullptr, &errMsg);
    sqlite3_exec(db,
        "CREATE TABLE ORANGERIE_ORDER_PAYMENTS (order_id INTEGER PRIMARY KEY, order_cost REAL);"
        , nullptr, nullptr, &errMsg);

    sqlite3_exec(db,
        "INSERT INTO ORANGERIE_FLOWERS (flower_name, flower_sort, price) VALUES ('Rose', 'Red', 2.50);", nullptr, nullptr, &errMsg);
    sqlite3_exec(db,
        "INSERT INTO ORANGERIE_COMPOSITION_FLOWERS (composition_id, flower_id, quantity) VALUES (1, 1, 10);", nullptr, nullptr, &errMsg);
    sqlite3_exec(db,
        "INSERT INTO ORANGERIE_ORDERS (order_date, fulfillment_date, composition_id, quantity, customer_id) VALUES ('2025-04-01', '2025-04-02', 1, 2, 1);", nullptr, nullptr, &errMsg);
}

TEST(QueriesTest, QueryTotalReceivedWorks) {
    sqlite3* db = open_database(":memory:");
    ASSERT_NE(db, nullptr);
    setup_test_db(db);
    sqlite3_exec(db,
        "INSERT INTO ORANGERIE_ORDER_PAYMENTS (order_id, order_cost) VALUES (1, 62.5);", nullptr, nullptr, nullptr);
    close_database(db);
}

TEST(QueriesTest, QueryMaxDemandCompositionWorks) {
    sqlite3* db = open_database(":memory:");
    ASSERT_NE(db, nullptr);
    setup_test_db(db);
    sqlite3_exec(db,
        "INSERT INTO ORANGERIE_ORDERS (order_date, fulfillment_date, composition_id, quantity, customer_id) VALUES ('2025-04-03', '2025-04-04', 1, 3, 2);", nullptr, nullptr, nullptr);
    close_database(db);
}
