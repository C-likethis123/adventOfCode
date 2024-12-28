#include "user_defined.h"
#include <algorithm>
#include <experimental/iterator>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>

using namespace std;
using pr = user_defined::pair<int>;
using pair_hash = user_defined::pair_hash<int>;

// Helper function to check if a subset is a clique
bool find_clique(const vector<string> &vertices,
                 const unordered_map<string, unordered_set<string>> &edges) {
  for (size_t i = 0; i < vertices.size() - 1; ++i) {
    for (size_t j = i + 1; j < vertices.size(); ++j) {
      if (edges.at(vertices[i]).count(vertices[j]) == 0) {
        return false;
      }
    }
  }
  return true;
}

int main(int argc, const char *argv[]) {
  if (argc < 2) {
    cerr << "supply a file name" << endl;
    return -1;
  }

  ifstream test_case(argv[1]);
  if (!test_case.is_open()) {
    cerr << "could not open file" << endl;
    return -1;
  }

  unordered_map<string, unordered_set<string>> edges;
  string line;
  while (getline(test_case, line)) {
    vector<string> pair = user_defined::split(line, "-");
    edges[pair[0]].insert(pair[1]);
    edges[pair[1]].insert(pair[0]);
  }

  vector<string> vertices;
  for (const auto &v : edges) {
    vertices.push_back(v.first);
  }

  // Sort vertices by degree (number of neighbors)
  sort(vertices.begin(), vertices.end(),
       [&edges](const string &a, const string &b) {
         return edges[a].size() > edges[b].size();
       });

  vector<string> largest_clique;
  for (const auto &vertex : vertices) {
    vector<string> neighbours(edges[vertex].begin(), edges[vertex].end());
    int n = neighbours.size();
    int totalSubsets = 1 << n; // 2^n subsets

    for (int mask = 0; mask < totalSubsets; ++mask) {
      vector<string> subset;
      subset.push_back(vertex); // Include the vertex itself
      for (int i = 0; i < n; ++i) {
        if (mask & (1 << i)) {
          subset.push_back(neighbours[i]);
        }
      }

      if (find_clique(subset, edges) && subset.size() > largest_clique.size()) {
        largest_clique = subset;
      }
    }
  }

  // Sort and output the largest clique
  sort(largest_clique.begin(), largest_clique.end());
  std::copy(largest_clique.begin(), largest_clique.end(),
            std::experimental::make_ostream_joiner(std::cout, ","));

  return 0;
}
