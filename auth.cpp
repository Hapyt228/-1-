#include "auth.h"
#include "consolecleaning.h"
#include "hash.h"


const User ADMIN = { "admin", "admin123"};
User users[MAX_USERS]; 
int userCount = 1;
User* currentUser = nullptr; 
bool Admin=false;


void loadUsers() {
    queue <User> client;
    ifstream file(USERS_FILE);
    if (!file) return;
    User p;
    string username, password;
    bool isAdmin;
    while (file >> username >> password) {
        if (userCount < MAX_USERS) {
            users[userCount++] = { username, password};
            p.username = username;
           client.push(p);
        }
    }
    file.close();
}


void saveUsers() {
    ofstream file(USERS_FILE);
    for (int i = 1; i < userCount; i++) {
        file << users[i].username << " " << users[i].password << endl;
    }
    file.close();
}


void registerUser() {
    system("cls");
    if (userCount >= MAX_USERS) {
        cout << "��������� ������������ ���������� �������������!" << endl;
        return;
    }

    string username, password;
    cout << "������� �����: ";
    getline(cin, username);  

    for (int i = 1; i < userCount; i++) {
        if (users[i].username == username && username == ADMIN.username) {  
            cout << "����� ������������ ��� ����������!" << endl;
            return;
        }
    }

    cout << "������� ������: ";
    getline(cin, password);  

    users[userCount] = { username,  hashPassword(password) };
    currentUser = &users[userCount];
    saveUsers();
    cout << "����������� �������!" << endl;
}


void loginUser() {
    system("cls");
    string username, password;
    cout << "������� �����: ";
    getline(cin, username);  
    cout << "������� ������: ";
    getline(cin, password);  

    if (username == ADMIN.username && password == ADMIN.password) {
        static User adminUser = ADMIN;
        currentUser = &adminUser;
        return;
    }

    for (int i = 1; i < userCount; i++) {
        if (users[i].username == username && users[i].password == hashPassword(password)) {
            currentUser = &users[i];
            system("cls");
            return;
        }
    }

    cout << "�������� ����� ��� ������!" << endl;
}



string getCurrentUser() {
    return currentUser ? currentUser->username : "";
}


bool checkIfAdmin() {
    return currentUser != nullptr && currentUser->username == "admin";
}