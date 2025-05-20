#include "auth.h"
#include "user.h"
#include "admin.h"
#include "consolecleaning.h"
#include "proferka.h"

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
        getValidatedIntFromInput(loginChoice);
        switch (loginChoice) {
        case 1:
            loginUser();
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

        if (checkIfAdmin()) {
            system("cls");
            cout << "����� ����������, �������������!" << endl;
            Adminmenu();
        }
        else {
            Usermenu();
        }
        if (!loggedIn) {
            Cleaning();
        }

    }

    return 0;
}
