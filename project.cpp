#include "auth.h"
#include "user.h"
#include "admin.h"
#include "consolecleaning.h"

int main() {
    setlocale(LC_ALL, "Russian");

    loadUsers();

    bool loggedIn = false;
    int loginChoice;

    while (!loggedIn) {
        cout << "1. Войти" << endl;
        cout << "2. Регистрация" << endl;
        cout << "3. Выход" << endl;
        cout << "Выберите действие: ";
        cin >> loginChoice;

        switch (loginChoice) {
        case 1:
            loginUser();
            loggedIn = currentUser != nullptr;
            if (checkIfAdmin()) {
                loggedIn = checkIfAdmin;
            }
            break;
        case 2:
            registerUser();
            break;
        case 3:
            cout << "Выход из программы." << endl;
            return 0;  
        default:
            cout << "Неверный выбор! Попробуйте снова." << endl;
        }
        if (!loggedIn) {
            system("cls");
        }
    }

    if (checkIfAdmin()) {
        system("cls");
        cout << "Добро пожаловать, администратор!" << endl;
        Adminmenu();
    }
    else {
        Usermenu();
    }

    return 0;
}
