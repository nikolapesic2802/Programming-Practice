/*
    -We can find the connecting room with a binary search and some math.
    -Build a graph and run dijkstra to get the answer.
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

int main()
{
	ll n;
	scanf("%lld",&n);
	int lim=2*sqrt(n);
	int k=1000;
	scanf("%i",&k);
	vector<pair<ll,ll> > edges;
	vector<ll> vrednosti;
	vrednosti.pb(n);
	vrednosti.pb(1);
	for(int i=0;i<k;i++)
    {
        ll b;
        scanf("%lld",&b);
        int l=1,r=lim;
        while(l<r)
        {
            int m=(l+r)>>1;
            if((ll)m*m<b)
                l=m+1;
            else
                r=m;
        }
        ll val=(ll)(l-2)*(l-2)+1;
        ll diff=(ll)l*l-b;
        assert(diff>=0);
        if(diff>=l)
            diff-=2;
        ll a=val-diff;
        edges.pb({a,b});
        vrednosti.pb(a);
        vrednosti.pb(b);
    }
    sort(all(vrednosti));
    vrednosti.erase(unique(all(vrednosti)),vrednosti.end());
    gp_hash_table<ll,int> mapa;
    int m=vrednosti.size();
    for(int i=0;i<m;i++)
        mapa[vrednosti[i]]=i;
    vector<vector<pair<int,ll> > > graf(m);
    for(int i=1;i<m;i++)
        graf[i].pb({i-1,vrednosti[i]-vrednosti[i-1]}),graf[i-1].pb({i,vrednosti[i]-vrednosti[i-1]});
    for(auto p:edges)
        graf[mapa[p.f]].pb({mapa[p.s],1}),graf[mapa[p.s]].pb({mapa[p.f],1});
    vector<ll> daljina(m,LLONG_MAX);
    daljina[0]=0;
    set<pair<ll,int> > q;
    q.insert({0,0});
    while(q.size())
    {
        pair<ll,int> tr=*q.begin();
        q.erase(q.begin());
        if(tr.f>daljina[tr.s])
            continue;
        for(auto p:graf[tr.s])
        {
            ll d=tr.f+p.s;
            if(d<daljina[p.f])
            {
                daljina[p.f]=d;
                q.insert({d,p.f});
            }
        }
    }
    printf("%lld\n",daljina[mapa[n]]);
    return 0;
}
