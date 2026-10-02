#ifndef CUSTOMER_H
#define CUSTOMER_H

#include "structures.h"

void addCustomer(struct Customer customers[], int *customerCount);
void displayCustomers(struct Customer customers[], int customerCount);
void searchCustomer(struct Customer customers[], int customerCount);
void updateCustomer(struct Customer customers[], int customerCount);
void deleteCustomer(struct Customer customers[], int *customerCount);

#endif