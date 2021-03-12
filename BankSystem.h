#ifndef BANKSYSTEM_H_INCLUDED
#define BANKSYSTEM_H_INCLUDED


#include <vector>
#include <string>
#include <cstring>
using namespace std;

class Customer;
class Account;
class Transaction;
//////////////////////////////////////////////////
///////////////////Bank///////////////////////////
//////////////////////////////////////////////////
class Bank
{
public:
    Bank(){};
    long unsigned create_customer(string const _name,string const _last_name);
    void disp_all_customers(void)const;
    void disp_all_accounts(void)const;
    long unsigned create_account(vector<long unsigned> const customer_id,double const balance);
    void add_owner_to_account(long unsigned const acc_id,long unsigned const owner_id);
    long unsigned book_transaction(long unsigned const _from_acc,long unsigned const _to_acc,double const _amount);
    void approve_transaction(long unsigned const _transaction_id,long unsigned const _owner_id);
    void decline_transaction(long unsigned const _transaction_id,long unsigned const _owner_id);
    void show_account(long unsigned const _acc_id)const;
private:
    vector<Customer> customers;
    vector<Account> accounts;
    vector<Transaction> transactions;
};

//////////////////////////////////////////////////
///////////////////Account////////////////////////
//////////////////////////////////////////////////
class Account
{
public:
    Account(vector<long unsigned> const _account_owners_ids,double const _balance);
    long unsigned get_id(void) const {return account_id;}
    double get_balance(void) const {return balance;}
    vector<long unsigned> get_owners(void) const{return account_owners_ids;}
    void add_owner(long unsigned const owner_id);
    void add_transaction(long unsigned const _tranaction_id){transactions_id.push_back(_tranaction_id);}
    vector<long unsigned> get_owners_ids(void) const{return account_owners_ids;}
    vector<long unsigned> get_transactions_ids(void) const{return transactions_id;}
private:
    static long unsigned account_id_counter;
    long unsigned account_id;
    vector<long unsigned> account_owners_ids;
    double balance;
    vector<long unsigned> transactions_id;
    friend class Bank;
};


enum Trans_status {Pending,Approved,Rejected};
//////////////////////////////////////////////////
//////////////////Transaction/////////////////////
//////////////////////////////////////////////////
class Transaction
{
public:
    Transaction(long unsigned const _from_acc,long unsigned const _to_acc,double const _amount,vector<long unsigned> _account_owners_ids,string const _status = "Pending");
    void each_owner_approval(long unsigned const _owner_id);
    void each_owner_decline(long unsigned const _owner_id);
    long unsigned get_transaction_id(void)const {return transaction_id;}
    string get_status(void)const {return status;}
    bool check_for_final_approval(void)const;
    double get_amount(void)const {return amount;}
    long unsigned get_from_acc(void)const {return from_acc;}
    long unsigned get_to_acc(void)const {return to_acc;}
private:
    static long unsigned transaction_id_counter;
    long unsigned transaction_id;
    long unsigned from_acc;
    long unsigned to_acc;
    double amount;
    string status;
    vector<pair<long unsigned,enum Trans_status>> owner_approval;
    friend class Bank;
};

//////////////////////////////////////////////////
///////////////////Customer///////////////////////
//////////////////////////////////////////////////
class Customer
{
public:
    Customer(string const _name,string const _last_name);
    long unsigned get_customer_id(void)const {return customer_unique_id;}
    string get_name(void) const {return name;}
    string get_last_name(void) const {return last_name;}
private:
    static long unsigned customer_id_counter;
    string name;
    string last_name;
    long unsigned customer_unique_id;
};

#endif // BANKSYSTEM_H_INCLUDED
