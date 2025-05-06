#include "structure.h"
#include "auth.h"
#include "consolecleaning.h"
#include "hash.h"

using namespace std;

const string filename = "assembly.txt";
const string selectedFilename = "selected.txt";
queue<Product> tempQueue;

void AdminView() {
    system("cls");
    readProductsFromFile(filename);
    int count=0;
    while (!queueMy.empty()) {
        Product current = queueMy.front();
        cout << count+1 << ") " << "[" << current.category << "] " << current.name << " — $" << current.price << endl;
        queueMy.pop();
        tempQueue.push(current);
        count++;
    }
    queueMy = tempQueue;
    clearProducts();
}

void Delete() {
    AdminView();
    readProductsFromFile(filename);
    int userChoice;
    cout << "Введите строку, который хотите удалить: ";
    cin >> userChoice;
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
    cin >> choiceCategory;
    Product p;
    string name;
    cout << "Введите название товара " << endl;
    cin.ignore();
    getline(cin, name);
    int price;
    cout << "Введите стоимость товара " << endl;
    cin >> price;
    int id;
    cout << "Введите айди товара " << endl;
    cin >> id;
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
    AdminView();
    readProductsFromFile(filename);
    int choice;
    cout << "Выберите строку где хотите изменить ";
    cin >> choice;
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
                cin >> choiceUser;
                int choiceCategory;
                string name;
                int price;
                int id;
                switch (choiceUser) {
                case 1:
                    cout << "Введите категорию на которую хотите изменить(от 1 до 8) " << endl;
                    cin >> choiceCategory;
                    current.category = categoryNames[choiceCategory - 1];
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 2:                    
                    cout << "Введите новое название товара " << endl;
                    cin.ignore();
                    getline(cin, name);
                    current.name = name;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 3:
                    cout << "Введите новую стоимость товара " << endl;
                    cin >> price;
                    current.price = price;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 4:
                    cout << "Введите новое айди товара " << endl;
                    cin >> id;
                    current.id = id;
                    sup = false;
                    tempQueue.push(current);
                    break;
                default:
                    cout << "Ошибка: выберите вариант от 1 до 5." << endl;
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
        cin >> choiceUser;
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
    cin.ignore();
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
    cin >> index;
    cin.ignore;

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
        cin >> choiceUser;
        cout << endl;
        switch (choiceUser) {
        case 1:
            cout << "Список пользователей:" << endl;
            for (int i = 1; i < userCount; i++) {
                cout << i << ": " << users[i].username << endl;
            }
            cin.ignore();
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