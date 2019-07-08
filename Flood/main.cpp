/*
    -Start from the node with the lowest x coordinate (lowest y if there is a tie)
    -Always take a right turn first, then forward then left, then backwards.
    -If we find a loop, all the walls in that loop will be destroyed.
    -If a wall is not in a loop it will stay.
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

const int N=1e5;
vector<vector<pair<int,int> > > nxt(N,vector<pair<int,int> >(4,{-1,-1}));
vector<pair<pair<int,int>,int> > nodes;
vector<int> ans,visited(N);
int dfs(int tr,int dir)
{
    if(visited[tr])
        return tr;
    visited[tr]=1;
    for(int k=0;k<4;k++)
    {
        int l=(dir+1-k+4)%4;
        int sl=nxt[tr][l].f;
        if(sl==-1)
            continue;
        int i=nxt[tr][l].s;
        nxt[tr][l]={-1,-1};
        nxt[sl][(l+2)%4]={-1,-1};
        int loop=dfs(sl,l);
        if(loop==-1)
        {
            ans.pb(i);
            continue;
        }
        if(loop!=tr)
        {
            visited[tr]=0;
            return loop;
        }
    }
  	visited[tr]=0;
  	return -1;
}
int main()
{
	int n;
	scanf("%i",&n);
	nodes.resize(n);
	for(int i=0;i<n;i++)
        scanf("%i %i",&nodes[i].f.f,&nodes[i].f.s),nodes[i].s=i;
    int w;
    scanf("%i",&w);
    for(int i=1;i<=w;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;b--;
        if(nodes[a].f.f==nodes[b].f.f)
        {
            if(nodes[a].f.s>nodes[b].f.s)
                swap(a,b);
            nxt[a][0]={b,i};
            nxt[b][2]={a,i};
        }
        else
        {
            if(nodes[a].f.f>nodes[b].f.f)
                swap(a,b);
            nxt[a][1]={b,i};
            nxt[b][3]={a,i};
        }
    }
    sort(nodes.begin(),nodes.end());
    for(auto p:nodes)
        dfs(p.s,0);
    printf("%i\n",ans.size());
    for(auto p:ans)
        printf("%i\n",p);
    return 0;
}
