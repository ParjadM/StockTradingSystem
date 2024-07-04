// StockTradingSystem.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <string>
#include <deque>
#include <limits>
#include <map>
#include <utility>

//including header files!
#include "StockTrade.h"
#include "Account.h"
#include "User.h"
#include "TradeRecord.h"
#include "StockPriceNext.h"
#include "Exception.h"
#include "StockInfo.h"

// Global variable
int loggedin = 0;
int globalid = 4;
int stockglobalid = 8;
std::vector<StockTrade> vect;
std::vector<User> vectuser;
TradeRecord tradeRecord;
std::vector<Trader> vectuser1;
std::vector<std::pair<int, std::map<int, int>>> vec;
std::vector<std::pair<std::string, double>> account;
// to store the original values
std::vector<double> originalValues;
// to store the differences
std::vector<double> differences;

//option 1
void Option1()
{
	try {
		int n = 0;
		double m = 0;
		int h = 0;
		double temp = 0;
		double temp6 = 0;
		double temp4 = 0;
		double temp5 = 0;
		double temp1 = 0;
		double temp7 = 0;
		int selection;
		Account accounts;
		Sell sell;
		Purchase buy;
		do
		{
			//Option 1 
			std::cout << "Stock Exchange" << std::endl;
			std::cout << "1: Buy" << std::endl;
			std::cout << "2: Sell" << std::endl;
			std::cout << "3: Display" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: Return to main menu" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				std::cout << "You have Entered Option 1" << std::endl;
				std::cout << "Please select id of the StockBroker to purchase" << std::endl;
				std::cout << "ID Choices are from 1 to " << vectuser.size() << std::endl;
				std::cin >> n;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > vectuser.size()) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(vectuser.size()) + ".");
				}
				temp = vectuser[n - 1].getBalance();

				temp6 = vectuser[n - 1].getQuantity();

				buy.setBalance(temp);
				std::cout << "Please select id of the Stock Option you would like to purchase" << std::endl;
				std::cout << "ID Choices are from 1 to " << vect.size() << std::endl;
				std::cin >> h;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > vect.size()) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(vect.size()) + ".");
				}
				temp7 = vect[h - 1].getStockPrice();
				std::cout << "Please enter how much you want to purchase" << std::endl;
				std::cout << "Your budget is " << temp << std::endl;
				std::cin >> m;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > temp) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(temp) + ".");
				}
				buy.setQuantity(temp6);
				buy.setprice(temp7);

				temp4 = buy.buy(m);

				


				temp5 = buy.getQuantity();
				temp1 = buy.getBalance();

				if (temp > temp1) {
					double result = temp - m - temp6;
					vectuser[n - 1].setBalance(result);
					std::cout << "New Balance: $" << vectuser[n - 1].getBalance() << std::endl;
					std::cout << "Fee Charge of: $" << buy.getfee() << std::endl;
					std::cout << "New Stock Quantity is now: " << buy.getQuantity() << std::endl;
					std::cout << "You Bought at Stock Price: $" << temp7 << std::endl;
					vectuser[n - 1].setQuantity(buy.getQuantity());

					//update the value
					if ((n-1) >= 0 && (n-1) <= vec.size()) {
						std::map<int, int>& idQuantityMap = vec[n-1].second;
						if (idQuantityMap.count(h-1) > 0) {
							idQuantityMap[h-1] = buy.getQuantity();
							std::cout << "Updateded Stock ID: " << (h) << " to " << buy.getQuantity() << std::endl;
						}
						else {
							std::cout << "Key not found in map." << std::endl;
						}
					}
					else {
						std::cout << "Index out of range." << std::endl;
					}

					std::cout << "_______________________________" << std::endl;
					double percentageChange = StockPriceNext::modifyStockPriceBuy(vect, h);
					std::cout << "the New Stock Price has increased by: " << percentageChange << "%" << std::endl;

					int stockId = h - 1;
					std::string stockSymbol = vect[stockId].getStockSymbol();
					std::string stockTradeName = vect[stockId].getStockTrade();
					double price = vect[stockId].getStockPrice();

					// After a successful buy operation
					tradeRecord.addTrade(stockSymbol, stockId, stockTradeName, price, "Purchase", n);


					//calculate the loss
					double totaldif = (percentageChange/100) * m;
					account.push_back(std::make_pair("Buy", -totaldif));
				}
				else {
					std::cout << "insufficent fund" << std::endl;
				}
				system("pause");
			}
			else if (selection == 2)
			{
				std::cout << "You have Entered Option 2" << std::endl;
				std::cout << "Please select id of the StockBroker to Sell" << std::endl;
				std::cout << "ID Choices are from 1 to " << vectuser.size() << std::endl;
				std::cin >> n;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > vectuser.size()) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(vectuser.size()) + ".");
				}

				temp = vectuser[n - 1].getBalance();
				sell.setBalance(temp);
				
				std::cout << "Please select id of the Stock Option you would like to sell" << std::endl;
				std::cout << "ID Choices are from 1 to " << vect.size() << std::endl;
				std::cin >> h;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > vect.size()) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(vect.size()) + ".");
				}
				//retrieve and store in temp6
				std::map<int, int>& idQuantityMap = vec[n - 1].second;
				temp6 = idQuantityMap[h-1];

				std::cout << "Please enter how much you want to Sell" << std::endl;
				std::cout << "You have: " << temp6 << " Many Stocks avaiable" << std::endl;
				std::cin >> m;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > temp6) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(temp6) + ".");
				}
				temp7 = vect[h - 1].getStockPrice();
				sell.setQuantity(temp6);
				sell.setprice(temp7);
				temp4 = sell.SoldFee(m);

				
				


				if (temp4 <= temp6) {

					double result = temp + m - temp6;
					vectuser[n - 1].setBalance(result);
					std::cout << "New Balance: $" << vectuser[n - 1].getBalance() << std::endl;
					std::cout << "Fee Charge of: $" << sell.getfee() << std::endl;
					std::cout << "Stock Quantity is now " << sell.getQuantity() << std::endl;
					std::cout << "You sold at Stock Price: $" << temp7 << std::endl;
					vectuser[n - 1].setQuantity(sell.getQuantity());

					std::cout << "_______________________________" << std::endl;
					double percentageChange = StockPriceNext::modifyStockPriceSell(vect, h);
					std::cout << "the New Stock Price has decreased by: -" << percentageChange << "%" << std::endl;

					
					

					int stockId = h - 1;
					std::string stockSymbol = vect[stockId].getStockSymbol();
					std::string stockTradeName = vect[stockId].getStockTrade();
					double price = vect[stockId].getStockPrice();

					// After a successful sell operation
					tradeRecord.addTrade(stockSymbol, stockId, stockTradeName, price, "Sold", n);



					//calculate the loss
					double totaldif = (percentageChange / 100) * m;
					account.push_back(std::make_pair("Sell", -totaldif));

					system("pause");




				}
				else {
					std::cout << "not enough stocks available" << std::endl;
				}

			}
			else if (selection == 3)
			{
				std::cout << "You have Entered Option 3" << std::endl;
				std::cout << "Please select id of the StockBroker to display Balance" << std::endl;
				std::cout << "ID Choices are from 1 to " << vectuser.size() << std::endl;
				std::cin >> n;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > vectuser.size()) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(vectuser.size()) + ".");
				}
				std::cout << "Balance is: $" << vectuser[n - 1].getBalance() << std::endl;
				system("pause");
			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else
			{

				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}


		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Option1();
	}
}


void Option2()
{
	try {
		int selection;
		do
		{
			//Option 2 
			std::cout << "Stock Information Menu" << std::endl;
			std::cout << "1: Display Stock Information" << std::endl;
			std::cout << "2: Add Stock Information" << std::endl;
			std::cout << "3: Remove Stock Information" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: Return to main menu" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				std::cout << "_____________________________________________" << std::endl;
				for (int i = 1; i < vect.size() + 1; i++) {
					std::string temp1 = vect[i - 1].getStockTrade();
					if (temp1 != "Null") {
						vect[i - 1].showInfo();
						std::cout << std::endl;
					}
				}
				std::cout << "All user information displayed" << std::endl;
				system("pause");
			}
			else if (selection == 2)
			{
				std::string StockTradeName = "";
				int id = stockglobalid;
				std::string StockSymbol = "";
				double price = 0;
				std::cout << "Please enter the name of the stock" << std::endl;
				std::cin >> StockTradeName;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				std::cout << "Please enter the symbol of stock" << std::endl;
				std::cin >> StockSymbol;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				std::cout << "Please enter the stock price" << std::endl;
				std::cin >> price;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				vect.push_back(StockTrade(StockSymbol, stockglobalid, StockTradeName, price));

				// add to vec
				std::map<int, int> my_map;
				my_map[stockglobalid] = 0;

				std::vector<std::pair<int, std::map<int, int>>> vec;
				vec.push_back(std::make_pair(1, my_map));


				std::cout << "You have succesfully added an stock" << std::endl;
				std::cout << "The User ID is: " << stockglobalid << std::endl;
				stockglobalid++;
				system("pause");
			}
			else if (selection == 3)
			{
				int num = 0;
				int position = 0;
				std::cout << "Please enter id number of the Stock Trade to remove from the list" << std::endl;
				std::cout << "ID Choices are from 1 to " << vect.size() << std::endl;
				std::cin >> num;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				position = (num - 1);
				if (num > 0)
				{
					vect[num - 1].setStockTrade("Null");
					vect[num - 1].setTradeID(0);
					vect[num - 1].setStockSymbol("Null");
					vect[num - 1].setStockPrice(0);
					std::cout << "You have successfully removed user from the list!" << std::endl;

				}
				else
				{
					std::cout << "you enter wrong number please try agian";
				}
				system("pause");
			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else
			{

				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}

		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Option2();
	}
}

void Option3()
{
	try {
		int selection;
		do
		{
			//Option 3 
			std::cout << "Portfolio Menu" << std::endl;
			std::cout << "1: Add User" << std::endl;
			std::cout << "2: Remove User" << std::endl;
			std::cout << "3: Display All User" << std::endl;
			std::cout << "4: Display Individual Stocks For User" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: Return to main menu" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				std::string name = "";
				int id = globalid;
				int age = 0;
				double balance = 0;
				double stockquantity = 0;
				std::cout << "Please enter the name of the user" << std::endl;
				std::cin >> name;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				std::cout << "Please enter the age" << std::endl;
				std::cin >> age;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				std::cout << "Please enter the balance of user" << std::endl;
				std::cin >> balance;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				vectuser.push_back(User(name, globalid, age, balance, 0));
				// add user to vec
				for (int i = 0; i < vectuser.size(); ++i) {
					std::map<int, int> idQuantityMap;
					for (int j = 0; j < stockglobalid; ++j) {
						idQuantityMap[j] = 0;
					}
					vec.push_back(std::make_pair(i, idQuantityMap));
				}

				std::cout << "You have succesfully added an user" << std::endl;
				std::cout << "The User ID is: " << globalid << std::endl;
				globalid++;
				system("pause");
			}
			else if (selection == 2)
			{
				int num = 0;
				int position = 0;
				std::cout << "Please enter id number of the User to remove from the list" << std::endl;
				std::cout << "ID Choices are from 1 to " << vectuser.size() << std::endl;
				std::cin >> num;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				position = (num - 1);
				if (num > 0)
				{
					vectuser[num - 1].setName("Null");
					vectuser[num - 1].setId(0);
					vectuser[num - 1].setAge(0);
					vectuser[num - 1].setBalance(0);
					vectuser[num - 1].setQuantity(0);
					std::cout << "You have successfully removed user from the list!" << std::endl;
				}
				else
				{
					std::cout << "you enter wrong number please try agian";
				}

				system("pause");
			}
			else if (selection == 3)
			{
				std::cout << "_____________________________________________" << std::endl;
				for (int i = 1; i < vectuser.size() + 1; i++) {
					std::string temp1 = vectuser[i - 1].getName();
					if (temp1 != "Null") {
						vectuser[i - 1].showInfo();
						std::cout << std::endl;
					}
				}
				std::cout << "All user information displayed" << std::endl;
				system("pause");
			}
			else if (selection == 4) {
				int n = 0;
				std::cout << "Please enter the ID of user to display it's Stock" << std::endl;
				std::cout << "ID Choices are from 1 to " << vectuser.size() << std::endl;
				std::cin >> n;
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
					throw CustomException("Invalid input. Please enter a number.");
				}
				else if (n <= 0 || n > vectuser.size()) {
					throw CustomException("Invalid input. Please enter a number between 1 and " + std::to_string(vectuser.size()) + ".");
				}
				// Assuming n is a valid index for vec
				std::map<int, int>& traderStocks = vec[n - 1].second;

				// Loop through the map
				for (const auto& pair : traderStocks) {
					int stockId = pair.first;
					int quantity = pair.second;
					std::cout << "Stock ID: " << (stockId + 1) << ", Quantity: " << quantity << std::endl;
				}

			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else
			{

				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}

		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Option3();
	}
}
// Option 4
void Option4()
{
	try {
		int selection;
		do
		{
			//Option 4
			std::cout << "Trade Record History Menu" << std::endl;
			std::cout << "1: Display Trade Record" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: Return to main menu" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				std::cout << "_____________________________________________" << std::endl;
				tradeRecord.displayTrades();
				system("pause");
			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else
			{
				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}

		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Option4();
	}
}
// Option 5
void Option5()
{
	try {
		int selection;
		do
		{
			//Option 5
			std::cout << "Refresh Menu" << std::endl;
			std::cout << "1: Refresh" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: Return to main menu" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				std::cout << "_____________________________________________" << std::endl;

				std::srand(static_cast<unsigned>(std::time(0)));

				// to store the percentage changes
				std::deque<double> percentageChanges;

				for (int i = 1; i <= vect.size(); i++) {
					originalValues.push_back(vect[i - 1].getStockPrice());
					percentageChanges.push_back(StockPriceNext::modifyStockPrice(vect, i));
				}
				std::cout << "----------- Show Info -----------" << std::endl;
				for (int i = 1; i < vect.size() + 1; i++) {
					std::string temp1 = vect[i - 1].getStockTrade();
					if (temp1 != "Null") {
						std::cout << "The stock price for trade ID: " << i << std::endl;
						vect[i - 1].showInfo();
					}
					std::cout << "Stock Changed by: " << percentageChanges[i - 1] << " % " << std::endl;
					double difference = vect[i - 1].getStockPrice() - originalValues[i - 1];
					double originalValue = originalValues[i - 1];
					double newValue = vect[i - 1].getStockPrice();
					double difference1 = newValue - originalValue;
					double percentageChange = (difference1 / originalValue) * 100;
					originalValues[i - 1] += difference;
					if (differences.size() > i - 1) {
						differences[i - 1] += percentageChange;
					}
					else {
						differences.push_back(percentageChange);
					}
					std::cout << "The Total Percentage Change: " << differences[i - 1] << "%" << std::endl;
					std::cout << std::endl;
				}

				system("pause");
			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else
			{
				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}

		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Option5();
	}
}
// Option 6
void Option6()
{
	try {
		int selection;
		do
		{
			//Option 6
			std::cout << "Stock Difference Menu" << std::endl;
			std::cout << "1: loss" << std::endl;
			std::cout << "2: Profit/Loss in percentage after refresh" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: Return to main menu" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				std::cout << "_____________________________________________" << std::endl;
				for (const auto& pair : account) {
					std::cout << "Type: " << pair.first << ", loss$: " << pair.second << std::endl;
				}

			}
			else if (selection == 2) {
				std::cout << "_____________________________________________" << std::endl;
				for (int i = 0; i < differences.size(); i++) {
					std::cout << "Difference for trade ID " << (i + 1) << ": " << differences[i] << "%" << std::endl;
				}
			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else
			{
				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}

		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Option5();
	}
}
//Main Menu
void MainMenu()
{
	try {
		int selection;
		do
		{
			//Main menu options
			std::cout << "----------Main Menu-------------" << std::endl;
			std::cout << "1: Stock Exchange" << std::endl;
			std::cout << "2: Stock Information (Including add/remove stock options)" << std::endl;
			std::cout << "3: User Details (Including add/remove user)" << std::endl;
			std::cout << "4: Display Trade Record History" << std::endl;
			std::cout << "5: Refresh" << std::endl;
			std::cout << "6: Stock Difference (Profit/loss)" << std::endl;
			std::cout << "10: clear screen" << std::endl;
			std::cout << "0: End Program" << std::endl;
			std::cout << "Enter selection:" << std::endl;
			std::cin >> selection;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (selection == 1)
			{
				Option1();
			}
			else if (selection == 2)
			{
				Option2();
			}
			else if (selection == 3)
			{
				Option3();
			}
			else if (selection == 4)
			{
				Option4();
			}
			else if (selection == 5)
			{
				Option5();
			}
			else if (selection == 6)
			{
				Option6();
			}
			else if (selection == 10)
			{
				system("CLS");
			}
			else if (selection == 0)
			{
				std::cout << "END OF PROGRAM THANK YOU FOR USING IT!" << std::endl;
			}
			else
			{
				std::cout << "Please Enter the correct number choices in menu" << std::endl;
			}

		} while (selection != 0);
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		MainMenu();
	}
}

void Login()
{
	try {
		//log in menu
		int password = 1111;
		int username = 1111;
		int pass = 0;
		int user = 0;
		int attempt = 0;
		while (true) {
			std::cout << "Welcome To Stock Trading System." << std::endl;
			std::cout << "Please enter your username and password." << std::endl;
			std::cout << "For demonstration purposes the password and username is (1111)" << std::endl;
			std::cout << "Username:" << std::endl;
			std::cin >> user;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			std::cout << "Enter Your Password: " << std::endl;
			std::cin >> pass;
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw CustomException("Invalid input. Please enter a number.");
			}
			if (pass == password && user == username) {
				std::cout << "You have successfully logged in" << std::endl;
				loggedin = 1;
				break;
			}
			else
			{
				std::cout << "You entered the wrong user name and/or password" << std::endl;
			}
			attempt = attempt + 1;
			std::cout << "You have three attempts this is attempt: #" << attempt << std::endl;
			if (attempt == 3) {
				std::cout << "You have failed to log in, System Shutdown!" << std::endl;
				loggedin = 0;
				break;
			}
		}
	}
	catch (const CustomException& e) {
		std::cerr << "Caught an exception: " << e.what() << std::endl;
		std::cout << "Please Try Agian" << std::endl;
		std::cout << "Reset" << std::endl;
		Login();
	}
}
int main()
{
	// Preload User
	vectuser.push_back(User("user1", 1, 25, 10000, 0));
	vectuser.push_back(User("user2", 2, 20, 10000, 0));
	vectuser.push_back(User("user3", 3, 20, 10000, 0));

	// Preload StockTrade
	vect.push_back(StockTrade("Agilent Technologies", 1, "A", 10));
	vect.push_back(StockTrade("Apple", 2, "APPL", 20));
	vect.push_back(StockTrade("Berkshire Hathaway", 3, "BRK", 10));
	vect.push_back(StockTrade("Citigroup", 4, "C", 20));
	vect.push_back(StockTrade("Google", 5, "GOOG", 20));
	vect.push_back(StockTrade("Intel", 6, "INTC", 10));
	vect.push_back(StockTrade("Microsoft", 7, "MSFT", 30));


	
	

	// Preload Trader data
	for (int i = 0; i < vectuser1.size(); ++i) { 
		Trader trader(i);
		vectuser1.push_back(trader);
	}

	// Preload Stock data for each Trader
	for (Trader& trader : vectuser1) {
		for (int j = 0; j < vect.size(); ++j) { 
			trader.addStock(j, 0); // 
		}
	}
	// Preload pair data
	for (int i = 0; i < vectuser.size(); ++i) {
		std::map<int, int> idQuantityMap;
		for (int j = 0; j < stockglobalid; ++j) {
			idQuantityMap[j] = 0; 
		}
		vec.push_back(std::make_pair(i, idQuantityMap));
	}
	
	//login menu
	Login();

	//main menu
	if (loggedin == 1)
	{
		system("CLS");
		//call the menu
		MainMenu();
	}
	//unsuccessful attempt 
	else
	{
		system("CLS");
		std::cout << "You have entered the wrong information too many times" << std::endl;
		std::cout << "Have a nice day!" << std::endl;
	}
	return 0;
}
