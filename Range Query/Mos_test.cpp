#include <bits/stdc++.h>
#include "Mos.h"
#define ll long long

using namespace std;

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    ll N = 5, Q = 3;

    vector<ll> v = {1,1,2,1,3};
    vector<pair<ll,ll>> q = {{0,4}, {1,3}, {2,4}};

    vector<ll> ans = Mos(v,q);

    for(auto itr : ans) cout << itr<<"\n";

    return 0;
} // Example : BOJ 13547 Example 1