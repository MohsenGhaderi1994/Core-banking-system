#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>
#include <cstdlib>
#include <cstring>
#include <utility>
#include "BankSystem.h"

using namespace std;

////////////////////////////////////////////
vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(), [] (const char &x, const char &y) {
        return x == y and x == ' ';
    });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}

////////////////////////////////////////////
int main()
{
    string buffer;
    Bank my_bank;
    while(true)
    {
        getline(cin,buffer);
        vector<string> temp = split_string(buffer);
        if(temp[0]=="create_customer")
        {
            my_bank.create_customer(temp[1],temp[2]);
        }
        else if(temp[0]=="create_account")
        {
            vector<long unsigned> customers_id(temp.size()-2,0);
            for(size_t i = 0;i<customers_id.size();i++)
            {
                char * cstr = new char [temp[i+1].length()+1];
                std::strcpy (cstr, temp[i+1].c_str());
                customers_id[i] = strtoul (cstr, NULL, 0);
            }
            my_bank.create_account(customers_id,stod(temp.back()));
        }
        else if(temp[0]=="display_customers")
        {
            my_bank.disp_all_customers();
            //my_bank.disp_all_accounts();
        }
        else if(temp[0]=="add_owner")
        {
            char * cstr = new char [temp[1].length()+1];
            std::strcpy (cstr, temp[1].c_str());
            long unsigned acc_id = strtoul (cstr, NULL, 0);
            char * cstr1 = new char [temp[2].length()+1];
            std::strcpy (cstr1, temp[2].c_str());
            long unsigned owner_id = strtoul (cstr1, NULL, 0);
            my_bank.add_owner_to_account(acc_id,owner_id);
        }
        else if(temp[0]=="book_transaction")
        {
            char * cstr = new char [temp[1].length()+1];
            std::strcpy (cstr, temp[1].c_str());
            long unsigned from_id = strtoul (cstr, NULL, 0);
            char * cstr1 = new char [temp[2].length()+1];
            std::strcpy (cstr1, temp[2].c_str());
            long unsigned to_id = strtoul (cstr1, NULL, 0);

            my_bank.book_transaction(from_id,to_id,stod(temp[3]));
        }
        else if(temp[0]=="approve_transaction")
        {
            char * cstr = new char [temp[1].length()+1];
            std::strcpy (cstr, temp[1].c_str());
            long unsigned tran_id = strtoul (cstr, NULL, 0);
            char * cstr1 = new char [temp[2].length()+1];
            std::strcpy (cstr1, temp[2].c_str());
            long unsigned owner_id = strtoul (cstr1, NULL, 0);
            my_bank.approve_transaction(tran_id, owner_id);
        }
        else if(temp[0]=="decline_transaction")
        {
            char * cstr = new char [temp[1].length()+1];
            std::strcpy (cstr, temp[1].c_str());
            long unsigned tran_id = strtoul (cstr, NULL, 0);
            char * cstr1 = new char [temp[2].length()+1];
            std::strcpy (cstr1, temp[2].c_str());
            long unsigned owner_id = strtoul (cstr1, NULL, 0);
            my_bank.decline_transaction(tran_id, owner_id);
        }
        else if(temp[0]=="show_account")
        {
            char * cstr = new char [temp[1].length()+1];
            std::strcpy (cstr, temp[1].c_str());
            long unsigned acc_id = strtoul (cstr, NULL, 0);
            my_bank.show_account(acc_id);
        }
        else if(temp[0]=="exit")
        {
            break;
        }
        else
        {
            cout << "Invalid command" <<endl;
        }
    }

    return 0;
}
