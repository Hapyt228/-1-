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
        cout << "1. �����" << endl;
        cout << "2. �����������" << endl;
        cout << "3. �����" << endl;
        cout << "�������� ��������: ";
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
            cout << "����� �� ���������." << endl;
            return 0;  
        default:
            cout << "�������� �����! ���������� �����." << endl;
        }
        if (!loggedIn) {
            system("cls");
        }
    }

    if (checkIfAdmin()) {
        system("cls");
        cout << "����� ����������, �������������!" << endl;
        Adminmenu();
    }
    else {
        Usermenu();
    }

    return 0;
}
