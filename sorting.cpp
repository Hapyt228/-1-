//#include "Курсач.h"
//
//void Sort() {
//    ifstream filename("assembly.txt");
//    if (!filename) {
//        cerr << "Ошибка: Не удалось открыть файл!" << endl;
//        return;
//    }
//
//    const int MAX_LINES = 100;
//    string lines[MAX_LINES];
//    int indexes[MAX_LINES];
//    int count = 0;
//    int firstIndex = -1;  // Индекс первой строки
//
//    while (getline(filename, lines[count]) && count < MAX_LINES) {
//        if (lines[count] == "----------") break;  // Останавливаемся на первой черте
//
//        size_t pos = lines[count].rfind('#');
//        if (pos != string::npos) {
//            indexes[count] = stoi(lines[count].substr(pos + 1));  // Извлекаем индекс
//
//            if (firstIndex == -1) {
//                firstIndex = indexes[count];  // Запоминаем индекс первой строки
//            }
//
//            count++;
//        }
//    }
//    filename.close();
//
//    // Сортировка пузырьком по индексу
//    for (int i = 0; i < count - 1; i++) {
//        for (int j = 0; j < count - i - 1; j++) {
//            if (indexes[j] > indexes[j + 1]) {
//                swap(indexes[j], indexes[j + 1]);
//                swap(lines[j], lines[j + 1]);
//            }
//        }
//    }
//
//    // Вывод только строк с таким же индексом, как у первой строки
//    for (int i = 0; i < count; i++) {
//        if (indexes[i] == firstIndex) {
//            cout << lines[i] << endl;
//        }
//    }
//}