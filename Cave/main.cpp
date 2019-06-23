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

const int N=5e4+1;
vector<int> siz(N);
vector<bool> visited(N);
vector<vector<int> > graf(N),centroid(N);
void build(int tr,int par)
{
    siz[tr]=1;
    int mx=0;
    for(auto p:graf[tr])
    {
        if(p==par||visited[p])
            continue;
        build(p,tr);
        mx=max(mx,siz[p]);
    }
    siz[tr]+=mx;
}
int nadji(int tr,int pre,int par)
{
    int n=siz[tr]+pre;
    int mx=n/2,gde=-1,cnt=0;
    for(auto p:graf[tr])
    {
        if(p==par||visited[p])
            continue;
        int s=siz[p];
        if(s>mx)
            mx=s,gde=p;
    }
    mx=0;
    for(auto p:graf[tr])
    {
        if(p==par||visited[p])
            continue;
        int s=siz[p];
        if(s>mx&&gde!=p)
            mx=s;
    }
    if(gde==-1)
        return tr;
    return nadji(gde,pre+mx+1,tr);
}
int decompose(int tr)
{
    //printf("%i!: ",tr);
    build(tr,-1);
    int cen=nadji(tr,0,-1);
    //printf("%i!\n",cen);
    visited[cen]=1;
    for(auto p:graf[cen])
    {
        if(visited[p])
            continue;
        int sl=decompose(p);
        centroid[cen].pb(sl);
    }
    return cen;
}
int main()
{
	int n;
	scanf("%i",&n);
	for(int i=0;i<n-1;i++)
    {
        int a,b;
        scanf("%i %i",&a,&b);
        a--;b--;
        graf[a].pb(b);
        graf[b].pb(a);
    }
    int start=decompose(0);
    fill(all(siz),0);
    queue<int> q;
    q.push(start);
    siz[start]=1;
    while(q.size())
    {
        int tr=q.front();
        q.pop();
        for(auto p:centroid[tr])
        {
            siz[p]=siz[tr]+1;
            q.push(p);
        }
    }
    int mx=0;
    for(auto p:siz)
        mx=max(mx,p);
    printf("%i\n",mx-1);
    return 0;
}
