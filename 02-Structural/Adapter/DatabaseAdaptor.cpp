#include<iostream>
#include<string>
#include<memory>
// =============================================================================
// EXAMPLE 3: Database Adapter (Real-world scenario)
// =============================================================================

// Target interface - standardized database operations
class DatabaseInterface {
public:
    virtual ~DatabaseInterface() = default;
    virtual void connect(const std::string& connectionString) = 0;
    virtual void executeQuery(const std::string& query) = 0;
    virtual void disconnect() = 0;
};

// Legacy MySQL database class (Adaptee)
class MySQLDatabase {
public:
    void mysql_connect(const std::string& host, int port, const std::string& user, const std::string& password) {
        std::cout << "Connected to MySQL: " << host << ":" << port << " as " << user << std::endl;
    }
    
    void mysql_query(const std::string& sql) {
        std::cout << "MySQL Query: " << sql << std::endl;
    }
    
    void mysql_close() {
        std::cout << "MySQL connection closed" << std::endl;
    }
   
};

// PostgreSQL database class (Another Adaptee)
class PostgreSQLDatabase {
public:
    void pg_connect(const std::string& connInfo) {
        std::cout << "Connected to PostgreSQL: " << connInfo << std::endl;
    }
    
    void pg_exec(const std::string& statement) {
        std::cout << "PostgreSQL Statement: " << statement << std::endl;
    }
    
    void pg_disconnect() {
        std::cout << "PostgreSQL connection closed" << std::endl;
    }
   
};

// MySQL Adapter
class MySQLAdapter : public DatabaseInterface {
private:
    std::unique_ptr<MySQLDatabase> mysqlDb;
    
public:
    MySQLAdapter() {
        mysqlDb = std::make_unique<MySQLDatabase>();
    }
    
    void connect(const std::string& connectionString) override {
        // Parse connection string and call MySQL-specific method
        mysqlDb->mysql_connect("localhost", 3306, "user", "password");
    }
    
    void executeQuery(const std::string& query) override {
        mysqlDb->mysql_query(query);
    }
    
    void disconnect() override {
        mysqlDb->mysql_close();
    }
};

// PostgreSQL Adapter
class PostgreSQLAdapter : public DatabaseInterface {
private:
    std::unique_ptr<PostgreSQLDatabase> pgDb;
    
public:
    PostgreSQLAdapter() {
        pgDb = std::make_unique<PostgreSQLDatabase>();
    }
    
    void connect(const std::string& connectionString) override {
        pgDb->pg_connect(connectionString);
    }
    
    void executeQuery(const std::string& query) override {
        pgDb->pg_exec(query);
    }
    
    void disconnect() override {
        pgDb->pg_disconnect();
    }
};

// Client code that uses the standardized interface
class DatabaseManager {
public:
    void performDatabaseOperations(DatabaseInterface& db) {
        db.connect("connection_string");
        db.executeQuery("SELECT * FROM users");
        db.executeQuery("UPDATE users SET status = 'active'");
        db.disconnect();
    }
};
int main(){
    // Example  Database Adapters
    std::cout << " Database Adapter Example:" << std::endl;
    
    DatabaseManager dbManager;
    
    std::cout << "Using MySQL through adapter:" << std::endl;
    MySQLAdapter mysqlAdapter;
    dbManager.performDatabaseOperations(mysqlAdapter);
    
    std::cout << "\nUsing PostgreSQL through adapter:" << std::endl;
    PostgreSQLAdapter pgAdapter;
    dbManager.performDatabaseOperations(pgAdapter);
    
    std::cout << "\n=== Adapter Pattern Benefits Demonstrated ===" << std::endl;
    std::cout << "✓ Incompatible interfaces made compatible" << std::endl;
    std::cout << "✓ Legacy code reused without modification" << std::endl;
    std::cout << "✓ Client code uses consistent interface" << std::endl;
    std::cout << "✓ Different implementations can be swapped easily" << std::endl;
    
    return 0;
}
