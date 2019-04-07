/*
    -For every state, we know that every vertex that is on the shortest path between any two vertexes belonging to the state must be in the same final group.
    -Do this merging for every state and compress the tree based on which vertexes must belong to the same final group.
    -Our goal is to compress this tree(the compressed tree) into one vertex by merging some states together.
    -This is equivalent to the problem of: Choose minimum number of pairs of vertexes in the tree such that if we mark all the vertexes on the simple path between the vertexes of each pair, we will mark every vertex.
    -This can be done by sorting all the leaves(its optimal to choose only leaves) of the tree in order in which they appear in the euler tour of the tree.
    -Choose vertex number 1 and n/2+1,2 and n/2+2 and so on. There are (n+1)/2 of these pairs. n is the number of leaves.
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

const int N=5e5+5;
struct dsu{
    vector<int> par;
    void init()
    {
        par.resize(N);
        for(int i=0;i<N;i++)
            par[i]=i;
    }
    int find(int tr)
    {
        if(par[tr]==tr)
            return tr;
        return par[tr]=find(par[tr]);
    }
    void merge(int a,int b)
    {
        a=find(a);
        b=find(b);
        if(a==b)
            return;
        par[b]=a;
    }
}d;
vector<int> up(N),depth(N);
vector<vector<int> > graf(N);
void setup(int tr)
{
    for(auto p:graf[tr])
    {
        if(p==up[tr])
            continue;
        depth[p]=depth[tr]+1;
        up[p]=tr;
        setup(p);
    }
}
void merge(int a,int b)
{
    a=d.find(a);b=d.find(b);
    while(a!=b)
    {
        if(depth[a]<depth[b])
            swap(a,b);
        d.merge(up[a],a);
        a=d.find(up[a]);
    }
}
int main()
{
    d.init();
    int n,k;
    scanf("%i %i",&n,&k);
    for(int i=1;i<n;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    setup(0);
    vector<vector<int> > group(k);
    for(int i=0;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        a--;
        group[a].pb(i);
    }
    for(int i=0;i<k;i++)
        for(int j=1;j<group[i].size();j++)
            merge(group[i][0],group[i][j]);
    int sol=0;
    vector<int> deg(n);
    for(int i=0;i<n;i++)
        for(auto p:graf[i])
            if(d.find(i)!=d.find(p))
            {
                if(deg[d.find(i)]==0)
                    sol++;
                if(deg[d.find(i)]==1)
                    sol--;
                deg[d.find(i)]++;
            }
    printf("%i\n",(sol+1)/2);
    return 0;
}
