#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <numeric>
#include <vector>
#include <algorithm>
#include <iterator>
#include <sstream>
#include <queue>

/*
changes made:
- number of starting positions
- how starting positions are identified
- how ending positions are identified

Not optimal - it does not stop running, especially on long inputs.
use lcm - why?
- each node ending with A can only reach one node ending in Z
- after reaching the node, it takes the same amount of steps to get back to it.
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

        vector<Node> get_starting_positions() {
            vector<Node> res;
            for (auto x : s) {
                if (x.first[2] == 'A') {
                    res.push_back(x.first);
                }
            }
            return res;
        };
};

bool is_ending_position(Node& n) {
    return n[2] == 'Z';
}

long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = a % b;
        a = b;
        b = temp;
    }
    return a;
}

long long lcm(long long a, long long b){
    return a * b / gcd(a, b);
}

int main()
{
    long long ans = 0;
    string line;
    ifstream test_case("test.txt");
    if (test_case.is_open()) {
        getline(test_case, line);
        string instructions = line;
        
        Graph graph;
        getline(test_case, line);
        while (getline(test_case, line) && !line.empty()) {
            graph.add(line);
        }

        vector<Node> nodes = graph.get_starting_positions();
        vector<long long> ways;
        ways.resize(nodes.size(), 0);
        
        for (int i = 0; i < nodes.size(); i++) {
            bool node_not_found = true;
            while (node_not_found) {
                for (char dir : instructions) {
                    Node new_node = graph.move(nodes[i], dir);
                    nodes[i] = new_node;
                    ways[i] += 1;
                    if (is_ending_position(new_node)) {
                        node_not_found = false;
                        break;
                    }
                }
            }
        }

        // find lcm
        ans = std::reduce(ways.begin() + 1, ways.end(), ways[0], [](long long a, long long b) {
            return lcm(a, b);
        });
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
