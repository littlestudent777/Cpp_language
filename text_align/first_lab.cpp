#include <iostream> // input and output
#include <fstream> // ifstream
#include <string> // getline
#include <sstream> // istringstream
#include <iterator>
#include <vector>

using namespace std;

//�������, ���������� �� ����� ������� � ����������� �����, ������� ������� ������ ����� ������
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
                //word_length ��� ������� �� ���� ���� ����������
                word_length = (length <= left_length) ? length : left_length;
                //substr() �������� ���������. 1�� �������� - ������, � �������� ���������� ���������. 2�� - ���-�� �������� ����������� ���������.
                string short_word = long_word.substr(taken_len, word_length);
                words.insert(words.begin() + i + j, short_word);
            }
            //���������� �������� �����, ������� ������ ��� ��������
            i += num_short_words - 1;
        }
    }
}

//������������� �������� ��� ������������� ������
void alignLine(int length, int current_length, string& final_line, string& current_line) {
    //���������� ���������� �������� ��� ������������ ����� �� ������
    int spaces_to_add = (length - current_length) / 2;
    final_line += string(spaces_to_add, ' ') + current_line + "\n";
}

//�������� ������� ������������� ������
void alignText(string& line, int length) {
    //����� �������� �� ������� ��� � �������
    //��� ��������� ������� ������ �� �����
    istringstream iss(line);
    //c������� ������� �����, ����������� ����� �� ������� ������.
    vector<string> words(istream_iterator<string>{iss}, istream_iterator<string>());
    
    wordSplit(words, length);

    string current_line;
    //������, ������� ����� ��������� ����������� �����
    string final_line;
    int current_length = 0;

    for (const auto& word : words) {
        if (current_length + word.size() + 1 > length) { //+1 ��� ������� ����� ��������� � ����� ������
            //���������� ���������� �������� ��� ������������ ����� �� ������
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