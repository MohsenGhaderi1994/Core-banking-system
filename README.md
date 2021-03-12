# Core-banking-system

The goal is to design a core banking system with object-oriented programming in C++. 
The system should be able to support the following operations:  
  customer registration 
  
  account opening 
  
  link multiple accounts to a client 
  
  support co-owner accounts 
  
  support money transfer between the accounts 
  
  ask for approval of all the owners before performing the transaction

### Sample input
"""
  create_customer Peter Mims
  
  create_customer Paul Turnage
  
  create_customer Elizabeth Sanders
  
  create_customer Angel Garces
  
  create_account 1 2 2000
  
  create_account 3 1000
  
  book_transaction 0 1 1800
  
  book_transaction 0 1 1000
  
  add_owner 0 0
  
  approve_transaction 0 1
  
  approve_transaction 0 2
  
  approve_transaction 1 1
  
  approve_transaction 1 2
  
  show_account 0
"""
### Sample output
"""
0

1

2 

3 

0 

1 

0 

1

Balance : 200

Owners : Paul Turnage , Elizabeth Sanders , Peter Mims

Transactions:

[1] 1800 to 1 -> accepted

[2] 1000 to 1 -> rejected
"""
