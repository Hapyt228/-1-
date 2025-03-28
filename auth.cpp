#include "Курсач.h"

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
        cout << "Превышено максимальное количество пользователей!" << endl;
        return;
    }

    string username, password;
    cout << "Введите логин: ";
    cin.ignore();
    getline(cin, username);

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username) {
            cout << "Такой пользователь уже существует!" << endl;
            return;
        }
    }

    cout << "Введите пароль: ";
    getline(cin, password);

    users[userCount++] = { username, password, false }; 
    saveUsers();
    cout << "Регистрация успешна!" << endl;
}


void loginUser() {
    string username, password;
    cout << "Введите логин: ";
    cin.ignore();
    getline(cin, username);
    cout << "Введите пароль: ";
    getline(cin, password);

    if (username == ADMIN.username && password == ADMIN.password) {
        cout << "Вход выполнен: Администратор!" << endl;
        Admin = true;
        return;
    }

    for (int i = 0; i < userCount; i++) {
        if (users[i].username == username && users[i].password == password) {
            currentUser = &users[i];
            cout << "Вход выполнен успешно!" << endl;
            return;
        }
    }

    cout << "Неверный логин или пароль!" << endl;
}


string getCurrentUser() {
    return currentUser ? currentUser->username : "";
}


bool checkIfAdmin() {
    return Admin;
}
