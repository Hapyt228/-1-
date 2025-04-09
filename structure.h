#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
using namespace std;

 const int MAX_PRODUCTS = 1000;

struct Product {
    std::string category;
    std::string name;
    int price;
    int id;
};

extern Product products[MAX_PRODUCTS];
extern int productCount;
extern queue <Product> queueMy;
extern const char* categoryNames[];

void readProductsFromFile(const std::string& filename);
void clearProducts();
void saveQueueToFile();

#endif // PRODUCT_DATA_H
