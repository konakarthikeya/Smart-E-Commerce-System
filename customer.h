#ifndef CUSTOMER_H
#define CUSTOMER_H

struct Customer
{
    int id;
    char name[50];
    char phone[20];
    char email[50];
};

void addCustomer(struct Customer customers[], int *customerCount);
void displayCustomers(struct Customer customers[], int customerCount);
void searchCustomer(struct Customer customers[], int customerCount);
void updateCustomer(struct Customer customers[], int customerCount);
void deleteCustomer(struct Customer customers[], int *customerCount);

#endif