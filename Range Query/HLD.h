#pragma once

#include <vector>
#include <queue>
#include <algorithm>

#define ll long long
using namespace std;

class HLD{
    /*
        Heavy-Light Decomposition

        Attributes:
            <Integers>
            N : number of nodes
            order : variable for DFS ordering

            <Vector of integers>
            sz : sz[i] -> size of subtree with node i as a root
            depth : depth[i] -> depth of node i
            p : p[i] -> parent of node i
            top : top[i] -> node with the lowest depth among the group that node i is in
            in, out : DFS ordering

            <2D vector of integers>
            g : g[i] -> child nodes of node i
    */
    private :
        ll N, order;
        vector<ll> chck, sz, depth, p, top, in, out;
        vector<vector<ll>> g, e;

        void dfs(ll n = 1){
            this-> chck[n] = 1;
            for(auto itr : e[n]){
                if(chck[itr]) continue;
                chck[itr] = 1;
                g[n].push_back(itr);
                dfs(itr);
            }
        }

        void dfs1(ll n = 1){

            this->sz[n] = 1;
            ll until = this->g[n].size();

            for(int i =0; i<until; ++i){

                ll itr = this->g[n][i];
                this->depth[itr] = this->depth[n]+1;
                this-> p[itr] = n;

                dfs1(itr);

                this->sz[n] += this->sz[itr];
                if(this->sz[itr] > this->sz[g[n][0]]) swap(this->g[n][i], this->g[n][0]);
            }

        }; // Fill the sz, p, and depth array. 
        // Also, make g[i][0] as the child node of i with the largest subtree size.

        void dfs2(ll n = 1){
            this->in[n] = ++order;
            ll until = this->g[n].size();

            for(int i =0; i<until; ++i){
                if(i == 0) top[g[n][i]] = top[n];
                else top[g[n][i]] = g[n][i];
                dfs2(g[n][i]);
            }
            
            this->out[n] = order;
        }; // DFS Ordering + Decomposition

    public : 

        HLD(ll N, vector<vector<ll>> E, ll root = 1){
            this->N = N;
            this->order = 0;
            this->chck.resize(N+1);
            this->sz.resize(N+1);
            this->depth.resize(N+1);
            this->p.resize(N+1);
            this->top.resize(N+1);
            this->in.resize(N+1);
            this->out.resize(N+1);
            this->g.resize(N+1, vector<ll>());
            this->e.resize(N+1, vector<ll>());    
            for(int i =1; i<=N; ++i){
                for(auto itr : E[i]){
                    e[i].push_back(itr);
                }
            }
            dfs(root);
            dfs1(root);
            dfs2(root);

            return;
        };

        vector<ll> get_sz(){return this->sz;};
        vector<ll> get_depth(){return this->depth;};
        vector<ll> get_p(){return this->p;};
        vector<ll> get_top(){return this->top;};
        vector<ll> get_in(){return this->in;};
        vector<ll> get_out(){return this->out;};
};

// Query and Update Example
/*
ll query(ll a, ll b){
    ll ans = 0;
    while(top[a] != top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a,b);// 더 아래에 있는 노드를 위로 올린다.
        ll t = top[a];
        ans += seg.query(in[t], in[a]);
        a = p[t];
    }
    if(dep[a] > dep[b]) swap(a,b);
    ans += seg.query(in[a], in[b]);
    return ans;
};

void update(ll a, ll b, ll val){
    while(top[a] != top[b]){
        if(dep[top[a]] < dep[top[b]]) swap(a,b);
        ll t = top[a];
        seg.update(in[t], in[a], val);
        a = p[t];
    }
    if(dep[a] > dep[b]) swap(a,b);
    seg.update(in[a], in[b], val);
    return;
}; // for lazy propagation

void update_point(ll a, ll val){
    seg.update(in[a], in[a], val);
    return;
}
*/