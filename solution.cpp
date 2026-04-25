
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

vector<vector<int>> graph;
vector<int> subtree_size;
vector<int> parent;
int n, k;

// DFS to calculate subtree sizes and parent pointers
void dfs(int u, int p) {
    parent[u] = p;
    subtree_size[u] = 1;
    for (int v : graph[u]) {
        if (v != p) {
            dfs(v, u);
            subtree_size[u] += subtree_size[v];
        }
    }
}

// Check if removing node u satisfies the condition
bool canRemove(int u) {
    // Check all components formed by removing u
    for (int v : graph[u]) {
        int component_size;
        // If v is a child of u, the component size is subtree_size[v]
        // If v is the parent of u, the component size is n - subtree_size[u]
        if (v == parent[u]) {
            // v is parent of u
            component_size = n - subtree_size[u];
        } else {
            // v is a child of u (since our DFS tree is rooted at 1)
            component_size = subtree_size[v];
        }
        
        if (component_size > k) {
            return false;
        }
    }
    return true;
}

int main() {
    cin >> n >> k;
    
    graph.resize(n + 1);
    subtree_size.resize(n + 1);
    parent.resize(n + 1);
    
    // Read edges
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    // Calculate subtree sizes and parent pointers starting from node 1
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
