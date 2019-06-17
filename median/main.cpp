/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2000/sol.pdf
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <ext/rope>

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

int Med3(int a, int b, int c);
int NN;
vector<int> sortiraj(vector<int> indeksi,int edge,int distL,int distR,int side)
{
    int n=indeksi.size();
    if(n<=1||distL>=NN||distR>=NN)
        return indeksi;
    int p1=rng()%n,p2=rng()%n;
    while(p1==p2)
        p2=rng()%n;
    p1=indeksi[p1];
    p2=indeksi[p2];
    if(edge!=-1)
    {
        int t=Med3(p1,p2,edge);
        assert(t!=edge);
        if(t==p1)
            swap(p1,p2);
        if(side)
            swap(p1,p2);
    }
    vector<int> le,mi,ri;
    for(auto p:indeksi)
    {
        if(p==p1||p==p2)
            continue;
        int t=Med3(p1,p2,p);
        if(t==p)
            mi.pb(p);
        if(t==p1)
            le.pb(p);
        if(t==p2)
            ri.pb(p);
    }
    le=sortiraj(le,p1,distL,distR+mi.size()+ri.size()+2,0);
    mi=sortiraj(mi,p2,distL+le.size()+1,distR+ri.size()+1,0);
    ri=sortiraj(ri,p2,distL+le.size()+mi.size()+2,distR,1);
    le.pb(p1);
    for(auto p:mi)
        le.pb(p);
    le.pb(p2);
    for(auto p:ri)
        le.pb(p);
    return le;
}
int Median(int n) {
    NN=(n+1)/2;
    vector<int> o;
    for(int i=1;i<=n;i++)
        o.pb(i);
    o=sortiraj(o,-1,0,0,0);
    return o[n/2];
}
