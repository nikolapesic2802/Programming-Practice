/*
    -At first only consider edges with value 0.
    -Transform the graph taking strongly connected components as one vertex (SCCDAG) because it doesn't matter which group we take first in a scc.
    -In the SCCDAG, we must be able to cover all the vertexes by starting bfs/dfs from all the vertexes with in degree 0 such that no node is reachable from multiple vertexes with in degree 0.
    -After that we can combine all the nodes in the SCCDAG connected by any edges, getting a graph with no edges.
    -To this graph we add all the edges with value 1 in the reverse direction. If the edge connects two vertexes from the same components the answer is -1.
    -Next do a topological sort on this graph and that is the order in which you should take the nodes.
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

const int N=2e4+5,M=2e5+5;
vector<vector<int> > graf(N),rev(N),sccdag(N),components(N),finalGraph(N),svi(N);
vector<int> scc(N),order,st,visited(N),degree(N),s(M),e(M),x(M);
int scccnt;
void dfs(int tr)
{
    visited[tr]=1;
    for(auto p:graf[tr])
        if(!visited[p])
            dfs(p);
    st.pb(tr);
}
void get(int tr)
{
    visited[tr]=0;
    scc[tr]=scccnt;
    for(auto p:rev[tr])
        if(visited[p])
            get(p);
}
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	vector<pair<int,int> > edges;
	for(int i=0;i<m;i++)
    {
        scanf("%i %i %i",&s[i],&e[i],&x[i]);
        s[i]--;
        e[i]--;
        if(x[i]==0)
            graf[s[i]].pb(e[i]),rev[e[i]].pb(s[i]),edges.pb({s[i],e[i]});
    }
    for(int i=0;i<n;i++)
        if(!visited[i])
            dfs(i);
    while(st.size())
    {
        if(visited[st.back()])
            get(st.back()),scccnt++;
        st.pop_back();
    }
    for(int i=0;i<n;i++)
        components[scc[i]].pb(i);
    for(auto p:edges)
        if(scc[p.f]!=scc[p.s])
            sccdag[scc[p.f]].pb(scc[p.s]),degree[scc[p.s]]++;
    vector<int> starts;
    vector<int> number(scccnt,-1);
    for(int i=0;i<scccnt;i++)
        if(degree[i]==0)
            starts.pb(i);
    int cntNum=0;
    for(auto p:starts)
    {
        queue<int> q;
        q.push(p);
        if(number[p]!=-1)
        {
            printf("-1\n");
            return 0;
        }
        number[p]=cntNum;
        while(q.size())
        {
            int tr=q.front();
            q.pop();
            for(auto d:sccdag[tr])
            {
                if(number[d]==cntNum)
                    continue;
                if(number[d]!=-1)
                {
                    printf("-1\n");
                    return 0;
                }
                number[d]=cntNum;
                q.push(d);
            }
        }
        cntNum++;
    }
    for(int i=0;i<scccnt;i++)
    {
        degree[number[i]]=0;
        svi[number[i]].pb(i);
    }
    for(int i=0;i<m;i++)
        if(x[i]==1)
            finalGraph[number[scc[e[i]]]].pb({number[scc[s[i]]]}),degree[number[scc[s[i]]]]++;
    queue<int> q;
    for(int i=0;i<cntNum;i++)
        if(degree[i]==0)
            q.push(i);
    while(q.size())
    {
        int tr=q.front();
        q.pop();
        for(auto p:svi[tr])
            for(auto d:components[p])
                order.pb(d);
        for(auto p:finalGraph[tr])
        {
            degree[p]--;
            if(degree[p]==0)
                q.push(p);
        }
    }
    if(order.size()!=n)
    {
        printf("-1\n");
        return 0;
    }
    for(auto p:order)
        printf("%i ",p+1);
    return 0;
}
