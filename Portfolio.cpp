#include "Portfolio.h"

void Portfolio::buyStock(const std::string& symbol, int quantity, double price)
{
    stocks[symbol].quantity += quantity;
    stocks[symbol].avgPurchasePrice = ((stocks[symbol].avgPurchasePrice * stocks[symbol].quantity) + (price * quantity)) / (stocks[symbol].quantity + quantity);
}

void Portfolio::sellStock(const std::string& symbol, int quantity, double price)
{
    if (stocks[symbol].quantity >= quantity) {
        stocks[symbol].quantity -= quantity;
    }
}

double Portfolio::getCurrentValue(const std::map<std::string, double>& currentPrices) const
{
    double totalValue = 0.0;
    for (const auto& pair : stocks) {
        totalValue += pair.second.quantity * currentPrices.at(pair.first);
    }
    return totalValue;
}

double Portfolio::getProfitLoss(const std::string& symbol, double currentPrice) const
{
    return (currentPrice - stocks.at(symbol).avgPurchasePrice) * stocks.at(symbol).quantity;
}
