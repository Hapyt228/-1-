#include <iostream>
#include <string>

using namespace std;

void Cleaning() {
    cout << "   Нажмите Enter для продолжения " << endl;
    string Enter;
    bool sup=true;
    while (sup) {
        getline(cin, Enter);
        if (Enter.empty()) {
            system("cls");
            sup = false;
        }
        else {
            cout << "Введите Enter, а не другой символ ";
        }
    }

}
