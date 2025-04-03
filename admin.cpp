#include "adminfunc.h"

void Adminmenu() {
    bool start = true;
    while (start) {
        cout << "                                            Выберите что хотите сделать" << endl;
        cout << "                                                 1 - Просмотр файла" << endl;
        cout << "                                                 2 - Удаление из файла" << endl;
        cout << "                                                 3 - Редактирование сборки пользователя" << endl;
        cout << "                                                 4 - Редактирование файла" << endl;
        cout << "                                                 6 - Выход" << endl;

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
            cout << "Спасибо за использование приложения!" << endl;
            start = false;
            break;
        default:
            cout << "Ошибка: выберите вариант от 1 до 3." << endl;
        }
    }
}