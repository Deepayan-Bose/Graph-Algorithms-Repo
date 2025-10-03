#include <bits/stdc++.h>

#define mp make_pair
#define pb push_back
using vi = vector<int>;
using vl = vector<long long>;
using ll = long long;
using vvi = vector<vector<int > >;
int timer ;
vi lo, tin, vis;
// lo[node] -> contains the minimum possible entry time for a node that can be visited from node
// tin[node] -> entry time for node in the dfs traversal
vvi adj;// adj[u] -> list of nodes v such that u->v exists 
vi ans; // list of nodes that are articulation point


// reference articles 
// https://codeforces.com/blog/entry/71146
// https://www.geeksforgeeks.org/dsa/articulation-points-or-cut-vertices-in-a-graph/

class Solution {
    void dfs(int node, int pred){
        
        vis[node] = 1; // mark the node visited
        lo[node] = tin[node] = ++timer; // set the lo[node] and tin[node] as the timer
        bool flg = false; // indicates if node is an AP
        int childCnt = 0; // count of children from u (excluding back edges)

        for(auto ele : adj[node]){
            if(ele == pred) continue; // skip the parent node (for undirected edges)
            if(vis[ele] == -1){
                childCnt++;
                dfs(ele, node); // recursively perform DFS for its children
                // case 1 : when vis[ele] == -1
                lo[node] = min(lo[node], lo[ele]); // update lo[node] to min(lo[node], lo[ele])
                if(pred != -1 && tin[node] <= lo[ele]) flg = true;  
                // this is for the case when there exists a node v such that there exists no node  x present in subtree rooted at v st 
                // there is a backedge from the x to node
                
            }
            else {
                // ele is already visited (back edge)
                lo[node] = min(lo[node], tin[ele]);
            }
        }
        if(pred == -1 && childCnt > 1){
            // this is for root node when it has 
            // at least 2 children -> it is an AP 
            flg = true;
        }
        if(flg) ans.pb(node);
        
    }
  public:
    vector<int> articulationPoints(int V, vector<vector<int>>& edges) {
        // Code here
        vis.assign(V, -1);
        tin.resize(V), lo.resize(V);
        ans.clear();
        adj.assign(V, vi());
        for(auto edge : edges){
            int u = edge[0], v = edge[1];
            adj[u].pb(v);
            adj[v].pb(u);
        }
        // for each component perform DFS above 
        for(int i = 0; i < V; i++){
            if(vis[i] == -1) dfs(i, -1);
        }
        // if no AP exists -> return {-1}
        if(ans.empty()) return {-1};
        return ans;
    }
};