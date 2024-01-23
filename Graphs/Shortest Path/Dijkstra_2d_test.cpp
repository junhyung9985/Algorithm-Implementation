#include<bits/stdc++.h>
#include "./Dijkstra_2d.h"
#define ll long long

int main(){

    // Example 1
    ll N = 3, M = 100;
    Dijkstra_2d dijkstra(N, M);
    
    dijkstra.add_edge(1,2,1,1);
    dijkstra.add_edge(2,3,1,1);
    dijkstra.add_edge(1,3,30,3);
    dijkstra.sort_edges();

    ll dist = dijkstra.run_dst(1, N);
    if(dist == -1) cout <<"Poor KCM";
    else cout << dist;
    cout<<"\n";

    // Example 2
    N = 4, M = 10;
    Dijkstra_2d dijkstra2(N, M);
    dijkstra2.add_edge(1,2,3,5);
    dijkstra2.add_edge(2,3,4,5);
    dijkstra2.add_edge(3,4,5,1);
    dijkstra2.add_edge(1,3,6,10);
    
    dist = dijkstra2.run_dst(1, N);
    if(dist == -1) cout <<"Poor KCM";
    else cout << dist;

    return 0;
} // Example : BOJ 10217 Example 1 and 2

