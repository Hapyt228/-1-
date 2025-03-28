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
        cout << "������: �� ������� ������� ���� " << filename << endl;
        return;
    }
    string line;
    int counter = 1;
    int count = 0;
    cout << "������ ����������:\n";
    while (getline(inFile, line)) {
        if (line == "") {
            switch (counter)
            {
            case 1:
                cout << "\n������ ���������:\n";
                break;
            case 2:
                cout << "\n������ ����������� �����:\n";
                break;
            case 3:
                cout << "\n������ ����������� ������:\n";
                break;
            case 4:
                cout << "\n������ ������ ����������:\n";
                break;
            case 5:
                cout << "\n������ �����������:\n";
                break;
            case 6:
                cout << "\n������ ������ �������:\n";
                break;
            case 7:
                cout << "\n������ ��������:\n";
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