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
vector<vector<int> > komponente;
const int N=1e5+5;
vector<vector<int> > graf(N),revgraf(N);
vector<int> stk,visited(N),visited2(N);
void dfs(int tr)
{
    visited[tr]=1;
    for(auto p:graf[tr])
    {
        if(!visited[p])
            dfs(p);
    }
    stk.pb(tr);
}
void add(int tr)
{
    visited2[tr]=1;
    komponente.back().pb(tr);
    for(auto p:revgraf[tr])
    {
        if(!visited2[p])
            add(p);
    }
}
char s[N][50];
vector<int> komp(N);
vector<int> indeks(N);
vector<vector<int> > kompgraf(N);
int sol[N][50];
vector<vector<vector<int> > > moze;
int calc(int tr,int d)
{
    moze[tr].resize(komponente[tr].size(),vector<int>(50));
    moze[tr][indeks[komponente[tr][0]]][0]=1;
    queue<pair<int,int> > q;
    q.push({komponente[tr][0],0});
    while(q.size())
    {
        auto tr=q.front();
        q.pop();
        for(auto p:graf[tr])
        {

        }
    }
}
int main()
{
	int n,m,d;
	scanf("%i %i %i",&n,&m,&d);
	for(int i=0;i<m;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;
        b--;
        graf[a].pb(b);
        revgraf[b].pb(a);
    }
    for(int i=0;i<n;i++)
        scanf("%s",s[i]);
    for(int i=0;i<n;i++)
    {
        if(visited[i])
            continue;
        dfs(i);
    }
    while(stk.size())
    {
        int tr=stk.back();
        stk.pop_back();
        if(visited2[tr])
            continue;
        vector<int> k;
        komponente.pb(k);
        add(tr);
    }
    for(int i=0;i<komponente.size();i++)
    {
        for(auto p:komponente[i])
            komp[p]=i;
        for(int j=0;j<komponente[i].size();j++)
            indeks[komponente[i][j]]=j;
    }
    for(int i=0;i<n;i++)
        for(auto p:graf[i])
            if(komp[i]!=komp[p])
                kompgraf[komp[i]].pb(komp[p]);
    moze.resize(komponente.size());
    return 0;
}
