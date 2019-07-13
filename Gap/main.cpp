/*
    -For subtask 1 just repeatedly find the next biggest and smallest number.
    -For subtask 2, find the biggest and the smallest number (cost will be N+1);
    -Now notice that the solution will be at least (r-l+1-n)/(n-1) rounded up.
    -We can split the search space into parts of that size and query for the biggest and smallest numbers.
    -We don't care if we have some gap/numbers inbetween the biggest and smallest numbers of a part since the gap can not be big enough to be the biggest.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
#include "gap.h"

#define ll long long
#define pb push_back
#define sz(x) (int)(x).size()
#define mp make_pair
#define f first
#define s second
#define all(x) x.begin(), x.end()
#define D(x) cerr << #x << " is " << (x) << "\n";

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

ll findGap(int t,int n)
{
    vector<ll> arr;
    ll l=0,r=1e18,a,b;
    if(t==1)
    {
        for(int i=0;i<(n+1)/2;i++)
        {
            MinMax(l,r,&a,&b);
            arr.pb(a);
            arr.pb(b);
            l=a+1;
            r=b-1;
        }
    }
    else
    {
        MinMax(l,r,&l,&r);
        ll deo=(r-l+1-n)/(n-1);
        if((r-l+1-n)%(n-1))
            deo++;
        arr.pb(l);
        arr.pb(r);
        l++;
        r--;
        for(int i=0;i<n-1;i++)
        {
            ll le=l+(deo+1)*i,ri=min(r,l+(deo+1)*(i+1)-1);
            if(le>ri)
                continue;
            MinMax(le,ri,&a,&b);
            if(a!=-1)
                arr.pb(a),arr.pb(b);
        }
    }
    sort(all(arr));
    ll sol=0;
    for(int i=0;i<(int)arr.size()-1;i++)
        sol=max(sol,arr[i+1]-arr[i]);
    return sol;
}
