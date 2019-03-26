/*
    -Process edges in order, if the edge is in the spanning tree give it the minimum value possible,
    if the edge is not in the spanning tree, then we need to make its weight bigger than all of the edges on the path from the two vertices it connects.
    so we "save" the smallest values we can for the edges on the path that don't have a value assigned or saved and make the edge that is not in the spanning tree the smallest value it can be.
    We later use the saved values when the edges in the spanning tree come.
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
const int N=3e5+5,L=20;
int up[N][L];
vector<int> visited(N),depth(N),nxt(N);
vector<vector<int> > graf(N);
void setup(int tr=0)
{
    visited[tr]=1;
    for(auto p:graf[tr])
    {
        if(visited[p]==1)
            continue;
        depth[p]=depth[tr]+1;
        up[p][0]=nxt[p]=tr;
        setup(p);
    }
}
int lca(int a,int b)
{
    if(depth[a]<depth[b])
        swap(a,b);
    for(int j=L-1;j>=0;j--)
        if(depth[a]-depth[b]>=(1<<j))
            a=up[a][j];
    if(a==b)
        return a;
    for(int j=L-1;j>=0;j--)
        if(up[a][j]!=up[b][j])
            a=up[a][j],b=up[b][j];
    return up[a][0];
}
int main()
{
	int n,e;
	scanf("%i %i",&n,&e);
	vector<pair<int,int> > edges(e);
	map<int,int> mapa[n];
	for(int i=0;i<e;i++)
    {
        scanf("%i %i",&edges[i].f,&edges[i].s);
        edges[i].f--;edges[i].s--;
    }
    vector<int> inD(e);
    for(int i=1;i<n;i++)
    {
        int a;
        scanf("%i",&a);
        inD[a-1]=1;
        int x=edges[a-1].f,y=edges[a-1].s;
        mapa[x][y]=a-1;
        mapa[y][x]=a-1;
        graf[x].pb(y);
        graf[y].pb(x);
    }
    vector<int> next_value;
    vector<int> index(e);
    int val=1;
    next_value.pb(1);
    depth[0]=1;
    setup();
    for(int j=1;j<L;j++)
        for(int i=0;i<n;i++)
            up[i][j]=up[up[i][j-1]][j-1];
    for(int i=0;i<e;i++)
    {
        int sol;
        if(inD[i])
        {
            if(index[i]==0)
            {
                sol=val;
                val++;
            }
            else
            {
                sol=next_value[index[i]];
                next_value[index[i]]++;
            }
        }
        else
        {
            int a=edges[i].f,b=edges[i].s;
            int l=lca(a,b);
            int cnt=0;
            next_value.pb(val);
            while(depth[a]>depth[l])
            {
                int in=mapa[a][nxt[a]];
                if(in>i)
                {
                    cnt++;
                    index[in]=next_value.size()-1;
                    mapa[a][nxt[a]]=0;
                }
                int nxtt=nxt[a];
                nxt[a]=l;
                a=nxtt;
            }
            while(depth[b]>depth[l])
            {
                int in=mapa[b][nxt[b]];
                if(in>i)
                {
                    cnt++;
                    index[in]=next_value.size()-1;
                    mapa[b][nxt[b]]=0;
                }
                int nxtt=nxt[b];
                nxt[b]=l;
                b=nxtt;
            }
            val+=cnt;
            sol=val;
            val++;
        }
        printf("%i ",sol);
    }
    return 0;
}
