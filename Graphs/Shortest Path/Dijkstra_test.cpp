#include<bits/stdc++.h>
#include "./Dijkstra.h"
#define ll long long

int main(){
    ll N = 5, M = 8;
    Dijkstra dijkstra(N);
    
    dijkstra.add_edge(1,2,2);
    dijkstra.add_edge(1,3,3);
    dijkstra.add_edge(1,4,1);
    dijkstra.add_edge(1,5,10);
    dijkstra.add_edge(2,4,2);
    dijkstra.add_edge(3,4,1);
    dijkstra.add_edge(3,5,1);
    dijkstra.add_edge(4,5,3);
    dijkstra.sort_edges();
    
    pair<ll, vector<ll>> ret = dijkstra.run_backtrack(1,5);

    cout << ret.first <<"\n";
    cout << ret.second.size()<<"\n";
    for(auto itr : ret.second){
        cout << itr <<" ";
    }

    return 0;
} // Example : BOJ 11779 Example 1

