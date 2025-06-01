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

/*
graph question.
- start at single tile at the top
- end at single tile at the bottom

problem type: find longest path

nodes and edges:
- . : can go in any direction
- # : cannot move there
- >|<|v|^: can only go in the specified direction


problem constraints:
- you cannot step onto the same tile twice
- i don't think it's a cycle for now,see how it goes.
- how many steps long is the longest hike?

*/
using namespace std;

#define L 140

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

int main()
{
    int ans = INT_MIN;
    string line;
    ifstream test_case("input.txt");
    ofstream debug("output.txt");
    if (test_case.is_open()) {
        
        while (getline(test_case, line)) {
            
        }
    }
    return 0;
}
