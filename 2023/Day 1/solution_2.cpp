#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>

using namespace std;

/**
check if the start of the string is a number.
if yes, append string. move counter.

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

string find_first_digit(string line) {
    string res;
    for (int i = 0; i < line.length(); i++) {
        for (auto &kv : digit_map) {
            bool is_match = true;
            for (int j = 0; j < kv.first.length(); j++) {
                if ((i+j >= line.length()) || (line[i+j] != kv.first[j])) {
                    is_match = false;
                    break;
                }
            }
            if (is_match) {
                return kv.second;
            }
        }
        if (isdigit(line[i])) {
            res = line[i];
            return res;
        }
    }
    return res;
}

// TODO: figure out how to find the first digit from the back.
string find_last_digit(string line) {
    string res;
    for (int i = line.length() - 1; i >= 0; i--) {
        for (auto &kv : digit_map) {
            bool is_match = true;
            for (int j = kv.first.length() - 1; j >= 0; j++) {
                if (line[i+j] != kv.first[j]) {
                    is_match = false;
                    break;
                }
            }
            if (is_match) {
                return kv.second;
            }
        }
        if (isdigit(line[i])) {
            res = line[i];
            return res;
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
            string num;
            num += find_first_digit(line);
            num += find_last_digit(line);
            sum += stod(num);
        }
    }
    cout << "sum: "<< sum << '\n';
    return 0;
}
