#include <iostream>
#include <windows.h>
#include <fstream>
using namespace std;


unsigned my_str_len(char* S)
{
    unsigned L = 0;
    while (S[L])
        ++L;
    return L;
}
void keyboard_input(char* text, int N) {
    cin.getline(text, N, '.');
    int len_of_sequence = my_str_len(text);
    for (int j = 0; j < len_of_sequence; j++) {
        text[j] = text[j + 1];
    }
    --len_of_sequence;
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

void delete_space(char* text, int N) {
    for (int i = 0; i < N; ++i) {
        if (text[i] == ' ' and text[i + 1] == ' ') {
            while (text[i + 1] == ' ') {
                for (int j = i + 1; j < N; j++) {
                    text[j] = text[j + 1];
                }
                --N;
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
            else {
                while (ispunct(text[i + 1])) {
                    for (int j = i + 1; j < N; j++) {
                        text[j] = text[j + 1];
                    }
                    --N;
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
void how_many_symbols_in_word(char* text, int N) {
    int counter = 0;
    for (int i = 0; i < N; i++) {
        if (text[i] != ' ' && text[i] != '\0') {
            cout << text[i];
            counter += 1;
        }
        else {
            cout << " - " << counter << endl;
            counter = 0;
        }
    }
}
int linear_search(char* text, char pattern[], int N) {
    int pattern_len = my_str_len(pattern);
    for (int i = 0; i <= N - pattern_len; ++i) {
        int j;
        for (j = 0; j <= pattern_len; ++j) {
            if (text[i + j] != pattern[j]) {
                break;
            }
        }
        if (j == pattern_len) {
            return i;
        }
    }
    return -1;
}
void prepare_table(const char* pattern, int pattern_len, int table[256]) {
    for (int i = 0; i < 256; i++) {
        table[i] = pattern_len;
    }
    for (int i = 0; i < pattern_len - 1; i++) {
        table[(unsigned char)pattern[i]] = pattern_len - i - 1;
    }
}
int Boyer_Moore_algorithm(char* text, char pattern[], int N, int* table) {
    int pattern_len = my_str_len(pattern);
    int text_len = my_str_len(text);
    prepare_table(pattern, pattern_len, table);
    int j, k;

    int i = pattern_len - 1;
    while (i < text_len) {
        int j = pattern_len - 1;
        int k = i;

        while (j >= 0 && k >= 0 && text[k] == pattern[j]) {
            k--;
            j--;
        }

        if (j < 0) {
            return k + 1;
        }
        i += table[(unsigned char)text[i]];
    }

    return -1;
}
int organize_words(char* text, char words[][10]) {
    int i = 0, word_len = 0, count = 0;
    while (text[i] != '\0' && count < 50) {
        if (text[i] == ' ' || text[i + 1] == '\0') {
            if (word_len > 0) {
                words[count][word_len] = '\0';
                count++;
                word_len = 0;
            }
        }
        else {
            words[count][word_len] = text[i];
            word_len++;
        }
        i++;
    }
    return count;
}
void swap_words(char words[][10], int j) {
    char temp[10];
    int k = 0;
    while (words[j][k] != '\0' && k < 10) {
        temp[k] = words[j][k];
        k++;
    }
    temp[k] = '\0';
    k = 0;
    while (words[j - 1][k] != '\0' && k < 10) {
        words[j][k] = words[j - 1][k];
        k++;
    }
    words[j][k] = '\0';
    k = 0;
    while (temp[k] != '\0' && k < 10) {
        words[j - 1][k] = temp[k];
        k++;
    }
    words[j - 1][k] = '\0';
}
void sort_alphabetically(char words[][10], int count) {
    int c = 0;
    for (int i = 0; i < count - 1; i++) {
        for (int j = count - 1; j > i; j--) {
            if (words[j][0] < words[j - 1][0]) {
                swap_words(words, j);
            }
            else if (words[j][0] == words[j - 1][0]) {
                while (words[j][c] == words[j - 1][c]) {
                    c++;
                }
                if (words[j][c] < words[j - 1][c]) {
                    swap_words(words, j);
                }

            }
        }
    }
}
void display_menu() {
    cout << "Выберите действие:" << endl;
    cout << "1. Выберите откуда брать последовательность." << endl;
    cout << "2. Необходимо отредактировать входной текст." << endl;
    cout << "3. Вывести на экран слова последовательности в алфавитном порядке." << endl;
    cout << "4. Вывести на экран количество символов в каждом слове исходной последовательности." << endl;
    cout << "5. Необходимо найти все подстроки, которую введёт пользователь в имеющейся строке." << endl;
    cout << "6. Алгоритм Бойера-Мура" << endl;
}

int main()
{
    setlocale(LC_ALL, "");
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    int identificator, num1, num2, n, len_of_sequence, result, count, index;
    const int N = 600;
    char sequence[N] = { ' ' }, pattern[30], pattern1[30], words[50][10];
    int table[256];
    while (true) {
        display_menu();
        cout << "ВВЕДИТЕ НОМЕР ЗАДАНИЯ: ";
        cin >> identificator;
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
                sequence[my_str_len(sequence)] = ' ';
                sequence[my_str_len(sequence) + 1] = '\0';
                break;
            case 2:
                const char* filePath = "C:/laba4/ladna.txt";
                ifstream file(filePath, ios::in);
                if (!file.is_open()) {
                    cout << "Файл не открывается!!!!! \n";
                    return -1;
                }
                file.read((char*)sequence, sizeof(sequence));
                file.close();
                break;
            }
            cout << my_str_len(sequence) << endl;
            print_result(sequence, my_str_len(sequence));
            break;
        case 2:
            cout << "Измененный текст, очищенный от пробелов, знаков препинания и неправильного регистра" << endl;
            delete_space(sequence, my_str_len(sequence));
            delete_punctuation(sequence, my_str_len(sequence));
            make_lower(sequence, my_str_len(sequence));
            cout << my_str_len(sequence) << endl;
            print_result(sequence, my_str_len(sequence));
            break;
        case 3:
            cout << "Отсортированные по алфавиту слова:" << endl;
            count = organize_words(sequence, words);
            sort_alphabetically(words, count);
            for (int i = 0; i < count; i++) {
                cout << words[i] << " ";
            }
            break;
        case 4:
            cout << "Вывести на экран количество символов в каждом слове исходной последовательности." << endl;
            how_many_symbols_in_word(sequence, my_str_len(sequence));
            break;
        case 5:
            system("cls");
            cout << "Введите слово для линейного поиска" << endl;
            cin.clear();
            cin.sync();
            keyboard_input(pattern, my_str_len(pattern));
            result = linear_search(sequence, pattern, my_str_len(sequence));
            if (result == -1) {
                cout << "Нет таких слов в последовательности" << endl;
            }
            else {
                cout << "Есть такая подстрока,начиная с индекса " << result << endl;
            }
            break;
        case 6:
            system("cls");
            cout << "Введите слово для поиска" << endl;
            cin.clear();
            cin.sync();
            keyboard_input(pattern1, my_str_len(pattern1));
            index = Boyer_Moore_algorithm(sequence, pattern1, my_str_len(sequence), table);
            if (index != -1) {
                cout << "Первое вхождение найдено на индексе: " << index << endl;
            }
            else {
                cout << "Шаблон не найден." << endl;
            }
            break;
        case 7:
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