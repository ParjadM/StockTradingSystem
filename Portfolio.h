#include <map>
#include <string>

class Portfolio {
public:
    struct Stock {
        int quantity;
        double avgPurchasePrice;
    };

    // Add a stock to the portfolio
    void buyStock(const std::string& symbol, int quantity, double price);

    // Sell a stock from the portfolio
    void sellStock(const std::string& symbol, int quantity, double price);

    // Get the current value of the portfolio
    double getCurrentValue(const std::map<std::string, double>& currentPrices) const;

    // Get the profit or loss for a stock
    double getProfitLoss(const std::string& symbol, double currentPrice) const;

private:
    std::map<std::string, Stock> stocks;
};
