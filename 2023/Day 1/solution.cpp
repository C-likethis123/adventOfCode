#include <iostream>
#include <fstream>
#include <string>

using namespace std;

/**
check if the start of the string is a number.
if yes, append string. move counter.

*/
string convert_line(string &line) {
    string res;
    for (int i = 0; i < line.length(); i++) {
        if (isdigit(line[i])) {
            num.append(line[i]);
        } else {
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
                    num.append(kv.second);
                    i += j;
                    found_match = true;
                    break;
                }
            }
        }
    }
}

int main()
{
    string line;
    double sum;
    
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        while ( getline (test_case,line) ){
            std::string converted_line = convert_line(line);
            string num;
            for (int i = 0; i < converted_line.length(); i++) {
                if (isdigit(converted_line[i])) {
                    num.append(converted_line[i]);
                    break;
                }
            }
            for (int i = converted_line.length() - 1; i >= 0; i--) {
                if (isdigit(converted_line[i])) {
                    num.append(converted_line[i]);
                    break;
                }
            }
            sum += stod(num);
        }
    }
    cout << sum << '\n';
    return 0;
}
