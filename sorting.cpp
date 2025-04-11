#include "auth.h"
#include "structure.h"



void Sort(int categoryIndex, bool sortByPrice, int filterID) {
    while (!queueMy.empty()) queueMy.pop();

    
    Product* tempProducts = new Product[productCount];
    int validCount = 0;
    int count=categoryIndex+1;
    if (count==8)
    {
        count--;
    }
   
    for (int i = 0; i < productCount; i++) {
        if (products[i].category == categoryNames[count] && (products[i].id == filterID || products[i].id == 4)) {
            tempProducts[validCount++] = products[i];
        }
    }

   
    if (sortByPrice && validCount > 0) {
        for (int i = 0; i < validCount - 1; i++) {
            for (int j = 0; j < validCount - i - 1; j++) {
                if (tempProducts[j].price > tempProducts[j + 1].price) {
                    Product temp = tempProducts[j];
                    tempProducts[j] = tempProducts[j + 1];
                    tempProducts[j + 1] = temp;
                }
            }
        }
    }

  
    for (int i = 0; i < validCount; i++) {
        queueMy.push(tempProducts[i]);
    }

    delete[] tempProducts;
}

void SortOutput() {
    if (queueMy.empty()) {
        cout << "Нет товаров для отображения.\n";
        return;
    }

    queue<Product> tempQueue = queueMy;
    int counter = 1;

    while (!tempQueue.empty()) {
        Product item = tempQueue.front();
        cout << counter++ << ")" << item.name << " — $" << item.price << "\n";
        tempQueue.pop();
    }
}

void SortPrice(int categoryIndex, bool sortByPrice) {
  
    while (!queueMy.empty()) queueMy.pop();

  
    Product* tempProducts = new Product[productCount];
    int validCount = 0;

   
    for (int i = 0; i < productCount; i++) {
        if (products[i].category == categoryNames[categoryIndex]){
            tempProducts[validCount++] = products[i];
        }
    }

   
    if (sortByPrice && validCount > 0) {
        for (int i = 0; i < validCount - 1; i++) {
            for (int j = 0; j < validCount - i - 1; j++) {
                if (tempProducts[j].price > tempProducts[j + 1].price) {
                    Product temp = tempProducts[j];
                    tempProducts[j] = tempProducts[j + 1];
                    tempProducts[j + 1] = temp;
                }
            }
        }
    }

 
    for (int i = 0; i < validCount; i++) {
        queueMy.push(tempProducts[i]);
    }

    delete[] tempProducts;
}

void SortOutputPrice() {
    if (queueMy.empty()) {
        cout << "Нет товаров для отображения.\n";
        return;
    }

    queue<Product> tempQueue = queueMy;
    int counter = 1;

    while (!tempQueue.empty()) {
        Product item = tempQueue.front();
        cout << counter++ << ")" << item.name << " — $" << item.price << "\n";
        tempQueue.pop();
    }
}