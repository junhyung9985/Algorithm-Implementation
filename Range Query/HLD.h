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
    
    ll N, order;
    vector<ll> sz, depth, p, top, in, out;
    vector<vector<ll>> g;

    private :
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

        };

    public:

        HLD(ll N, vector<vector<ll>> E, ll root = 1){
            this->N = N;
            this->order = 0;
            this->sz.resize(N+1);
            this->depth.resize(N+1);
            this->p.resize(N+1);
            this->top.resize(N+1);
            this->in.resize(N+1);
            this->out.resize(N+1);
            this->g.resize(N+1);
            for(int i =1; i<=N; ++i){
                for(auto itr : E[i]){
                    g[i].push_back(itr);
                }
            }

            dfs1(root);
            dfs2(root);

            return;
        };

        vector<ll> get_top(){
            return this->top;
        };
        
        vector<ll> get_in(){
            return this->in;
        };

        /*
            TO DO
            -> Implement query and update function after implementing Lazy Segmnet Tree class.
        */

};