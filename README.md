Smart E-Commerce Product Search and Recommendation System

Project Overview

The Smart E-Commerce Product Search and Recommendation System is a console-based application developed using the C programming language. The project demonstrates the practical application of Data Structures and Algorithms (DSA) in an e-commerce environment.

It provides features such as product management, searching, sorting, shopping cart management, purchasing, purchase history, customer management, and product recommendations.

The main objective of this project is to demonstrate how data structures and algorithms can be used to build an efficient product search and recommendation system.

Team Members

- Sowjanya
- Jaswanth
- Karthikeya
- Keerthi

Features

1. Product Management

- Add new products.
- Display available products.
- Update product details.
- Delete products.
- Manage product information such as ID, name, category, brand, type, price, rating, and stock quantity.

2. Product Search

- Search products by product ID.
- Search products by name.
- Search products by category.
- Use a Binary Search Tree (BST) for product ID searching.

3. Product Sorting

- Sort products by price.
- Sort products by rating.
- Sort products by name.
- Use selection sort for sorting operations.

4. Shopping Cart

- Add products to the cart.
- Remove products from the cart.
- Manage product quantities in the cart.
- Display cart contents.

5. Purchase Management

- Purchase products from the cart.
- Update product stock after purchase.
- Generate a purchase bill.
- Maintain purchase history.

6. Customer Management

- Add new customers.
- Search for customers.
- Update customer details.
- Delete customer records.
- Display customer information.

7. Product Recommendation

- Recommend products based on purchase information.
- Prioritize products with matching brand and type, where applicable.
- Consider matching product types and categories.
- Exclude products that have already been purchased or are out of stock, where implemented.

8. Binary Search Tree

- Insert product IDs into a BST.
- Search for products using the BST.
- Display product IDs using inorder traversal.
- Delete product IDs from the BST.

Data Structures Used

1. Arrays

Arrays are used to store product and customer information.

2. Linked Lists

Linked lists are used for managing shopping cart items and purchase history.

3. Binary Search Tree (BST)

A Binary Search Tree is used to organize product IDs and support searching, insertion, traversal, and deletion operations.

Algorithms Used

- Linear Search: Used to search for products and customers.
- BST Search: Used to search for products by ID.
- Selection Sort: Used to sort products by price, rating, and name.
- BST Insertion: Used to insert product IDs into the tree.
- Inorder Traversal: Used to display product IDs in sorted order.
- BST Deletion: Used to remove product IDs from the tree.
- Rule-Based Recommendation: Used to recommend products based on product attributes and purchase information.

Technologies Used

- Programming Language: C
- IDE: Dev-C++
- Compiler: TDM-GCC
- Data Structures: Arrays, Linked Lists, Binary Search Trees
- Application Type: Console-Based Application

Project Structure

Smart-E-Commerce-System/
│
├── main.c
├── structures.h
│
├── bst.c
├── bst.h
│
├── cart.c
├── cart.h
│
├── customer.c
├── customer.h
│
├── purchase.c
├── purchase.h
│
├── search_sort.c
├── search_sort.h
│
├── recommendation.c
└── recommendation.h

How to Run the Project

1. Clone or download this repository.
2. Open Dev-C++.
3. Open the project source files.
4. Make sure all ".c" files are included in the compilation.
5. Compile the program.
6. Run the executable.
7. Use the console menu to access the available features.

Objective

The objective of this project is to apply Data Structures and Algorithms to a real-world e-commerce scenario. It demonstrates how arrays, linked lists, and Binary Search Trees can be used for product management, searching, sorting, cart operations, purchase history, and recommendations.

The project focuses on demonstrating DSA concepts through a practical application rather than implementing only basic CRUD operations.

Repository

GitHub: https://github.com/konakarthikeya/Smart-E-Commerce-System

Conclusion

The Smart E-Commerce Product Search and Recommendation System demonstrates the use of fundamental Data Structures and Algorithms in an e-commerce application. It combines product and customer management with searching, sorting, shopping cart operations, purchasing, and product recommendations in a modular C program.
