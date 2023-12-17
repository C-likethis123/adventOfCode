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

void split(string s, std::vector<int>& v, string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) {
           v.push_back(stoi(token)); 
        }
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(stoi(s));
}

/*

brute force:
- for every line:
    - find number of possible arrangements
        - permutate all possibilities of unknown numbers
        - determine if a possibility is possible
- return

brute force time complexity:
- number of lines * number of ? * length of line

how to determine a possible arrangement:
- iterate through groups. 
- check that it has X sets of broken springs.
- sets must be separated by at least one functional spring.

*/

bool is_possible_arrangement(string permutation, vector<int>& damaged_springs) {
    vector<string> damaged_springs_lst;
    split(permutation, damaged_springs_lst, ".");

    if (damaged_springs.size() != damaged_springs_lst.size()) {
        return false;
    }
    for (int i = 0; i < damaged_springs.size(); i++){
        if (damaged_springs_lst[i].size() != damaged_springs[i]){
            return false;
        }
    }
    return true;
}

vector<string>& get_permutations(vector<string>& permutations, string& row) {
    permutations.push_back("");
    for (char c : row) {
        if (c != '?') {
            // update current permutation string with appending
            for (string& permutation : permutations) {
                permutation.append(1, c);
            }
        } else {
            // update two possible ways, requires duplication of permutations
            vector<string> second_permutation;
            for (string& permutation : permutations) {
                string spring_1 = permutation;
                spring_1.append(1, '#');
                permutation.append(1, '.');
                second_permutation.push_back(spring_1);
            }
            for (string& permutation : second_permutation) {
                permutations.push_back(permutation);
            }
        }
    }
    return permutations;
}

// brute force: generate permutations, then go through it one by one.
int compute_possible_arrangements(string& row, vector<int>& damaged_springs) {
    vector<string> permutations;
    get_permutations(permutations, row);
    int ans = 0;
    for (string& permutation : permutations) {
        if (is_possible_arrangement(permutation, damaged_springs)) {
            ans += 1;
        }
    }
    return ans;
}

string get_row(string& line) {
    int pos = 0;
    std::string res;
    while (line[pos] != ' ') {
        res.append(1, line[pos]);
        line.erase(0, 1);
    }
    return res;
}

vector<int> get_damaged_springs(string& line) {
    line.erase(0,1); // remove spring
    vector<int> res;
    split(line, res, ",");
    return res;
}
int main()
{
    int ans = 0;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        while (getline(test_case, line)) {
            string row = get_row(line);
            vector<int> damaged_springs = get_damaged_springs(line);

            ans += compute_possible_arrangements(row, damaged_springs);
        }
    }
    cout << fixed << "ans: " << ans << endl;
    return 0;
}
