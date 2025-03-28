#include "Курсач.h"

using namespace std;

const string filename = "assembly.txt";
const string selectedFilename = "selected.txt";

void saveSelection(const string& selection, bool newcreating = false) {
    ofstream file(selectedFilename, ios::app);
    if (!file) {
        cout << "Ошибка: не удалось открыть файл " << selectedFilename << endl;
        return;
    }
    if (newcreating) {
        string user = getCurrentUser();
        file << user << endl;
        return;
    }


    file << selection << endl;
    
}


void readEnter(int counter, int& StartPos) {
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
    }
    string lines[10000];
    string line;
    int count = 0;
    int choice;
    while (getline(inFile, line)) {
        if (counter >= StartPos)
        {
            if (line == "----------") {
                StartPos = counter + 1;
                break;
            }
            lines[count] = line;
            count++;
            cout << count << ") " << line << endl;
            counter++;
        }
        else {
            counter++;
        }
    }
    cout << "Выберите номер комплектующего: ";
    cin >> choice;

    while (choice < 1 || choice > count) {
        cout << "Ошибка: некорректный выбор!\n";
        cout << "Выберите комплектующие снова: ";
        cin >> choice;
    }

    string selected = lines[choice - 1];

    cout << "Вы выбрали: " << selected << endl;
    cout << endl;
    saveSelection(selected);
}




void Creating() {
    cout << "                               Добро пожаловать в выбор комплектующих" << endl;
    cout << "                                     Предлагаю начать выбор с процессоров" << endl << endl;
    cout << endl;



    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }

    int counter = 1;
    int StartPos = 0;

    saveSelection("----------", true);


    cout << "Список процессоров:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать видеокартку" << endl << endl;

    cout << "Список видеокарт:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать материнскую плату" << endl << endl;

    cout << "Список материнскую плату:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать оперативную память" << endl << endl;

    cout << "Список оперативной памяти:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать систему охлаждения" << endl << endl;

    cout << "Список систем охлаждения:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать накопитель" << endl << endl;

    cout << "Список накопителей:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать блок питания" << endl << endl;

    cout << "Список блоков питания:\n";
    readEnter(counter, StartPos);

    cout << "                                     Теперь надо выбрать корпус" << endl << endl;

    cout << "Список корпусов:\n";
    readEnter(counter, StartPos);
    saveSelection("----------");


    cout << endl;
    cout << "                                                  ВЫ СОБРАЛИ СВОЮ СБОРКУ" << endl;
    cout << "                                                  Нажмите 2 чтобы просмотреть ее" << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    inFile.close();
}

void View() {
    ifstream inFile(selectedFilename);
    string line;
    int sum = 0;
    bool sup = false;
    cout << "                                                  ВАША СБОРКА" << endl << endl;
    while (getline(inFile, line)) {
        if (sup) {
            size_t pos = line.find('$');
            cout << line << endl;
            if (pos != string::npos) {
                string number_str = line.substr(pos + 1);
                int numbers = stoi(number_str);
                sum += numbers;
            }
            if (line == "----------") {
                sup = false;
            }
        }
        if (line == getCurrentUser()) {
            sup = true;
        }            
    }
    cout << "Общая цена вашей сборки: " << sum << "$" << endl;

    inFile.close();
}

void Deletespork() {
    ifstream inFile(selectedFilename);
    ofstream tempFile("temp.txt");
    string line;
    int counter = 0;
    bool sup = false;
    while (getline(inFile, line)) {
        if (sup) {
            if (line == "----------") {
                sup = false;
                counter++;
            }
        }
        else if (counter == 0) {
            if (line == getCurrentUser()) {
            sup = true;
            }
        }
        else{
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    remove(selectedFilename.c_str());
    rename("temp.txt", selectedFilename.c_str());
}