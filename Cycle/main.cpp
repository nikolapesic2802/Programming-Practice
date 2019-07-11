/*
    -First move to a room that is not in range (When n==2 there is no such room).
    -Binary search for the last place where we are in range.
    -If the current room is not in range, if it is over n/2 rooms away from the starting location, then the required room is to the left otherwise its to the right.
    -This is true because the size of the zone that is in range is n/2+1.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>
#include "cycle.h"

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

bool jump(int x);
void escape(int n)
{
    if(n==2)
    {
        jump(1);
        return;
    }
    while(jump(n-n/2-1));
    int tr=0,l=1,r=n-1;
    while(l<r)
    {
        int m=(l+r+1)>>1;
        int dist=m-tr;
        if(tr>m)
            dist=n-tr+m;
        if(jump(dist))
            l=m;
        else
            if(m<=n/2)
                l=m+1;
            else
                r=m-1;
        tr=m;
    }
    int dist=l-tr;
    if(tr>l)
        dist=n-tr+l;
    assert(jump(dist));
}
