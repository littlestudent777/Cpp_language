#include <iostream> // input and output
#include <fstream> // ifstream
#include <string> // getline
#include <sstream> // istringstream
#include <iterator>
#include <vector>

using namespace std;

//функция, проходящая по всему вектору и разделяющая слова, которые длиннее данной длины строки
void wordSplit(vector<string>& words, int length){
    for (int i = 0; i < words.size(); i++) {
        if (words[i].size() > length) {

            string long_word = words[i];
            words.erase(words.begin() + i);
            int num_short_words = static_cast<int>(long_word.length()) / length + 1;

            int taken_len, word_length, left_length;
            for (int j = 0; j < num_short_words; ++j) {
                taken_len = j * length;
                left_length = static_cast<int>(long_word.size()) - taken_len;
                //word_length это минимум из этих двух параметров
                word_length = (length <= left_length) ? length : left_length;
                //substr() получает подстроку. 1ый параметр - индекс, с которого начинается подстрока. 2ой - кол-во символов извлекаемой подстроки.
                string short_word = long_word.substr(taken_len, word_length);
                words.insert(words.begin() + i + j, short_word);
            }
            //пропускаем короткие слова, которые только что вставили
            i += num_short_words - 1;
        }
    }
}

//распределение пробелов для центрирования строки
void alignLine(int length, int current_length, string& final_line, string& current_line) {
    //вычисление количества пробелов для выравнивания слова по центру
    int spaces_to_add = (length - current_length) / 2;
    final_line += string(spaces_to_add, ' ') + current_line + "\n";
}

//основная функция центрирования текста
void alignText(string& line, int length) {
    //чтобы работать со строкой как с потоком
    //для разбиения входной строки на слова
    istringstream iss(line);
    //cоздание вектора строк, содержащего слова из входной строки.
    vector<string> words(istream_iterator<string>{iss}, istream_iterator<string>());
    
    wordSplit(words, length);

    string current_line;
    //строка, которая будет содержать выровненный текст
    string final_line;
    int current_length = 0;

    for (const auto& word : words) {
        if (current_length + word.size() + 1 > length) { //+1 для пробела между имеющимся и новым словом
            //вычисление количества пробелов для выравнивания слова по центру
            alignLine(length, current_length, final_line, current_line);
            current_length = 0;
            current_line.clear();
        }

        if (current_length == 0) {
            current_line += word;
            current_length += static_cast<int>(word.size());
        }
        else {
            current_line += " " + word;
            current_length += static_cast<int>(word.size()) + 1;
        }
    }
    alignLine(length, current_length, final_line, current_line);
    cout << final_line;
}

int askLength();
string askFileName();

int main() {
    int length = askLength();
    string file_name = askFileName();

    ifstream file(file_name);
    string line;
    if (file.is_open()) {
        //The getline() function returns true as long as there are lines left to be read in the file.
        while (getline(file, line)) {
            alignText(line, length);
        }
    }

    file.close();
    return 0;
}

int askLength() {
    cout << "Length of lines: ";
    int length;
    cin >> length;
    cin.ignore(); //to ignore \n
    return length;
}

string askFileName() {
    cout << "Write a file name" << endl;
    string file_name;
    cin >> file_name;
    cout << "\n";
    return file_name;
}