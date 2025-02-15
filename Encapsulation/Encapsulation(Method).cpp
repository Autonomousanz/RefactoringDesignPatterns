/* Example - ecommerce website, calculate order grand total */
/* Tax varies for different countries*/
#include<vector>
#include<string>
#include<algorithm>// std::for_each
#include <numeric> //std::accumulate to iterate through the orders
using namespace std;

struct OrderDetails {
  std::string Countryname;
  float price;
  int quantity;
  
};
float grandTotal(vector<OrderDetails>& orders){
    float total = 0;
    for(auto order : orders){
        total += order.price * order.quantity;
        // This part inside method varies as per country, this can encapsulated
        if(order.Countryname == "US"){
            total += total * 0.07;
        }
        else if(order.Countryname == "UK"){
            total += total * 0.2;
        }

    }
    return total;
}
// After encapsulation 
class Ecommerce{
    public:
    float grandTotal(vector<OrderDetails>& orders){
        float total = 0;
        for(auto order : orders){
            total += order.price * order.quantity;
            total += total * getTaxRate(order.Countryname);
        }

            // Use for_each with a lambda function to calculate total
        auto calculateTotal = [this](const std::vector<OrderDetails>& orders) {
        return std::accumulate(orders.begin(), orders.end(), 0.0f, [this](float total, const OrderDetails& order) {
                total += order.price * order.quantity;
                total += total * getTaxRate(order.Countryname);
                return total;
            });
        };
        return total;
    }
    float getTaxRate(string country){
                // This part inside method varies as per country, this can encapsulated
            if(country == "US") return 0.07;
            
            else if (country == "UK") return 0.2;
            
            else return 0.1;
            
    }
};