//File name: main.cpp
//Developer: Giovanni Carmona
//Email: carmonag141228@student.vvc.edu
//Description: This program will prompt the user for the day for which they will provide a deposit or withdrawl. The user will also have to provide the description of the deposit/withdrawl. It will compute the balance of the user and the minimum and average daily balance interest.
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

class Transaction
{
public:
   Transaction();
   void read();
   int get_day();
   double get_amount();
   void print() const;
private:
   int day;
   double amount;
   std::string description;

};
Transaction::Transaction()
{
  day = 0;
  amount = 0;
}

void Transaction::read()
{
  std::cout << "Please enter day: ";
  std::cin >> day; 
  std::cout << "Please enter amount: ";
  std::cin >> amount; 
  std::cout <<"Please enter description: ";
  std::cin.ignore();
  std::getline(std::cin,description);
}

int Transaction::get_day()
{
  return day;
}
double Transaction::get_amount()
{
  return amount;
}
void Transaction::print() const
{
  std::cout << "Day: "  << day << std::endl;
  std::cout << "Amount: " << amount << std::endl;
  std::cout << "Description: " << description << std::endl;
}

const int MAX_DAY = 30;

class Statement
{
public:
   Statement();
   void read();
   void compute_balances();
   void print();
   double get_average_daily_balance();
   double get_minimum_daily_balance();
   
private:
   std::vector<Transaction> transactions;
   std::vector<double> daily_balances;
};
Statement::Statement()
{
  
}

void Statement::read()
{
 bool more = true;
  while(more)
  {
    Transaction tran;
    tran.read();
   std::cout << "More data? (y/n)";
   std::string response;
   std::cin >> response;

   if(response != "y")
   {
     more= false;
   }
    else 
    {
   transactions.push_back(tran);
    
    }
  }
  compute_balances();
}

void Statement::compute_balances()
{
  int i = 0;
  double balance = 0;
  int day;
  for(day = 1; day <= MAX_DAY; day ++)
  {
    while (i < transactions.size() && transactions[i].get_day() == day)
    {
      balance = balance + transactions[i].get_amount();
      i ++;
    }
    daily_balances.push_back(balance);
  }
}

void Statement::print()
{
  int i = 0;
  std::cout << std::endl << "Statement" << std::endl;
  for(int day = 1; day <= MAX_DAY; day++)
  {
    if(i < transactions.size() && transactions[i].get_day() == day)
    {
      transactions[i].print();
       i++;
    std::cout << "Day: " << std::setw(2) << day << std::endl << "Amount: " << std::setw(2) << daily_balances[i -1]<< std::endl << std::endl;
    }
    else
    {
     
     day = 31;
      
    }
  }
  const double interest = 0.005;
  std::cout << "Minimun daily balance interest: " << get_minimum_daily_balance() * interest << std:: endl;
  std::cout << "Average daily balance interest: " << get_average_daily_balance() * interest << std::endl;
}
double Statement::get_average_daily_balance()
{
  int day;
  double sum = 0;
  for (day = 0; day < daily_balances.size(); day++)
  {
    sum = sum + daily_balances[day];
  }
  return sum/MAX_DAY;
}
double Statement::get_minimum_daily_balance()
{
  double min = daily_balances[0];
  for(int day = 1; day < daily_balances.size(); day++)
  {
    if(daily_balances[day] < min)
    {
        min = daily_balances[day];
    }  
  }
    return min; 

}
int main()
{
   Statement b;
   b.read();
   b.print();

   return 0;
}
