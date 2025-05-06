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
        cout << count+1 << ") " << "[" << current.category << "] " << current.name << " � $" << current.price << endl;
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
    cout << "������� ������, ������� ������ �������: ";
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
    cin >> choiceCategory;
    Product p;
    string name;
    cout << "������� �������� ������ " << endl;
    cin.ignore();
    getline(cin, name);
    int price;
    cout << "������� ��������� ������ " << endl;
    cin >> price;
    int id;
    cout << "������� ���� ������ " << endl;
    cin >> id;
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
    AdminView();
    readProductsFromFile(filename);
    int choice;
    cout << "�������� ������ ��� ������ �������� ";
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
            cout << "�������� ������: " << endl << currentIndex+1 << ") " << "[" << current.category << "] " << current.name << " � $" << current.price << " " << current.id << endl;
            cout << "�������� ��� ������ �������� (1- ���������, 2-��������, 3-����, 4-����): " << endl;
            bool sup = true;
            while (sup) {
                cin >> choiceUser;
                int choiceCategory;
                string name;
                int price;
                int id;
                switch (choiceUser) {
                case 1:
                    cout << "������� ��������� �� ������� ������ ��������(�� 1 �� 8) " << endl;
                    cin >> choiceCategory;
                    current.category = categoryNames[choiceCategory - 1];
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 2:                    
                    cout << "������� ����� �������� ������ " << endl;
                    cin.ignore();
                    getline(cin, name);
                    current.name = name;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 3:
                    cout << "������� ����� ��������� ������ " << endl;
                    cin >> price;
                    current.price = price;
                    sup = false;
                    tempQueue.push(current);
                    break;
                case 4:
                    cout << "������� ����� ���� ������ " << endl;
                    cin >> id;
                    current.id = id;
                    sup = false;
                    tempQueue.push(current);
                    break;
                default:
                    cout << "������: �������� ������� �� 1 �� 5." << endl;
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
    cin.ignore();
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
    cin >> index;
    cin.ignore;

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
        cin >> choiceUser;
        cout << endl;
        switch (choiceUser) {
        case 1:
            cout << "������ �������������:" << endl;
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
            cout << "������: �������� ������� �� 1 �� 4." << endl;
        }
        if (start == true) {
            Cleaning();
        }


    }
}