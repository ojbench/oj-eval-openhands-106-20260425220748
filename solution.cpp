
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> graph;
vector<int> subtree_size;
int n, k;

// DFS to calculate subtree sizes
int dfs(int u, int parent) {
    subtree_size[u] = 1;
    for (int v : graph[u]) {
        if (v != parent) {
            subtree_size[u] += dfs(v, u);
        }
    }
    return subtree_size[u];
}

// Check if removing node u satisfies the condition
bool canRemove(int u) {
    // Check all children subtrees
    for (int v : graph[u]) {
        if (subtree_size[v] > k) {
            return false;
        }
    }
    
    // Check the component containing the parent
    int parent_component = n - 1 - (subtree_size[u] - 1);
    return parent_component <= k;
}

int main() {
    cin >> n >> k;
    
    graph.resize(n + 1);
    subtree_size.resize(n + 1);
    
    // Read edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    // Calculate subtree sizes starting from node 1
    dfs(1, -1);
    
    vector<int> valid_nodes;
    for (int u = 1; u <= n; u++) {
        if (canRemove(u)) {
            valid_nodes.push_back(u);
        }
    }
    
    // Sort in descending order
    sort(valid_nodes.rbegin(), valid_nodes.rend());
    
    if (valid_nodes.empty()) {
        cout << "None" << endl;
    } else {
        for (int i = 0; i < valid_nodes.size(); i++) {
            if (i > 0) cout << " ";
            cout << valid_nodes[i];
        }
        cout << endl;
    }
    
    return 0;
}
