/*
    -Find the max matching.
    -For every vertex, if we can remove it and the number of matched vertexes stays the same, Mirko wins, otherwise Slavko wins.
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

struct edge{
    int nxt,rev,cap;
};
const int N=5001;
vector<vector<edge> > graf(2*N);
int source=2*N-1,sink=2*N-2;
int addEdge(int i,int j)
{
    edge a={j,graf[j].size(),1},b={i,graf[i].size(),0};
    graf[i].pb(a);
    graf[j].pb(b);
}
vector<int> st(2*N),level(2*N);
bool bfs()
{
    fill(all(st),0);
    fill(all(level),-1);
    level[source]=0;
    queue<int> q;
    q.push(source);
    while(q.size())
    {
        int tr=q.front();
        q.pop();
        for(auto p:graf[tr])
        {
            if(level[p.nxt]!=-1||p.cap==0)
                continue;
            level[p.nxt]=level[tr]+1;
            q.push(p.nxt);
        }
    }
    return level[sink]!=-1;
}
int dfs(int tr=source,int cap=1)
{
    if(tr==sink)
        return cap;
    for(;st[tr]<(int)graf[tr].size();st[tr]++)
    {
        edge p=graf[tr][st[tr]];
        if(level[p.nxt]!=level[tr]+1||p.cap==0)
            continue;
        if(int d=dfs(p.nxt,min(p.cap,cap)))
        {
            graf[tr][st[tr]].cap-=d;
            graf[p.nxt][p.rev].cap+=d;
            return d;
        }
    }
    return 0;
}
int dinic()
{
    int f=0;
    while(bfs())
        while(int d=dfs())
            f+=d;
    return f;
}
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;b--;
        addEdge(a,b+N);
    }
    for(int i=0;i<n;i++)
        addEdge(source,i),addEdge(i+N,sink);
    int total=dinic();
    for(int i=0;i<n;i++)
    {
        if(graf[i].back().cap==0)
        {
            printf("Mirko\n");
            continue;
        }
        for(auto p:graf[i])
        {
            if(p.cap==0&&p.nxt!=source)
            {
                graf[p.nxt].back().cap^=1;
                if(bfs())
                    printf("Mirko\n");
                else
                    printf("Slavko\n");
                graf[p.nxt].back().cap^=1;
            }
        }
    }
    return 0;
}
