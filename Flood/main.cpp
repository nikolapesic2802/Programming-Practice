/*
    -https://github.com/mostafa-saad/MyCompetitiveProgramming/blob/master/Olympiad/IOI/official/2007/editorial.pdf
    -Alternative model solution
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
vector<pair<int,pair<int,int> > > walls(1);
vector<int> ans,trwalls;
int start;
bool dfs(int tr,int dir)
{
    if(tr==start&&dir!=4)
        return true;
    for(int k=0;k<4;k++)
    {
        int l=(dir+1-k+4)%4;
        int sl=nxt[tr][l].f;
        if(sl==-1)
            continue;
        trwalls.pb(nxt[tr][l].s);
        nxt[tr][l]={-1,-1};
        if(dfs(sl,l))
            return true;
    }
    return false;
}
void doit(int tr)
{
    start=tr;
    dfs(tr,4);
    sort(all(trwalls));
    trwalls.pb(-1);
    for(int i=0,n=trwalls.size()-1;i<n;i++)
    {
        if(trwalls[i]==trwalls[i+1])
        {
            ans.pb(trwalls[i]);
            i++;
            continue;
        }
        nxt[walls[trwalls[i]].s.f][walls[trwalls[i]].f]={-1,-1};
        nxt[walls[trwalls[i]].s.s][walls[trwalls[i]].f+2]={-1,-1};
    }
    trwalls.clear();
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
            walls.pb({0,{a,b}});
            nxt[a][0]={b,i};
            nxt[b][2]={a,i};
        }
        else
        {
            if(nodes[a].f.f>nodes[b].f.f)
                swap(a,b);
            walls.pb({1,{a,b}});
            nxt[a][1]={b,i};
            nxt[b][3]={a,i};
        }
    }
    sort(nodes.rbegin(),nodes.rend());
    for(auto p:nodes)
        for(int i=0;i<2;i++)
            doit(p.s);
    printf("%i\n",ans.size());
    for(auto p:ans)
        printf("%i\n",p);
    return 0;
}
