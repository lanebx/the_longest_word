//
//  main.cpp
//  The_longest_word
//
//  Created by Лана Темкаева on 04.01.2024.
//

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <list>


using namespace std;

class Article {
public:
  Article(const string& mot) : mot(mot), pmot(mot) {
    sort(pmot.begin(), pmot.end());
  }

  string mot;
  string pmot;
};

list<list<Article>> cteateListOfArticle(const string& filename) {
    ifstream file(filename);

    if (!file.is_open()) {
        cout << "Unable to open file: " << filename << endl;
    }
    
    list<list<Article>> wordsByLength(10);
    
    string word;
        
    while (file >> word) {
        // Определяем длину слова
        unsigned long length = word.length();

        // Проверяем, что длина не превышает 10
        if (length <= 10) {
            // Ищем нужный список
            auto it = wordsByLength.begin();
            advance(it, length - 1);

            // Добавляем слово в соответствующий список
            it->emplace_back(Article(word));
        }
    }
//
//  Проверка
//
//    for (auto itOuter = wordsByLength.begin(); itOuter != wordsByLength.end(); ++itOuter) {
//        if (!itOuter->empty()) {
//            cout << "Первый элемент: " << itOuter->front().mot << endl;
//        } else {
//            cout << "Строка пуста." << endl;
//        }
//    }
    
    return wordsByLength;
}

vector<char> generateLetters(int numDigits) {
    vector<char> letters;

    // Инициализация генератора случайных чисел
    srand(static_cast<unsigned>(time(0)));

    for (int i = 0; i < numDigits; ++i) {
        // Генерация случайной буквы в диапазоне от 'a' до 'z'
        char currentChar = 'a' + rand() % 26;
        letters.push_back(currentChar);
    }
    
    cout << "До сортування: ";
    for (char c : letters) cout << c << " ";
    cout << endl;
    
    sort(letters.begin(), letters.end());
    
    cout << "Пiсля сортування: ";
    for (char c : letters) cout << c << " ";
    cout << endl;

    return letters;
}

vector<char> createLetters() {
    vector<char> letters;

    cout << "Вводите буквы по одной используя Enter после каждой (для завершения ввода введите '0'): " << endl;
    
    int iterator = 0;
    char input;
    while (iterator < 10) {
        cin >> input;

        // Проверка на '0' для завершения ввода
        if (input == '0') {
            break;
        }

        letters.push_back(input);
        iterator++;
    }
    
    sort(letters.begin(), letters.end());
    
    cout << "Пiсля сортування: ";
    for (char c : letters) cout << c << " ";
    cout << endl;

    return letters;
}

Article findTheLongestWord(const list<list<Article>>& dicos, const vector<char>& letters) {
  // Ищем список слов заданной длины
  auto it = dicos.begin();
  advance(it, letters.size() - 1);

  // Если список пуст, то возвращаем пустое слово

  if (it == dicos.end()) {
    return Article("");
  }

  // Ищем первое слово в списке, которое соответствует перестановке букв в letters
  Article result("");
  for (const auto& word : *it) {
    if (equal(word.pmot.begin(), word.pmot.end(), letters.begin())) {
      result = word;
      break;
    }
  }

  // Если такое слово не найдено, то рекурсивно ищем его в списке слов меньшей длины
  for (size_t i = 0; i < letters.size(); ++i) {
    vector<char> newLetters(letters);
    newLetters.erase(newLetters.begin() + i);
    Article r = findTheLongestWord(dicos, newLetters);
    if (r.mot.size() > result.mot.size()) {
      result = r;
    }
  }

  // Если мы дошли до конца списка, то возвращаем пустое слово
  return result;
}



int main(int argc, char *argv[]) {
    vector<char> letters;
    bool useranswer = true;
    
//  Завантаження данних з файлу
    string filename = "francais.txt";
    list<list<Article>> dicos = cteateListOfArticle(filename);
    
    // Проверка наличия аргументов командной строки
    if (argc > 1) {
        // Преобразование первого аргумента (argv[1]) в вектор букв
        for (int i = 1; i < argc; ++i) {
            // Итерирование по символам каждого аргумента и добавление в вектор letters
            for (char *c = argv[i]; *c != '\0'; ++c) {
                letters.push_back(*c);
            }
        }
        
        if(letters.size() > 10) {
            cerr << "Ошибка: количество аргументов должно быть от 1 до 10." << endl;
            return 1; // Возвращаем код ошибки
        }
        
        cout << "Буквы из командной строки что вы ввели для поиска слова : ";
        for (char c : letters) {
            cout << c << " ";
        }
        cout << endl;
        
        sort(letters.begin(), letters.end());
        
        cout << "Пiсля сортування: ";
        for (char c : letters) cout << c << " ";
        cout << endl;
        
    //  пошук найдовшого слова зi списку Article  abaissas
        string thelongestword = findTheLongestWord(dicos, letters).mot;
        if(thelongestword == "") {
            cout << "Cамое длинное слово из заданых букв - Невозможно составить." << endl;
        } else {
            cout << "Cамое длинное слово из заданых букв : " << findTheLongestWord(dicos, letters).mot << endl;
        }
    
        cout << "Хотите продолжить игру ? (1 - да, 0 - нет.) : " ;
        cin >> useranswer;
        
    } else {
        cout << "Нет аргументов командной строки. Введите буквы самостоятельно или сгенерируйте их." << endl;
    }
    
    while (useranswer) {
        cout << "Хотите ввести буквы сами или сгенерировать компьютером? (введите '1 - ввод' или '2 - генерация'): ";
        string choice;
        cin >> choice;
        
        if (choice == "1") {
            letters = createLetters();
        } else {
            int numDigits;
            cout << "Введите количество цифр (до 10 включно): ";
            cin >> numDigits;

            if (numDigits <= 0 || numDigits >= 10) {
                cerr << "Ошибка: количество цифр должно быть от 1 до 10." << endl;
                return 1; // Возвращаем код ошибки
            }
            
            letters = generateLetters(numDigits);
        }
        
        //  пошук найдовшого слова зi списку Article  abaissas
        string thelongestword = findTheLongestWord(dicos, letters).mot;
        if(thelongestword == "") {
            cout << "Cамое длинное слово из заданых букв - Невозможно составить." << endl;
        } else {
            cout << "Cамое длинное слово из заданых букв : " << findTheLongestWord(dicos, letters).mot << endl;
        }
        
        cout << "Хотите продолжить игру ? (1 - да, 0 - нет.) : " ;
        cin >> useranswer;
    }

    return 0;
}
