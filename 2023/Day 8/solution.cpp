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
1. graph question?
2. graph representation - adjacency list
3. follow a list of instructions, keep iterating. for each iteration, increment.
4. repeat until zzz is found.
*/
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

typedef string Node;

class Graph {
    protected:
        unordered_map<Node, pair<Node, Node>> s;
    public:
        void add(string line) {
            vector<string> v;
            split(line, v, " = ");
            Node key = v[0];
            string temp = v[1];
            v.clear();

            split(temp, v, ", ");
            vector<string> v1;
            split(v[0], v1, "(");
            Node left = v1[0];
            v1.clear();
            split(v[1], v1, ")");
            Node right = v1[0];
            s.emplace(key, pair<Node, Node>{left, right});
        };
        Node move(Node& n, char dir) {
            pair<Node, Node> p = s[n];
            if (dir == 'L') {
                return p.first;
            } else {
                return p.second;
            }
        };
};

int main()
{
    long long ans = 0;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        getline(test_case, line);
        string instructions = line;
        
        Graph graph;
        getline(test_case, line);
        while (getline(test_case, line) && !line.empty()) {
            graph.add(line);
        }
        bool not_found = true;
        Node n = std::string("AAA");
        while (not_found) {
            for (char dir : instructions) {
                n = graph.move(n, dir);
                ans += 1;
                if (n == std::string("ZZZ")) {
                    cout << "ans: " << ans << '\n';
                    return 0;
                }
            }
        }

    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
