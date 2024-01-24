#pragma once
#include <vector>
#include <utility>
#include <cmath>
#include <algorithm>
#define ll long long

using namespace std;

vector<ll> Mos(vector<ll> v, vector<pair<ll,ll>> queries){ // vector of array with values, vector of pairs {start, end} queries 
    
    ll N = v.size();
    ll bucket_size = sqrt(N);
    ll Q = queries.size();

    vector<tuple<ll,ll,ll,ll>> Queries(Q);
    vector<ll> ans(Q);
    
    for(int i = 0; i < Q; ++i){
        Queries[i] = {queries[i].first/bucket_size, queries[i].second, queries[i].first, i};
    }

    sort(Queries.begin(), Queries.end());

    ll curr_ans = 0;
    ll sqrt_s, e, s, idx;
    tie(sqrt_s, e, s, idx) = Queries[0];
    
    /// Logics start
    vector<ll> how_many(1000001);
    for (int i = s; i <= e; ++i){
        if(how_many[v[i]] == 0) ++curr_ans;
        ++how_many[v[i]];
    }
    ans[idx] = curr_ans;
    /// Logics end

    for(int i = 1; i < Q; ++i){
        ll sqrt_s, n_e, n_s, idx;
        tie(sqrt_s, n_e, n_s, idx) = Queries[i];

        while(n_s < s){
            --s;
            /// Logics start
            if(how_many[v[s]] == 0) ++curr_ans;
            ++how_many[v[s]];
            /// Logics end
        }

        while(n_e > e){
            ++e;
            /// Logics start
            if(how_many[v[e]] == 0) ++curr_ans;
            ++how_many[v[e]];
            /// Logics end
        }

        while(n_s > s){
            /// Logics start
            --how_many[v[s]];
            if(how_many[v[s]] == 0) --curr_ans;
            /// Logics end
            ++s;
        }

        while(n_e < e){
            /// Logics start
            --how_many[v[e]];
            if(how_many[v[e]] == 0) --curr_ans;
            /// Logics end
            --e;
        }

        ans[idx] = curr_ans;
    }

    return ans;
};
/*
    쿼리에 따라서 로직이 바뀌어야 하는 점 주의해주셔야합니다.
    쿼리에 따라서 로직이 바뀌어야 할 부분들은 
    /// Logics start, /// Logics end 이렇게 감싸두었습니다.

    현재 쿼리는 BOJ 13547 기준으로, {s,e} 범위 내에서 서로 다른 수들의 개수를 물어보는 쿼리로 짜두었습니다.
*/