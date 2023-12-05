#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

/**
check if the start of the string is a number.
if yes, append string. move counter.
account for overlapping letters
*/

unordered_map<string,string> digit_map = {
    {"one", "1"},
    {"two", "2"},
    {"three", "3"},
    {"four", "4"},
    {"five", "5"},
    {"six", "6"},
    {"seven", "7"},
    {"eight", "8"},
    {"nine", "9"}
};

string convert_line(string line) {
    string res;
    for (int i = 0; i < line.length(); i++) {
        bool found_match = false;
        for (auto &kv : digit_map) {
            bool is_match = true;
            for (int j = 0; j < kv.first.length(); j++) {
                if ((i+j >= line.length()) || (line[i+j] != kv.first[j])) {
                    is_match = false;
                    break;
                }
            }
            if (is_match) {
                res.append(kv.second);
                // hack here: instead of completely skipping the letter
                // start at the second last letter to account for overlapping/shared letters.
                i += kv.first.length() - 2;
                found_match = true;
                break;
            }
        }
        if (!found_match) {
            res += line[i];
        }
    }
    return res;
}

int main()
{
    string line;
    double sum;
    
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        while ( getline (test_case,line) ){
            string converted_line = convert_line(line);
            string num;
            for (int i = 0; i < converted_line.length(); i++) {
                if (isdigit(converted_line[i])) {
                    num += converted_line[i];
                    break;
                }
            }
            for (int i = converted_line.length() - 1; i >= 0; i--) {
                if (isdigit(converted_line[i])) {
                    num += converted_line[i];
                    break;
                }
            }
            sum += stod(num);
        }
    }
    cout << "sum: "<< sum << '\n';
    return 0;
}
