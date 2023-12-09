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
            ans += 1;
        }
    }
    return ans;
}

int main()
{
    string line;
    double ans = 0;
    int cards[208];
    for (int i = 0; i < 208; i++) {
        cards[i] = 1;
    }
    
    ifstream test_case("input.txt");
    int card_num = 0;
    if (test_case.is_open()) {
        while (getline(test_case,line)) {
            vector<string> v;
            split(line, v, ": ");
            std::string temp = v[1];
            v.clear();
            split(temp, v, " | ");

            std::unordered_set<int> winning_numbers = get_winning_numbers(v[0]);
            int points = calculate_points(winning_numbers, v[1]);
            for (int i = 1; i <= points; i++) {
                if (card_num + i < 208){
                    cards[card_num + i] += cards[card_num];
                }
            }
            card_num += 1;
        }
    }
    for (int x : cards) {
        ans += x;
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
