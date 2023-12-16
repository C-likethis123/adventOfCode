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

bad_alloc could be due to a lack of memory.

another approach:
- dfs until you reach a cycle. then divide by 2.
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


char letters[L][L];

pair<int, int> N = {-1, 0};
pair<int, int> S = {1, 0};
pair<int, int> E = {0, 1};
pair<int, int> W = {0, -1};

vector<pair<int, int>> get_directions(char letter) {
        // hardcoded because i'm too lazy
        vector<pair<int, int>> directions;
        if (letter == '|' || letter == 'S'){
            directions.push_back(N);
            directions.push_back(S);
        } else if (letter == '-') {
            directions.push_back(E);
            directions.push_back(W);
        } else if (letter == 'L') {
            directions.push_back(N);
            directions.push_back(E);
        } else if (letter == 'J') {
            directions.push_back(N);
            directions.push_back(W);
        } else if (letter == '7') {
            directions.push_back(S);
            directions.push_back(W);
        } else if (letter == 'F') {
            directions.push_back(S);
            directions.push_back(E);
        } else if (letter == '.') {
            return directions;
        }
        return directions;
}

/*
input: coordinates to starting position
output: list of nodes reachable from starting position, types converted, that has all neighbours connected to each other.

assumptions:
- all neighbours are fully connected
- i can translate a letter into a node with its corresponding neighbours
- no out of bound errors, assume input is valid
*/

int main()
{
    int ans = INT_MIN;
    string line;
    ifstream test_case("input.txt");
    ofstream debug("output.txt");
    if (test_case.is_open()) {
        int distances[L][L];
        pair<int, int> starting_position;
        for (int r = 0; getline(test_case, line); r++) {
            for (int c = 0; c < line.size(); c++) {
                letters[r][c] = line[c];
                distances[r][c] = INT_MAX - 1;
                if (letters[r][c] == 'S') {
                    starting_position = {r, c};
                    distances[r][c] = 0;
                }
            }
        }
        test_case.close();
        
        for (int x = 0; x < L; x++) {
            for (int y = 0; y < L; y++) {
                vector<pair<int, int>> directions = get_directions(letters[x][y]);
                for (auto& direction : directions) {
                    int n_x = direction.first + x;
                    int n_y = direction.second + y;
                    if (distances[x][y] + 1 < distances[n_x][n_y]) {
                        distances[n_x][n_y] = distances[x][y] + 1;
                    }
                }
            }
        }
        for (int i = 0; i < L; i++) {
            for (int j = 0; j < L; j++) {
                debug << distances[i][j] << '|';
            }
            debug << endl;
        }
        // cout << "ans: " << fixed << ans << '\n';
    }
    return 0;
}
