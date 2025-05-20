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
        cout << "��� ������� ��� ������.\n";
        return;
    }

    int categoryIndex = 0;
    cout << "������� ��������� � ������� ������ ����� (�� 1 �� 8): ";
    getValidatedIntFromInput(categoryIndex);
    while (categoryIndex < 1 || categoryIndex > 9) {
        cout << "������� ������ ��������� �� 1 �� 8" << endl;
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

        cout << "������ " << categoryNames[categoryIndex] << ":\n";
        for (int i = 0; i < indexCounter; ++i) {
            int index = matchingIndices[i];
            cout << i + 1 << ") " << products[index].name
                << " � $" << products[index].price << "\n";
        }

    cout << endl << endl;

    cout << "�������� ��� ������:\n";
    cout << "1) �� �������������\n";
    cout << "2) �� ����\n";
    int choice;
    getValidatedIntFromInput(choice);
    while (choice < 0 || choice > 3) {
        cout << "������� ������ ��������� �� 1 �� 2" << endl;
        getValidatedIntFromInput(choice);
    }



    string producer;
    int price;
    bool flag = false;
    int i = 0;

    if (choice == 2) {
        Product temp[MAX_PRODUCTS];
        int size = 0;
        cout << "������� ������������ ����: ";
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
                cout << "[" << temp[i].category << "] " << temp[i].name << " � $" << temp[i].price << endl;
                found = true;
            }
        }
    }
    if (choice == 1) {
        cout << "������� �������������: ";
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
                    cout << "[" << current.category << "] " << current.name << " � $" << current.price << endl;
                    flag = true;
                }
            }
            tempQueue.push(current);
            i++;
        }
    }
    if (choice == 1 && !flag) {
       cout << "������� � ����� ����� ����" << endl;
    }
    else if (choice == 2 && !flag) {
        cout << "������� � ����� �������������� ����" << endl;
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
        cout << count + 1 << ") " << "[" << current.category << "] " << current.name << " � $" << current.price << endl;
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
        cout << "3) �������� ���� �������\n";
        cout << "2) ����� �� ������������� ��� ����\n";
        cout << "1) �����\n";
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
            cout << "������: �������� ������� �� 1 �� 3." << endl;;
            choice = 0;
            break;
        } 
    } while (choice != 1);
}

void Delete() {
    AdminViewdefolt();
    readProductsFromFile(filename);
    int userChoice;
    cout << "������� ������, ������� ������ �������: ";
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
                cout << "������� ������: " << userChoice << endl;
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
    cout << "������� ��������� ������� ������ ��������(�� 1 �� 8)" << endl;
    getValidatedIntFromInput(choiceCategory);
    while (choiceCategory < 0 || choiceCategory > 8) {
        cout << "������� ������ ��������� �� 1 �� 8" << endl;
        getValidatedIntFromInput(choiceCategory);
    }
    Product p;
    string name;
    cout << "������� �������� ������ " << endl;
    getline(cin, name);
    int price;
    cout << "������� ��������� ������ " << endl;
    getValidatedIntFromInput(price);
    int id;
    cout << "������� ���� ������ " << endl;
    getValidatedIntFromInput(id);
    p.category = categoryNames[choiceCategory-1];
    p.name = name;
    p.price = price;
    p.id = id;
    queueMy.push(p);
    saveQueueToFile();
    cout << "������������� ��������� " << endl;
    clearProducts();
}

void postEditing() {
    AdminViewdefolt();
    readProductsFromFile(filename);
    int choice;
    cout << "�������� ������ ��� ������ �������� ";
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
            cout << "�������� ������: " << endl << currentIndex+1 << ") " << "[" << current.category << "] " << current.name << " � $" << current.price << " " << current.id << endl;
            cout << "�������� ��� ������ �������� (1- ���������, 2-��������, 3-����, 4-����): " << endl;
            bool sup = true;
            while (sup) {
                getValidatedIntFromInput(choiceUser);
                int choiceCategory;
                string name;
                int price;
                int id;
                switch (choiceUser) {
                case 1:
                    cout << "������� ��������� �� ������� ������ ��������(�� 1 �� 8) " << endl;
                    getValidatedIntFromInput(choiceCategory);
                    current.category = categoryNames[choiceCategory - 1];
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 2:                    
                    cout << "������� ����� �������� ������ " << endl;
                    getline(cin, name);
                    current.name = name;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 3:
                    cout << "������� ����� ��������� ������ " << endl;
                    getValidatedIntFromInput(price);
                    current.price = price;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 4:
                    cout << "������� ����� ���� ������ " << endl;
                    getValidatedIntFromInput(id);
                    current.id = id;
                    sup = false;
                    tempQueue.push(current);
                    break;
                default:
                    cout << "������: �������� ������� �� 1 �� 4." << endl;
                    break;
                }
            }

        }
        currentIndex++;
    }
    queueMy = tempQueue;
    saveQueueToFile();
    cout << "����� �������!" << endl;
    clearProducts();
}




void Editing() {
    system("cls");
    bool start = true;
    while (start) {

        cout << "                                            �������� ��� ������ �������" << endl;
        cout << "                                                 1 - �������� � ����" << endl;
        cout << "                                                 2 - ������������� ���������� � �����" << endl;
        cout << "                                                 3 - �����" << endl;

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
            cout << "������: �������� ������� �� 1 �� 4." << endl;
        }
        if (start == true){
             
            Cleaning();
        }


    }
}

void AddUser() { 
    system("cls");
    if (userCount >= MAX_USERS) {
        cout << "��������� ������������ ���������� �������������!" << endl;
        return;
    }

    string username, password;
    cout << "������� ����� ������������: ";
    getline(cin, username);

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << "������������ � ����� ������� ��� ����������!" << endl;
            return;
        }
    }

    cout << "������� ������: ";
    getline(cin, password);

    users[userCount++] = { username, hashPassword(password) };
    saveUsers();
    cout << "������������ ������� ��������!" << endl;
}

void DeleteUser(){
    system("cls");
    cout << "������ �������������:" << endl;
    for (int i = 1; i < userCount; i++) {
        cout << i << ": " << users[i].username << endl;
    }

    int index;
    cout << "������� ������ ������������ ��� ��������: ";
    getValidatedIntFromInput(index);
   

    if (index < 0 || index >= userCount) {
        cout << "�������� ������!" << endl;
        return;
    }

    for (int i = index; i < userCount - 1; i++) {
        users[i] = users[i + 1];
    }

    userCount--;
    saveUsers();
    cout << "������������ ������� �����!" << endl;
}



void Menuadminuser() {
    system("cls");
    bool start = true;
    while (start) {

        cout << "                                            �������� ��� ������ �������" << endl;
        cout << "                                                 1 - ����������� �������������" << endl;
        cout << "                                                 2 - �������� ������������" << endl;
        cout << "                                                 3 - ������� ������������" << endl;
        cout << "                                                 4 - �����" << endl;

        int choiceUser;
        getValidatedIntFromInput(choiceUser);
        
        cout << endl;
        switch (choiceUser) {
        case 1:
            cout << "������ �������������:" << endl;
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
            cout << "������: �������� ������� �� 1 �� 4." << endl;
        }
        if (start == true) {
             
            Cleaning();
        }


    }
}