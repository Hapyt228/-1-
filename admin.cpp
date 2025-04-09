#include "adminfunc.h"

void Adminmenu() {
    bool start = true;
    while (start) {
        cout << "                                            Выберите что хотите сделать" << endl;
        cout << "                                                 1 - Просмотр файла" << endl;
        cout << "                                                 2 - Удаление из файла" << endl;
        cout << "                                                 3 - Редактирование файла" << endl;
        cout << "                                                 4 - Выход" << endl;

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
            cout << "Спасибо за использование приложения!" << endl;
            start = false;
            break;
        default:
            cout << "Ошибка: выберите вариант от 1 до 4." << endl;
        }
    }
}