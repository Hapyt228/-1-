#include "adminfunc.h"

void Adminmenu() {
    bool start = true;
    while (start) {
        cout << "                                            �������� ��� ������ �������" << endl;
        cout << "                                                 1 - �������� �����" << endl;
        cout << "                                                 2 - �������� �� �����" << endl;
        cout << "                                                 3 - �������������� ������ ������������" << endl;
        cout << "                                                 4 - �������������� �����" << endl;
        cout << "                                                 6 - �����" << endl;

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

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:
            cout << "������� �� ������������� ����������!" << endl;
            start = false;
            break;
        default:
            cout << "������: �������� ������� �� 1 �� 3." << endl;
        }
    }
}