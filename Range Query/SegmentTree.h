#pragma once

#include <vector>
#include <queue>
#include <algorithm>

#define ll long long
using namespace std;

template <typename T>
class SegmentTree{
    public: 
        ll N;
        vector<T> tr;
        vector<T> lazy;
        vector<T> arr;

        T func(T a, T b){
            return max(a, b);
        }// Needs to be implemented by user.
        // Define this based on the type of the query

        T init(ll n, ll s, ll e){
            if(s == e) return this->tr[n] = this->arr[s];
            ll mid = (s+e)/2;
            return this->tr[n] = func(init(2*n, s, mid), init(2*n+1, mid+1, e));
        }

        SegmentTree(vector<T> v){
            this->N = v.size();
            this->arr.resize(this->N);
            this->tr.resize(4 * (this->N));
            for(int i =0; i<N; ++i)
                this->arr[i] = v[i];
            init(1,0,this->N-1);
        }

        T _update(ll n, ll s, ll e, ll idx){
            if(idx < s || idx > e) return this->tr[n];
            if(s == e) return this->tr[n] = this->arr[s];
            ll mid = (s+e)/2;
            return this->tr[n] = func(_update(2*n, s, mid, idx), _update(2*n+1, mid+1, e, idx));
        }

        T update(ll idx, T val){
            this->arr[idx] = val;
            return _update(1,0,this->N-1, idx);
        }

        T _query(ll n, ll s, ll e, ll l, ll r){
            if(e < l || r < s) return 0; // this also should be changed from user
            if(l <= s && e <= r) return tr[n];
            ll mid = (s+e)/2;
            return func(_query(2*n, s, mid, l, r), _query(2*n+1, mid+1, e, l, r));
        }

        T query(ll l, ll r){
            return _query(1,0,this->N-1, l, r);
        }
};
