#include "auth.h"
#include "structure.h"
#include <queue>


void Sort(int categoryIndex, bool sortByPrice, int filterID) {
    // Очищаем очередь перед заполнением
    while (!queueMy.empty()) queueMy.pop();

    // 1. Создаем временный массив
    Product* tempProducts = new Product[productCount];
    int validCount = 0;
    int count=categoryIndex+1;
    if (count==8)
    {
        count--;
    }
    // 2. Копируем только нужные товары (с фильтрацией по категории, если задана)
    for (int i = 0; i < productCount; i++) {
        if (products[i].category == categoryNames[count] && (products[i].id == filterID || products[i].id == 4)) {
            tempProducts[validCount++] = products[i];
        }
    }

    // 3. Сортировка по цене (если нужно)
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

    // 4. Заполняем очередь
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
    // Очищаем очередь перед заполнением
    while (!queueMy.empty()) queueMy.pop();

    // 1. Создаем временный массив
    Product* tempProducts = new Product[productCount];
    int validCount = 0;

    // 2. Копируем только нужные товары (с фильтрацией по категории, если задана)
    for (int i = 0; i < productCount; i++) {
        if (products[i].category == categoryNames[categoryIndex]){
            tempProducts[validCount++] = products[i];
        }
    }

    // 3. Сортировка по цене (если нужно)
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

    // 4. Заполняем очередь
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