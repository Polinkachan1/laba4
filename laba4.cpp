#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;
void keyboard_input(char* text, int N) {
    cin.getline(text, N, '.');
    cin.sync();
}
void input_from_file(char* text) {
    ifstream File;
    File.open("text.txt");
    if (!File.is_open()) {
        cout << "" << endl;
    }
    File.read((char*)text, sizeof(text));
    File.close();
}
void print_result(char* text, int N) {
    for (int i = 0; i < N; ++i)
        cout << text[i];
    cout << endl;
}
unsigned my_str_len(char* S)
{
    unsigned L = 0;
    while (S[L])
        ++L;
    return L;
}
void delete_space(char* text, int N) {
    for (int i = 0; i < N; ++i) {
        if (text[i] == ' ' and text[i + 1] == ' ') {
            while (text[i+1] == ' '){
                for (int j = i + 1; j < N; j++) {
                    text[j] = text[j + 1];
                }
                text[N - 1] = '\0';;
            }

        }
    }
}
void delete_punctuation(char* text, int N) {
    for (int i = 0; i < N; ++i) {
        if (ispunct(text[i]) and ispunct(text[i + 1])) {
            if (text[i] == '.' and text[i + 1] == '.' and text[i + 2] == '.' and not ispunct(text[i + 3])) {
                i += 3;
            }
            else{
                while (ispunct(text[i + 1])) {
                    for (int j = i + 1; j < N; j++) {
                        text[j] = text[j + 1];
                    }
                    text[N-1] = '\0';
                }
            }
        }
    }

}
void make_lower(char* text, int N) {
    for (int i = 0; i < N; ++i) {
        if (i == 0) {
            text[i] = toupper(text[i]);
        }
        else if (text[i - 1] == ' ' and isalpha(text[i])) {
            text[i] = toupper(text[i]);
        }
        else {
            text[i] = tolower(text[i]);
        }
    }
}
void correctLetterCase(char* text) {
    for (int i = 0; i < my_str_len(text); i++) {
        if (isalpha(text[i]) && (i == 0 || text[i - 1] == ' ')) {
            text[i] = toupper(text[i]);
        }
        else {
            text[i] = tolower(text[i]);
        }
    }
}
void display_menu() {
    cout << "Выберите действие:" << endl;
    cout << "1. Выберите откуда брать последовательность." << endl;
    cout << "2. Необходимо отредактировать входной текст." << endl;
    cout << "3. Вывести на экран слова последовательности в алфавитном порядке." << endl;
    cout << "4. Вывести на экран ту же последовательность, заменив во всех словах первую букву соответствующей прописной буквой." << endl;
    cout << "5. Необходимо найти все подстроки, которую введёт пользователь в имеющейся строке." << endl;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int identificator, num1, num2, n, len_of_sequence;
    const int N = 600;
    char sequence[N];
    while (true) {
        display_menu();
        cout << "ВВЕДИТЕ НОМЕР ЗАДАНИЯ: ";
        cin >> identificator;
        system("cls");
        switch (identificator) {
        case 1:
            cout << "Выберите ввод:" << endl;
            cout << "1. С клавиатуры." << endl;
            cout << "2. Из файла." << endl;
            cin >> num1;
            cout << endl;
            switch (num1) {
            case 1:
                keyboard_input(sequence, N);
                break;
            case 2:
                input_from_file(sequence);
                break;
            }
            len_of_sequence = my_str_len(sequence);
            cout << len_of_sequence << endl;
            print_result(sequence, len_of_sequence);
            break;
        case 2:
            delete_space(sequence, len_of_sequence);
            //delete_punctuation(sequence, len_of_sequence);
            //len_of_sequence = my_str_len(sequence);
            //make_lower(sequence, len_of_sequence);
            correctLetterCase(sequence);
            len_of_sequence = my_str_len(sequence);
            cout << len_of_sequence << endl;
            print_result(sequence, len_of_sequence);
            break;
        case 3:
            break;
        case 4:
            break;
        case 6:
            cout << "Выход!" << endl;
            return 0;

        default:
            cout << "Некорректный номер задания." << endl;
            break;
        }
        cout << "Задание выполнено. Нажмите Enter, чтобы продолжить." << endl;
        cin.ignore();
        cin.get();
    }
    return 0;
}
