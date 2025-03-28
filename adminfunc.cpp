#include <iostream>
#include <fstream>
#include <string>
#include <list>

using namespace std;

const string filename = "assembly.txt";
const string selectedFilename = "selected.txt";

void AdminView() {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    string line;
    int counter = 1;
    int count = 0;
    cout << "Список процесоров:\n";
    while (getline(inFile, line)) {
        if (line == "") {
            switch (counter)
            {
            case 1:
                cout << "\nСписок видеокарт:\n";
                break;
            case 2:
                cout << "\nСписок материнскую плату:\n";
                break;
            case 3:
                cout << "\nСписок оперативной памяти:\n";
                break;
            case 4:
                cout << "\nСписок систем охлаждения:\n";
                break;
            case 5:
                cout << "\nСписок накопителей:\n";
                break;
            case 6:
                cout << "\nСписок блоков питания:\n";
                break;
            case 7:
                cout << "\nСписок корпусов:\n";
                break;
            default:
                break;
            }
            counter++;
            continue;
        }
        count++;
        cout << count << ") " << line << endl;
        if (count == 10) {
            count = 0;
        }
    }

    inFile.close();
}

void Delete() {
  
}