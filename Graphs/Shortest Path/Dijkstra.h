#pragma once

#include <vector>
#include <queue>
#include <algorithm>

#define ll long long
using namespace std;

bool sort_cmp(pair<ll,ll> a, pair<ll,ll> b){
    return get<1>(a) < get<1>(b);
}

class Dijkstra{
    public :
        ll N;
        vector<vector<pair<ll,ll>>> E, E2;

        Dijkstra(ll num_nodes){
            this->N = num_nodes;
            this->E.resize(N+1, vector<pair<ll,ll>>());
            this->E2.resize(N+1, vector<pair<ll,ll>>());
        };

        void add_edge(ll from, ll to, ll weight){
            this->E[from].push_back({to,weight});
            this->E2[to].push_back({from,weight});
            return;
        }

        void sort_edges(){
            for(int i = 1; i <= N; ++i){
                sort(E[i].begin(), E[i].end(), sort_cmp);
                sort(E2[i].begin(), E2[i].end(), sort_cmp);
            }        
        }

        vector<ll> run(ll src){

            priority_queue<pair<ll,ll>> pq;
            vector<ll> dist(N+1, -1); // array of shortest distance from src, -1 if unreachable
            dist[src] = 0;
            pq.push({0, src});
            
            while(!pq.empty()){
                ll d, curr;
                tie(d,curr) = pq.top();
                pq.pop();
                d *= -1;
                if(dist[curr] < d) continue;

                for(auto itr : this->E[curr]){
                    ll next,cost;
                    tie(next, cost) = itr;
                    if(dist[next] == -1 || dist[next] > d+cost){
                        dist[next] = d+cost;
                        pq.push({-d-cost, next});
                    }
                }
            }
            return dist;
        }; // return all the shortest distance from src to all nodes

        ll run_dst(ll src, ll dst){
            return run(src)[dst];
        }; // return shortest distance from src to dst

        pair<ll,vector<ll>> run_backtrack(ll src, ll dst){
            vector<ll> dist = run(src);
            ll distance = dist[dst];
            ll curr = dst;
            vector<ll> path;

            if(distance == -1) return {-1, path};

            path.push_back(dst);
            while(curr != src){
                for(auto itr : this->E2[curr]){
                    ll bef, cost;
                    tie(bef, cost) = itr;
                    if(distance == dist[bef]+cost){
                        distance -= cost;
                        path.push_back(bef);
                        curr = bef;
                        break;
                    }
                }
            }
            reverse(path.begin(), path.end());
            return{dist[dst], path};
        }; // return {shortest distance, one arbitary shortest path} from src to dst.
        // Empty vector will be returned if there isn't any shortest path available.  
};