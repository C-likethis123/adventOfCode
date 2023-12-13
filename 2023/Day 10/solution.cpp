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

/*
graph question.

parsing:
- each letter represents a node with X edges
- there are 4 possible edges: North, South, East, West. Depending on the letter, only a subset of them are valid.

graph properties:
- cyclic graph
- one starting point.
- equal weight edges

problem: find furthest node from starting position. if there is more than one possible way, store the min distance.


bfs: only works with unweighted, acyclic graphs
dijkstra's: only works with positive edge, acylic graphs
bellman ford: can be used to detect negative edge weight cycles


code:
- init graph as an edge list by reading the letter and creating edges for all directions that the letter can go
- init distance matrix, set to infinity
- iterate through all edges for v-1 iterations
    - update distance if it can be relaxed.

in the end:
- take the max distance.

Time complexity: O(EV)

how to optimise:
- only grids reachable from S needs to be considered.
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

class Node {
    public:
        int first;
        int second;
        vector<Node> neighbours;
        Node(int first, int second) : first(first), second(second) {};
        struct HashFunction
        {
            size_t operator()(const Node& node) const
            {
                size_t xHash = std::hash<int>()(node.first);
                size_t yHash = std::hash<int>()(node.second) << 1;
                return xHash ^ yHash;
            }
        };
        void add_neighbour(Node& n) {
            neighbours.push_back(n);
        };
        bool operator==(const Node& n) const {
            return n.first == first && n.second == second;
        };
};

char letters[140][140];

pair<int, int> N = {1, 0};
pair<int, int> S = {-1, 0};
pair<int, int> E = {0, 1};
pair<int, int> W = {0, -1};

vector<pair<int, int>> get_directions(char letter) {
    switch (letter) {
        case '|': 
            return { N, S };
        case '-':
            return { E, W };
        case 'L':
            return { N, E };
        case 'J':
            return { N, W };
        case '7':
            return { S, W };
        case 'F':
            return { S, E };
        case '.':
            return {};
        case 'S':
            return {N, S};
        default:
            return {};
    }
}

/*
input: coordinates to starting position
output: list of nodes reachable from starting position, types converted, that has all neighbours connected to each other.

assumptions:
- all neighbours are fully connected
- i can translate a letter into a node with its corresponding neighbours
- no out of bound errors, assume input is valid
*/
vector<Node> get_subgraph_nodes(int r, int c) {
    vector<Node> queue;
    queue.emplace_back(r, c);

    // do bfs and store nodes in a set
    unordered_set<Node, Node::HashFunction> encountered;
    for (; !queue.empty(); queue.pop_back()) {
        Node n = queue.back();
        encountered.insert(n);
        auto directions = get_directions(letters[n.first][n.second]);
        for (auto direction : directions) {
            Node neighbour(n.first + direction.first, n.second + direction.second);
            n.add_neighbour(neighbour);
            if (encountered.find(neighbour) != encountered.end()) {
                queue.push_back(neighbour);
            }
        }
    }
    // convert set to vector and return
    queue.reserve(encountered.size());
    copy(encountered.begin(), encountered.end(), queue.begin());
    return queue;
}

int main()
{
    int ans = INT_MIN;
    string line;
    ifstream test_case("input.txt");
    if (test_case.is_open()) {
        int distances[140][140];
        pair<int, int> starting_position;
        for (int r = 0; getline(test_case, line); r++) {
            for (int c = 0; c < line.size(); c++) {
                letters[r][c] = line[c];
                distances[r][c] = INT_MAX;
                if (letters[r][c] == 'S') {
                    starting_position = {r, c};
                }
            }
        }
        
        vector<Node> nodes = get_subgraph_nodes(starting_position.first, starting_position.second);
        cout << nodes.size() << endl;
        for (Node n : nodes) {
            int x = n.first;
            int y = n.second;
            for (Node neighbour : n.neighbours) {
                int n_x = neighbour.first;
                int n_y = neighbour.second;
                if (distances[x][y] + 1 < distances[n_x][n_y]) {
                    distances[n_x][n_y] = distances[x][y] + 1;
                }
            }
        }

        for (Node n : nodes) {
            if (distances[n.first][n.second] > ans) {
                ans = distances[n.first][n.second];
            }
        }
    }
    cout << "ans: " << fixed << ans << '\n';
    return 0;
}
