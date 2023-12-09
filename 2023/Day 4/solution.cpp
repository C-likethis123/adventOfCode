#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>

using namespace std;

/*
idea:
- parse the output into two sets: winning numbers and cards i have
- find intersection of sets

*/

void split(string s, std::vector<std::string>& v, string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) {
           v.push_back(token); 
        }
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(s);
}

unordered_set<int> get_winning_numbers(std::string &numbers) {
    unordered_set<int> res;
    vector<string> v;
    split(numbers, v, " ");
    for (string& num : v) {
        res.insert(stoi(num));
    }
    return res;
}

int calculate_points(unordered_set<int>& winning_numbers, string& numbers) {
    vector<string> v;
    split(numbers, v, " ");
    int ans = 0;
    for (string& num : v) {
        if (winning_numbers.find(stoi(num)) != winning_numbers.end()) {
            if (ans == 0) {
                ans = 1;
            } else {
                ans *= 2;
            }
        }
    }
    return ans;
}

int main()
{
    string line;
    double ans = 0;
    
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        while (getline(test_case,line)) {
            vector<string> v;
            split(line, v, ": ");
            std::string temp = v[1];
            v.clear();
            split(temp, v, " | ");

            std::unordered_set<int> winning_numbers = get_winning_numbers(v[0]);
            int points = calculate_points(winning_numbers, v[1]);
            ans += points;
        }
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
