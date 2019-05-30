/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/CEOI/official/2002/guards-sol.pdf
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

const int N=201*201,source=2*N-1,sink=2*N-2;
struct edge{
    int nxt,cap,rev;
};
vector<vector<edge> > graf(2*N);
map<int,pair<int,int> > mapa[2*N];
int cnt=0;
void addEdge(int i,int j,int c,int x=-1,int y=-1)
{
    if(x!=-1)
        mapa[i][j]={x,y};
    cnt++;
    edge a={j,c,graf[j].size()},b={i,0,graf[i].size()};
    graf[i].pb(a);
    graf[j].pb(b);
}
vector<int> levels(2*N),st(2*N);
bool bfs()
{
    fill(all(levels),-1);
    fill(all(st),0);
    queue<int> q;
    q.push(source);
    levels[source]=0;
    while(q.size())
    {
        int tr=q.front();
        q.pop();
        for(auto p:graf[tr])
        {
            if(levels[p.nxt]!=-1||p.cap==0)
                continue;
            levels[p.nxt]=levels[tr]+1;
            q.push(p.nxt);
        }
    }
    return levels[sink]!=-1;
}
int dfs(int tr,int cap)
{
    if(tr==sink)
        return cap;
    for(;st[tr]<(int)graf[tr].size();st[tr]++)
    {
        if(levels[graf[tr][st[tr]].nxt]==levels[tr]+1&&graf[tr][st[tr]].cap>0)
            if(int t=dfs(graf[tr][st[tr]].nxt,min(cap,graf[tr][st[tr]].cap)))
            {
                graf[tr][st[tr]].cap-=t;
                graf[graf[tr][st[tr]].nxt][graf[tr][st[tr]].rev].cap+=t;
                return t;
            }
    }
    return 0;
}
int dinic()
{
    int f=0;
    while(bfs())
        while(int fl=dfs(source,N))
            f+=fl;
    return f;
}
int main()
{
	int n,m;
	scanf("%i %i",&n,&m);
	vector<vector<int> > mat(n,vector<int>(m));
	for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            scanf("%i",&mat[i][j]);
    int row[n][m],cnt=0;
    addEdge(source,cnt,1);
	for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(mat[i][j]==2)
                cnt++,addEdge(source,cnt,1);
            else
                row[i][j]=cnt;
        }
        cnt++;
        addEdge(source,cnt,1);
    }
    cnt=0;
    addEdge(N+cnt,sink,1);
    for(int j=0;j<m;j++)
    {
        for(int i=0;i<n;i++)
        {
            if(mat[i][j]==2)
                cnt++,addEdge(N+cnt,sink,1);
            else
                if(mat[i][j]==0)
                    addEdge(row[i][j],N+cnt,1,i,j);
        }
        cnt++;
        addEdge(N+cnt,sink,1);
    }
    printf("%i\n",dinic());
    for(int i=0;i<sink;i++)
        for(auto p:graf[i])
            if(p.cap==0&&mapa[i].find(p.nxt)!=mapa[i].end())
                printf("%i %i\n",mapa[i][p.nxt].f+1,mapa[i][p.nxt].s+1);
    return 0;
}
