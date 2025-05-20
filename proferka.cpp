#include <iostream>
#include <string>
#include <sstream>
#include "userfunc.h"
#include "consolecleaning.h"
#include "proferka.h"

using namespace std;


int getValidatedIntFromInput(int& value) {
    string input;

    while (true) {
        getline(cin, input); 
        stringstream ss(input);   
        
        if (ss >> value && ss.eof()) { 
            return value;
        }
        else {
            cout << "������: ������� ���������� ����� �����: ";

        }
    }
}
