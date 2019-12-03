/*
    -Do centroid decomposition, for every subtree, for every node find the maximum time some edge is added and the xor of all the edges on the path from the centroid to that node.
    -We can calculate the answer by sorting by the maximum time for every node and using a hash table.
*/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

#define ll long long
#define pb push_back
#define mp make_pair
#define f first
#define s second
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()

using namespace std;
using namespace __gnu_pbds;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
template<class T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag,tree_order_statistics_node_update>; ///find_by_order(),order_of_key()
template<class T1, class T2> ostream& operator<<(ostream& os, const pair<T1,T2>& a) { os << '{' << a.f << ", " << a.s << '}'; return os; }
template<class T> ostream& operator<<(ostream& os, const vector<T>& a){os << '{';for(int i=0;i<sz(a);i++){if(i>0&&i<sz(a))os << ", ";os << a[i];}os<<'}';return os;}
template<class T> ostream& operator<<(ostream& os, const set<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T> ostream& operator<<(ostream& os, const multiset<T>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const map<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}
template<class T1,class T2> ostream& operator<<(ostream& os, const gp_hash_table<T1,T2>& a) {os << '{';int i=0;for(auto p:a){if(i>0&&i<sz(a))os << ", ";os << p;i++;}os << '}';return os;}

const int N=1e5+5;
struct edge{
    int nxt,x,t;
};
vector<vector<edge> > graf(N);
vector<bool> marked(N);
vector<int> siz(N);
void init(int tr,int par){
    siz[tr]=1;
    for(auto p:graf[tr])
        if(!marked[p.nxt]&&p.nxt!=par)
            init(p.nxt,tr),siz[tr]+=siz[p.nxt];
}
int findCentroid(int tr,int par,int s){
    for(auto p:graf[tr])
        if(!marked[p.nxt]&&p.nxt!=par&&siz[p.nxt]>s/2)
            return findCentroid(p.nxt,tr,s);
    return tr;
}
vector<pair<pair<int,int>,int> > svi;
void getln(int tr,int par,int t,int x,int pos){
    svi.pb({{t,x},pos});
    for(auto p:graf[tr])
        if(!marked[p.nxt]&&p.nxt!=par)
            getln(p.nxt,tr,max(t,p.t),x^p.x,pos);
}
vector<ll> sol(N);
gp_hash_table<int,int> cnt;
vector<gp_hash_table<int,int> > cntminus(N);
void decomp(int tr){
    init(tr,tr);
    tr=findCentroid(tr,tr,siz[tr]);
    svi.clear();
    cnt.clear();
    int n=0;
    for(auto p:graf[tr])
        if(!marked[p.nxt])
            getln(p.nxt,tr,p.t,p.x,n++);
    sort(all(svi));
    for(int i=0;i<n;i++)
        cntminus[i].clear();
    for(auto p:svi)
        sol[p.f.f]+=cnt[p.f.s]-cntminus[p.s][p.f.s],cnt[p.f.s]++,cntminus[p.s][p.f.s]++;
    for(auto p:svi)
        if(p.f.s==0)
            sol[p.f.f]++;
    marked[tr]=1;
    for(auto p:graf[tr])
        if(!marked[p.nxt])
            decomp(p.nxt);
}
int main()
{
    int n,a,tr=0;
    scanf("%i",&n);
    vector<edge> in(n-1);
    vector<int> order(n-1);
    for(int i=0;i<n-1;i++)
        scanf("%i %i %i",&in[i].nxt,&in[i].x,&in[i].t),in[i].nxt--,in[i].x--;
    for(int i=0;i<n-1;i++)
        scanf("%i",&a),a--,order[a]=n-2-i;
    for(auto p:in)
        graf[p.nxt].pb({p.x,p.t,order[tr]}),graf[p.x].pb({p.nxt,p.t,order[tr++]});
    decomp(0);
    for(int i=1;i<n-1;i++)
        sol[i]+=sol[i-1];
    for(int i=n-2;i>=0;i--)
        printf("%lld\n",sol[i]);
    printf("0\n");
    return 0;
}
