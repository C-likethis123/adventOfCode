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
        vector<vector<int>> sequences(2);
        while (getline(test_case, line)) {
            // TODO: figure out a more elegantway to do this
            vector<int> split_int;
            split(line, split_int, " ");
            for (int i = 0; i < 2; i++){
                sequences[i].emplace_back(split_int[i]);
            }
        }

        // sort lists
        for (int i = 0; i < 2; i++){
            std::sort(sequences[i].begin(), sequences[i].end());
        }

        // get distance
        size_t list_length = sequences[0].size();
        for (size_t i = 0; i < list_length; i++) {
            ans += std::abs(sequences[0][i] - sequences[1][i]);
        }
        cout << fixed << ans << endl;
    }
    return 0;
}
