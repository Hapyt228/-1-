#include "adminfunc.h"
#include "consolecleaning.h"
#include "proferka.h"

void Adminmenu() {
    bool start = true;
    bool view = false;
    while (start) {
        cout << "�������� ��� ������ �������" << endl;
        cout << "1 - �������� �����" << endl;
        cout << "2 - �������� �� �����" << endl;
        cout << "3 - �������������� �����" << endl;
        cout << "4 - �������������� ������������" << endl;
        cout << "5 - �����" << endl;


        int choice;
        getValidatedIntFromInput(choice);
        
        cout << endl;

        switch (choice) {
        case 1:
            AdminView();
            view = true;
            break;
        case 2:
            Delete();
            break;
        case 3:
            Editing();
            break;
        case 4: 
            Menuadminuser();
            break;
        case 5:
            cout << "������� �� ������������� ����������!" << endl;
            start = false;
            break;
        default:
            cout << "������: �������� ������� �� 1 �� 4." << endl;
        }
        if (start == true) {
            Cleaning();
        }
    }
}