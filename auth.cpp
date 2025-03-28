#include "������.h"

const User ADMIN = { "admin", "admin123", true };
User users[MAX_USERS]; 
int userCount = 1;
User* currentUser = nullptr; 
bool Admin=false;

void loadUsers() {
    ifstream file(USERS_FILE);
    if (!file) return;

    string username, password;
    bool isAdmin;
    while (file >> username >> password >> isAdmin) {
        if (userCount < MAX_USERS) {
            users[userCount++] = { username, password, isAdmin };
        }
    }
    file.close();
}


void saveUsers() {
    ofstream file(USERS_FILE);
    for (int i = 0; i < userCount; i++) {
        file << users[i].username << " " << users[i].password << " " << users[i].isAdmin << endl;
    }
    file.close();
}


void registerUser() {
    if (userCount >= MAX_USERS) {
        cout << "��������� ������������ ���������� �������������!" << endl;
        return;
    }

    string username, password;
    cout << "������� �����: ";
    cin.ignore();
    getline(cin, username);

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << "����� ������������ ��� ����������!" << endl;
            return;
        }
    }

    cout << "������� ������: ";
    getline(cin, password);

    users[userCount++] = { username, password, false }; 
    saveUsers();
    cout << "����������� �������!" << endl;
}


void loginUser() {
    string username, password;
    cout << "������� �����: ";
    cin.ignore();
    getline(cin, username);
    cout << "������� ������: ";
    getline(cin, password);

    if (username == ADMIN.username && password == ADMIN.password) {
        cout << "���� ��������: �������������!" << endl;
        Admin = true;
        return;
    }

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            currentUser = &users[i];
            cout << "���� �������� �������!" << endl;
            return;
        }
    }

    cout << "�������� ����� ��� ������!" << endl;
}


string getCurrentUser() {
    return currentUser ? currentUser->username : "";
}


bool checkIfAdmin() {
    return Admin;
}
