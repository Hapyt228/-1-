#include "������.h"

using namespace std;

void Usermenu() {
    bool start = true;

    cout << "                           ����� ���������� � ���������� ��� �������� ����� ������ ��" << endl;
    cout << endl;

    while (start) {
        cout << "                                            �������� ��� ������ �������" << endl;
        cout << "                                                 1 - �������� ������" << endl;
        cout << "                                                 2 - �������� ������" << endl;
        cout << "                                                 4 - �������� ������" << endl;
        cout << "                                                 3 - �����" << endl;

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
            cout << "������� �� ������������� ����������!" << endl;
            start = false;
            break;
        case 4:
            Deletespork();
            break;
        default:
            cout << "������: �������� ������� �� 1 �� 3." << endl;
        }
    }
}