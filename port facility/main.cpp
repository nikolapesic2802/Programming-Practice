/*
    -Construct a graph where we connect two containers if they can no be in the same row (the intervals of time for which they are at the port intersect).
    -If this graph has a cycle of odd length, the answer is 0.
    -Otherwise the answer is 2^(number of components).
    -We can check in the graph has a cycle of odd length by splitting each vertex into two mark them i and i+n, now instead of connecting vertexes i and j directly, connect i to j+n and j to i+n.
    -If we have a path from i to i+n, there is a cycle of odd length.
    -In this new graph we will have twice as many components as in the original one.
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
const int N=2e6+5,mod=1e9+7;
vector<int> par(N);
int find(int tr)
{
    if(par[tr]==tr)
        return tr;
    return par[tr]=find(par[tr]);
}
void merge(int a,int b)
{
    par[find(a)]=find(b);
}
int powmod(int k,int x=2)
{
    int ans=1;
    for(;k;k>>=1,x=(ll)x*x%mod)
        if(k&1)
            ans=(ll)ans*x%mod;
    return ans;
}
int main()
{
    for(int i=0;i<N;i++)
        par[i]=i;
    int n;
	scanf("%i",&n);
	vector<pair<int,int> > niz(n);
	for(int i=0;i<n;i++)
        scanf("%i %i",&niz[i].f,&niz[i].s);
    sort(all(niz));
    set<pair<int,int> > ok;
    for(int i=0;i<n;i++)
    {
        while(ok.size()&&(*ok.begin()).f<niz[i].f)
            ok.erase(ok.begin());
        auto it=ok.upper_bound({niz[i].s,n});
        if(it!=ok.begin())
            for(it--;;it--)
            {
                merge(i,(*it).s+n),merge(i+n,(*it).s);
                if(find((*it).s)==find((*ok.begin()).s))
                    break;
                if(it==ok.begin())
                    break;
            }
        ok.insert({niz[i].s,i});
    }
    for(int i=0;i<n;i++)
        if(find(i)==find(i+n))
        {
            printf("0\n");
            return 0;
        }
    int ans=0;
    for(int i=0;i<2*n;i++)
        if(find(i)==i)
            ans++;
    printf("%i\n",powmod(ans/2));
    return 0;
}
