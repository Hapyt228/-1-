#include "adminfunc.h"

void Adminmenu() {
    bool start = true;
    while (start) {
        cout << "                                            �������� ��� ������ �������" << endl;
        cout << "                                                 1 - �������� �����" << endl;
        cout << "                                                 2 - �������� �� �����" << endl;
        cout << "                                                 3 - �������������� �����" << endl;
        cout << "                                                 4 - �����" << endl;

        int choice;
        cin >> choice;
        cout << endl;

        switch (choice) {
        case 1:
            AdminView();
            break;
        case 2:
            Delete();
            break;
        case 3:
            Editing();
            break;
        case 4:
            cout << "������� �� ������������� ����������!" << endl;
            start = false;
            break;
        default:
            cout << "������: �������� ������� �� 1 �� 4." << endl;
        }
    }
}