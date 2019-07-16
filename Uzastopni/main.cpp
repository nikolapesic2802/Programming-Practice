/*
    -For each node calculate all the possible segments we can take.
    -This can be done by constructing a graph as follows:
    -Connect v[current node] to v[current node]+1, for each child, for each of their possible segments [l,r], connect l to r+1 only if l>v[curr] or r<v[curr] (we need to take the value v[curr])
    -Now start a bfs for each vertex with value<=v[curr] and get all the vertexes we can reach that have value > v[curr]. All of the pairs between the vertex with value <= v[curr] and the vertexes with value >v[curr] are valid.
    -Notice that we cant take 2 of the same intervals from one of the children because they all overlap.
    -The theoretical complexity is O(N*L^3) but this code passes in 136ms
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

const int N=1e4+4,L=101;
vector<vector<int> > graf(N);
vector<int> v(N);
vector<pair<int,int> > calc(int tr,int par)
{
    vector<vector<int> > nxt(L);
    nxt[v[tr]].pb(v[tr]+1);
    for(auto p:graf[tr])
    {
        if(p==par)
            continue;
        auto sol=calc(p,tr);
        for(auto p:sol)
            if(p.f>v[tr]||p.s<=v[tr])
                nxt[p.f].pb(p.s);
    }
    vector<int> visited(L),reset;
    vector<pair<int,int> > sol;
    for(int i=0;i<=v[tr];i++)
    {
        queue<int> q;
        q.push(i);
        visited[i]=1;
        reset.pb(i);
        while(q.size())
        {
            int tr=q.front();
            q.pop();
            for(auto p:nxt[tr])
                if(!visited[p])
                    visited[p]=1,reset.pb(p),q.push(p);
        }
        for(int j=1;j<(int)reset.size();j++)
            if(reset[j]>v[tr])
                sol.pb({i,reset[j]});
        for(auto p:reset)
            visited[p]=0;
        reset.clear();
    }
    return sol;
}
int main()
{
	int n,a,b;
	scanf("%i",&n);
	for(int i=0;i<n;i++)
        scanf("%i",&v[i]),v[i]--;
    for(int i=1;i<n;i++)
        scanf("%i %i",&a,&b),a--,b--,graf[a].pb(b),graf[b].pb(a);
    auto sol=calc(0,0);
    printf("%i\n",sol.size());
    return 0;
}
