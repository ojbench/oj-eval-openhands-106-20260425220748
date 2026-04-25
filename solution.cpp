
#include &lt;vector&gt;
#include &lt;iostream&gt;
#include &lt;algorithm&gt;
using namespace std;

vector&lt;vector&lt;int&gt;&gt; graph;
vector&lt;int&gt; subtree_size;
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
        if (subtree_size[v] &gt; k) {
            return false;
        }
    }
    
    // Check the component containing the parent
    int parent_component = n - 1 - (subtree_size[u] - 1);
    return parent_component &lt;= k;
}

int main() {
    cin &gt;&gt; n &gt;&gt; k;
    
    graph.resize(n + 1);
    subtree_size.resize(n + 1);
    
    // Read edges
    for (int i = 0; i &lt; n - 1; i++) {
        int a, b;
        cin &gt;&gt; a &gt;&gt; b;
        graph[a].push_back(b);
        graph[b].push_back(a);
    }
    
    // Calculate subtree sizes starting from node 1
    dfs(1, -1);
    
    vector&lt;int&gt; valid_nodes;
    for (int u = 1; u &lt;= n; u++) {
        if (canRemove(u)) {
            valid_nodes.push_back(u);
        }
    }
    
    // Sort in descending order
    sort(valid_nodes.rbegin(), valid_nodes.rend());
    
    if (valid_nodes.empty()) {
        cout &lt;&lt; "None" &lt;&lt; endl;
    } else {
        for (int i = 0; i &lt; valid_nodes.size(); i++) {
            if (i &gt; 0) cout &lt;&lt; " ";
            cout &lt;&lt; valid_nodes[i];
        }
        cout &lt;&lt; endl;
    }
    
    return 0;
}
