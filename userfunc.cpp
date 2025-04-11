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
        cout << "������: �� ������� ������� ���� " << selectedFilename << endl;
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
        cout << "�������� ������ ���������.\n";
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
        cout << "������ " << categoryNames[categoryIndex] << ":\n";
        for (int i = 0; i < indexCounter; ++i) {
            int index = matchingIndices[i];
            cout << i + 1 << ") " << products[index].name
                << " � $" << products[index].price << "\n";
        }
    }
    else if(fork){
        SortOutput();
    }
    else {
        SortPrice(categoryIndex, sortByPrice);
        SortOutputPrice();
    }

    cout << "\n������� ����� ��� ������: ";
    int choice;
    cin >> choice;

    int maxChoice = fork ? queueMy.size() : indexCounter;
    if (choice < 1 || choice > maxChoice) {
        cout << "�������� �����. ���������� �����.\n";
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

    cout << "�� �������: " << selectedProduct.name << "\n\n";
    string sup = selectedProduct.name + " � $" + to_string(selectedProduct.price);
    int filterID = selectedProduct.id;
    if (categoryIndex == 0) {
        cout << "������ ����� ������ ���������������� �������������? (1-��, 2-���): ";
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
    cout << "                               ����� ���������� � ����� �������������" << endl;
    cout << "                               ������ ��� ����������� �� ����? (1-��, 2-���): ";
    int choiceSecondSort;
    cin >> choiceSecondSort;
    sortByPrice = (choiceSecondSort == 1);
    cout << "                                     ��������� ������ ����� � �����������" << endl << endl;
    cout << endl;
    ifstream inFile(filename);
    if (!inFile) {
        cout << "������: �� ������� ������� ���� " << filename << endl;
        return;
    }
    saveSelection("----------", true);

    readProductsFromFile(filename);
    bool fork=false;
    

    for (int i = 0; i < 8; ++i) {
        cout << "������ ���� ������� " << categoryNames[i] << "\n\n";
        displayAndSelectProduct(i, fork);
    }

    saveSelection("----------");
    clearProducts();

    cout << endl;
    cout << "                                                  �� ������� ���� ������" << endl;
    cout << "                                                  ������� 2 ����� ����������� ��" << endl;
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
    cout << "                                                  ���� ������" << endl << endl;
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
    cout << "����� ���� ����� ������: " << sum << "$" << endl;

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
    cout << "������ �������" << endl;

    remove(selectedFilename.c_str());
    rename("temp.txt", selectedFilename.c_str());
}