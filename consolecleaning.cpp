#include <iostream>
#include <string>

using namespace std;

void Cleaning() {
    cout << "   ������� Enter ��� ����������� " << endl;
    string Enter;
    bool sup=true;
    cin.ignore();
    while (sup) {
        getline(cin, Enter);
        if (Enter.empty()) {
            system("cls");
            sup = false;
        }
        else {
            cout << "������� Enter, � �� ������ ������ ";
        }
    }

}
