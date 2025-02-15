/* Example - ecommerce website, calculate order grand total */
/* Tax varies for different countries*/
#include<vector>
#include<string>
using namespace std;

struct OrderDetails {
  std::string Countryname;
  float price;
  int quantity;
  std::string state;
  std::string product;
  
};
class Ecommerce{
    public:
    float grandTotal(vector<OrderDetails>& orders){
        float total = 0;
        TaxCalculator taxcal;
        for(auto order : orders){
            total += order.price * order.quantity;
            total += total * taxcal.getTaxRate(order.Countryname, order.state, order.product);
        }

    }
};
class TaxCalculator{
    public:
        int tax = 0;
        float getTaxRate(string country, string state, string product){
            if (country == "US") getUSTax(state);
            else if (country == "UK") getUKTax(country);
            else getChinaTax(product);
            return tax;
        }
    private:
        void getUSTax(string state){
            tax = 0.07;
        }
        void getUKTax(string country){
            tax = 0.01;
        }
        void getChinaTax(string product){
            tax = 0.7;
        }

};