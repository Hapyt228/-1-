#include "userfunc.h"
#include "consolecleaning.h"

void Usermenu() {
    bool start = true;

    cout << "                           Добро пожаловать в приложение для создание своей сборки ПК" << endl;
    cout << endl;

    while (start) {
        cout << "                                            Выберите что хотите сделать" << endl;
        cout << "                                                 1 - Создание сборки" << endl;
        cout << "                                                 2 - Просмотр сборки" << endl;
        cout << "                                                 3 - Удаление сборки" << endl;
        cout << "                                                 4 - Выход" << endl;

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
            cout << "Спасибо за использование приложения!" << endl;
            start = false;
            break;
        default:
            cout << "Ошибка: выберите вариант от 1 до 4." << endl;
        }
        if (start) {
            Cleaning();
        }
    }
}