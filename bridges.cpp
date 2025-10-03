#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
#define nexl "\n"
using vi= vector<int>;
using vvi = vector<vector<int>>;
using pi = pair<int, int>;

vi lo, tin ;
vector<bool> vis;
vvi adj;
vector<pi> bridges;
int timer;
// lo[node] -> earliest tin of a node u which we can reach using a path from node to u 
// tin[node] -> entry time for node

// debugging purpose
template <typename T>
void debug(vector<T> & arr ){
    for(const auto &ele : arr)
        cout <<  ele << " ";
    cout << nexl;
}

// reference articles :
// https://codeforces.com/blog/entry/71146
// https://www.geeksforgeeks.org/dsa/bridge-in-a-graph/

class Solution {
    // dfs to identify the bridges in the graph G(V, E)
    void dfsBR(int node, int pred){
        lo[node] = tin[node] = ++timer;
        vis[node] = true;
        // bool parent_skipped = false; // for multiedge graphs only 
        for(auto ele : adj[node]){
            if(ele == pred) continue;
            // if ele is not visited yet i.e forward edge
            if(vis[ele] == false){
                // recursively perform DFS for ele
                dfsBR(ele, node);
                lo[node] = min(lo[node], lo[ele]);
                // if there exists a node ele such that it has no children  v in its subtree such that there is a path frrom v to node
                if(lo[ele] > tin[node]){
                    bridges.pb({node, ele});
                }
                
                
            }
            else{
                // simply update as like for AP
                lo[node] = min(lo[node], tin[ele]);
            }
        }
        
        
    }
  public:
    bool isBridge(int V, vector<vector<int>> &edges, int c, int d) {
        // checks if edge conn c and d is a bridge
        // Code here
        timer= 0;
        adj.assign(V, vi());
        vis.assign(V, false);
        tin.resize(V), lo.resize(V);
        bridges.clear();
        
        for(const auto &edge : edges){
            int u = edge[0], v = edge[1];
            adj[u].pb(v), adj[v].pb(u);
        }
        // perform DFS for each component
        for(int i = 0; i < V; i++){
            if(vis[i] == false){
                dfsBR(i, -1);
            }
        }
        // debug(tin), debug(lo);
        // debug(bridges);
        for(const auto & bridge : bridges){
            
            int u = bridge.first, v = bridge.second;
            // cout << u << " " << v << nexl;
            if(u == c && v == d){
                return true;
            }
            if(u == d && v == c){
                return true;
            }
        }
        
        return false;
        
    }
};