#include "structure.h"
#include "consolecleaning.h"

const char* categoryNames[] = {
       "����������", "����������", "����������� �����", "����������� ������",
       "����������", "����������", "����� �������", "�������"
};
Product products[MAX_PRODUCTS];
int productCount=0;
queue <Product> queueMy;


void readProductsFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "�� ������� ������� ����: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (productCount >= MAX_PRODUCTS) break;

        stringstream ss(line);
        string category, name, priceStr, idStr;

        if (getline(ss, category, ';') &&
            getline(ss, name, ';') &&
            getline(ss, priceStr, ';') &&
            getline(ss, idStr)) {

            if (!priceStr.empty() && priceStr[0] == '$') {
                priceStr = priceStr.substr(1);
            }

            Product p;
            p.category = category;
            p.name = name;
            p.price = stoi(priceStr);
            p.id = stoi(idStr);

            products[productCount++] = p;
            queueMy.push(p);
        }
    }

    file.close();
}

void clearProducts() {
    for (int i = 0; i < productCount; i++) {
        products[i].category.clear();
        products[i].name.clear();
        products[i].price = 0;
        products[i].id = 0;
    }
    productCount = 0;

    while (!queueMy.empty()) {
        queueMy.pop();
    }
}

void saveQueueToFile() {
    ofstream outFile("assembly.txt");
    if (!outFile.is_open()) {
        cerr << "������ ��� �������� ����� ��� ������!" << endl;
        return;    system("cls");
    }

    queue<Product> temp = queueMy;

    while (!temp.empty()) {
        Product p = temp.front();
        temp.pop();
        outFile <<  p.category << ";" << p.name << ";" << p.price << ";" << p.id << "\n";
    }

    outFile.close();
}