//#include "������.h"
//
//void Sort() {
//    ifstream filename("assembly.txt");
//    if (!filename) {
//        cerr << "������: �� ������� ������� ����!" << endl;
//        return;
//    }
//
//    const int MAX_LINES = 100;
//    string lines[MAX_LINES];
//    int indexes[MAX_LINES];
//    int count = 0;
//    int firstIndex = -1;  // ������ ������ ������
//
//    while (getline(filename, lines[count]) && count < MAX_LINES) {
//        if (lines[count] == "----------") break;  // ��������������� �� ������ �����
//
//        size_t pos = lines[count].rfind('#');
//        if (pos != string::npos) {
//            indexes[count] = stoi(lines[count].substr(pos + 1));  // ��������� ������
//
//            if (firstIndex == -1) {
//                firstIndex = indexes[count];  // ���������� ������ ������ ������
//            }
//
//            count++;
//        }
//    }
//    filename.close();
//
//    // ���������� ��������� �� �������
//    for (int i = 0; i < count - 1; i++) {
//        for (int j = 0; j < count - i - 1; j++) {
//            if (indexes[j] > indexes[j + 1]) {
//                swap(indexes[j], indexes[j + 1]);
//                swap(lines[j], lines[j + 1]);
//            }
//        }
//    }
//
//    // ����� ������ ����� � ����� �� ��������, ��� � ������ ������
//    for (int i = 0; i < count; i++) {
//        if (indexes[i] == firstIndex) {
//            cout << lines[i] << endl;
//        }
//    }
//}