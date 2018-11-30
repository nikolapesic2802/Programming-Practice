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

using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a) {
	os << '{';
	for(int i=0;i<sz(a);i++)
	{
		if(i>0&&i<sz(a)-1)
			os << ", ";
		os << a[i];
	}
	os << '}';
    return os;
}
const int N=15;
vector<vector<int> > graf(N),drvo(N);
vector<int> visited(N),siz(N),what(N);
void dfs(int tr,int par)
{
    siz[tr]=1;
    for(auto p:graf[tr])
    {
        if(visited[p]||p==par)
            continue;
        dfs(p,tr);
        siz[tr]+=siz[p];
    }
}
int find_centroid(int tr,int n,int par)
{
    for(auto p:graf[tr])
    {
        if(p==par||visited[p])
            continue;
        if(siz[p]>n/2)
            return find_centroid(p,n,tr);
    }
    return tr;
}
int decompose(int tr)
{
    dfs(tr,-1);
    tr=find_centroid(tr,siz[tr],-1);
    visited[tr]=1;
    for(auto p:graf[tr])
    {
        if(visited[p])
            continue;
        int t=decompose(p);
        //printf("%i--%i\n",tr,t);
        drvo[t].pb(tr);
        drvo[tr].pb(t);
    }
    return tr;
}
ll cnt1=0;
vector<int> allowed(N),str,fin,start(N),finish(N);
void calculate(int tr,int par,int offset,int maxx,int minn)
{
    //printf("Calculatujem %i\n",tr);
    if(what[tr]==0){
        offset++;
        maxx=max(maxx,offset);
        if(offset>=0&&offset==maxx)
        {
            str.pb(offset);
            //printf("Dodajem start %i\n",offset);
        }
    }
    else{
        offset--;
        minn=min(minn,offset);
        if(offset<=0&&offset==minn)
        {
            fin.pb(-1*offset);
            //printf("Dodajem finish %i\n",offset*-1);
        }
    }
    for(auto p:graf[tr])
    {
        if(allowed[p]==0||p==par)
            continue;
        calculate(p,tr,offset,maxx,minn);
    }
}
void solve(int tr,int par)
{
    for(auto p:drvo[tr])
    {
        if(p==par)
            continue;
        solve(p,tr);
    }
    int off;
    if(what[tr]==0)
        off=1;
    else
        off=-1;
    //printf("Solvujem %i %lld\n",tr,cnt);
    vector<int> s,f;
    for(auto p:graf[tr])
    {
        if(allowed[p]){
            //printf("Calculatujem %i\n",p);
            calculate(p,tr,0,0,0);
            for(auto p:str)
            {
                if(off+p>=0)
                    cnt1+=finish[p+off];
                s.pb(p);
            }
            for(auto p:fin){
                if(p-off>=0)
                    cnt1+=start[p-off];
                finish[p]++;
                f.pb(p);
            }
            for(auto p:str)
                start[p]++;
            str.clear();
            fin.clear();
        }
    }
    //printf("%i %i %i\n",tr,what[tr],finish[1]);
    allowed[tr]=1;
    if(what[tr]==0)
        cnt1+=finish[1];
    else
        cnt1+=start[1];
    for(auto p:s)
        start[p]=0;
    for(auto p:f)
        finish[p]=0;
}
#define F first
#define S second
#define pb push_back
#define eb emplace_back
#define right(x) x << 1 | 1
#define left(x) x << 1
#define forn(x, a, b) for (int x = a; x <= b; ++x)
#define for1(x, a, b) for (int x = a; x >= b; --x)
#define mkp make_pair
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define y1 kekekek
int ROOT = 0, cnt[N], tmp[N], MXVAL;
bool u[N];
char a[N];
vector < int > g[N];
ll ans;
int getsz(int v, int par, int sz) {
    int res = 1;
    bool ok = 1;
    for (auto to : g[v]) {
        if (to == par || u[to]) continue;
        int val = getsz(to, v, sz);
        if (val > sz / 2) ok = 0;
        res += val;
    }
    if (sz - res > sz / 2) ok = 0;
    if (ok) ROOT = v;
    return res;
}

void dfs(int v, int par, int bal, int mn) {
    bal += (a[v] == ')' ? -1 : 1);
    mn = min(mn, bal);
    if (bal == mn) cnt[-bal]++;
    for (auto to : g[v]) {
        if (to == par || u[to]) continue;
        dfs(to, v, bal, mn);
    }
}

void calc(int v, int par, int bal, int mn, int bal2, int mx, int kek) {
    bal += (a[v] == ')' ? -1 : 1);
    bal2 += (a[v] == ')' ? -1 : 1);
    mn = min(mn, bal);
    mx = max(mx, bal2);
    if (bal == mn) cnt[-bal] -= kek;
    if (bal == mn) MXVAL = max(MXVAL, abs(bal));
    if (bal2 == mx) tmp[bal2] += kek;
    if (bal2 == mx) MXVAL = max(MXVAL, abs(bal2));
    for (auto to : g[v]) {
        if (to == par || u[to]) continue;
        calc(to, v, bal, mn, bal2, mx, kek);
    }
}

void build(int v, int sz) {
    getsz(v, 0, sz);
    int root = ROOT;
    //cerr << root << " " << sz << "\n";
    forn(i, 0, sz / 2 + 1) cnt[i] = 0;
    dfs(root, 0, 0, 0);
    for (auto to : g[root]) {
        if (u[to]) continue;
        MXVAL = 0;
        calc(to, root, (a[root] == ')' ? -1 : 1), (a[root] == ')' ? -1 : 1), 0, 0, 1);
        forn(i, 0, MXVAL) {
            ans += 1ll * cnt[i] * tmp[i];
            //cerr << root << " " << to << " " << i << " " << cnt[i] << " " << tmp[i] << "\n";
        }
        calc(to, root, (a[root] == ')' ? -1 : 1), (a[root] == ')' ? -1 : 1), 0, 0, -1);
    }
    ans += cnt[0];
    //cerr << "kek " << cnt[0] << "\n";

    u[root] = 1;
    vector < int > vec;
    for (auto to : g[root]) {
        vec.eb(0);
        if (u[to]) continue;
        vec.back() = getsz(to, root, sz);
    }
    forn(i, 0, sz(g[root]) - 1) {
        if (u[g[root][i]]) continue;
        build(g[root][i], vec[i]);
    }
}

ll his(int n,string s) {
    forn(i, 1, n) {
        a[i]=s[i-1];
    }
    build(1, n);
	return ans;
}
void reset()
{
    ans=0;
    cnt1=0;
    MXVAL=0;
    ROOT=0;
    for(int i=0;i<N;i++)
    {
        allowed[i]=0;
        cnt[i]=0;
        tmp[i]=0;
        u[i]=false;
        drvo[i].clear();
        visited[i]=0;
        siz[i]=0;
    }
}
void r2()
{
    for(int i=0;i<N;i++)
    {
        graf[i].clear();
        g[i].clear();
    }
}
ll mein(int n,string s)
{
	for(int i=0;i<n;i++)
        what[i+1]=s[i]==')';
    int root=decompose(1);
    solve(root,-1);
    return cnt1;
}
int main()
{

    for(int n=1;n<11;n++){
            r2();
    for(int i=1;i<n;i++)
    {
        graf[i].pb(i+1);
        graf[i+1].pb(i);
        g[i].pb(i+1);
        g[i+1].pb(i);
    }
    for(int i=0;i<(1<<n);i++)
    {
        //printf("%i\n",i);
        //printf("AA\n");
        reset();
        string s="";
        for(int j=0;j<n;j++)
        {
            if(i&(1<<j))
                s+='(';
            else
                s+=')';
        }
        if(his(n,s)!=mein(n,s))
        {
            reset();
            printf("%lld %lld\n",his(n,s),mein(n,s));
            cout << s;
            //return 0;
        }
    }
    }
}
