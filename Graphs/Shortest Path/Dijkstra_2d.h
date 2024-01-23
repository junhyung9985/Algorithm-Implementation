#pragma once

#include <vector>
#include <queue>
#include <algorithm>

#define ll long long
using namespace std;

bool sort_cmp(tuple<ll,ll,ll> a, tuple<ll,ll,ll> b){
    if(get<1>(a) == get<1>(b)){
        return get<2>(a) < get<2>(b);
    }
    return get<1>(a) < get<1>(b);
}

class Dijkstra_2d{
    public :
        ll N, M;
        vector<vector<tuple<ll,ll,ll>>> E, E2;

        Dijkstra_2d(ll num_nodes, ll capacity){
            this-> N = num_nodes;
            this-> M = capacity;
            this->E.resize(N+1, vector<tuple<ll,ll,ll>>());
            //this->E2.resize(N+1, vector<tuple<ll,ll,ll>>());
        };

        void add_edge(ll from, ll to, ll weight, ll cost){
            this->E[from].push_back({to,weight, cost});
            //this->E2[to].push_back({from,weight,cost});
            return;
        }

        void sort_edges(){
            for(int i = 1; i<=N; ++i)
                sort(E[i].begin(), E[i].end(), sort_cmp);
        }

        vector<vector<ll>> run(ll src){

            priority_queue<tuple<ll,ll,ll>> pq;
            vector<vector<ll>> dist(M+1, vector<ll>(N+1, -1)); // array of shortest distance from src, -1 if unreachable
            dist[0][src] = 0;
            for(int i =1; i<=M; ++i) dist[i][src] = 0;
            pq.push({0, src, 0});
            
            while(!pq.empty()){
                ll d, curr, cst;
                tie(d,curr,cst) = pq.top();
                pq.pop();
                d *= -1;
                if(dist[cst][curr] < d) continue;

                for(auto itr : this->E[curr]){
                    ll next,cost,cst2;
                    tie(next,cost,cst2) = itr;
                    if(cst+cst2 > this->M) continue;
                    if(dist[cst+cst2][next] == -1 || dist[cst+cst2][next] > d+cost){
                        dist[cst+cst2][next] = d+cost;
                        for(int j = cst+cst2; j<=this->M; ++j){
                            if(dist[j][next] == -1) dist[j][next] = dist[cst+cst2][next];
                            else dist[j][next] = min(dist[j][next], dist[cst+cst2][next]);
                        }
                        pq.push({-d-cost, next, cst+cst2});
                    }
                }
            }
            return dist;
        }; // return all the shortest distance from src to all nodes

        ll run_dst(ll src, ll dst){
            return run(src)[M][dst];
        }; // return shortest distance from src to dst

        void run_backtrack(ll src, ll dst){
            return;
        }; // I don't know how... also, I haven't seen any 2D-dijkstra backtracking problem yet.
        // I will update about this after I've seen any problem like this.

}; // Costive Dijkstra