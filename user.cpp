#include "userfunc.h"
#include "consolecleaning.h"

void Usermenu() {
    bool start = true;

    cout << "                           ����� ���������� � ���������� ��� �������� ����� ������ ��" << endl;
    cout << endl;

    while (start) {
        cout << "                                            �������� ��� ������ �������" << endl;
        cout << "                                                 1 - �������� ������" << endl;
        cout << "                                                 2 - �������� ������" << endl;
        cout << "                                                 3 - �������� ������" << endl;
        cout << "                                                 4 - �����" << endl;

        int choice;
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            Creating();
            break;
        case 2:
            View();
            break;
        case 3:
            Deletespork();
            break;
        case 4:
            cout << "������� �� ������������� ����������!" << endl;
            start = false;
            break;
        default:
            cout << "������: �������� ������� �� 1 �� 4." << endl;
        }
        if (start) {
            Cleaning();
        }
    }
}