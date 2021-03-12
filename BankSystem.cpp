#include "BankSystem.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>

//////////////////////////////////////////////////
///////////////////Bank///////////////////////////
//////////////////////////////////////////////////

void Bank::show_account(long unsigned const _acc_id)const
{

    //vector<long unsigned>& curr_owners_ids= accounts[_acc_id].account_owners_ids;
    cout << setprecision(2) << fixed;
    cout << "Balance : " <<  accounts[_acc_id].get_balance() << endl;
    cout << "Owners : ";
    for(size_t j = 0; j<accounts[_acc_id].account_owners_ids.size();j++)
    {
        cout << customers[accounts[_acc_id].account_owners_ids[j]].get_name() << " " << customers[accounts[_acc_id].account_owners_ids[j]].get_last_name();
        if(j != accounts[_acc_id].account_owners_ids.size()-1)
            cout << " , ";
    }
    cout << endl;
    cout << "Transactions:" << endl;
    for(size_t j = 0; j<accounts[_acc_id].transactions_id.size();j++)
    {
        cout << "[" << j+1 << "] " << transactions[accounts[_acc_id].transactions_id[j]].get_amount();
        cout << " from account " <<transactions[accounts[_acc_id].transactions_id[j]].get_from_acc();
        cout << " to account " << transactions[accounts[_acc_id].transactions_id[j]].get_to_acc();
        cout << " -> " << transactions[accounts[_acc_id].transactions_id[j]].get_status() << endl;
    }
}
void Bank::approve_transaction(long unsigned const _transaction_id,long unsigned const _owner_id)
{
    Transaction& curr = transactions[_transaction_id];
    curr.each_owner_approval(_owner_id);
    if(curr.check_for_final_approval())
    {
        double account_balance = accounts[curr.get_from_acc()].get_balance();
        if(curr.get_amount() > account_balance)
        {
            curr.status = "Rejected";
        }
        else
        {
            accounts[curr.get_from_acc()].balance -= curr.get_amount();
            curr.status = "Accepted";
        }
    }
}
void Bank::decline_transaction(long unsigned const _transaction_id,long unsigned const _owner_id)
{
    transactions[_transaction_id].each_owner_decline(_owner_id);
}
long unsigned Bank::book_transaction(long unsigned const _from_acc,long unsigned const _to_acc,double const _amount)
{
    transactions.push_back(Transaction(_from_acc,_to_acc,_amount,accounts[_from_acc].get_owners_ids()));
    long unsigned id = transactions.back().get_transaction_id();
    accounts[_from_acc].add_transaction(id);
    accounts[_to_acc].add_transaction(id);
    return id;
}
void Bank::add_owner_to_account(long unsigned const acc_id,long unsigned const owner_id)
{
    accounts[acc_id].add_owner(owner_id);
}
/*void Bank::disp_all_accounts(void)const
{
    cout << "ID" << '\t' << "Balance" << "\t\t" << "Owners IDs" << endl;

    for(long unsigned i = 0 ; i< accounts.size();i++)
    {
        accounts[i].disp_account();
    }
}*/
long unsigned Bank::create_account(vector<long unsigned> const customer_id,double const balance)
{
    accounts.push_back(Account(customer_id,balance));
    return accounts.back().get_id();
}
long unsigned Bank::create_customer(string const _name,string const _last_name)
{
    customers.push_back(Customer(_name,_last_name));
    return customers.back().get_customer_id();
}
void Bank::disp_all_customers(void)const
{
    cout << "ID" << '\t' << "Name" << '\t' << "Last name" << endl;
    for(long unsigned i = 0 ; i< customers.size();i++)
    {
        cout << i << '\t' << customers[i].get_name() << '\t' << customers[i].get_last_name() << endl;
    }
}
//////////////////////////////////////////////////
///////////////////Account////////////////////////
//////////////////////////////////////////////////

long unsigned Account::account_id_counter = 0;

void Account::add_owner(long unsigned const owner_id)
{
    account_owners_ids.push_back(owner_id);
}

Account::Account(vector<long unsigned> const _account_owners_ids,double const _balance)
{
    balance = _balance;
    account_id = account_id_counter++;
    account_owners_ids.resize(_account_owners_ids.size());
    for(size_t i = 0 ; i< _account_owners_ids.size();i++)
    {
        account_owners_ids[i] = _account_owners_ids[i];
    }
}

//////////////////////////////////////////////////
//////////////////Transaction/////////////////////
//////////////////////////////////////////////////
long unsigned Transaction::transaction_id_counter=0;

bool Transaction::check_for_final_approval(void)const
{
    bool final_approved = true;
    for(size_t i = 0; i < owner_approval.size();i++)
    {
            if(owner_approval[i].second == Pending)
            {
                final_approved = false;
                break;
            }
    }
    return final_approved;
}

void Transaction::each_owner_approval(long unsigned const _owner_id)
{
    for(size_t i = 0; i < owner_approval.size();i++)
    {
        if(owner_approval[i].first == _owner_id)
        {
            owner_approval[i].second = Approved;
            break;
        }
    }
}
void Transaction::each_owner_decline(long unsigned const _owner_id)
{
    for(size_t i = 0; i < owner_approval.size();i++)
    {
        if(owner_approval[i].first == _owner_id)
        {
            owner_approval[i].second = Rejected;
            status = "Rejected";
            break;
        }
    }
}
Transaction::Transaction(long unsigned const _from_acc,long unsigned const _to_acc,double const _amount,vector<long unsigned> _account_owners_ids,string const _status)
{
    transaction_id = transaction_id_counter++;
    from_acc = _from_acc;
    to_acc = _to_acc;
    amount = _amount;
    status = _status;
    owner_approval.resize(_account_owners_ids.size());
    for(size_t i = 0; i< owner_approval.size();i++)
    {
        owner_approval[i]= make_pair(_account_owners_ids[i],Pending);
    }
}

//////////////////////////////////////////////////
///////////////////Customer///////////////////////
//////////////////////////////////////////////////
long unsigned Customer::customer_id_counter = 0;

Customer::Customer(string const _name,string const _last_name)
{
    name = _name;
    last_name = _last_name;
    customer_unique_id = customer_id_counter++;
}
