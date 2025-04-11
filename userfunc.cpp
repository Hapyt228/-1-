#include "auth.h"
#include "structure.h"
#include "sorting.h"
#include "consolecleaning.h"

const string filename = "assembly.txt";
const string selectedFilename = "selected.txt";
bool sortByPrice = false;

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


void displayAndSelectProduct(int categoryIndex, bool& fork) {
    if (categoryIndex < 0 || categoryIndex >= 8) {
        cout << "Неверный индекс категории.\n";
        return;
    }

    int matchingIndices[MAX_PRODUCTS];
    int indexCounter = 0;
    for (int i = 0; i < productCount; ++i) {
        if (products[i].category == categoryNames[categoryIndex]) {
            matchingIndices[indexCounter++] = i;
        }
    }


    if (!fork && !sortByPrice) {
        cout << "Список " << categoryNames[categoryIndex] << ":\n";
        for (int i = 0; i < indexCounter; ++i) {
            int index = matchingIndices[i];
            cout << i + 1 << ") " << products[index].name
                << " — $" << products[index].price << "\n";
        }
    }
    else if(fork){
        SortOutput();
    }
    else {
        SortPrice(categoryIndex, sortByPrice);
        SortOutputPrice();
    }

    cout << "\nВведите номер для выбора: ";
    int choice;
    cin >> choice;

    int maxChoice = fork ? queueMy.size() : indexCounter;
    if (choice < 1 || choice > maxChoice) {
        cout << "Неверный номер. Попробуйте снова.\n";
        return;
    }

    Product selectedProduct;

    if (fork) {
        queue <Product> tempQueue = queueMy;
        for (int i = 1; i < choice; ++i) tempQueue.pop();
        selectedProduct = tempQueue.front();
    }
    else {
        selectedProduct = products[matchingIndices[choice - 1]];
    }

    cout << "Вы выбрали: " << selectedProduct.name << "\n\n";
    string sup = selectedProduct.name + " — $" + to_string(selectedProduct.price);
    int filterID = selectedProduct.id;
    if (categoryIndex == 0) {
        cout << "Хотите вывод только совместимостимых комплектующих? (1-да, 2-нет): ";
        int choiceFirstSort;
        cin >> choiceFirstSort;
        if (choiceFirstSort == 1) {
            int filterID = selectedProduct.id;
            Sort(categoryIndex, sortByPrice, filterID); 
            fork = true;
        }
    }
    if (fork && categoryIndex > 0) {
            Sort(categoryIndex, sortByPrice, filterID);
        }

    saveSelection(sup);
    system("cls");
}


void Creating() {
    system("cls");
    cout << "                               Добро пожаловать в выбор комплектующих" << endl;
    cout << "                               Хотите еще сортировать по цене? (1-да, 2-нет): ";
    int choiceSecondSort;
    cin >> choiceSecondSort;
    sortByPrice = (choiceSecondSort == 1);
    cout << "                                     Предлагаю начать выбор с процессоров" << endl << endl;
    cout << endl;
    ifstream inFile(filename);
    if (!inFile) {
        cout << "Ошибка: не удалось открыть файл " << filename << endl;
        return;
    }
    saveSelection("----------", true);

    readProductsFromFile(filename);
    bool fork=false;
    

    for (int i = 0; i < 8; ++i) {
        cout << "Теперь надо выбрать " << categoryNames[i] << "\n\n";
        displayAndSelectProduct(i, fork);
    }

    saveSelection("----------");
    clearProducts();

    cout << endl;
    cout << "                                                  ВЫ СОБРАЛИ СВОЮ СБОРКУ" << endl;
    cout << "                                                  Нажмите 2 чтобы просмотреть ее" << endl;
    cout << endl;
    cout << endl;
    cout << endl;

    inFile.close();
}

void View() {
    system("cls");
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
    system("cls");
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
    cout << "Сборка удалена" << endl;

    remove(selectedFilename.c_str());
    rename("temp.txt", selectedFilename.c_str());
}