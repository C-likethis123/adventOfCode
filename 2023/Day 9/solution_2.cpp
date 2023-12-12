#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>

/*
for each sequence:
- generate a list of sequences until I get all zeros
- start extrapolating from bottom up

some observations:
- first extrapolated value is always 0
- second extrapolated value is always the same as the last value in the sequence
- to compute the extrapolated values, I don't need the entire sequence. I just need the last values.




10  13  16  21  30  45  68
   3   3   5   9  15  23
     0   2   4   6   8
       2   2   2   2
         0   0   0







brute force time complexity: O(n^2)
space complexity: O(n^2)
*/
using namespace std;

void split(string s, std::vector<long>& v, string delimiter) {
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(delimiter)) != std::string::npos) {
        token = s.substr(0, pos);
        if (!token.empty()) {
           v.push_back(stol(token)); 
        }
        s.erase(0, pos + delimiter.length());
    }
    v.push_back(stol(s));
}

vector<long> get_sequence(string line) {
    vector<long> sequence;
    split(line, sequence, " ");
    return sequence;
}

bool is_all_zeros(vector<long>& sequence) {
    for (long term : sequence) {
        if (term != 0) {
            return false;
        }
    }
    return true;
}

void get_all_sequences(vector<vector<long>>& sequences) {
    vector<long> new_sequence;
    vector<long> sequence = sequences.back();
    for (int i = 1; i < sequence.size(); i++) {
        int term = sequence[i] - sequence[i-1];
        new_sequence.push_back(term);
    }
    if (new_sequence.empty()) {
        return;
    }
    sequences.push_back(new_sequence);
    if (is_all_zeros(new_sequence)) {
        return;
    }
    get_all_sequences(sequences);
}

/*
x  10  13  16  21  30  45
  x   3   3   5   9  15
   x   0   2   4   6
      x   2   2   2
        x   0   0
*/
long add_extrapolated_values(vector<vector<long>>& sequences) {
    // iterate from the last sequence
    long sum = 0;
    for (int i = sequences.size() - 1; i > 0; i--) {
        long first_term = sequences[i].front();
        long second_term = sequences[i - 1].front();
        long extrapolated_term = second_term - first_term;
        sequences[i-1].insert(sequences[i-1].begin(), extrapolated_term);
        sum = extrapolated_term;
    }
    return sum;
}

int main()
{
    long long ans = 0;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        while (getline(test_case, line)) {
            vector<long> sequence = get_sequence(line);
            vector<vector<long>> sequences;
            sequences.push_back(sequence);
            
            get_all_sequences(sequences);
            ans += add_extrapolated_values(sequences);
        }
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
