#include "structure.h"
#include "auth.h"
#include "consolecleaning.h"
#include "hash.h"
#include "proferka.h"

using namespace std;

const string filename = "assembly.txt";
const string selectedFilename = "selected.txt";
queue<Product> tempQueue;

void SearchProducts() {
    system("cls");
    readProductsFromFile(filename);
    if (queueMy.empty()) {
        cout << "Нет товаров для поиска.\n";
        return;
    }

    int categoryIndex = 0;
    cout << "Введите категорию в которой хотите поиск (от 1 до 8): ";
    getValidatedIntFromInput(categoryIndex);
    while (categoryIndex < 1 || categoryIndex > 9) {
        cout << "Введите заново категорию от 1 до 8" << endl;
        getValidatedIntFromInput(categoryIndex);
    }
    categoryIndex -= 1;

    int matchingIndices[MAX_PRODUCTS];
    int indexCounter = 0;
    for (int i = 0; i < productCount; ++i) {
        if (products[i].category == categoryNames[categoryIndex]) {
            matchingIndices[indexCounter++] = i;
        }
    }

        cout << "Список " << categoryNames[categoryIndex] << ":\n";
        for (int i = 0; i < indexCounter; ++i) {
            int index = matchingIndices[i];
            cout << i + 1 << ") " << products[index].name
                << " — $" << products[index].price << "\n";
        }

    cout << endl << endl;

    cout << "Выберите тип поиска:\n";
    cout << "1) По производителю\n";
    cout << "2) По цене\n";
    int choice;
    getValidatedIntFromInput(choice);
    while (choice < 0 || choice > 3) {
        cout << "Введите заново категорию от 1 до 2" << endl;
        getValidatedIntFromInput(choice);
    }



    string producer;
    int price;
    bool flag = false;
    int i = 0;

    if (choice == 2) {
        Product temp[MAX_PRODUCTS];
        int size = 0;
        cout << "Введите максимальную цену: ";
        getValidatedIntFromInput(price);
        while (!queueMy.empty() && size < MAX_PRODUCTS) {
            temp[size++] = queueMy.front();
            queueMy.pop();
        }

        for (int i = 0; i < size - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < size; ++j) {
                if (temp[j].price < temp[minIndex].price) {
                    minIndex = j;
                }
            }
            if (minIndex != i) {
                Product t = temp[i];
                temp[i] = temp[minIndex];
                temp[minIndex] = t;
            }
        }

        int left = 0;
        int right = size - 1;
        int lastValidIndex = -1;

        while (left <= right) {
            int mid = (left + right) / 2;
            if (temp[mid].price <= price) {
                lastValidIndex = mid;
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }

        bool found = false;
        for (int i = 0; i <= lastValidIndex; ++i) {
            if (temp[i].category == categoryNames[categoryIndex]) {
                cout << "[" << temp[i].category << "] " << temp[i].name << " — $" << temp[i].price << endl;
                found = true;
            }
        }
    }
    if (choice == 1) {
        cout << "Введите производителя: ";
        getline(cin, producer);
        while (!queueMy.empty()) {
            Product current = queueMy.front();
            queueMy.pop();
            if (choice == 1 && products[i].category == categoryNames[categoryIndex]) {
                string sup = current.name;
                for (size_t i = 0; i < producer.length(); ++i) {
                    producer[i] = toupper(producer[i]);
                    sup[i] = toupper(sup[i]);
                }
                size_t pos = sup.find(producer);
                if (pos != string::npos) {
                    cout << "[" << current.category << "] " << current.name << " — $" << current.price << endl;
                    flag = true;
                }
            }
            tempQueue.push(current);
            i++;
        }
    }
    if (choice == 1 && !flag) {
       cout << "Товаров с такой ценой нету" << endl;
    }
    else if (choice == 2 && !flag) {
        cout << "Товаров с таким производителем нету" << endl;
    }


    queueMy = tempQueue;
    clearProducts();
    Cleaning();
}

void AdminViewdefolt() {
    system("cls");
    readProductsFromFile(filename);
    int count = 0;
    while (!queueMy.empty()) {
        Product current = queueMy.front();
        cout << count + 1 << ") " << "[" << current.category << "] " << current.name << " — $" << current.price << endl;
        queueMy.pop();
        tempQueue.push(current);
        count++;
    }
    cout << endl << endl;
    queueMy = tempQueue;

    clearProducts();
}


void AdminView() {
    system("cls");
    int choice;
    do {
        cout << "3) Просмотр всех товаров\n";
        cout << "2) Поиск по производителю или цене\n";
        cout << "1) Выход\n";
        getValidatedIntFromInput(choice);
        switch (choice) {
        case 3:
            AdminViewdefolt();
            break;
        case 2:
            SearchProducts();
            break;
        case 1:
            break;
        default:
            cout << "Ошибка: выберите вариант от 1 до 3." << endl;;
            choice = 0;
            break;
        } 
    } while (choice != 1);
}

void Delete() {
    AdminViewdefolt();
    readProductsFromFile(filename);
    int userChoice;
    cout << "Введите строку, который хотите удалить: ";
    getValidatedIntFromInput(userChoice);
        queue<Product> tempQueue;
        int currentIndex=0;

        while (!queueMy.empty()) {
            Product current = queueMy.front();
            queueMy.pop();

            if (currentIndex != userChoice-1) {
                tempQueue.push(current);
            }
            else {
                cout << "Удалена строка: " << userChoice << endl;
            }

            currentIndex++;
        }
        queueMy = tempQueue;
        saveQueueToFile();
        clearProducts();
}

void Addition() {
    system("cls");
    readProductsFromFile(filename);
    int choiceCategory;
    cout << "Введите категорию которую хотите добавить(от 1 до 8)" << endl;
    getValidatedIntFromInput(choiceCategory);
    while (choiceCategory < 0 || choiceCategory > 8) {
        cout << "Введите заново категорию от 1 до 8" << endl;
        getValidatedIntFromInput(choiceCategory);
    }
    Product p;
    string name;
    cout << "Введите название товара " << endl;
    getline(cin, name);
    int price;
    cout << "Введите стоимость товара " << endl;
    getValidatedIntFromInput(price);
    int id;
    cout << "Введите айди товара " << endl;
    getValidatedIntFromInput(id);
    p.category = categoryNames[choiceCategory-1];
    p.name = name;
    p.price = price;
    p.id = id;
    queueMy.push(p);
    saveQueueToFile();
    cout << "Комплектующие сохранено " << endl;
    clearProducts();
}

void postEditing() {
    AdminViewdefolt();
    readProductsFromFile(filename);
    int choice;
    cout << "Выберите строку где хотите изменить ";
    getValidatedIntFromInput(choice);
    queue<Product> tempQueue;
    int currentIndex=0;

    while (!queueMy.empty()) {
        Product current = queueMy.front();
        queueMy.pop();

        if (currentIndex != choice-1) {
            tempQueue.push(current);
        }
        else {
            int choiceUser;
            cout << "Выбраная строка: " << endl << currentIndex+1 << ") " << "[" << current.category << "] " << current.name << " — $" << current.price << " " << current.id << endl;
            cout << "Выберите что хотите изменить (1- категорию, 2-название, 3-цена, 4-айди): " << endl;
            bool sup = true;
            while (sup) {
                getValidatedIntFromInput(choiceUser);
                int choiceCategory;
                string name;
                int price;
                int id;
                switch (choiceUser) {
                case 1:
                    cout << "Введите категорию на которую хотите изменить(от 1 до 8) " << endl;
                    getValidatedIntFromInput(choiceCategory);
                    current.category = categoryNames[choiceCategory - 1];
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 2:                    
                    cout << "Введите новое название товара " << endl;
                    getline(cin, name);
                    current.name = name;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 3:
                    cout << "Введите новую стоимость товара " << endl;
                    getValidatedIntFromInput(price);
                    current.price = price;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 4:
                    cout << "Введите новое айди товара " << endl;
                    getValidatedIntFromInput(id);
                    current.id = id;
                    sup = false;
                    tempQueue.push(current);
                    break;
                default:
                    cout << "Ошибка: выберите вариант от 1 до 4." << endl;
                    break;
                }
            }

        }
        currentIndex++;
    }
    queueMy = tempQueue;
    saveQueueToFile();
    cout << "Товар изменен!" << endl;
    clearProducts();
}




void Editing() {
    system("cls");
    bool start = true;
    while (start) {

        cout << "                                            Выберите что хотите сделать" << endl;
        cout << "                                                 1 - Добавить в файл" << endl;
        cout << "                                                 2 - Редактировать написанное в файле" << endl;
        cout << "                                                 3 - Выход" << endl;

        int choiceUser;
        getValidatedIntFromInput(choiceUser);
        cout << endl;
        switch (choiceUser) {
        case 1:
            Addition();
            break;
        case 2:
            postEditing();
            break;
        case 3:
            start = false;
            break;
        default:
            cout << "Ошибка: выберите вариант от 1 до 4." << endl;
        }
        if (start == true){
             
            Cleaning();
        }


    }
}

void AddUser() { 
    system("cls");
    if (userCount >= MAX_USERS) {
        cout << "Превышено максимальное количество пользователей!" << endl;
        return;
    }

    string username, password;
    cout << "Введите логин пользователя: ";
    getline(cin, username);

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << "Пользователь с таким логином уже существует!" << endl;
            return;
        }
    }

    cout << "Введите пароль: ";
    getline(cin, password);

    users[userCount++] = { username, hashPassword(password) };
    saveUsers();
    cout << "Пользователь успешно добавлен!" << endl;
}

void DeleteUser(){
    system("cls");
    cout << "Список пользователей:" << endl;
    for (int i = 1; i < userCount; i++) {
        cout << i << ": " << users[i].username << endl;
    }

    int index;
    cout << "Введите индекс пользователя для удаления: ";
    getValidatedIntFromInput(index);
   

    if (index < 0 || index >= userCount) {
        cout << "Неверный индекс!" << endl;
        return;
    }

    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    userCount--;
    saveUsers();
    cout << "Пользователь успешно удалён!" << endl;
}



void Menuadminuser() {
    system("cls");
    bool start = true;
    while (start) {

        cout << "                                            Выберите что хотите сделать" << endl;
        cout << "                                                 1 - Просмотреть пользователей" << endl;
        cout << "                                                 2 - Добавить пользователя" << endl;
        cout << "                                                 3 - Удалить пользователя" << endl;
        cout << "                                                 4 - Выход" << endl;

        int choiceUser;
        getValidatedIntFromInput(choiceUser);
        
        cout << endl;
        switch (choiceUser) {
        case 1:
            cout << "Список пользователей:" << endl;
            for (int i = 1; i < userCount; i++) {
                cout << i << ": " << users[i].username << endl;
            }
            break;
        case 2:
            AddUser();
            break;
        case 3:
            DeleteUser();
            break;
        case 4:
            start = false;
            break;
        default:
            cout << "Ошибка: выберите вариант от 1 до 4." << endl;
        }
        if (start == true) {
             
            Cleaning();
        }


    }
}