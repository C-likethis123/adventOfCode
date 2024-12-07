#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>
#include <climits>
#include <bitset>

using namespace std;

void split(string s, std::vector<int>& v, string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) {
           v.push_back(std::stoi(token)); 
        }
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(std::stoi(s));
}

int main()
{
    long ans = 0;
    string line;
    ifstream test_case("input.txt");
    // ofstream debug("output.txt");
    
    if (test_case.is_open()) {
        // parse into two lists
        while (getline(test_case, line)) {
            // TODO: figure out a more elegantway to do this
            vector<int> sequence;
            split(line, sequence, " ");
            // continue because it's not a safe report
            if (sequence[0] == sequence[1]) {
                continue;
            }
            bool is_safe_report = true;
            bool first_polarity = sequence[0] < sequence[1];
            for (size_t i = 0; i < sequence.size() - 1; i++) {
                bool polarity = sequence[i] < sequence[i+1];
                if (polarity != first_polarity) {
                    is_safe_report = false;
                    break;
                }
                int difference = std::abs(sequence[i] - sequence[i+1]);
                if (difference < 1 || difference > 3) {
                    is_safe_report = false;
                    break;
                }
            }
            ans += is_safe_report;
        }
        cout << fixed << ans << endl;
    }
    return 0;
}
